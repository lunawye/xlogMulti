// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

/**
 * created on : 2012-11-28
 * author : yerungui
 */
#include "comm/platform_comm.h"

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#include "comm/xlogger/qm_xlogger.h"
#include "comm/xlogger/loginfo_extract.h"
#import "comm/objc/qm_scope_autoreleasepool.h"

#import <TargetConditionals.h>
#if !TARGET_OS_WATCH
#import <SystemConfiguration/CaptiveNetwork.h>
#import <CFNetwork/CFProxySupport.h>
#endif

#if TARGET_OS_IPHONE && !TARGET_OS_WATCH
#import <UIKit/UIApplication.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import <CoreTelephony/CTCarrier.h>
#import <NetworkExtension/NetworkExtension.h>
#endif

#if !TARGET_OS_IPHONE
#import <CoreWLAN/CWInterface.h>
#import <CoreWLAN/CWWiFiClient.h> 
#endif

#include <MacTypes.h>
#include <functional>

#include "comm/objc/objc_timer.h"
#import "comm/objc/Reachability.h"

#include "comm/thread/mutex.h"
#include "comm/thread/lock.h"
#include "comm/network/getifaddrs.h"


#if !TARGET_OS_IPHONE
static float __GetSystemVersion() {
    //	float system_version = [UIDevice currentDevice].systemVersion.floatValue;
    //	return system_version;
    NSString *versionString;
    NSDictionary * sv = [NSDictionary dictionaryWithContentsOfFile:@"/System/Library/CoreServices/SystemVersion.plist"];
    if (nil != sv){
        versionString = [sv objectForKey:@"ProductVersion"];
        return versionString != nil ? versionString.floatValue : 0;
    }
    
    return 0;
}
#endif

static MarsNetworkStatus __GetNetworkStatus()
{
#if TARGET_OS_WATCH
    return ReachableViaWiFi;
#else
    return [MarsReachability getCacheReachabilityStatus:NO];
#endif
}

static marsMulti::comm::WifiInfo sg_wifiinfo;
static marsMulti::comm::Mutex sg_wifiinfo_mutex;

