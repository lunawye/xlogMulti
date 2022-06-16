// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: main.proto

// This CPP symbol can be defined to use imports that match up to the framework
// imports needed when using CocoaPods.
#if !defined(GPB_USE_PROTOBUF_FRAMEWORK_IMPORTS)
 #define GPB_USE_PROTOBUF_FRAMEWORK_IMPORTS 0
#endif

#if GPB_USE_PROTOBUF_FRAMEWORK_IMPORTS
 #import <Protobuf/GPBProtocolBuffers_RuntimeSupport.h>
#else
 #import "GPBProtocolBuffers_RuntimeSupport.h"
#endif

 #import "Main.pbobjc.h"
// @@protoc_insertion_point(imports)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#pragma mark - MainRoot

@implementation MainRoot

// No extensions in the file and no imports, so no need to generate
// +extensionRegistry.

@end

#pragma mark - MainRoot_FileDescriptor

static GPBFileDescriptor *MainRoot_FileDescriptor(void) {
  // This is called by +initialize so there is no need to worry
  // about thread safety of the singleton.
  static GPBFileDescriptor *descriptor = NULL;
  if (!descriptor) {
    GPB_DEBUG_CHECK_RUNTIME_VERSIONS();
    descriptor = [[GPBFileDescriptor alloc] initWithPackage:@"com.tencent.marsMulti.sample.proto"
                                                     syntax:GPBFileSyntaxProto2];
  }
  return descriptor;
}

#pragma mark - Enum CmdID

GPBEnumDescriptor *CmdID_EnumDescriptor(void) {
  static GPBEnumDescriptor *descriptor = NULL;
  if (!descriptor) {
    static const char *valueNames =
        "CmdIdInvalid\000CmdIdUnknown\000CmdIdHello\000Cmd"
        "IdAuth\000CmdIdSendMessage\000CmdIdConversatio"
        "nList\000CmdIdJointopic\000CmdIdLefttopic\000";
    static const int32_t values[] = {
        CmdID_CmdIdInvalid,
        CmdID_CmdIdUnknown,
        CmdID_CmdIdHello,
        CmdID_CmdIdAuth,
        CmdID_CmdIdSendMessage,
        CmdID_CmdIdConversationList,
        CmdID_CmdIdJointopic,
        CmdID_CmdIdLefttopic,
    };
    GPBEnumDescriptor *worker =
        [GPBEnumDescriptor allocDescriptorForName:GPBNSStringifySymbol(CmdID)
                                       valueNames:valueNames
                                           values:values
                                            count:(uint32_t)(sizeof(values) / sizeof(int32_t))
                                     enumVerifier:CmdID_IsValidValue];
    if (!OSAtomicCompareAndSwapPtrBarrier(nil, worker, (void * volatile *)&descriptor)) {
      [worker release];
    }
  }
  return descriptor;
}

BOOL CmdID_IsValidValue(int32_t value__) {
  switch (value__) {
    case CmdID_CmdIdInvalid:
    case CmdID_CmdIdUnknown:
    case CmdID_CmdIdHello:
    case CmdID_CmdIdAuth:
    case CmdID_CmdIdSendMessage:
    case CmdID_CmdIdConversationList:
    case CmdID_CmdIdJointopic:
    case CmdID_CmdIdLefttopic:
      return YES;
    default:
      return NO;
  }
}

#pragma mark - HelloRequest

@implementation HelloRequest

@dynamic hasUser, user;
@dynamic hasText, text;

typedef struct HelloRequest__storage_ {
  uint32_t _has_storage_[1];
  NSString *user;
  NSString *text;
} HelloRequest__storage_;

// This method is threadsafe because it is initially called
// in +initialize for each subclass.
+ (GPBDescriptor *)descriptor {
  static GPBDescriptor *descriptor = nil;
  if (!descriptor) {
    static GPBMessageFieldDescription fields[] = {
      {
        .name = "user",
        .dataTypeSpecific.className = NULL,
        .number = HelloRequest_FieldNumber_User,
        .hasIndex = 0,
        .offset = (uint32_t)offsetof(HelloRequest__storage_, user),
        .flags = GPBFieldRequired,
        .dataType = GPBDataTypeString,
      },
      {
        .name = "text",
        .dataTypeSpecific.className = NULL,
        .number = HelloRequest_FieldNumber_Text,
        .hasIndex = 1,
        .offset = (uint32_t)offsetof(HelloRequest__storage_, text),
        .flags = GPBFieldRequired,
        .dataType = GPBDataTypeString,
      },
    };
    GPBDescriptor *localDescriptor =
        [GPBDescriptor allocDescriptorForClass:[HelloRequest class]
                                     rootClass:[MainRoot class]
                                          file:MainRoot_FileDescriptor()
                                        fields:fields
                                    fieldCount:(uint32_t)(sizeof(fields) / sizeof(GPBMessageFieldDescription))
                                   storageSize:sizeof(HelloRequest__storage_)
                                         flags:GPBDescriptorInitializationFlag_None];
    NSAssert(descriptor == nil, @"Startup recursed!");
    descriptor = localDescriptor;
  }
  return descriptor;
}

