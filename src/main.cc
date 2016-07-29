#include <nan.h>
#include <async_preprocessor.hh>

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

NAN_MODULE_INIT(Init) {
  Set(target, New<String>("preprocess").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(preprocess)).ToLocalChecked());
}

NODE_MODULE(addon, Init)