namespace marsMulti{
namespace comm{

static std::function<bool(std::string&)> g_new_wifi_id_cb;
static marsMulti::comm::Mutex wifi_id_mutex;

void SetWiFiIdCallBack(std::function<bool(std::string&)> _cb) {
    marsMulti::comm::ScopedLock lock(wifi_id_mutex);
    g_new_wifi_id_cb = _cb;
}
void ResetWiFiIdCallBack() {
    marsMulti::comm::ScopedLock lock(wifi_id_mutex);
    g_new_wifi_id_cb = NULL;
}


void FlushReachability() {
#if !TARGET_OS_WATCH
    [MarsReachability getCacheReachabilityStatus:YES];
    marsMulti::comm::ScopedLock lock(sg_wifiinfo_mutex);
    sg_wifiinfo.ssid.clear();
    sg_wifiinfo.bssid.clear();
#endif
}

float publiccomponent_GetSystemVersion() {
    NSString *versionString;
    NSDictionary * sv = [NSDictionary dictionaryWithContentsOfFile:@"/System/Library/CoreServices/SystemVersion.plist"];
    if (nil != sv){
        versionString = [sv objectForKey:@"ProductVersion"];
        return versionString != nil ? versionString.floatValue : 0;
    }
    
    return 0;
}

bool getProxyInfo(int& port, std::string& strProxy, const std::string& _host)
{
    xverbose_function();
    
#if TARGET_OS_WATCH
    return false;
    
#else
    SCOPE_POOL();
    NSDictionary *proxySettings = [NSMakeCollectable((NSDictionary *)CFNetworkCopySystemProxySettings()) autorelease];
    if (nil==proxySettings) return false;
    
    CFURLRef url = (CFURLRef)[NSURL URLWithString: [NSString stringWithUTF8String:(_host.c_str())]];
    
//    CFURLRef url = (CFURLRef)[NSURL URLWithString: @"http://www.google.com"];
    
    
    NSArray *proxies = [NSMakeCollectable((NSArray *)CFNetworkCopyProxiesForURL(url, (CFDictionaryRef)proxySettings)) autorelease];
    
    if (nil==proxies || 0==[proxies count]) return false;

    NSDictionary *settings = [proxies objectAtIndex:0];
    CFStringRef http_proxy = (CFStringRef)[settings objectForKey:(NSString *)kCFProxyHostNameKey];
    CFNumberRef http_port = (CFNumberRef)[settings objectForKey:(NSString *)kCFProxyPortNumberKey];
    CFStringRef http_type = (CFStringRef)[settings objectForKey:(NSString *)kCFProxyTypeKey];
    
   if (0==CFStringCompare(http_type, kCFProxyTypeAutoConfigurationURL, 0))
   {
       CFErrorRef  error = nil;
       CFStringRef proxyAutoConfigurationScript = (CFStringRef)[settings objectForKey:(NSString *)kCFProxyAutoConfigurationURLKey];
       if (nil==proxyAutoConfigurationScript) return false;
       
       proxies = [NSMakeCollectable((NSArray *)CFNetworkCopyProxiesForAutoConfigurationScript(proxyAutoConfigurationScript, url, &error)) autorelease];
       
       if (nil!=error) return false;

       
       if (nil==proxies || 0==[proxies count]) return false;
       settings = [proxies objectAtIndex:0];
       
       http_proxy = (CFStringRef)[settings objectForKey:(NSString *)kCFProxyHostNameKey];
       http_port = (CFNumberRef)[settings objectForKey:(NSString *)kCFProxyPortNumberKey];
   }
    
    if (nil==http_proxy || nil==http_port) return false;
    
    char tmp_proxy[128] = {0};
    int tmp_port = 0;
    

    if (!CFStringGetCString(http_proxy, tmp_proxy, sizeof(tmp_proxy), kCFStringEncodingASCII)
        || !CFNumberGetValue(http_port, kCFNumberSInt32Type, &tmp_port))
    {
        xerror2(TSF"convert error");
        return false;
    }

    strProxy = tmp_proxy;
    port = tmp_port;
    xdebug2(TSF"%0:%1", strProxy, port);
    return true;
#endif
}

int getNetInfo() {
    xverbose_function();
    SCOPE_POOL();
    
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_WATCH
    return marsMulti::comm::kWifi;
#endif

    switch (__GetNetworkStatus())
    {
        case NotReachable:
            return marsMulti::comm::kNoNet;
        case ReachableViaWiFi:
            return marsMulti::comm::kWifi;
        case ReachableViaWWAN:
            return marsMulti::comm::kMobile;
        default:
            return marsMulti::comm::kNoNet;
    }
}

int getNetTypeForStatistics(){
    int type = getNetInfo();
    if (marsMulti::comm::kWifi == type){
        return (int)marsMulti::comm::NetTypeForStatistics::NETTYPE_WIFI;
    }
    if (marsMulti::comm::kNoNet == type){
        return (int)marsMulti::comm::NetTypeForStatistics::NETTYPE_NON;
    }
    
    marsMulti::comm::RadioAccessNetworkInfo rani;
    if (!getCurRadioAccessNetworkInfo(rani)){
        return (int)marsMulti::comm::NetTypeForStatistics::NETTYPE_NON;
    }
    
    if (rani.Is2G()){
        return (int)marsMulti::comm::NetTypeForStatistics::NETTYPE_2G;
    }else if(rani.Is3G()){
        return (int)marsMulti::comm::NetTypeForStatistics::NETTYPE_3G;
    }else if(rani.Is4G()){
        return (int)marsMulti::comm::NetTypeForStatistics::NETTYPE_4G;
    }
    
    return (int)marsMulti::comm::NetTypeForStatistics::NETTYPE_NON;
}

unsigned int getSignal(bool isWifi){
    xverbose_function();
    SCOPE_POOL();
    return (unsigned int)0;
}

bool isNetworkConnected()
{
   SCOPE_POOL(); 
    switch (__GetNetworkStatus())
    {
        case NotReachable:
            return false;
        case ReachableViaWiFi:
            return true;
        case ReachableViaWWAN:
            return true;
        default:
            return false;
    }
}

#define SIMULATOR_NET_INFO "SIMULATOR"
#define IWATCH_NET_INFO "IWATCH"
#define USE_WIRED  "wired"

static bool __WiFiInfoIsValid(const marsMulti::comm::WifiInfo& _wifi_info) {
    // CNCopyCurrentNetworkInfo is now only available to your app in three cases:
    // * Apps with permission to access location
    // * Your app is the currently enabled VPN app
    // * Your app configured the WiFi network the device is currently using via NEHotspotConfiguration
    // otherwise return nil.
    // But if you use 'NEHotspotConfiguration' and without permission to access location
    // Instead, the information returned by default will be:
    // * SSID: “Wi-Fi” or “WLAN” (“WLAN" will be returned for the China SKU)
    // * BSSID: "00:00:00:00:00:00" 
    static const std::string kConstBSSID = "00:00:00:00:00:00";
    return !_wifi_info.bssid.empty() && kConstBSSID != _wifi_info.bssid;
}

bool getCurWifiInfo(marsMulti::comm::WifiInfo& wifiInfo, bool _force_refresh)
{
    SCOPE_POOL();
    
#if TARGET_IPHONE_SIMULATOR
    wifiInfo.ssid = SIMULATOR_NET_INFO;
    wifiInfo.bssid = SIMULATOR_NET_INFO;
    return true;
#elif !TARGET_OS_IPHONE
    
    static marsMulti::comm::Mutex mutex;
    marsMulti::comm::ScopedLock lock(mutex);
    
    static float version = 0.0;
    
    CWInterface* info = nil;
    
    if (version < 0.1) {
        version = __GetSystemVersion();
    }
    
    if (version < 10.10){
        static CWInterface* s_info = [[CWInterface interface] retain];
        info = s_info;
    }else{
        CWWiFiClient* wificlient = [CWWiFiClient sharedWiFiClient];
        if (nil != wificlient) info = [wificlient interface];
    }

    if (nil == info) return false;
    if (info.ssid != nil) {
        const char* ssid = [info.ssid UTF8String];
        if(NULL != ssid) wifiInfo.ssid.assign(ssid, strnlen(ssid, 32));
        //wifiInfo.bssid = [info.bssid UTF8String];
    } else {
        wifiInfo.ssid = USE_WIRED;
        wifiInfo.bssid = USE_WIRED;
    }
    return true;
    
#elif TARGET_OS_WATCH
    wifiInfo.ssid = IWATCH_NET_INFO;
    wifiInfo.bssid = IWATCH_NET_INFO;
    return true;
#else
    wifiInfo.ssid = "WiFi";
    wifiInfo.bssid = "WiFi";
    
    marsMulti::comm::ScopedLock wifi_id_lock(wifi_id_mutex);
    if (!g_new_wifi_id_cb) {
        xwarn2("g_new_wifi_id_cb is null");
    }
    xdebug2(TSF"_force_refresh %_", _force_refresh);
    // 来自mars的调用全部使用新的netid, 并且 _force_refresh = false
    // 来自业务调用的全部 _force_refresh = true
    if (g_new_wifi_id_cb && !_force_refresh) {
        std::string newid = "no_ssid_wifi";
        if (g_new_wifi_id_cb(newid)) {
            wifiInfo.ssid = newid;
            wifiInfo.bssid = newid;
            return true;
        }
        return false;
    }
    wifi_id_lock.unlock();
    
    if ([CLLocationManager authorizationStatus] == kCLAuthorizationStatusDenied) {
        return false;
    }
    
    marsMulti::comm::ScopedLock lock(sg_wifiinfo_mutex);
    if (__WiFiInfoIsValid(sg_wifiinfo) && !_force_refresh) {
        wifiInfo = sg_wifiinfo;
        return true;
    }

    wifi_id_lock.lock();
    // g_new_wifi_id_cb表示来自微信的调用, 而非外部开源调用，只有微信会设置g_new_wifi_id_cb
    // 为了减少定位图片的出现次数:
    // 微信逻辑改为_force_refresh = true并且sg_wifiinfo没有设置的情况下才强制获取一次
    if (_force_refresh && g_new_wifi_id_cb) {
        if (__WiFiInfoIsValid(sg_wifiinfo)) {
            wifiInfo = sg_wifiinfo;
            return true;
        }
    }
    wifi_id_lock.unlock();
    lock.unlock();
    NSArray *ifs = nil;
    @synchronized (@"CNCopySupportedInterfaces") {
        ifs = (id)CNCopySupportedInterfaces();
    }
    if(ifs == nil) {
        return false;
    }
        
    id info = nil;
    for (NSString *ifnam in ifs) {
        info = (id)CNCopyCurrentNetworkInfo((CFStringRef)ifnam);
        if (info && [info count] && info[@"SSID"]) {
            break;
        }
            
        if (nil!=info) {
            CFRelease(info);
            info = nil;
        }
    }
        
    if (info == nil) {
        CFRelease(ifs);
        return false;
    }
        
    const char* ssid_cstr = [[info objectForKey:@"SSID"] UTF8String];
    const char* bssid_cstr = [[info objectForKey:@"BSSID"] UTF8String];
    if (NULL != ssid_cstr) {
        wifiInfo.ssid = ssid_cstr;
    }
        
    if (NULL != bssid_cstr) {
        wifiInfo.bssid = bssid_cstr;
    }
    CFRelease(info);
    CFRelease(ifs);

    // CNCopyCurrentNetworkInfo is now only available to your app in three cases:
    // * Apps with permission to access location
    // * Your app is the currently enabled VPN app
    // * Your app configured the WiFi network the device is currently using via NEHotspotConfiguration
    // otherwise return nil.
    // But if you use 'NEHotspotConfiguration' and without permission to access location
    // Instead, the information returned by default will be:
    // * SSID: “Wi-Fi” or “WLAN” (“WLAN" will be returned for the China SKU)
    // * BSSID: "00:00:00:00:00:00" 
    lock.lock();
    sg_wifiinfo = wifiInfo;
    xinfo2(TSF"get wifi info:%_", sg_wifiinfo.ssid);

    return __WiFiInfoIsValid(wifiInfo);
#endif
}

#if TARGET_OS_IPHONE && !TARGET_OS_WATCH
bool getCurSIMInfo(marsMulti::comm::SIMInfo& simInfo)
{
    static marsMulti::comm::Mutex mutex;
    marsMulti::comm::ScopedLock lock(mutex);
    
    SCOPE_POOL();
    static CTTelephonyNetworkInfo* s_networkinfo = [[CTTelephonyNetworkInfo alloc] init];
    CTCarrier* carrier = s_networkinfo.subscriberCellularProvider;
    
    if (nil == carrier)
    {
        return false;
    }
    
    if (nil == carrier.mobileCountryCode || nil == carrier.mobileNetworkCode)
    {
        return false;
    }

    simInfo.isp_code += [carrier.mobileCountryCode UTF8String];
    simInfo.isp_code += [carrier.mobileNetworkCode UTF8String];
    xverbose2(TSF"isp_code:%0", simInfo.isp_code);

    return true;
}

#else

bool getCurSIMInfo(SIMInfo& simInfo)
{
    return false;
}
#endif

bool getAPNInfo(marsMulti::comm::APNInfo& info)
{
    marsMulti::comm::RadioAccessNetworkInfo raninfo;
    if (marsMulti::comm::kMobile != getNetInfo()) return false;
    if (!marsMulti::comm::getCurRadioAccessNetworkInfo(raninfo)) return false;
    
    info.nettype = marsMulti::comm::kMobile;
    info.extra_info = raninfo.radio_access_network;
    return true;
}

bool getifaddrs_ipv4_hotspot(std::string& _ifname, std::string& _ifip)
{
    std::vector<ifaddrinfo_ipv4_t> addrs;
    if (!getifaddrs_ipv4_lan(addrs)) return false;
    
    for (auto it=addrs.begin(); it!=addrs.end(); ++it)
    {
        if (std::string::npos != it->ifa_name.find("bridge"))
        {
            _ifname = it->ifa_name;
            _ifip = it->ip;
            return true;
        }
    }
    
    return false;
}

/**
CTTelephonyNetworkInfo *telephonyInfo = [CTTelephonyNetworkInfo new];
NSLog(@"Current Radio Access Technology: %@", telephonyInfo.currentRadioAccessTechnology);
[NSNotificationCenter.defaultCenter addObserverForName:CTRadioAccessTechnologyDidChangeNotification 
                                                object:nil 
                                                 queue:nil 
                                            usingBlock:^(NSNotification *note) 
{
    NSLog(@"New Radio Access Technology: %@", telephonyInfo.currentRadioAccessTechnology);
}];
**/

#if TARGET_OS_IPHONE && !TARGET_OS_WATCH
bool getCurRadioAccessNetworkInfo(marsMulti::comm::RadioAccessNetworkInfo& _raninfo)
{
    SCOPE_POOL();
    if (publiccomponent_GetSystemVersion() < 7.0){
        return false;
    }
    
    static CTTelephonyNetworkInfo* s_networkinfo = [[CTTelephonyNetworkInfo alloc] init];
    
    NSString *currentRadioAccessTechnology = s_networkinfo.currentRadioAccessTechnology;
    if (!currentRadioAccessTechnology) { return false;}
    
    _raninfo.radio_access_network =  [currentRadioAccessTechnology UTF8String];
    _raninfo.radio_access_network.erase(0, strlen("CTRadioAccessTechnology"));
    
    xassert2(!_raninfo.radio_access_network.empty(), "%s", [currentRadioAccessTechnology UTF8String]);
    
    return true;
}
#else
bool getCurRadioAccessNetworkInfo(RadioAccessNetworkInfo& _raninfo)
{
   return false;
}
#endif


}   // namespace comm
}   // namespace marsMulti

void comm_export_symbols_1(){}