@end

#pragma mark - HelloResponse

@implementation HelloResponse

@dynamic hasRetcode, retcode;
@dynamic hasErrmsg, errmsg;

typedef struct HelloResponse__storage_ {
  uint32_t _has_storage_[1];
  int32_t retcode;
  NSString *errmsg;
} HelloResponse__storage_;

// This method is threadsafe because it is initially called
// in +initialize for each subclass.
+ (GPBDescriptor *)descriptor {
  static GPBDescriptor *descriptor = nil;
  if (!descriptor) {
    static GPBMessageFieldDescription fields[] = {
      {
        .name = "retcode",
        .dataTypeSpecific.className = NULL,
        .number = HelloResponse_FieldNumber_Retcode,
        .hasIndex = 0,
        .offset = (uint32_t)offsetof(HelloResponse__storage_, retcode),
        .flags = GPBFieldRequired,
        .dataType = GPBDataTypeInt32,
      },
      {
        .name = "errmsg",
        .dataTypeSpecific.className = NULL,
        .number = HelloResponse_FieldNumber_Errmsg,
        .hasIndex = 1,
        .offset = (uint32_t)offsetof(HelloResponse__storage_, errmsg),
        .flags = GPBFieldOptional,
        .dataType = GPBDataTypeString,
      },
    };
    GPBDescriptor *localDescriptor =
        [GPBDescriptor allocDescriptorForClass:[HelloResponse class]
                                     rootClass:[MainRoot class]
                                          file:MainRoot_FileDescriptor()
                                        fields:fields
                                    fieldCount:(uint32_t)(sizeof(fields) / sizeof(GPBMessageFieldDescription))
                                   storageSize:sizeof(HelloResponse__storage_)
                                         flags:GPBDescriptorInitializationFlag_None];
    NSAssert(descriptor == nil, @"Startup recursed!");
    descriptor = localDescriptor;
  }
  return descriptor;
}

@end

#pragma mark - Conversation

@implementation Conversation

@dynamic hasTopic, topic;
@dynamic hasNotice, notice;
@dynamic hasName, name;

typedef struct Conversation__storage_ {
  uint32_t _has_storage_[1];
  NSString *topic;
  NSString *notice;
  NSString *name;
} Conversation__storage_;

// This method is threadsafe because it is initially called
// in +initialize for each subclass.
+ (GPBDescriptor *)descriptor {
  static GPBDescriptor *descriptor = nil;
  if (!descriptor) {
    static GPBMessageFieldDescription fields[] = {
      {
        .name = "topic",
        .dataTypeSpecific.className = NULL,
        .number = Conversation_FieldNumber_Topic,
        .hasIndex = 0,
        .offset = (uint32_t)offsetof(Conversation__storage_, topic),
        .flags = GPBFieldRequired,
        .dataType = GPBDataTypeString,
      },
      {
        .name = "notice",
        .dataTypeSpecific.className = NULL,
        .number = Conversation_FieldNumber_Notice,
        .hasIndex = 1,
        .offset = (uint32_t)offsetof(Conversation__storage_, notice),
        .flags = GPBFieldRequired,
        .dataType = GPBDataTypeString,
      },
      {
        .name = "name",
        .dataTypeSpecific.className = NULL,
        .number = Conversation_FieldNumber_Name,
        .hasIndex = 2,
        .offset = (uint32_t)offsetof(Conversation__storage_, name),
        .flags = GPBFieldRequired,
        .dataType = GPBDataTypeString,
      },
    };
    GPBDescriptor *localDescriptor =
        [GPBDescriptor allocDescriptorForClass:[Conversation class]
                                     rootClass:[MainRoot class]
                                          file:MainRoot_FileDescriptor()
                                        fields:fields
                                    fieldCount:(uint32_t)(sizeof(fields) / sizeof(GPBMessageFieldDescription))
                                   storageSize:sizeof(Conversation__storage_)
                                         flags:GPBDescriptorInitializationFlag_None];
    NSAssert(descriptor == nil, @"Startup recursed!");
    descriptor = localDescriptor;
  }
  return descriptor;
}

@end

#pragma mark - ConversationListRequest

@implementation ConversationListRequest

@dynamic hasAccessToken, accessToken;
@dynamic hasType, type;

typedef struct ConversationListRequest__storage_ {
  uint32_t _has_storage_[1];
  int32_t type;
  NSString *accessToken;
} ConversationListRequest__storage_;

