#include <async_preprocessor.hh>
#include <preprocessor.hh>

AsyncPreprocessor::AsyncPreprocessor(std::string inputPath, std::string outputPath, Callback* callback)
    : _inputPath(inputPath)
    , _outputPath(outputPath)
    , AsyncWorker(callback)
{
  this->_result = false;
}

AsyncPreprocessor::~AsyncPreprocessor()
{
}

void AsyncPreprocessor::Execute()
{
  this->_result = preprocess(this->_inputPath, this->_outputPath);
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
  v8::String::Utf8Value inputPathjs(info[0]->ToString());
  v8::String::Utf8Value outputPathjs(info[1]->ToString());

  std::string inputPath = std::string(*inputPathjs);
  std::string outputPath = std::string(*outputPathjs);

  Callback* callback = new Callback(info[2].As<Function>());
  AsyncQueueWorker(new AsyncPreprocessor(inputPath, outputPath, callback));
}
