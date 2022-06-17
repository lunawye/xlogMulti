// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

/*
 ============================================================================
 Name		: qm_xlogger.h
 ============================================================================
 */

#ifndef XLOGGER_H_
#define XLOGGER_H_

#include <stdlib.h>
#include <assert.h>
#include <sys/cdefs.h>
#include <sys/time.h>

#include "qm_string_cast.h"
#include "qm_xloggerbase.h"
#include "qm_preprocessor.h"

#ifdef XLOGGER_DISABLE
#define  xlogger_IsEnabledFor(_level)	(false)
#define  xlogger_AssertP(...)			((void)0)
#define  xlogger_Assert(...)			((void)0)
#define  xlogger_VPrint(...)			((void)0)
#define  xlogger_Print(...)				((void)0)
#define  xlogger_Write(...)				((void)0)
#endif

#ifdef __cplusplus
#include <string>

template <bool x> struct XLOGGER_STATIC_ASSERTION_FAILURE;
template <> struct XLOGGER_STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
template<int x> struct xlogger_static_assert_test{};


#define XLOGGER_STATIC_ASSERT( ... ) typedef ::xlogger_static_assert_test<\
                                        sizeof(::XLOGGER_STATIC_ASSERTION_FAILURE< ((__VA_ARGS__) == 0 ? false : true) >)>\
                                        PP_CAT(boost_static_assert_typedef_, __LINE__)


#ifdef __APPLE__
using TypeSafeFormat = void*;
#else
const struct TypeSafeFormat {TypeSafeFormat(){}} __tsf__;
#endif
const struct XLoggerTag {XLoggerTag(){}} __xlogger_tag__;
const struct XLoggerInfoNull {XLoggerInfoNull(){}} __xlogger_info_null__;

class XMessage {
public:
    XMessage(): m_message() { m_message.reserve(512); }
    XMessage(std::string& _holder):m_message(_holder){}
    ~XMessage() {}

public:
    const std::string& Message() const { return m_message;}
    std::string& Message() { return m_message;}

    const std::string& String() const { return m_message;}
    std::string& String() { return m_message;}

#ifdef __GNUC__
    __attribute__((__format__ (printf, 2, 0)))
#endif
    XMessage&  WriteNoFormat(const char* _log) { m_message+= _log; return *this;}
#ifdef __GNUC__
    __attribute__((__format__ (printf, 3, 0)))
#endif
    XMessage&  WriteNoFormat(const TypeSafeFormat&, const char* _log) { m_message+= _log; return *this;}

    XMessage& operator<<(const string_cast& _value);
    XMessage& operator>>(const string_cast& _value);

    XMessage& operator()() {return *this;}
    void operator+=(const string_cast& _value) { m_message += _value.str();}
#ifdef __GNUC__
    __attribute__((__format__ (printf, 2, 3)))
#endif
    XMessage& operator()(const char* _format, ...);

#ifdef __GNUC__
    __attribute__((__format__ (printf, 2, 0)))
#endif
    XMessage& VPrintf(const char* _format, va_list _list);

#define XLOGGER_FORMAT_ARGS(n) PP_ENUM_TRAILING_PARAMS(n, const string_cast& a)
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(0));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(1));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(2));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(3));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(4));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(5));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(6));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(7));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(8));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(9));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(10));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(11));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(12));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(13));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(14));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(15));
    XMessage&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(16));
#undef XLOGGER_FORMAT_ARGS

private:
    void DoTypeSafeFormat(const char* _format, const string_cast** _args);

private:
//	  XMessage(const XMessage&);
//	  XMessage& operator=(const XMessage&);

private:
    std::string m_message;
};

class QM_XLogger {
public:
    QM_XLogger(TLogLevel _level, const char* _tag, const char* _file, const char* _func, int _line, bool _trace = false, bool (*_hook)(XLoggerInfo& _info, std::string& _log) = NULL);
    ~QM_XLogger();

public:
    QM_XLogger& Assert(const char* _exp);
    
    bool Empty() const { return !m_isassert && m_message.empty();}
    const std::string& Message() const { return m_message;}
    void ForwardToSysTrace(){   m_info.traceLog = 1;    }
    void Clear() { m_message.clear(); }

#ifdef __GNUC__
    __attribute__((__format__ (printf, 2, 0)))
#endif
    QM_XLogger&  WriteNoFormat(const char* _log) { m_message+= _log; return *this;}
#ifdef __GNUC__
     __attribute__((__format__ (printf, 3, 0)))
#endif
    QM_XLogger&  WriteNoFormat(const TypeSafeFormat&, const char* _log) { m_message+= _log; return *this;}

