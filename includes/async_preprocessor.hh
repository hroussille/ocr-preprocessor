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

  AsyncPreprocessor(std::string inputPath , 
                    std::string outputPath , 
                    unsigned int blur ,
                    unsigned int threshold ,
                    unsigned int matrix ,
                    unsigned int constant ,
                    bool revert ,
                    bool isolate ,
                    Callback* callback);

  ~AsyncPreprocessor(); 

  void Execute();
  void HandleOKCallback();

  private:
 
  std::string  _inputPath;
  std::string  _outputPath;

  unsigned int _blur;
  unsigned int _threshold;
  unsigned int _matrix;
  unsigned int _constant;

  bool         _revert;
  bool         _isolate;
  bool         _result;

};

NAN_METHOD(preprocess);

#endif // ASYNCPREPROCESSOR_HH
