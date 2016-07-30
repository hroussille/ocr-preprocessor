#include <async_preprocessor.hh>
#include <preprocessor.hh>
#include <Params.hh>

AsyncPreprocessor::AsyncPreprocessor(std::string inputPath, 
                                     std::string outputPath, 
                                     Params params,
                                     Callback* callback)

    : _inputPath(inputPath)
    , _outputPath(outputPath)
    , _params(params)
    , AsyncWorker(callback)
{
  this->_result = false;
}

AsyncPreprocessor::~AsyncPreprocessor()
{
}

void AsyncPreprocessor::Execute()
{
  this->_result = preprocess(this->_inputPath, this->_outputPath , this->_params);
}

void AsyncPreprocessor::HandleOKCallback()
{
  HandleScope scope;

  Local<Value> argv[] = {
    Null(),
    New<v8::String>(this->_outputPath).ToLocalChecked()
  };

  if (this->_result == false)
    argv[0] = New<v8::String>(std::string("Error while preprocessing the image")).ToLocalChecked();

  callback->Call(2, argv);
}

NAN_METHOD(preprocess)
{

  Params params;
  v8::String::Utf8Value inputPathjs(info[0]->ToString());
  v8::String::Utf8Value outputPathjs(info[1]->ToString());

  params.blur         = info[2]->Uint32Value();
  params.threshold    = info[3]->Uint32Value();
  params.matrix       = info[4]->Uint32Value();
  params.constant     = info[5]->Uint32Value();
  params.revert       = info[6]->BooleanValue(); 
  params.isolate      = info[7]->BooleanValue(); 
  params.deskew       = info[8]->BooleanValue();
  params.matchCount   = info[9]->Uint32Value();
  params.ratio        = info[10]->NumberValue();
  params.lineStep     = info[11]->Uint32Value();
  Callback* callback  = new Callback(info[12].As<Function>());

  std::string inputPath   = std::string(*inputPathjs);
  std::string outputPath  = std::string(*outputPathjs);

  AsyncQueueWorker(new AsyncPreprocessor(inputPath, outputPath, params , callback));
}
