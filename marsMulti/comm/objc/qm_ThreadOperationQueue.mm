// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

//
//  ThreadOperationQueue.mm
//  MicroMessenger
//
//  Created by yerungui on 12-12-18.
//

#import "comm/objc/qm_ThreadOperationQueue.h"

#import "comm/objc/qm_scope_autoreleasepool.h"

static class __ThreadRunOnStart
{
public:
    __ThreadRunOnStart()
    {
        m_operationQueue = [[NSOperationQueue alloc] init];
        assert(m_operationQueue);
    }
    ~__ThreadRunOnStart()
    {
        [m_operationQueue release];
        m_operationQueue = nil;
    }
    
    NSOperationQueue* m_operationQueue;
} gs_threadrunonstart;

@interface __CThreadWarp : NSObject
{
    void (*qm_m_funp)(void*);
    void* qm_m_arg;
    void (*qm_m_fun)();
    
}

-(void) qm_Run;
@property (nonatomic, assign)  void (*qm_m_funp)(void*);
@property (nonatomic, assign)  void (*qm_m_fun)();
@property (nonatomic, assign)  void* qm_m_arg;
@end

@implementation __CThreadWarp

@synthesize qm_m_funp;
@synthesize qm_m_fun;
@synthesize qm_m_arg;

-(id) init
{
    if (self = [super init]) {
        qm_m_funp = nil;
        qm_m_arg = nil;
        qm_m_fun = nil;
    }
    
    return self;
}

-(void) qm_Run
{
    SCOPE_POOL();
    assert(nil!=qm_m_funp || nil!=qm_m_fun);
    if (nil!=qm_m_funp)
        qm_m_funp(qm_m_arg);
    else
        qm_m_fun();
        
}
@end


@interface __ThreadWarp : NSObject
{
    id qm_m_target;
    SEL qm_m_sel;
    id qm_m_arg;
}

-(void) qm_Run;
@property (nonatomic, retain)  id qm_m_target;
@property (nonatomic, assign)  SEL qm_m_sel;
@property (nonatomic, retain)  id qm_m_arg;
@end

@implementation __ThreadWarp

@synthesize qm_m_target;
@synthesize qm_m_sel;
@synthesize qm_m_arg;

-(id) init
{
    if (self = [super init]) {
        qm_m_target = nil;
        qm_m_sel = 0;
        qm_m_arg = nil;
    }
    
    return self;
}

- (void)qm_dealloc {
    self.qm_m_target = nil;
    self.qm_m_arg = nil;
    [super qm_dealloc];
}

-(void) qm_Run
{
    SCOPE_POOL();
    [qm_m_target performSelector:qm_m_sel withObject:qm_m_arg];
}
@end

@implementation qm_ThreadQueue

+(BOOL) qm_RunWithTarget:(id)target selector:(SEL)sel object:(id)arg
{
    SCOPE_POOL();
    __ThreadWarp* warp = [[__ThreadWarp alloc] init];
    warp.qm_m_target= target;
    warp.qm_m_sel= sel;
    warp.qm_m_arg = arg;
    
    NSInvocationOperation* invocation = [[NSInvocationOperation alloc]
                                         initWithTarget:warp selector:@selector(qm_Run) object:nil];
    if (nil==invocation)
    {
        [warp release];
        return NO;
    }
    
    [gs_threadrunonstart.m_operationQueue addOperation:invocation];
    [invocation release];
    [warp release];
    return YES;
}

@end

extern "C" BOOL qm_RunWithTarget(void (*_funp)(void*), void* _arg)
{
    SCOPE_POOL();
    __CThreadWarp* warp = [[__CThreadWarp alloc] init];
    warp.qm_m_funp = _funp;
    warp.qm_m_arg = _arg;
    
    NSInvocationOperation* invocation = [[NSInvocationOperation alloc]
                                         initWithTarget:warp selector:@selector(qm_Run) object:nil];
    if (nil==invocation)
    {
        [warp release];
        return NO;
    }
    
    [gs_threadrunonstart.m_operationQueue addOperation:invocation];
    [invocation release];
    [warp release];
    return YES;
}

extern "C" BOOL qm_RunWithTargetNoParam(void (*_fun)())
{
    SCOPE_POOL();
    __CThreadWarp* warp = [[__CThreadWarp alloc] init];
    warp.qm_m_fun = _fun;
    
    NSInvocationOperation* invocation = [[NSInvocationOperation alloc]
                                         initWithTarget:warp selector:@selector(qm_Run) object:nil];
    if (nil==invocation)
    {
        [warp release];
        return NO;
    }
    
    [gs_threadrunonstart.m_operationQueue addOperation:invocation];
    [invocation release];
    [warp release];
    return YES;
}

void comm_export_symbols_4(){}
