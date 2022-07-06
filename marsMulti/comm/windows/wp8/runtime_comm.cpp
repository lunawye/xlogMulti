/*  Copyright (c) 2013-2015 Tencent. All rights reserved.  */
#include "runtime_comm.h"

#include "alarm.h"


using namespace PublicComponent;


void Cs2Runtime_Comm::OnAlarm(int id) {
    Alarm::OnAlarm(reinterpret_cast<Alarm*>(id));
}


void Cs2Runtime_Comm::OnCreate() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#else
    signal(SIGPIPE, SIG_IGN);
#endif
    appender_SetConsoleLog(true);  // just for test  //TODO
    qm_xwarn2(TSF"onCreate");
    qm_appender_open(EAppednerAsync, (::getAppFilePath() + "\\log").c_str(), "MM");
    MMLogLogic::InitLogInfo();
#ifndef NDEBUG
    xlogger_SetLevel(ELevelDebug);
#endif
}

void Cs2Runtime_Comm::OnDestroy() {
    qm_xwarn2(TSF"onDestroy");
#ifdef _WIN32
    WSACleanup();
#endif

    SINGLETON_RELEASE_ALL();
    qm_xwarn2(TSF"ReleaseXLogger---------------------------------------------------------");
    qm_appender_close();
}

void Cs2Runtime_Comm::OnSingalCrash(int _sig) {
    qm_xverbose2(TSF"ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc=%0", _sig);
    qm_appender_close();
}

void Cs2Runtime_Comm::OnExceptionCrash() {
    qm_xverbose2(TSF"ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
    qm_appender_close();
}

void Cs2Runtime_Comm::OnForeground(bool _isforeground) {
    SINGLETON_STRONG(ActiveLogic).OnForeground(_isforeground);
}




Runtime2Cs_Comm::Runtime2Cs_Comm():
    m_callback(nullptr) {
}

Runtime2Cs_Comm^ Runtime2Cs_Comm::instance = nullptr;

Runtime2Cs_Comm^ Runtime2Cs_Comm::Singleton() {
    if (instance == nullptr) {
        instance = ref new Runtime2Cs_Comm();
    }

    return instance;
}

void Runtime2Cs_Comm::SetCallback(ICallback_Comm^ _callback) {
    m_callback = _callback;
}




bool Runtime2Cs_Comm::startAlarm(int id, int after) {
    if (nullptr == m_callback) return false;

    return m_callback->startAlarm(id, after);
}

bool Runtime2Cs_Comm::stopAlarm(int id) {
    if (nullptr == m_callback) return false;

    return m_callback->stopAlarm(id);
}

int Runtime2Cs_Comm::getNetInfo() {
    if (nullptr == m_callback) return -1;

    return m_callback->getNetInfo();
}

int Runtime2Cs_Comm::getStatisticsNetType() {
    if (nullptr == m_callback) return -1;

    return m_callback->getStatisticsNetType();
}

ProxyInfo^ Runtime2Cs_Comm::getProxyInfo() {
    if (nullptr == m_callback) return nullptr;

    return m_callback->getProxyInfo();
}

bool Runtime2Cs_Comm::isNetworkConnected() {
    if (nullptr == m_callback) return false;

    return m_callback->isNetworkConnected();
}

CurWifiInfo^ Runtime2Cs_Comm::getCurWifiInfo() {
    if (nullptr == m_callback) return nullptr;

    return m_callback->getCurWifiInfo();
}



void Runtime2Cs_Comm::ConsoleLog(int logLevel, Platform::String^ tag, Platform::String^ filename, Platform::String^ funcname, int line, Platform::String^ log) {
    if (nullptr == m_callback) return;

    return m_callback->ConsoleLog(logLevel, tag, filename, funcname, line, log);
}
