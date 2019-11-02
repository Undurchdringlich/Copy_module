#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;
using std::ios_base;

const static int BUF_SIZE = 4096;

void CopyFileInDirectory(const string *, const string, void (*f1)(string), void (*f2)(string));
string NameFileInPath(string);
void printProgress(string);
void printSuccess(string);

int main() {
    setlocale(0, "");

    const string files[3] = { "D:\\Programming\\test\\text.txt", "D:\\Programming\\test\\image.jpg", "D:\\Programming\\test\\radeon-software-adrenalin-2019-19.9.2-minimalsetup-190923_64bit.exe"};
    const string location = "D:\\Programming\\location";
    CopyFileInDirectory(files, location, printProgress, printSuccess);
}

void CopyFileInDirectory(const string *files, const string location, void (*printProgress)(string text), void (*printSuccess)(string text)) {
    int countFiles = sizeof(files)/sizeof(files[0]);
    cout << sizeof(files) << endl;
    countFiles = 3;
    for(int i = 0; i < countFiles; i++) {
        string nameFile = NameFileInPath(files[i]);
        ifstream fileTargetCopy(files[i], ios_base::in | ios_base::binary);
        ofstream fileTargetPaste(location + "\\" + nameFile, ios_base::out | ios_base::binary);
        
        char buf[BUF_SIZE];

         do {

            fileTargetCopy.read(&buf[0], BUF_SIZE); // Считываем максимум n байт в буфер,

            fileTargetPaste.write(&buf[0], fileTargetCopy.gcount()); // Записываем содержимое буфера

        } while (fileTargetCopy.gcount() > 0);
        fileTargetCopy.close();
        fileTargetPaste.close();

        printProgress("File: " + files[i] + " copied");
    }
    printSuccess("All files are copied!");
}

string NameFileInPath(string path) {
    int checkLastSymbol = 0, checkPosition = 0, resultPosition = 0;
    char checkSymbol = '\\';

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

void printProgress(string text) {
    cout << text << endl;
}

void printSuccess(string text) {
    cout << text << endl;
}