#include <async_preprocessor.hh>
#include <preprocessor.hh>

AsyncPreprocessor::AsyncPreprocessor(std::string inputPath, 
                                     std::string outputPath, 
                                     unsigned int blur , 
                                     unsigned int threshold , 
                                     unsigned int matrix , 
                                     unsigned int constant , 
                                     bool revert ,
                                     bool isolate ,
                                     Callback* callback)

    : _inputPath(inputPath)
    , _outputPath(outputPath)
    , _blur(blur)
    , _threshold(threshold)
    , _matrix(matrix)
    , _constant(constant)
    , _revert(revert)
    , _isolate(isolate)
    , AsyncWorker(callback)
{
  this->_result = false;
}

AsyncPreprocessor::~AsyncPreprocessor()
{
}

void AsyncPreprocessor::Execute()
{
  this->_result = preprocess(this->_inputPath, this->_outputPath ,
      this->_blur , this->_threshold , this->_matrix , this->_constant,
      this->_revert , this->_isolate);
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

  unsigned int blur       = info[2]->Uint32Value();
  unsigned int threshold  = info[3]->Uint32Value();
  unsigned int matrix     = info[4]->Uint32Value();
  unsigned int constant   = info[5]->Uint32Value();
  bool revert             = info[6]->BooleanValue(); 
  bool isolate            = info[7]->BooleanValue(); 
  Callback* callback      = new Callback(info[8].As<Function>());

  std::string inputPath   = std::string(*inputPathjs);
  std::string outputPath  = std::string(*outputPathjs);

  AsyncQueueWorker(new AsyncPreprocessor(inputPath, outputPath, blur ,
        threshold, matrix, constant , revert , isolate ,callback));
}