    QM_XLogger& operator<<(const string_cast& _value);
    QM_XLogger& operator>>(const string_cast& _value);

    void operator>> (QM_XLogger& _xlogger);

    void operator<< (QM_XLogger& _xlogger);

    QM_XLogger& operator()() { return *this; }
    QM_XLogger& operator()(const XLoggerInfoNull&) { m_isinfonull = true; return *this;}
    QM_XLogger& operator()(const XLoggerTag&, const char* _tag) { m_info.tag = _tag; return *this;}
#ifdef __GNUC__
    __attribute__((__format__ (printf, 2, 3)))
#endif
    QM_XLogger& operator()(const char* _format, ...);

#ifdef __GNUC__
     __attribute__((__format__ (printf, 2, 0)))
#endif
    QM_XLogger& VPrintf(const char* _format, va_list _list);

#define XLOGGER_FORMAT_ARGS(n) PP_ENUM_TRAILING_PARAMS(n, const string_cast& a)
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(0));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(1));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(2));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(3));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(4));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(5));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(6));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(7));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(8));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(9));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(10));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(11));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(12));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(13));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(14));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(15));
    QM_XLogger&  operator()(const TypeSafeFormat&, const char*_format XLOGGER_FORMAT_ARGS(16));
#undef XLOGGER_FORMAT_ARGS

private:
    void DoTypeSafeFormat(const char* _format, const string_cast** _args);
    
private:
    QM_XLogger(const QM_XLogger&);
    QM_XLogger& operator=(const QM_XLogger&);
    
private:
    XLoggerInfo m_info;
    std::string m_message;
    bool m_isassert;
    const char* m_exp;
    bool (*m_hook)(XLoggerInfo& _info, std::string& _log);
    bool m_isinfonull;
};


class XScopeTracer {
public:
    XScopeTracer(TLogLevel _level, const char* _tag, const char* _name, const char* _file, const char* _func, int _line, const char* _log);

    ~XScopeTracer();
    
    void Exit(const std::string& _exitmsg) { m_exitmsg += _exitmsg; }
    
private:
    XScopeTracer(const XScopeTracer&);
    XScopeTracer& operator=(const XScopeTracer&);

private:
    bool m_enable;
    XLoggerInfo m_info;
    char m_name[128];
    timeval m_tv;
    
    std::string m_exitmsg;
};

#define XLOGGER_FORMAT_ARGS(n) PP_ENUM_TRAILING_PARAMS(n, const string_cast& a)
#define XLOGGER_VARIANT_ARGS(n) PP_ENUM_PARAMS(n, &a)
#define XLOGGER_VARIANT_ARGS_NULL(n) PP_ENUM(n, NULL)
#define XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(n, m) \
        inline XMessage& XMessage::operator()(const TypeSafeFormat&, const char* _format XLOGGER_FORMAT_ARGS(n)) { \
        if (_format != NULL) { \
            const string_cast* args[16] = { XLOGGER_VARIANT_ARGS(n) PP_COMMA_IF(PP_AND(n, m)) XLOGGER_VARIANT_ARGS_NULL(m) }; \
            DoTypeSafeFormat(_format, args); \
        } \
        return *this;\
    }

XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(0, 16)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(1, 15)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(2, 14)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(3, 13)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(4, 12)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(5, 11)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(6, 10)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(7, 9)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(8, 8)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(9, 7)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(10, 6)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(11, 5)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(12, 4)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(13, 3)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(14, 2)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(15, 1)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(16, 0)

#undef XLOGGER_FORMAT_ARGS
#undef XLOGGER_VARIANT_ARGS
#undef XLOGGER_VARIANT_ARGS_NULL
#undef XLOGGER_TYPESAFE_FORMAT_IMPLEMENT

#define XLOGGER_FORMAT_ARGS(n) PP_ENUM_TRAILING_PARAMS(n, const string_cast& a)
#define XLOGGER_VARIANT_ARGS(n) PP_ENUM_PARAMS(n, &a)
#define XLOGGER_VARIANT_ARGS_NULL(n) PP_ENUM(n, NULL)
#define XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(n, m) \
        inline QM_XLogger& QM_XLogger::operator()(const TypeSafeFormat&, const char* _format XLOGGER_FORMAT_ARGS(n)) { \
        if (_format != NULL) { \
            const string_cast* args[16] = { XLOGGER_VARIANT_ARGS(n) PP_COMMA_IF(PP_AND(n, m)) XLOGGER_VARIANT_ARGS_NULL(m) }; \
            DoTypeSafeFormat(_format, args); \
        } \
        return *this;\
    }

XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(0, 16)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(1, 15)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(2, 14)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(3, 13)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(4, 12)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(5, 11)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(6, 10)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(7, 9)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(8, 8)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(9, 7)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(10, 6)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(11, 5)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(12, 4)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(13, 3)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(14, 2)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(15, 1)
XLOGGER_TYPESAFE_FORMAT_IMPLEMENT(16, 0)


#undef XLOGGER_FORMAT_ARGS
#undef XLOGGER_VARIANT_ARGS
#undef XLOGGER_VARIANT_ARGS_NULL
#undef XLOGGER_TYPESAFE_FORMAT_IMPLEMENT

#endif //cpp


#define __CONCAT_IMPL__(x, y)		x##y
#define __CONCAT__(x, y)			__CONCAT_IMPL__(x, y)
#define __ANONYMOUS_VARIABLE__(x)	__CONCAT__(x, __LINE__)

#define __XFILE__					(__FILE__)

#ifndef _MSC_VER
    //#define __XFUNCTION__		  __PRETTY_FUNCTION__
    #define __XFUNCTION__		__FUNCTION__
#else
    // Definitely, VC6 not support this feature!
    #if _MSC_VER > 1200
        //#define __XFUNCTION__	__FUNCSIG__
        #define __XFUNCTION__	__FUNCTION__
    #else
        #define __XFUNCTION__	"N/A"
        #warning " is not supported by this compiler"
    #endif
#endif

//qm_xlogger define

#ifndef XLOGGER_TAG
#define XLOGGER_TAG ""
#endif

/* tips: this code replace or change the tag in source file
static const char* __my_xlogger_tag = "prefix_"XLOGGER_TAG"_suffix";
#undef XLOGGER_TAG
#define XLOGGER_TAG __my_xlogger_tag
*/

#define xdump xlogger_dump
#define XLOGGER_ROUTER_OUTPUT(op1,op,...) PP_IF(PP_NUM_PARAMS(__VA_ARGS__),PP_IF(PP_DEC(PP_NUM_PARAMS(__VA_ARGS__)),op,op1), )

#if !defined(__cplusplus)

#ifdef __GNUC__
__attribute__((__format__ (printf, 2, 3)))
#endif
__inline void  __xlogger_c_write(const XLoggerInfo* _info, const char* _log, ...) { xlogger_Write(_info, _log); }

#define qm_xlogger2(level, tag, file, func, line, ...)		 if ((!xlogger_IsEnabledFor(level)));\
                                                              else { XLoggerInfo info= {level, tag, file, func, line,\
                                                                     {0, 0}, -1, -1, -1, false};\ gettimeofday(&info.m_tv, NULL);\
                                                                     XLOGGER_ROUTER_OUTPUT(__xlogger_c_write(&info, __VA_ARGS__),xlogger_Print(&info, __VA_ARGS__), __VA_ARGS__);}

#define qm_xlogger2_if(exp, level, tag, file, func, line, ...)    if (!(exp) || !xlogger_IsEnabledFor(level));\
                                                                    else { XLoggerInfo info= {level, tag, file, func, line,\
                                                                           {0, 0}, -1, -1, -1, false}; gettimeofday(&info.timeval, NULL);\
                                                                           XLOGGER_ROUTER_OUTPUT(__xlogger_c_write(&info, __VA_ARGS__),xlogger_Print(&info, __VA_ARGS__), __VA_ARGS__);}

#define __xlogger_c_impl(level,  ...)			qm_xlogger2(level, XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__, __VA_ARGS__)
#define __xlogger_c_impl_if(level, exp, ...)	qm_xlogger2_if(exp, level, XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__, __VA_ARGS__)

#define qm_xverbose2(...)			   __xlogger_c_impl(kLevelVerbose, __VA_ARGS__)
#define qm_xdebug2(...)			   __xlogger_c_impl(kLevelDebug, __VA_ARGS__)
#define qm_xinfo2(...)				   __xlogger_c_impl(kLevelInfo, __VA_ARGS__)
#define qm_xwarn2(...)				   __xlogger_c_impl(kLevelWarn, __VA_ARGS__)
#define qm_xerror2(...)			   __xlogger_c_impl(kLevelError, __VA_ARGS__)
#define qm_xfatal2(...)			   __xlogger_c_impl(kLevelFatal, __VA_ARGS__)

