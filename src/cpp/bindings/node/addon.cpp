#include <napi.h>
#include "skill_engine.h"
#include "file_processor.h"
#include "pattern_scanner.h"

using namespace claude::skills;

Napi::Value ReadFile(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return env.Null();
    }
    std::string path = info[0].As<Napi::String>().Utf8Value();
    std::string content = FileProcessor::readFile(path);
    return Napi::String::New(env, content);
}

Napi::Value ListFiles(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return env.Null();
    }
    std::string dir = info[0].As<Napi::String>().Utf8Value();
    std::string ext = info.Length() > 1 && info[1].IsString() 
                     ? info[1].As<Napi::String>().Utf8Value() 
                     : "";
    auto files = FileProcessor::listFiles(dir, ext);
    Napi::Array result = Napi::Array::New(env, files.size());
    for (size_t i = 0; i < files.size(); ++i) {
        result[i] = Napi::String::New(env, files[i]);
    }
    return result;
}

// Аналогично для других методов

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("readFile", Napi::Function::New(env, ReadFile));
    exports.Set("listFiles", Napi::Function::New(env, ListFiles));
    return exports;
}

NODE_API_MODULE(claude_skills, Init)