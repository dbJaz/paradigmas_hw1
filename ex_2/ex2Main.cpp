#include<iostream>
#include <fstream>
using namespace std;

//FALTA PROBAR LAS COSAS
int main(){
    logMessage("This is a debug message", 1);
    logMessage("This is a info message", 2);
    logMessage("This is a warning message", 3);
    logMessage("This is a error message", 4);
    logMessage("This is a critical message", 5);
return 0;}

int writeOnFile(string message, string fileName){
    ofstream outfile("logFile.txt", ios::app);
    if (outfile.is_open()){
        outfile << message << endl; 
        outfile.close(); 
        return 0;
    }else{
        cout << "Couldnt open file" <<endl;
        return 1;}
}

void logMessage (string message, int severityLvl){

    enum {DEBUG=1, INFO, WARNING, ERROR, CRITICAL};
    switch (severityLvl){
        case DEBUG:
            writeOnFile("[DEBUG]<" + message + ">", "logFile.txt");break; 
        case INFO: 
            writeOnFile("[INFO]<" + message + ">", "logFile.txt");break;
        case WARNING: 
            writeOnFile("[WARNING]<" + message + ">", "logFile.txt");break;
        case ERROR: 
            writeOnFile("[ERROR]<" + message + ">", "logFile.txt");break;
        case CRITICAL: 
            writeOnFile("[CRITICAL]<" + message + ">", "logFile.txt");break;
        }
}
//FALTA TRY Y CATCH 

void logMessage (string message, string fileName, int codeLine){
    writeOnFile ("<"+ message  + "in file" + fileName + ",at line"  + to_string(codeLine) + ">", fileName);
}
void logMessage (string message, string fileName, string userName){
    writeOnFile ("[SECURITY]<" + message + ", log by " + userName +">", fileName);
}
