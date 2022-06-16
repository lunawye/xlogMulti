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
//  TopicViewController.h
//  iOSDemo
//
//  Created by caoshaokun on 16/11/25.
//  Copyright © 2016年 caoshaokun. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "UINotifyDelegate.h"
#import "Main.pb.h"
#import "../Bussiness/PushNotifyDelegate.h"

@interface TopicViewController : NSViewController<UINotifyDelegate, PushNotifyDelegate> {
    NSString* text;
}

@property (weak) IBOutlet NSTextField *textField;
@property NSTextView *recvTextView;

-(void)setHostController:(NSViewController*)controller;
-(void)setConversation:(Conversation*)conversation;
@end
