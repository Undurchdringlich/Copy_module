#include <napi.h>
#include "async.h"

//-----------------------Initialization start---------------------------//
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "copy"), Napi::Function::New(env, CopyFileInDirectory));
  return exports;
}

NODE_API_MODULE(cp_module, Init)
//-----------------------Initialization end-----------------------------//