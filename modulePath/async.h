#ifndef ASYNC_H
#define ASYNC_H

#include <iostream>
#include <napi.h>

using namespace std;

void CopyFileInDirectory(const Napi::CallbackInfo&);

class AsyncCopy : public Napi::AsyncWorker {
    public:
        AsyncCopy(const Napi::CallbackInfo& info, string*);
        ~AsyncCopy();

        void Execute();
        void OnOK();
    private:
        const static int BUF_SIZE = 4096;
        Napi::Env env;
        Napi::Function callbackProgress;
        string location;
        const Napi::Array arrayString;
        string *files;
        const int arrayLenght;
        void CopyFiles();
        void PrintProgress(Napi::Env, Napi::Function, string);
        string NameFileInPath(string, char);
};

#endif  // ASYNC_H