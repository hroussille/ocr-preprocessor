#ifndef ASYNCPREPROCESSOR_HH
#define ASYNCPREPROCESSOR_HH

#include <nan.h>

using v8::Function;
using v8::Local;
using v8::Number;
using v8::Value;
using v8::String;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;

class AsyncPreprocessor: public AsyncWorker {

  public:

  AsyncPreprocessor(std::string inputPath , std::string outputPath , Callback* callback);
  ~AsyncPreprocessor(); 

  void Execute();
  void HandleOKCallback();

  private:
 
  std::string _inputPath;
  std::string _outputPath;
  bool _result;

};

NAN_METHOD(preprocess);

#endif // ASYNCPREPROCESSOR_HH
