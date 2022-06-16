
#include "cs2runtime.h"
#include "uwpAppCallback.h"
#include "uwpStnCallback.h"
#include "stn/stn_logic.h"
#include "stn/proto/longlink_packer.h"
#include "log/qm_appender.h"
#include "sdt/sdt_logic.h"
#include "runtime_utils.h"
#include "marsMulti\baseevent\base_logic.h"

using namespace marsMulti;
using namespace std;

bool marsMulti::MarsRuntimeComponent::Init(ICallback_Comm ^ callBackForRuntime)
{
	if (nullptr == callBackForRuntime)
	{
		return false;
	}

	static bool s_bIsInited = false;
	if (s_bIsInited)
	{
		return false;
	}
	s_bIsInited = true;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	Runtime2Cs_Comm::Singleton()->SetCallback(callBackForRuntime);
	app::SetCallback(new uwpAppCallback());
	stn::SetCallback(new uwpStnCallback());
	return true;
}


void marsMulti::MarsRuntimeComponent::OnCreate()
{
	marsMulti::baseevent::OnCreate();
}

void  marsMulti::MarsRuntimeComponent::OnDestroy()
{
	marsMulti::baseevent::OnDestroy();
}

void marsMulti::MarsRuntimeComponent::OnSingalCrash(int _sig)
{
	marsMulti::baseevent::OnSingalCrash(_sig);
}

void marsMulti::MarsRuntimeComponent::OnExceptionCrash()
{
	marsMulti::baseevent::OnExceptionCrash();
}

void marsMulti::MarsRuntimeComponent:: OnForeground(bool _isforeground)
{
	marsMulti::baseevent::OnForeground(_isforeground);
}

void marsMulti::MarsRuntimeComponent:: OnNetworkChange()
{
	marsMulti::baseevent::OnNetworkChange();
}


void _FillUint16Array(vector<uint16_t> & outArray, const Platform::Array<uint16>^ inArray)
{
	outArray.clear();
	outArray.resize(inArray->Length);
	for (size_t i = 0; i < inArray->Length; i++)
	{
		outArray[i] = inArray[i];
	}
}

void _FillStdStrArray(vector<string> & outArray, const Platform::Array<Platform::String^>^ inArray)
{
	outArray.clear();
	outArray.resize(inArray->Length);
	for (size_t i = 0; i < inArray->Length; i++)
	{
		String2stdstring(outArray[i], inArray[i]);
	}
}

void marsMulti::StnComponent::SetLonglinkSvrAddr(Platform::String ^ host, const Platform::Array<uint16>^ ports)
{
	string stdStrHost = String2stdstring(host);

	vector<uint16_t> stdArrPorts;
	_FillUint16Array(stdArrPorts, ports);

	stn::SetLonglinkSvrAddr(stdStrHost, stdArrPorts);
}

void marsMulti::StnComponent::SetClientVersion(uint32 ver)
{
	stn::SetClientVersion(ver);
}

void marsMulti::StnComponent::SetShortlinkSvrAddr(uint16 port)
{
	stn::SetShortlinkSvrAddr(port);
}

void marsMulti::StnComponent::SetLonglinkSvrAddr(Platform::String ^ host, const Platform::Array<uint16>^ ports, Platform::String ^ debugip)
{
	string stdStrHost = String2stdstring(host);

	vector<uint16_t> stdArrPorts;
	_FillUint16Array(stdArrPorts, ports);

	string stdStrDebugIp = String2stdstring(debugip);

	stn::SetLonglinkSvrAddr(stdStrHost, stdArrPorts, stdStrDebugIp);
}

void marsMulti::StnComponent::SetShortlinkSvrAddr(uint16 port, Platform::String ^ debugip)
{
	string stdStrDebugIp = String2stdstring(debugip);

	stn::SetShortlinkSvrAddr(port, stdStrDebugIp);
}

