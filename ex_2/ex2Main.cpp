#include<iostream>
#include <fstream>
using namespace std;


int writeOnFile(string message, string fileName = "logFile.txt"){
    ofstream outfile(fileName, ios::app);
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
void logMessage (string message, string fileName, int codeLine){
    writeOnFile ("[LINE ERROR]<"+ message  + " in file " + fileName + ", at line "  + to_string(codeLine) + ">", "logFile.txt");
}
void logMessage (string message, string userName){
    writeOnFile ("[SECURITY]<" + message + ", log by " + userName +">", "logFile.txt");
}
int main(){
    enum {DEBUG=1, INFO, WARNING, ERROR, CRITICAL,SECURITY, LINE_ERROR};
        try{
            int elected;
            string message;
            string name;
            string fileName;
            int code_line;

            while(true){
                cout << "\nWhat type of issue do you want to register?\n"<<endl;
                cout<< "1- [DEBUG]"<<endl;
                cout<< "2- [INFO]"<<endl;
                cout<< "3- [WARNING]"<<endl;
                cout<< "4- [ERROR]"<<endl;
                cout<< "5- [CRITICAL]"<<endl;
                cout<< "6- [SECURITY]"<<endl;
                cout<< "7- [REPORT LINE ERROR]"<<endl;
                cout<< "8- QUIT\n"<<endl;
                cin>> elected;
                if(elected>8 || elected<1){
                    throw runtime_error("That numbers is not part of the options");  
                }//probar si es int
                // if(elected>8 || elected<1){
                //     throw "That numbers is not part of the options";  
                // }//probar si es int
                else if (8==elected){break;}

                switch (elected){
                    case DEBUG :
                    case INFO :
                    case WARNING:
                    case ERROR: 
                    case CRITICAL:
                        cout <<"\n Write a message for the file: "<<endl;
                        cin>> message;
                        logMessage(message,elected );
                        break;
                    case SECURITY: 
                        cout << "\n What is your name?:"<<endl;
                        cin >> name;
                        logMessage("Access permitted", name);//poner contraseña?
                        break;
                    case LINE_ERROR: 
                        cout<< "\nWhat is the file name?"<<endl;
                        cin >> fileName;
                        cout<< "\nWhat is the line?"<<endl;
                        cin >> code_line;
                        if(code_line <1){
                            throw runtime_error("The code line cant be a negative number.");
                        }
                        logMessage("Segmentation fault",fileName,code_line);
                        break;
                    }
            }    
        }catch(runtime_error e){
            cout << "<[ERROR] "<< e.what() <<">"<< endl;}
        // catch(consy char* e){
        //     cout << "<[ERROR] "<< e <<">"<< endl;}      
    return 0;}