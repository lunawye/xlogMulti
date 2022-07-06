## Mars

[![license](https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat)](https://github.com/Tencent/marsMulti/blob/master/LICENSE)
[![Release Version](https://img.shields.io/badge/release-1.2.3-red.svg)](https://github.com/Tencent/marsMulti/releases)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://github.com/Tencent/marsMulti/pulls)
[![WeChat Approved](https://img.shields.io/badge/Wechat_Approved-1.2.3-red.svg)](https://github.com/Tencent/marsMulti/wiki)
[![WeChat Approved](https://img.shields.io/badge/Platform(cmake)-%20iOS%20%7C%20OS%20X%20%7C%20Android(ndkr20)%20%7C%20Windows(vs2015)%20-brightgreen.svg)](https://github.com/Tencent/marsMulti/wiki)

(中文版本请参看[这里](#mars_cn))

Mars is a cross-platform infrastructure component developed by WeChat Mobile Team.
It is proved to be effective by billions of WeChat users.

1. Cross platform, easy to deploy if you are developing multi-platform or multi-business application.
2. Suitable for small amount data transmission
3. Mobile platform friendly, low power and traffic consumption
4. A network solution fit for mobile application

![marsMulti](https://github.com/WeMobileDev/article/blob/master/assets/marsMulti/marsMulti.png?raw=true)

* comm: common library, including socket, thread, message queue, coroutine, etc.
* Xlog: a reliable log component with high-performance.
* SDT: a network detection component.
* STN: a signaling network component, the major part of Mars.

## Samples

Start with sample usage [here](https://github.com/Tencent/marsMulti/wiki/Mars-sample-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E).

## Getting started

Choose [Android](#android) or [iOS/OS X](#apple) or [Windows](#windows).

### <a name="android">[Android](https://github.com/Tencent/marsMulti/wiki/Mars-Android-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)</a>

You can use either [marsMulti-wrapper](#wrapper) or [marsMulti-core](#core). We recommend you to use marsMulti-wrapper when you just wanna build a sample or demo, while marsMulti-core is preferred to be used in your APP.

#### <a name="wrapper">marsMulti-wrapper</a>

Add dependencies by adding the following lines to your app/build.gradle.

```xml
dependencies {
    compile 'com.tencent.marsMulti:marsMulti-wrapper:1.2.5'
}
```

**OR**

#### <a name="core">marsMulti-core</a>

Add dependencies by adding the following lines to your app/build.gradle.

```xml
dependencies {
    compile 'com.tencent.marsMulti:marsMulti-core:1.2.5'
}
```
**OR**
#### <a name="">marsMulti-xlog</a>
If you just want to user xlog, add dependencies by adding the following lines to your app/build.gradle.
note: xlog is included in marsMulti-core and marsMulti-wrapper.

```xml
dependencies {
    compile 'com.tencent.marsMulti:marsMulti-xlog:1.2.5'
}
```

If you read here, make sure you have added dependencies of marsMulti-wrapper, marsMulti-core or marsMulti-xlog.

#### <a name="Xlog">Xlog Init</a>

Initialize Xlog when your APP starts. Remember to use an exclusive folder to save the log files, no other files are acceptable in the folder since they would be removed by the cleansing function in Xlog automatically.

When multiple processes is used in your app, make sure that each process owns its exclusive log file.

```java
System.loadLibrary("c++_shared");
System.loadLibrary("marsxlog");

final String SDCARD = Environment.getExternalStorageDirectory().getAbsolutePath();
final String logPath = SDCARD + "/marssample/log";

// this is necessary, or may crash for SIGBUS
final String cachePath = this.getFilesDir() + "/xlog"

//init xlog
Xlog xlog = new Xlog();
Log.setLogImp(xlog);

if (BuildConfig.DEBUG) {
    Log.setConsoleLogOpen(true);
  	Log.appenderOpen(Xlog.LEVEL_DEBUG, Xlog.AppednerModeAsync, "", logPath, logFileName, 0);
} else {
    Log.setConsoleLogOpen(false);
  	Log.appenderOpen(Xlog.LEVEL_INFO, Xlog.AppednerModeAsync, "", logPath, logFileName, 0);
}

```

Uninitialized Xlog when your app exits


```java
Log.appenderClose();
```

#### <a name="STN">STN Init</a>

If you add dependencies of marsMulti-core to your project, you need to initialize and release STN.
Initialize STN before you use it

```java
// set callback
AppLogic.setCallBack(stub);
StnLogic.setCallBack(stub);
SdtLogic.setCallBack(stub);

// Initialize the Mars PlatformComm
Mars.init(getApplicationContext(), new Handler(Looper.getMainLooper()));

// Initialize the Mars
StnLogic.setLonglinkSvrAddr(profile.longLinkHost(), profile.longLinkPorts());
StnLogic.setShortlinkSvrAddr(profile.shortLinkPort());
StnLogic.setClientVersion(profile.productID());
Mars.onCreate(true);

BaseEvent.onForeground(true);
StnLogic.makesureLongLinkConnected();
```
Firstly, you should call the setCallBack interface, and secondly, the Mars.init. Then, to initialize the Mars, there is to need to strictly follow the orders of the four commands. Finally, after Mars are initialized, onForeground and makesureLongLinkConnect can be called.

Destroy STN or exit your app:

```java
Mars.onDestroy();
```

#### <a name="even">Event Change</a>

Network change:

```java
BaseEvent.onNetworkChange()
```
**********
If you add dependencies of marsMulti-wrapper to your project, you just need initialize STN and no need uninitialized.

```java
MarsServiceProxy.init(this, getMainLooper(),null);
```
************
No matter which way of dependencies you used, you must pay attention to these.

The state (background or foreground) of the APP is changed:

```java
BaseEvent.onForeground(boolean);
```

The account of the APP is changed:

```java
StnLogic.reset();
```

If you want to modify the encryption algorithm of Xlog, the packer/unpacker of longlink/shortlink, or you want to define the other components by yourself, refer [here](https://github.com/Tencent/marsMulti/wiki/Mars-Android-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)

### <a name="apple">[iOS/OS X](https://github.com/Tencent/marsMulti/wiki/Mars-iOS%EF%BC%8FOS-X-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)</a>
Compile

```python
python build_ios.py
```

or 
```python
python build_osx.py
```

1. Add marsMulti.framework as a dependency of your project.
2. Rename files in marsMulti/libraries/mars_android_sdk/jni with .rewriteme extension to .cc extension.
3. Add header files in marsMulti/libraries/mars_android_sdk/jni and source files from step 2 into your project.

#### <a name="Xlog">Xlog Init</a>

Initialize Xlog when your app starts. Remember to use an exclusive folder to save the log files, no other files are acceptable in the folder since they would be removed by the cleansing function in Xlog automatically.

```cpp
NSString* logPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingString:@"/log"];

// set do not backup for logpath
const char* attrName = "com.apple.MobileBackup";
u_int8_t attrValue = 1;
setxattr([logPath UTF8String], attrName, &attrValue, sizeof(attrValue), 0, 0);

// init qm_xlogger
#if DEBUG
xlogger_SetLevel(kLevelDebug);
qm_appender_set_console_log(true);
#else
xlogger_SetLevel(kLevelInfo);
qm_appender_set_console_log(false);
#endif
XLogConfig config;
config.mode_ = kAppenderAsync;
config.logdir_ = [logPath UTF8String];
config.nameprefix_ = "Test";
config.pub_key_ = "";
config.compress_mode_ = kZlib;
config.compress_level_ = 0;
config.cachedir_ = "";
config.cache_days_ = 0;
qm_appender_open(config);
```

Close xlog in function "applicationWillTerminate"


```cpp
qm_appender_close();
```

#### <a name="STN">STN Init</a>

Initialize STN before you use it:

```objc
- (void)setCallBack {
    marsMulti::stn::SetCallback(marsMulti::stn::StnCallBack::Instance());
    marsMulti::app::SetCallback(marsMulti::app::AppCallBack::Instance());
}

- (void) createMars {
    marsMulti::baseevent::OnCreate();
}

- (void)setClientVersion:(UInt32)clientVersion {
    marsMulti::stn::SetClientVersion(clientVersion);
}

- (void)setShortLinkDebugIP:(NSString *)IP port:(const unsigned short)port {
    std::string ipAddress([IP UTF8String]);
    marsMulti::stn::SetShortlinkSvrAddr(port, ipAddress);
}

- (void)setShortLinkPort:(const unsigned short)port {
    marsMulti::stn::SetShortlinkSvrAddr(port);
}

- (void)setLongLinkAddress:(NSString *)string port:(const unsigned short)port debugIP:(NSString *)IP {
    std::string ipAddress([string UTF8String]);
    std::string debugIP([IP UTF8String]);
    std::vector<uint16_t> ports;
    ports.push_back(port);
    marsMulti::stn::SetLonglinkSvrAddr(ipAddress,ports,debugIP);
}

- (void)setLongLinkAddress:(NSString *)string port:(const unsigned short)port {
    std::string ipAddress([string UTF8String]);
    std::vector<uint16_t> ports;
    ports.push_back(port);
    marsMulti::stn::SetLonglinkSvrAddr(ipAddress,ports);
}

- (void)reportEvent_OnForeground:(BOOL)isForeground {
    marsMulti::baseevent::OnForeground(isForeground);
}

- (void)makesureLongLinkConnect {
    marsMulti::stn::MakesureLonglinkConnected();
}
```

Firstly, you should call the setCallBack interface, and secondly, the Mars.init. Then, to initialize the Mars, there is to need to strictly follow the orders of the four commands. Finally, after Mars are initialized, onForeground and makesureLongLinkConnect can be called.

If you want to destroy STN or exit App:

```objc
- (void)destroyMars {
    marsMulti::baseevent::OnDestroy();
}
```

#### <a name="even">Event Change</a>

When the App's state of background or foreground is changed:

```objc
- (void)reportEvent_OnForeground:(BOOL)isForeground {
    marsMulti::baseevent::OnForeground(isForeground);
}
```

Network change:

```objc
- (void)reportEvent_OnNetworkChange {
    marsMulti::baseevent::OnNetworkChange();
}
```

### <a name="windows">[Windows](https://github.com/Tencent/marsMulti/wiki/Mars-Windows-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)</a>
Install Visual Studio 2015.

Compile
```python
python build_windows.py
```

1. Add marsMulti.lib as a dependency of your project.
2. Rename files in marsMulti/libraries/mars_android_sdk/jni with .rewriteme extension to .cc extension.
3. Add header files in marsMulti/libraries/mars_android_sdk/jni and source files from step 2 into your project.

#### <a name="Xlog">Xlog Init</a>

Initialize Xlog when your app starts. Remember to use an exclusive folder to save the log files, no other files are acceptable in the folder since they would be removed by the cleansing function in Xlog automatically.

```cpp
std::string logPath = ""; //use your log path
std::string pubKey = ""; //use you pubkey for log encrypt

// init xlog
#if DEBUG
xlogger_SetLevel(kLevelDebug);
qm_appender_set_console_log(true);
#else
xlogger_SetLevel(kLevelInfo);
qm_appender_set_console_log(false);
#endif
qm_appender_open(kAppenderAsync, logPath.c_str(), "Test", 0, pubKey.c_str());
```

Uninitialized xlog before your app exits


```cpp
qm_appender_close();
```

#### <a name="STN">STN Init</a>

Initialize STN before you use it:

```cpp
void setShortLinkDebugIP(const std::string& _ip, unsigned short _port)
{
	marsMulti::stn::SetShortlinkSvrAddr(_port, _ip);
}
void setShortLinkPort(unsigned short _port)
{
	marsMulti::stn::SetShortlinkSvrAddr(_port, "");
}
void setLongLinkAddress(const std::string& _ip, unsigned short _port, const std::string& _debug_ip)
{
	vector<uint16_t> ports;
	ports.push_back(_port);
	marsMulti::stn::SetLonglinkSvrAddr(_ip, ports, _debug_ip);
}

void Init()
{
	marsMulti::stn::SetCallback(marsMulti::stn::StnCallBack::Instance());
	marsMulti::app::SetCallback(marsMulti::app::AppCallBack::Instance());
	marsMulti::baseevent::OnCreate();

	//todo
	//marsMulti::stn::SetClientVersion(version);
	//setShortLinkDebugIP(...)
	//setLongLinkAddress(...)

	marsMulti::baseevent::OnForeground(true);
	marsMulti::stn::MakesureLonglinkConnected();
}
```

Firstly, you should call the setCalBack interface, and secondly, the Mars.init. Then, to initialize the Mars, there is to need to strictly follow the orders of the four commands. Finally, after Mars are initialized, onForeground and makesureLongLinkConnect can be called.

If you want to destroy STN or exit App:

```cpp
marsMulti::baseevent::OnDestroy();
```

## Support

Any problem?

1. Learn more from [marsMulti/sample](https://github.com/Tencent/marsMulti/tree/master/samples).
2. Read the [source code](https://github.com/Tencent/marsMulti/tree/master).
3. Read the [wiki](https://github.com/Tencent/marsMulti/wiki) or [FAQ](https://github.com/Tencent/marsMulti/wiki/Mars-%E5%B8%B8%E8%A7%81%E9%97%AE%E9%A2%98) for help.
4. Contact us for help.

## Contributing

For more information about contributing issues or pull requests, see our [Mars Contributing Guide](https://github.com/Tencent/marsMulti/blob/master/CONTRIBUTING.md).

## License

Mars is under the MIT license. See the [LICENSE](https://github.com/Tencent/marsMulti/blob/master/LICENSE) file for details.

------------------------------
## <a name="mars_cn">Mars</a>

[![license](https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat)](https://github.com/Tencent/marsMulti/blob/master/LICENSE)
[![Release Version](https://img.shields.io/badge/release-1.2.3-red.svg)](https://github.com/Tencent/marsMulti/releases)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://github.com/Tencent/marsMulti/pulls)
[![WeChat Approved](https://img.shields.io/badge/Wechat_Approved-1.2.3-red.svg)](https://github.com/Tencent/marsMulti/wiki)
[![WeChat Approved](https://img.shields.io/badge/Platform-%20iOS%20%7C%20OS%20X%20%7C%20Android%20-brightgreen.svg)](https://github.com/Tencent/marsMulti/wiki)

Mars 是微信官方的跨平台跨业务的终端基础组件。


![marsMulti](https://github.com/WeMobileDev/article/blob/master/assets/marsMulti/marsMulti.png?raw=true)

* comm：可以独立使用的公共库，包括 socket、线程、消息队列、协程等；
* xlog：高可靠性高性能的运行期日志组件；
* SDT： 网络诊断组件；
* STN： 信令分发网络模块，也是 Mars 最主要的部分。

## Samples

sample 的使用请参考[这里](https://github.com/Tencent/marsMulti/wiki/Mars-sample-%E4%BD%BF%E7%94%A8%E8%AF%B4%E6%98%8E)。

## Getting started

接入 [Android](#android_cn) 或者 [iOS/OS X](#apple_cn) 或者 [Windows](#windows_cn) 。

### <a name="android_cn">[Android](https://github.com/Tencent/marsMulti/wiki/Mars-Android-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)</a>

gradle 接入我们提供了两种接入方式：[marsMulti-wrapper](#wrapper) 或者 [marsMulti-core](#core)。如果你只是想做个 sample 推荐使用 marsMulti-wrapper，可以快速开发；但是如果你想把 marsMulti 用到你的 app 中的话，推荐使用 marsMulti-core，可定制性更高。

#### <a name="wrapper">marsMulti-wrapper</a>

在 app/build.gradle 中添加 marsMulti-wrapper 的依赖：


```xml
dependencies {
    compile 'com.tencent.marsMulti:marsMulti-wrapper:1.2.5'
}
```

**或者**

#### <a name="core">marsMulti-core</a>

在 app/build.gradle 中添加 marsMulti-core 的依赖：


```xml
dependencies {
    compile 'com.tencent.marsMulti:marsMulti-core:1.2.5'
}
```
**或者**
#### <a name="">marsMulti-xlog</a>
如果只想使用 xlog,可以只加 xlog 的依赖(marsMulti-core,marsMulti-wrapper 中都已经包括 xlog)：
```xml
dependencies {
    compile 'com.tencent.marsMulti:marsMulti-xlog:1.2.5'
}
```
接着往下操作之前，请先确保你已经添加了 marsMulti-wrapper 或者 marsMulti-core 或者 marsMulti-xlog 的依赖

#### <a name="Xlog">Xlog Init</a>

在程序启动加载 Xlog 后紧接着初始化 Xlog。但要注意如果你的程序使用了多进程，不要把多个进程的日志输出到同一个文件中，保证每个进程独享一个日志文件。而且保存 log 的目录请使用单独的目录，不要存放任何其他文件防止被 xlog 自动清理功能误删。


```java
System.loadLibrary("c++_shared");
System.loadLibrary("marsxlog");

final String SDCARD = Environment.getExternalStorageDirectory().getAbsolutePath();
final String logPath = SDCARD + "/marssample/log";

// this is necessary, or may crash for SIGBUS
final String cachePath = this.getFilesDir() + "/xlog"

//init xlog
Xlog.XLogConfig logConfig = new Xlog.XLogConfig();
logConfig.mode = Xlog.AppednerModeAsync;
logConfig.logdir = logPath;
logConfig.nameprefix = logFileName;
logConfig.pubkey = "";
logConfig.compressmode = Xlog.ZLIB_MODE;
logConfig.compresslevel = 0;
logConfig.cachedir = "";
logConfig.cachedays = 0;
if (BuildConfig.DEBUG) {
    logConfig.level = Xlog.LEVEL_VERBOSE;
    Xlog.setConsoleLogOpen(true);
} else {
    logConfig.level = Xlog.LEVEL_INFO;
    Xlog.setConsoleLogOpen(false);
}

Log.setLogImp(new Xlog());
```

程序退出时关闭日志：


```java
Log.appenderClose();
```

#### <a name="STN">STN Init</a>

如果你是把 marsMulti-core 作为依赖加入到你的项目中的话，你需要显式的初始化和反初始化 STN

在使用 STN 之前进行初始化

```java
// set callback
AppLogic.setCallBack(stub);
StnLogic.setCallBack(stub);
SdtLogic.setCallBack(stub);

// Initialize the Mars PlatformComm
Mars.init(getApplicationContext(), new Handler(Looper.getMainLooper()));

// Initialize the Mars
StnLogic.setLonglinkSvrAddr(profile.longLinkHost(), profile.longLinkPorts());
StnLogic.setShortlinkSvrAddr(profile.shortLinkPort());
StnLogic.setClientVersion(profile.productID());
Mars.onCreate(true);
BaseEvent.onForeground(true);

StnLogic.makesureLongLinkConnected();
```

初始化顺序不一定要严格遵守上述代码的顺序，但在初始化时首先要调用 setCallBack 接口 (callback 文件的编写可以参考 demo)，再调用 Mars.init，最后再调用 onForeground 和 makesureLongLinkConnect，中间顺序可以随意更改。**注意：STN 默认是后台，所以初始化 STN 后需要主动调用一次**```BaseEvent.onForeground(true)```

需要释放 STN 或者退出程序时:

```java
Mars.onDestroy();
```

#### <a name="even">Event Change</a>

网络切换时:

```java
BaseEvent.onNetworkChange()
```
**********
如果你是把 marsMulti-wrapper 作为依赖加入到你的项目中，你只需要显式的初始化 STN，不需要反初始化(因为 marsMulti-wrapper 会进行反初始化)

```java
MarsServiceProxy.init(this, getMainLooper(),null);
```
************
不管你是使用 marsMulti-wrapper 还是 marsMulti-core，你都需要特别注意以下事件：


前后台切换:

```java
BaseEvent.onForeground(boolean);
```

应用的账号信息更改:

```java
StnLogic.reset();
```

如果你想修改 Xlog 的加密算法或者长短连的加解包部分甚至更改组件的其他部分，可以参考[这里](https://github.com/Tencent/marsMulti/wiki/Mars-Android-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)

### <a name="apple_cn">[iOS/OS X](https://github.com/Tencent/marsMulti/wiki/Mars-iOS%EF%BC%8FOS-X-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)</a>
编译

```
python build_ios.py
```

or 
```python
python build_osx.py
```

把 marsMulti.framework 作为依赖加入到你的项目中，把mars/libraries/mars_android_sdk/jni 目录的后缀名为 rewriteme 的文件名删掉".rewriteme"和头文件一起加入到你的项目中。

#### <a name="Xlog">Xlog Init</a>

在程序启动加载 Xlog 后紧接着初始化 Xlog。但要注意保存 log 的目录请使用单独的目录，不要存放任何其他文件防止被 xlog 自动清理功能误删。


```cpp
NSString* logPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingString:@"/log"];

// set do not backup for logpath
const char* attrName = "com.apple.MobileBackup";
u_int8_t attrValue = 1;
setxattr([logPath UTF8String], attrName, &attrValue, sizeof(attrValue), 0, 0);

// init qm_xlogger
#if DEBUG
xlogger_SetLevel(kLevelDebug);
qm_appender_set_console_log(true);
#else
xlogger_SetLevel(kLevelInfo);
qm_appender_set_console_log(false);
#endif

XLogConfig config;
config.mode_ = kAppenderAsync;
config.logdir_ = [logPath UTF8String];
config.nameprefix_ = "Test";
config.pub_key_ = "";
config.compress_mode_ = kZlib;
config.compress_level_ = 0;
config.cachedir_ = "";
config.cache_days_ = 0;
qm_appender_open(config);
```

在函数 "applicationWillTerminate" 中反初始化 Xlog

```cpp
qm_appender_close();
```

#### <a name="STN">STN Init</a>

在你用 STN 之前初始化：

```objc
- (void)setCallBack {
    marsMulti::stn::SetCallback(marsMulti::stn::StnCallBack::Instance());
    marsMulti::app::SetCallback(marsMulti::app::AppCallBack::Instance());
}

- (void) createMars {
    marsMulti::baseevent::OnCreate();
}

- (void)setClientVersion:(UInt32)clientVersion {
    marsMulti::stn::SetClientVersion(clientVersion);
}

- (void)setShortLinkDebugIP:(NSString *)IP port:(const unsigned short)port {
    std::string ipAddress([IP UTF8String]);
    marsMulti::stn::SetShortlinkSvrAddr(port, ipAddress);
}

- (void)setShortLinkPort:(const unsigned short)port {
    marsMulti::stn::SetShortlinkSvrAddr(port);
}

- (void)setLongLinkAddress:(NSString *)string port:(const unsigned short)port debugIP:(NSString *)IP {
    std::string ipAddress([string UTF8String]);
    std::string debugIP([IP UTF8String]);
    std::vector<uint16_t> ports;
    ports.push_back(port);
    marsMulti::stn::SetLonglinkSvrAddr(ipAddress,ports,debugIP);
}

- (void)setLongLinkAddress:(NSString *)string port:(const unsigned short)port {
    std::string ipAddress([string UTF8String]);
    std::vector<uint16_t> ports;
    ports.push_back(port);
    marsMulti::stn::SetLonglinkSvrAddr(ipAddress,ports);
}

- (void)reportEvent_OnForeground:(BOOL)isForeground {
    marsMulti::baseevent::OnForeground(isForground);
}

- (void)makesureLongLinkConnect {
    marsMulti::stn::MakesureLonglinkConnected();
}
```

初始化顺序不一定要严格遵守上述代码的顺序，但在初始化时首先要调用 setCallBack 接口 (callback 文件的编写可以参考 demo)，再调用 Mars.init，最后再调用 onForeground 和 makesureLongLinkConnect，中间顺序可以随意更改。**注意：STN 默认是后台，所以初始化 STN 后需要主动调用一次**```BaseEvent.onForeground(true)```


需要释放 STN 或者退出程序时:

```objc
- (void)destroyMars {
    marsMulti::baseevent::OnDestroy();
}
```

#### <a name="even">Event Change</a>

前后台切换时:

```objc
- (void)reportEvent_OnForeground:(BOOL)isForeground {
    marsMulti::baseevent::OnForeground(isForeground);
}
```

网络切换时：

```objc
- (void)reportEvent_OnNetworkChange {
    marsMulti::baseevent::OnNetworkChange();
}
```
### <a name="windows_cn">[Windows](https://github.com/Tencent/marsMulti/wiki/Mars-Windows-%E6%8E%A5%E5%85%A5%E6%8C%87%E5%8D%97)</a>
安装Visual Studio 2015

编译

```python
python build_windows.py
```

把 marsMulti.lib作为依赖加入到你的项目中，把mars/libraries/mars_android_sdk/jni 目录的后缀名为 rewriteme 的文件名删掉".rewriteme"和头文件一起加入到你的项目中。

#### <a name="Xlog">Xlog Init</a>

在程序启动加载 Xlog 后紧接着初始化 Xlog。但要注意保存 log 的目录请使用单独的目录，不要存放任何其他文件防止被 xlog 自动清理功能误删。

```cpp
std::string logPath = ""; //use your log path
std::string pubKey = ""; //use you pubkey for log encrypt

// init xlog
#if DEBUG
xlogger_SetLevel(kLevelDebug);
qm_appender_set_console_log(true);
#else
xlogger_SetLevel(kLevelInfo);
qm_appender_set_console_log(false);
#endif
qm_appender_open(kAppenderAsync, logPath.c_str(), "Test", 0,  pubKey.c_str());
```

在程序退出前反初始化 Xlog

```cpp
qm_appender_close();
```

#### <a name="STN">STN Init</a>

在你用 STN 之前初始化：

```cpp
void setShortLinkDebugIP(const std::string& _ip, unsigned short _port)
{
	marsMulti::stn::SetShortlinkSvrAddr(_port, _ip);
}
void setShortLinkPort(unsigned short _port)
{
	marsMulti::stn::SetShortlinkSvrAddr(_port, "");
}
void setLongLinkAddress(const std::string& _ip, unsigned short _port, const std::string& _debug_ip)
{
	vector<uint16_t> ports;
	ports.push_back(_port);
	marsMulti::stn::SetLonglinkSvrAddr(_ip, ports, _debug_ip);
}

void Init()
{
	marsMulti::stn::SetCallback(marsMulti::stn::StnCallBack::Instance());
	marsMulti::app::SetCallback(marsMulti::app::AppCallBack::Instance());
	marsMulti::baseevent::OnCreate();

	//todo
	//marsMulti::stn::SetClientVersion(version);
	//setShortLinkDebugIP(...)
	//setLongLinkAddress(...)

	marsMulti::baseevent::OnForeground(true);
	marsMulti::stn::MakesureLonglinkConnected();
}
```

初始化顺序不一定要严格遵守上述代码的顺序，但在初始化时首先要调用 setCallBack 接口 (callback 文件的编写可以参考 demo)，再调用 Mars.init，最后再调用 onForeground 和 makesureLongLinkConnect，中间顺序可以随意更改。**注意：STN 默认是后台，所以初始化 STN 后需要主动调用一次**```BaseEvent.onForeground(true)```


需要释放 STN 或者退出程序时:

```cpp
marsMulti::baseevent::OnDestroy();
```

## Support

还有其他问题？

1. 参看 [marsMulti/sample](https://github.com/Tencent/marsMulti/tree/master/samples)；
2. 阅读 [源码](https://github.com/Tencent/marsMulti/tree/master)；
3. 阅读 [wiki](https://github.com/Tencent/marsMulti/wiki) 或者 [FAQ](https://github.com/Tencent/marsMulti/wiki/Mars-%E5%B8%B8%E8%A7%81%E9%97%AE%E9%A2%98)；
4. 联系我们。

## Contributing
关于 Mars 分支管理、issue 以及 pr 规范，请阅读 [Mars Contributing Guide](https://github.com/Tencent/marsMulti/blob/master/CONTRIBUTING.md)。

## License
Mars 使用的 MIT 协议，详细请参考 [LICENSE](https://github.com/Tencent/marsMulti/blob/master/LICENSE)。
