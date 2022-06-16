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
 * proxy_test.h
 *
 *  Created on: 2017-3-29
 *      Author: yanguoyue
 */

#ifndef STN_SRC_PROXYTEST_H_
#define STN_SRC_PROXYTEST_H_

#include <string>
#include <vector>

#include "marsMulti/comm/singleton.h"
#include "marsMulti/comm/socket/unix_socket.h"
#include "marsMulti/comm/socket/socketselect.h"


namespace marsMulti {
    
namespace comm {
    class ProxyInfo;
}
    
namespace stn {

class ProxyTest {
    
public:
    SINGLETON_INTRUSIVE(ProxyTest, new ProxyTest, delete);
    bool ProxyIsAvailable(const marsMulti::comm::ProxyInfo _proxy_info, const std::string& _host, const std::vector<std::string>& _hardcode_ips);
    
private:
    ProxyTest() {}
    ~ProxyTest();
    
    SOCKET __Connect(const marsMulti::comm::ProxyInfo& _proxy_info, const std::string& _host, const std::vector<std::string>& _hardcode_ips);
    int __ReadWrite(SOCKET _sock, const marsMulti::comm::ProxyInfo& _proxy_info, const std::string& _host);
    
private:
    comm::SocketBreaker testproxybreak_;

};
        
}}

#endif // STN_SRC_PROXYTEST_H_
