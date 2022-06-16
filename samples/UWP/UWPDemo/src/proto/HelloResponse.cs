// Generated by ProtoGen, Version=2.3.0.277, Culture=neutral, PublicKeyToken=17b3b1f090c3ea48.  DO NOT EDIT!
#pragma warning disable 1591, 0612
#region Designer generated code

using pb = global::Google.ProtocolBuffers;
using pbc = global::Google.ProtocolBuffers.Collections;
using pbd = global::Google.ProtocolBuffers.Descriptors;
using scg = global::System.Collections.Generic;
namespace com.tencent.marsMulti.sample.proto {
  
  namespace Proto {
    
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("ProtoGen", "2.3.0.277")]
    public static partial class HelloResponse {
    
      #region Extension registration
      public static void RegisterAllExtensions(pb::ExtensionRegistry registry) {
      }
      #endregion
      #region Static variables
      #endregion
      #region Extensions
      internal static readonly object Descriptor;
      static HelloResponse() {
        Descriptor = null;
      }
      #endregion
      
    }
  }
  #region Messages
  [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
  [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
  [global::System.CodeDom.Compiler.GeneratedCodeAttribute("ProtoGen", "2.3.0.277")]
  public sealed partial class HelloResponse : pb::GeneratedMessageLite<HelloResponse, HelloResponse.Builder> {
    private HelloResponse() { }
    private static readonly HelloResponse defaultInstance = new HelloResponse().MakeReadOnly();
    private static readonly string[] _helloResponseFieldNames = new string[] { "errmsg", "retcode" };
    private static readonly uint[] _helloResponseFieldTags = new uint[] { 18, 8 };
    public static HelloResponse DefaultInstance {
      get { return defaultInstance; }
    }
    
    public override HelloResponse DefaultInstanceForType {
      get { return DefaultInstance; }
    }
    
    protected override HelloResponse ThisMessage {
      get { return this; }
    }
    
    public const int RetcodeFieldNumber = 1;
    private bool hasRetcode;
    private int retcode_;
    public int Retcode {
      get { return retcode_; }
    }
    
    public const int ErrmsgFieldNumber = 2;
    private bool hasErrmsg;
    private string errmsg_ = "";
    public string Errmsg {
      get { return errmsg_; }
    }
    
    public override bool IsInitialized {
      get {
        if (!hasRetcode) return false;
        return true;
      }
    }
    
    public override void WriteTo(pb::ICodedOutputStream output) {
      int size = SerializedSize;
      string[] field_names = _helloResponseFieldNames;
      if (hasRetcode) {
        output.WriteInt32(1, field_names[1], Retcode);
      }
      if (hasErrmsg) {
        output.WriteString(2, field_names[0], Errmsg);
      }
    }
    
    private int memoizedSerializedSize = -1;
    public override int SerializedSize {
      get {
        int size = memoizedSerializedSize;
        if (size != -1) return size;
        
        size = 0;
        if (hasRetcode) {
          size += pb::CodedOutputStream.ComputeInt32Size(1, Retcode);
        }
        if (hasErrmsg) {
          size += pb::CodedOutputStream.ComputeStringSize(2, Errmsg);
        }
        memoizedSerializedSize = size;
        return size;
      }
    }
    
    #region Lite runtime methods
    public override int GetHashCode() {
      int hash = GetType().GetHashCode();
      if (hasRetcode) hash ^= retcode_.GetHashCode();
      if (hasErrmsg) hash ^= errmsg_.GetHashCode();
      return hash;
    }
    
    public override bool Equals(object obj) {
      HelloResponse other = obj as HelloResponse;
      if (other == null) return false;
      if (hasRetcode != other.hasRetcode || (hasRetcode && !retcode_.Equals(other.retcode_))) return false;
      if (hasErrmsg != other.hasErrmsg || (hasErrmsg && !errmsg_.Equals(other.errmsg_))) return false;
      return true;
    }
    
    public override void PrintTo(global::System.IO.TextWriter writer) {
      PrintField("retcode", hasRetcode, retcode_, writer);
      PrintField("errmsg", hasErrmsg, errmsg_, writer);
    }
    #endregion
    
    public static HelloResponse ParseFrom(byte[] data) {
      return ((Builder) CreateBuilder().MergeFrom(data)).BuildParsed();
    }
    private HelloResponse MakeReadOnly() {
      return this;
    }
    
    public static Builder CreateBuilder() { return new Builder(); }
    public override Builder ToBuilder() { return CreateBuilder(this); }
    public override Builder CreateBuilderForType() { return new Builder(); }
    public static Builder CreateBuilder(HelloResponse prototype) {
      return new Builder(prototype);
    }
    
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("ProtoGen", "2.3.0.277")]
    public sealed partial class Builder : pb::GeneratedBuilderLite<HelloResponse, Builder> {
      protected override Builder ThisBuilder {
        get { return this; }
      }
      public Builder() {
        result = DefaultInstance;
        resultIsReadOnly = true;
      }
      internal Builder(HelloResponse cloneFrom) {
        result = cloneFrom;
        resultIsReadOnly = true;
      }
      
      private bool resultIsReadOnly;
      private HelloResponse result;
      
      private HelloResponse PrepareBuilder() {
        if (resultIsReadOnly) {
          HelloResponse original = result;
          result = new HelloResponse();
          resultIsReadOnly = false;
          MergeFrom(original);
        }
        return result;
      }
      
      public override bool IsInitialized {
        get { return result.IsInitialized; }
      }
      
      protected override HelloResponse MessageBeingBuilt {
        get { return PrepareBuilder(); }
      }
      
      public override Builder Clear() {
        result = DefaultInstance;
        resultIsReadOnly = true;
        return this;
      }
      
      public override Builder Clone() {
        if (resultIsReadOnly) {
          return new Builder(result);
        } else {
          return new Builder().MergeFrom(result);
        }
      }
      
      public override HelloResponse DefaultInstanceForType {
        get { return global::com.tencent.marsMulti.sample.proto.HelloResponse.DefaultInstance; }
      }
      
      public override HelloResponse BuildPartial() {
        if (resultIsReadOnly) {
          return result;
        }
        resultIsReadOnly = true;
        return result.MakeReadOnly();
      }
      
      public override Builder MergeFrom(pb::IMessageLite other) {
        if (other is HelloResponse) {
          return MergeFrom((HelloResponse) other);
        } else {
          base.MergeFrom(other);
          return this;
        }
      }
      
      public override Builder MergeFrom(HelloResponse other) {
      return this;
      }
      
      public override Builder MergeFrom(pb::ICodedInputStream input) {
        return MergeFrom(input, pb::ExtensionRegistry.Empty);
      }
      
      public override Builder MergeFrom(pb::ICodedInputStream input, pb::ExtensionRegistry extensionRegistry) {
        PrepareBuilder();
        uint tag;
        string field_name;
        while (input.ReadTag(out tag, out field_name)) {
          if(tag == 0 && field_name != null) {
            int field_ordinal = global::System.Array.BinarySearch(_helloResponseFieldNames, field_name, global::System.StringComparer.Ordinal);
            if(field_ordinal >= 0)
              tag = _helloResponseFieldTags[field_ordinal];
            else {
              ParseUnknownField(input, extensionRegistry, tag, field_name);
              continue;
            }
          }
          switch (tag) {
            case 0: {
              throw pb::InvalidProtocolBufferException.InvalidTag();
            }
            default: {
              if (pb::WireFormat.IsEndGroupTag(tag)) {
                return this;
              }
              ParseUnknownField(input, extensionRegistry, tag, field_name);
              break;
            }
            case 8: {
              result.hasRetcode = input.ReadInt32(ref result.retcode_);
              break;
            }
            case 18: {
              result.hasErrmsg = input.ReadString(ref result.errmsg_);
              break;
            }
          }
        }
        
        return this;
        }
        
        
        public int Retcode {
          get { return result.Retcode; }
          set { SetRetcode(value); }
        }
        public Builder SetRetcode(int value) {
          PrepareBuilder();
          result.hasRetcode = true;
          result.retcode_ = value;
          return this;
        }
        public Builder ClearRetcode() {
          PrepareBuilder();
          result.hasRetcode = false;
          result.retcode_ = 0;
          return this;
        }
        
        public string Errmsg {
          get { return result.Errmsg; }
          set { SetErrmsg(value); }
        }
        public Builder SetErrmsg(string value) {
          pb::ThrowHelper.ThrowIfNull(value, "value");
          PrepareBuilder();
          result.hasErrmsg = true;
          result.errmsg_ = value;
          return this;
        }
        public Builder ClearErrmsg() {
          PrepareBuilder();
          result.hasErrmsg = false;
          result.errmsg_ = "";
          return this;
        }
      }
      static HelloResponse() {
        object.ReferenceEquals(global::com.tencent.marsMulti.sample.proto.Proto.HelloResponse.Descriptor, null);
      }
    }
    
    #endregion
    
  }
  
  #endregion Designer generated code
