#include <iostream>
#include <nan.h>

void Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() != 3) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  v8::Isolate *isolate = info.GetIsolate();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();

  // for (int i = 0; i < info.Length(); i++) {
  //   if (!isalnum(info[0][i])) {
  //     Nan::ThrowTypeError("Wrong arguments");
  //     return;
  //   }
  // }
  
  double arg0 = info[0]->NumberValue(context).FromJust();
  double arg1 = info[1]->NumberValue(context).FromJust();

  v8::Local<v8::Number> num = Nan::New(arg0 + arg1);

  v8::Local<v8::String> deviceName = info[3].As<v8::String>();

  char *charDeviceName = new char[15];
  (*deviceName)->WriteUtf8(isolate, charDeviceName);
  
  std::string stringDeviceName;
  stringDeviceName.assign(charDeviceName);

  std::cout << stringDeviceName;
  delete charDeviceName;

  info.GetReturnValue().Set(num);
}

void Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context = exports->CreationContext();
  exports->Set(context,
               Nan::New("add").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Add)
                   ->GetFunction(context)
                   .ToLocalChecked());
}

NODE_MODULE(addon, Init)