// This method is threadsafe because it is initially called
// in +initialize for each subclass.
+ (GPBDescriptor *)descriptor {
  static GPBDescriptor *descriptor = nil;
  if (!descriptor) {
    static GPBMessageFieldDescription fields[] = {
      {
        .name = "accessToken",
        .dataTypeSpecific.className = NULL,
        .number = ConversationListRequest_FieldNumber_AccessToken,
        .hasIndex = 0,
        .offset = (uint32_t)offsetof(ConversationListRequest__storage_, accessToken),
        .flags = GPBFieldRequired,
        .dataType = GPBDataTypeString,
      },
      {
        .name = "type",
        .dataTypeSpecific.className = NULL,
        .number = ConversationListRequest_FieldNumber_Type,
        .hasIndex = 1,
        .offset = (uint32_t)offsetof(ConversationListRequest__storage_, type),
        .flags = GPBFieldRequired,
        .dataType = GPBDataTypeInt32,
      },
    };
    GPBDescriptor *localDescriptor =
        [GPBDescriptor allocDescriptorForClass:[ConversationListRequest class]
                                     rootClass:[MainRoot class]
                                          file:MainRoot_FileDescriptor()
                                        fields:fields
                                    fieldCount:(uint32_t)(sizeof(fields) / sizeof(GPBMessageFieldDescription))
                                   storageSize:sizeof(ConversationListRequest__storage_)
                                         flags:GPBDescriptorInitializationFlag_None];
    NSAssert(descriptor == nil, @"Startup recursed!");
    descriptor = localDescriptor;
  }
  return descriptor;
}

@end

#pragma mark - Enum ConversationListRequest_FilterType

GPBEnumDescriptor *ConversationListRequest_FilterType_EnumDescriptor(void) {
  static GPBEnumDescriptor *descriptor = NULL;
  if (!descriptor) {
    static const char *valueNames =
        "Default\000All\000NearBy\000Friends\000Hot\000";
    static const int32_t values[] = {
        ConversationListRequest_FilterType_Default,
        ConversationListRequest_FilterType_All,
        ConversationListRequest_FilterType_NearBy,
        ConversationListRequest_FilterType_Friends,
        ConversationListRequest_FilterType_Hot,
    };
    GPBEnumDescriptor *worker =
        [GPBEnumDescriptor allocDescriptorForName:GPBNSStringifySymbol(ConversationListRequest_FilterType)
                                       valueNames:valueNames
                                           values:values
                                            count:(uint32_t)(sizeof(values) / sizeof(int32_t))
                                     enumVerifier:ConversationListRequest_FilterType_IsValidValue];
    if (!OSAtomicCompareAndSwapPtrBarrier(nil, worker, (void * volatile *)&descriptor)) {
      [worker release];
    }
  }
  return descriptor;
}

BOOL ConversationListRequest_FilterType_IsValidValue(int32_t value__) {
  switch (value__) {
    case ConversationListRequest_FilterType_Default:
    case ConversationListRequest_FilterType_All:
    case ConversationListRequest_FilterType_NearBy:
    case ConversationListRequest_FilterType_Friends:
    case ConversationListRequest_FilterType_Hot:
      return YES;
    default:
      return NO;
  }
}

#pragma mark - ConversationListResponse

@implementation ConversationListResponse

@dynamic listArray, listArray_Count;

typedef struct ConversationListResponse__storage_ {
  uint32_t _has_storage_[1];
  NSMutableArray *listArray;
} ConversationListResponse__storage_;

// This method is threadsafe because it is initially called
// in +initialize for each subclass.
+ (GPBDescriptor *)descriptor {
  static GPBDescriptor *descriptor = nil;
  if (!descriptor) {
    static GPBMessageFieldDescription fields[] = {
      {
        .name = "listArray",
        .dataTypeSpecific.className = GPBStringifySymbol(Conversation),
        .number = ConversationListResponse_FieldNumber_ListArray,
        .hasIndex = GPBNoHasBit,
        .offset = (uint32_t)offsetof(ConversationListResponse__storage_, listArray),
        .flags = GPBFieldRepeated,
        .dataType = GPBDataTypeMessage,
      },
    };
    GPBDescriptor *localDescriptor =
        [GPBDescriptor allocDescriptorForClass:[ConversationListResponse class]
                                     rootClass:[MainRoot class]
                                          file:MainRoot_FileDescriptor()
                                        fields:fields
                                    fieldCount:(uint32_t)(sizeof(fields) / sizeof(GPBMessageFieldDescription))
                                   storageSize:sizeof(ConversationListResponse__storage_)
                                         flags:GPBDescriptorInitializationFlag_None];
    NSAssert(descriptor == nil, @"Startup recursed!");
    descriptor = localDescriptor;
  }
  return descriptor;
}

@end


#pragma clang diagnostic pop

// @@protoc_insertion_point(global_scope)