#define qm_xverbose2_if(exp, ...)	   __xlogger_c_impl_if(kLevelVerbose, exp, __VA_ARGS__)
#define qm_xdebug2_if(exp, ...)	   __xlogger_c_impl_if(kLevelDebug, exp, __VA_ARGS__)
#define qm_xinfo2_if(exp, ...)		   __xlogger_c_impl_if(kLevelInfo, exp, __VA_ARGS__)
#define qm_xwarn2_if(exp, ...)		   __xlogger_c_impl_if(kLevelWarn, exp,  __VA_ARGS__)
#define qm_xerror2_if(exp, ...)	   __xlogger_c_impl_if(kLevelError, exp, __VA_ARGS__)
#define qm_xfatal2_if(exp, ...)	   __xlogger_c_impl_if(kLevelFatal, exp, __VA_ARGS__)

#define qm_xassert2(exp, ...)	  if (((exp) || !xlogger_IsEnabledFor(kLevelFatal)));else {\
                                    XLoggerInfo info= {kLevelFatal, XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__,\
                                    {0, 0}, -1, -1, -1, false};\
                                    gettimeofday(&info.m_tv, NULL);\
                                    xlogger_AssertP(&info, #exp, __VA_ARGS__);}
//"##__VA_ARGS__" remove "," if NULL
#else

#ifndef QM_XLOGGER_HOOK
#define QM_XLOGGER_HOOK NULL
#endif

#define qm_xlogger(level, tag, file, func, line, ...)	   if ((!xlogger_IsEnabledFor(level)));\
                                                       else QM_XLogger(level, tag, file, func, line, false, QM_XLOGGER_HOOK)\
                                                             XLOGGER_ROUTER_OUTPUT(.WriteNoFormat(TSF __VA_ARGS__),(TSF __VA_ARGS__), __VA_ARGS__)

#define qm_xlogger2(level, tag, file, func, line, ...)		if ((!xlogger_IsEnabledFor(level)));\
                                                        else QM_XLogger(level, tag, file, func, line, false, QM_XLOGGER_HOOK)\
                                                             XLOGGER_ROUTER_OUTPUT(.WriteNoFormat(__VA_ARGS__),(__VA_ARGS__), __VA_ARGS__)

#define qm_xlogger2_if(exp, level, tag, file, func, line, ...)		if ((!(exp) || !xlogger_IsEnabledFor(level)));\
                                                                else QM_XLogger(level, tag, file, func, line, false, QM_XLOGGER_HOOK)\
                                                                     XLOGGER_ROUTER_OUTPUT(.WriteNoFormat(__VA_ARGS__),(__VA_ARGS__), __VA_ARGS__)

#define qm_xlogger_trace(level, tag, file, func, line, ...)		if ((!xlogger_IsEnabledFor(level)));\
                                                        else QM_XLogger(level, tag, file, func, line, true, QM_XLOGGER_HOOK)\
                                                             XLOGGER_ROUTER_OUTPUT(.WriteNoFormat(__VA_ARGS__),(__VA_ARGS__), __VA_ARGS__)

#define __xlogger_cpp_impl2(level, ...)				 qm_xlogger2(level, XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__, __VA_ARGS__)
#define __xlogger_cpp_impl_if(level, exp, ...)	   qm_xlogger2_if(exp, level, XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__, __VA_ARGS__)
#define __xlogger_cpp_impl_trace(level, ...)        qm_xlogger_trace(level,  XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__, __VA_ARGS__)

#define qm_xverbose2(...)			   __xlogger_cpp_impl2(kLevelVerbose, __VA_ARGS__)
#define qm_xdebug2(...)			   __xlogger_cpp_impl2(kLevelDebug, __VA_ARGS__)
#define qm_xinfo2(...)				   __xlogger_cpp_impl2(kLevelInfo, __VA_ARGS__)
#define qm_xwarn2(...)				   __xlogger_cpp_impl2(kLevelWarn, __VA_ARGS__)
#define qm_xerror2(...)			   __xlogger_cpp_impl2(kLevelError, __VA_ARGS__)
#define qm_xfatal2(...)			   __xlogger_cpp_impl2(kLevelFatal, __VA_ARGS__)
#define qm_xlog2(level, ...)		   __xlogger_cpp_impl2(level, __VA_ARGS__)

#define qm_xverbose2_if(exp, ...)	   __xlogger_cpp_impl_if(kLevelVerbose, exp,  __VA_ARGS__)
#define qm_xdebug2_if(exp, ...)	   __xlogger_cpp_impl_if(kLevelDebug, exp,	__VA_ARGS__)
#define qm_xinfo2_if(exp, ...)		   __xlogger_cpp_impl_if(kLevelInfo, exp,  __VA_ARGS__)
#define qm_xwarn2_if(exp, ...)		   __xlogger_cpp_impl_if(kLevelWarn, exp,  __VA_ARGS__)
#define qm_xerror2_if(exp, ...)	   __xlogger_cpp_impl_if(kLevelError, exp,	__VA_ARGS__)
#define qm_xfatal2_if(exp, ...)	   __xlogger_cpp_impl_if(kLevelFatal, exp, __VA_ARGS__)
#define qm_xlog2_if(level, ...)	   __xlogger_cpp_impl_if(level, __VA_ARGS__)

#define qm_xverbose_trace(...)			   __xlogger_cpp_impl_trace(kLevelVerbose, __VA_ARGS__)
#define qm_xdebug_trace(...)			   __xlogger_cpp_impl_trace(kLevelDebug, __VA_ARGS__)
#define qm_xinfo_trace(...)				   __xlogger_cpp_impl_trace(kLevelInfo, __VA_ARGS__)
#define qm_xwarn_trace(...)				   __xlogger_cpp_impl_trace(kLevelWarn, __VA_ARGS__)
#define qm_xerror_trace(...)			   __xlogger_cpp_impl_trace(kLevelError, __VA_ARGS__)
#define qm_xfatal_trace(...)			   __xlogger_cpp_impl_trace(kLevelFatal, __VA_ARGS__)

#define xgroup2_define(group)	   QM_XLogger group(kLevelAll, XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__, QM_XLOGGER_HOOK)
#define qm_xgroup2(...)			   QM_XLogger(kLevelAll, XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__, false, QM_XLOGGER_HOOK)(__VA_ARGS__)
#define qm_xgroup2_if(exp, ...)	   if ((!(exp))); else QM_XLogger(kLevelAll, XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__, false, QM_XLOGGER_HOOK)(__VA_ARGS__)

#define qm_xassert2(exp, ...)	  if (((exp) || !xlogger_IsEnabledFor(kLevelFatal)));\
                             else QM_XLogger(kLevelFatal, XLOGGER_TAG, __XFILE__, __XFUNCTION__, __LINE__, false, QM_XLOGGER_HOOK).Assert(#exp)\
                                  XLOGGER_ROUTER_OUTPUT(.WriteNoFormat(__VA_ARGS__),(__VA_ARGS__), __VA_ARGS__)

#define qm_xmessage2_define(name, ...)		XMessage name; name XLOGGER_ROUTER_OUTPUT(.WriteNoFormat(__VA_ARGS__),(__VA_ARGS__), __VA_ARGS__)
#define qm_xmessage2(...)					XMessage() XLOGGER_ROUTER_OUTPUT(.WriteNoFormat(__VA_ARGS__),(__VA_ARGS__), __VA_ARGS__)


#define XLOGGER_SCOPE_MESSAGE(...)		PP_IF(PP_NUM_PARAMS(__VA_ARGS__), qm_xmessage2(__VA_ARGS__).String().c_str(), NULL)
#define __xscope_impl(level, name, ...)   XScopeTracer __ANONYMOUS_VARIABLE__(_tracer_)(level, XLOGGER_TAG, name, __XFILE__, __XFUNCTION__, __LINE__, XLOGGER_SCOPE_MESSAGE(__VA_ARGS__))

#define qm_xverbose_scope(name, ...)		__xscope_impl(kLevelVerbose, name, __VA_ARGS__)
#define qm_xdebug_scope(name, ...)			__xscope_impl(kLevelDebug, name, __VA_ARGS__)
#define qm_xinfo_scope(name, ...)			__xscope_impl(kLevelInfo, name, __VA_ARGS__)

#define __xfunction_scope_impl(level, name, ...)	XScopeTracer __ANONYMOUS_VARIABLE__(_xfunction_)(level, XLOGGER_TAG, name, __XFILE__, __XFUNCTION__, __LINE__, XLOGGER_SCOPE_MESSAGE(__VA_ARGS__))

#define qm_xverbose_function(...)			__xfunction_scope_impl(kLevelVerbose, __FUNCTION__, __VA_ARGS__)
#define qm_xdebug_function(...)			__xfunction_scope_impl(kLevelDebug, __FUNCTION__, __VA_ARGS__)
#define qm_xinfo_function(...)				__xfunction_scope_impl(kLevelInfo, __FUNCTION__, __VA_ARGS__)

#ifdef __APPLE__
#define TSF __builtin_return_address(0),
#else
#define TSF __tsf__,
#endif
#define XTAG __xlogger_tag__,
#define XNULL __xlogger_info_null__
#define XENDL "\n"
#define XTHIS "@%p, ", this

#endif
#endif /* XLOGGER_H_ */
