#include <iostream>
#include <fstream>
#include <string>
#include <napi.h>

using namespace std;
using std::ios_base;

const static int BUF_SIZE = 4096;

void CopyFileInDirectory(const Napi::CallbackInfo&);
void PrintProgress(const Napi::CallbackInfo&, string);
void PrintSuccess(const Napi::CallbackInfo&);
string NameFileInPath(string, char);


//------------------------Main function(start)--------------------------//
void CopyFileInDirectory(const Napi::CallbackInfo& info) {
  const Napi::Array arrayString = info[0].As<Napi::Array>();
  const int arrayLenght =  arrayString.Length();
  string *files = new string[arrayLenght];
  string location = info[1].As<Napi::String>();
  char checkSymbol = '\\';

  for(int i = 0; i < arrayLenght; i++) {
    *(files+i) = arrayString[i].ToString();
  }


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

    PrintProgress(info, files[i]);
  }
  PrintSuccess(info);
}

void TraslateInBasicString(const Napi::CallbackInfo& info, string& result) {

}

//---------------Callback function "Progress"(start)--------------------//
void PrintProgress(const Napi::CallbackInfo& info, string path) {
  Napi::Env env = info.Env();
  Napi::Function printProgress = info[2].As<Napi::Function>();
  printProgress.Call(env.Global(), {
    Napi::String::New(env, "File " + path + " copied")
  });
}
//----------------Callback function "Progress"(end)---------------------//


//----------------Callback function "Success"(start)--------------------//
void PrintSuccess(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Function printSuccess = info[3].As<Napi::Function>();
  printSuccess.Call(env.Global(), {
    Napi::String::New(env, "All files are copied!")
  });
}
//----------------Callback function "Success"(end)---------------------//


//-----------------Check name file in path(start)-------------=--------//
string NameFileInPath(string path, char checkSymbol) {
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
//------------------Check name file in path(end)-----------------------//


//-----------------------Initialization start---------------------------//
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "copy"), Napi::Function::New(env, CopyFileInDirectory));
  return exports;
}

NODE_API_MODULE(cp_module, Init)
//-----------------------Initialization end-----------------------------//