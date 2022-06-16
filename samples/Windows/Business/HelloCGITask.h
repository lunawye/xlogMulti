// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

/*
*  HelloCGITask.h
*
*  Created on: 2017-7-7
*      Author: chenzihao
*/

#ifndef _HELLO_CGI_TASK_H_
#define _HELLO_CGI_TASK_H_

#include "Wrapper/CGITask.h"

#include "proto/generate/main.pb.h"
#include "marsMulti/boost/weak_ptr.hpp"
class HelloCGITask;
class HelloCGICallback
{
public:
	virtual void OnResponse(HelloCGITask* task, const com::tencent::marsMulti::sample::proto::HelloResponse& response) = 0;
};
class HelloCGITask : public CGITask 
{
public:
	virtual bool Req2Buf(uint32_t _taskid, void* const _user_context, AutoBuffer& _outbuffer, AutoBuffer& _extend, int& _error_code, const int _channel_select);
	virtual int Buf2Resp(uint32_t _taskid, void* const _user_context, const AutoBuffer& _inbuffer, const AutoBuffer& _extend, int& _error_code, const int _channel_select);

	std::string user_;
	std::string text_;
	boost::weak_ptr<HelloCGICallback> callback_;
};

#endif