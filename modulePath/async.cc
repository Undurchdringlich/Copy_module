#include "async.h"
#include <fstream>
#include <string>

AsyncCopy::AsyncCopy(const Napi::CallbackInfo& info, string *ptrFiles)
    : arrayString(info[0].As<Napi::Array>()),
    location(info[1].As<Napi::String>()),
    callbackProgress(info[2].As<Napi::Function>()),
    Napi::AsyncWorker(info[3].As<Napi::Function>()),
    env(info.Env()),
    arrayLenght(arrayString.Length()),
    files(ptrFiles) {
        
    }

AsyncCopy::~AsyncCopy() {
    delete [] files;
    files = nullptr;
}

void AsyncCopy::Execute() {
    CopyFiles();
}

void AsyncCopy::OnOK() {
    Napi::HandleScope scope(env);
    Callback().Call({Napi::String::New(env, "All files are copied!")});
}

void AsyncCopy::CopyFiles() {
    char checkSymbol = '\\';

    for(int i = 0; i < arrayLenght; i++) {
        string nameFile = NameFileInPath(files[i], checkSymbol);
        ifstream fileTargetCopy(files[i], ios_base::in | ios_base::binary);
        ofstream fileTargetPaste(location + checkSymbol + nameFile, ios_base::out | ios_base::binary);

        char buf[BUF_SIZE];

        do {
            fileTargetCopy.read(&buf[0], BUF_SIZE);

            fileTargetPaste.write(&buf[0], fileTargetCopy.gcount());

        } while (fileTargetCopy.gcount() > 0);
        
        fileTargetCopy.close();
        fileTargetPaste.close();

        if(!fileTargetPaste.is_open()) {
            cout << "File " + files[i] + " copied" << endl;
        }
        
    }
}

void AsyncCopy::PrintProgress(Napi::Env env, Napi::Function printProgress, string path) {
  printProgress.Call(env.Global(), {
    Napi::String::New(env, "File " + path + " copied")
  });
}


string AsyncCopy::NameFileInPath(string path, char checkSymbol) {
    int checkLastSymbol = 0, checkPosition = 0, resultPosition = 0;

    while(path[checkLastSymbol] != '\0') {
        if(path[checkLastSymbol] == checkSymbol) {
            checkPosition = checkLastSymbol;
        }
        checkLastSymbol++;
    }

    char *result = new char[checkLastSymbol-checkPosition];

    for(int j = checkPosition; j < checkLastSymbol; j++) {
        result[resultPosition] = path[j+1];
        resultPosition++;
    }

    return result;
}

void CopyFileInDirectory(const Napi::CallbackInfo& info) {
    const Napi::Array arrayString = info[0].As<Napi::Array>();
    int arrayLenght = arrayString.Length();
    string *files = new string[arrayLenght];

    for(int i = 0; i < arrayLenght; i++) {
        files[i] = arrayString[i].ToString();
    }

    AsyncCopy *asyncCopy = new AsyncCopy(info, files);
    asyncCopy->Queue();
}