void marsMulti::StnComponent::SetDebugIP(Platform::String ^ host, Platform::String ^ ip)
{
	string stdStrHost = String2stdstring(host);


	string stdStrDebugIp = String2stdstring(ip);

	stn::SetDebugIP(stdStrHost, stdStrDebugIp);
}

void marsMulti::StnComponent::SetBackupIPs(Platform::String ^ host, const Platform::Array<Platform::String^>^ iplist)
{
	string stdStrHost = String2stdstring(host);

	vector<string> stdArrStrs;
	_FillStdStrArray(stdArrStrs, iplist);

	stn::SetBackupIPs(stdStrHost, stdArrStrs);
}

void marsMulti::StnComponent::StartTask(TaskRuntime ^ task)
{
	stn::Task tTask;

	tTask.taskid = task->taskid;
	tTask.cmdid = task->cmdid;
	tTask.channel_select = task->channel_select;
	String2stdstring(tTask.cgi, task->cgi);
	tTask.send_only = task->send_only;
	tTask.need_authed = task->need_authed;
	tTask.limit_flow = task->limit_flow;
	tTask.limit_frequency = task->limit_frequency;
	tTask.network_status_sensitive = task->network_status_sensitive;
	tTask.channel_strategy = task->channel_strategy;
	tTask.priority = task->priority;
	tTask.retry_count = task->retry_count;
	tTask.server_process_cost = task->server_process_cost;
	tTask.total_timetout = task->total_timetout;
	tTask.user_context = (void*)(task->user_context);
	String2stdstring(tTask.report_arg, task->report_arg);
	_FillStdStrArray(tTask.shortlink_host_list, task->shortlink_host_list);


	stn::StartTask(tTask);
}

void marsMulti::StnComponent::StopTask(int32 taskid)
{
	stn::StopTask(taskid);
}

bool marsMulti::StnComponent::HasTask(int32 taskid)
{
	return stn::HasTask(taskid);
}

void marsMulti::StnComponent::RedoTasks()
{
	stn::RedoTasks();
}

void marsMulti::StnComponent::ClearTasks()
{
	stn::ClearTasks();
}

void marsMulti::StnComponent::Reset()
{
	stn::Reset();
}

void marsMulti::StnComponent::SetSignallingStrategy(long long period, long long keeptime)
{
	stn::SetSignallingStrategy(period, keeptime);
}

void marsMulti::StnComponent::KeepSignalling()
{
	stn::KeepSignalling();
}

void marsMulti::StnComponent::StopSignalling()
{
	stn::StopSignalling();
}

void marsMulti::StnComponent::MakesureLonglinkConnected()
{
	stn::MakesureLonglinkConnected();
}

bool marsMulti::StnComponent::LongLinkIsConnected()
{
	return stn::LongLinkIsConnected();
}

uint32 marsMulti::StnComponent::GetNoopTaskID()
{
	return stn::getNoopTaskID();
}

void marsMulti::LogComponent::AppenderOpen(TAppenderModeRuntime _mode, Platform::String ^ _dir, Platform::String ^ _nameprefix)
{
	string stdStrDir; 
	String2stdstring(stdStrDir, _dir);


	string stdStrNameprefix;
	String2stdstring(stdStrNameprefix, _nameprefix);

	appender_open((TAppenderMode)_mode, stdStrDir.c_str(), stdStrNameprefix.c_str());
}

void marsMulti::LogComponent::AppenderOpenWithCache(TAppenderModeRuntime _mode, Platform::String ^ _cachedir, Platform::String ^ _logdir, Platform::String ^ _nameprefix)
{

	string stdStrCache;
	String2stdstring(stdStrCache, _cachedir);

	string stdStrDir;
	String2stdstring(stdStrDir, _logdir);

	string stdStrPrefix;
	String2stdstring(stdStrPrefix, _nameprefix);

	appender_open_with_cache((TAppenderMode)_mode, stdStrCache, stdStrDir, stdStrPrefix.c_str());
}

void marsMulti::LogComponent::AppenderFlush()
{
	appender_flush();
}

void marsMulti::LogComponent::AppenderFlushSync()
{
	appender_flush_sync();
}

void marsMulti::LogComponent::AppenderClose()
{
	appender_close();
}

void marsMulti::LogComponent::AppenderSetMode(TAppenderModeRuntime _mode)
{
	appender_setmode((TAppenderMode)_mode);
}

bool marsMulti::LogComponent::AppenderGetFilePathFromTimeSpan(int _timespan, Platform::String ^ _prefix, const Platform::Array<Platform::String^>^ _filepath_vec)
{
	string stdStrPrefix;
	String2stdstring(stdStrPrefix, _prefix);


	vector<string> stdArrPaths;
	_FillStdStrArray(stdArrPaths, _filepath_vec);

	return appender_getfilepath_from_timespan(_timespan, stdStrPrefix.c_str(), stdArrPaths);
}


LogGetPathRet^ marsMulti::LogComponent::AppenderGetCurrentLogPath()
{
	LogGetPathRet^ retInfo = ref new LogGetPathRet();

	int nLen = 1024 * 5;
	char* logPath = new char[nLen+1];
	memset(logPath, 0, nLen + 1);

	retInfo->bRet = appender_get_current_log_path(logPath, nLen);

	string strLogPath(logPath, nLen);
	delete[] logPath;
	logPath = NULL;

	retInfo->logPath = stdstring2String(strLogPath);
	return retInfo;
}

LogGetPathRet^ marsMulti::LogComponent::AppenderGetCurrentLogCachePath()
{
	LogGetPathRet^ retInfo = ref new LogGetPathRet();

	int nLen = 1024 * 5;
	char* logPath = new char[nLen + 1];
	memset(logPath, 0, nLen + 1);

	retInfo->bRet = appender_get_current_log_cache_path(logPath, nLen);

	string strLogPath(logPath, nLen);
	delete[] logPath;
	logPath = NULL;

	retInfo->logPath = stdstring2String(strLogPath);
	return retInfo;
}

void marsMulti::LogComponent::AppenderSetConsoleLog(bool _is_open)
{
	return appender_set_console_log(_is_open);
}

void marsMulti::LogComponent::SetLogLevel(TLogLevelRuntime _level)
{
	xlogger_SetLevel((TLogLevel)_level);
}

TLogLevelRuntime marsMulti::LogComponent::GetLogLevel()
{
	return (TLogLevelRuntime)xlogger_Level();
}

void marsMulti::LogComponent::LogWrite(TLogLevelRuntime _level, Platform::String^ _tag, Platform::String^ _filename, Platform::String^ _funcname, int _line, intmax_t _pid, intmax_t _tid, intmax_t _maintid, Platform::String^ _log)
{
	if (!xlogger_IsEnabledFor((TLogLevel)_level)) {
		return;
	}

	XLoggerInfo xlog_info;
	gettimeofday(&xlog_info.timeval, NULL);
	xlog_info.level = (TLogLevel)_level;
	xlog_info.line = _line;
	xlog_info.pid = _pid;
	xlog_info.tid = _tid;
	xlog_info.maintid = _maintid;

	string stdStrTag;
	String2stdstring(stdStrTag, _tag);

	string stdStrFileName;
	String2stdstring(stdStrFileName, _filename);

	string stdFuncName;
	String2stdstring(stdFuncName, _funcname);

	string stdStrLog;
	String2stdstring(stdStrLog, _log);

	xlog_info.tag = stdStrTag.c_str();
	xlog_info.filename = stdStrFileName.c_str();
	xlog_info.func_name = stdFuncName.c_str();

	xlogger_Write(&xlog_info, stdStrLog.size() == 0 ? "NULL == log" : stdStrLog.c_str());
}


void marsMulti::SdtComponent::SetHttpNetcheckCGI(Platform::String ^ cgi)
{
	string stdStrArg1;
	String2stdstring(stdStrArg1, cgi);

	sdt::SetHttpNetcheckCGI(stdStrArg1);
}

