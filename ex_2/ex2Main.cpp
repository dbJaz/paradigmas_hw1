#include<iostream>
#include <fstream>
#include<stdexcept>
using namespace std;

//(a)Para poder agregar entradas a un archivo, arme dos funciones. Una que se ocupe de escribir en el archivo (writeOnFile), y otra que dependiendo del nivel de severidad recivido arme el mensaje que se registrara en el archivo. 
//Elegi usar switch y enum porque es mas eficiente y prolijo de ver antes que utilizar ifs y else ifs. Ademas, enums permite asociar rapidamente un numero a los niveles de severidad y en combinacion con switch ir cambiando facilmente entre los distintos casos.
int writeOnFile(string message, string fileName = "logFile.txt"){
    ofstream outfile(fileName, ios::app);//ofstream es la libreria para escribir archivos y el copamdo app, permite escribir al final del archivo sin borrar el contenido. 
    if (outfile.is_open()){//si se pudo abrir el archivo, se escrive el mensaje y luego se cierra 
        outfile << message << endl; 
        outfile.close(); 
        return 0;
    }else{//del caso contrario tira error 
        cout << "Couldnt open file" <<endl;
        return 1;}
}
int logMessage (string message, int severityLvl){

        if (severityLvl>5 || severityLvl<1){
            throw runtime_error("Severity level is not valid");
        }
    
    enum {DEBUG=1, INFO, WARNING, ERROR, CRITICAL};//asocia DEBUG,INFO,etc... a numeros empezando desde el 1
    switch (severityLvl){//ve a que caso pertenece el numero de nivel de severidad, el 1 seria debug y continuan en orden. Estos numeros fueron asignados por el enum. 
        case DEBUG:
            writeOnFile("[DEBUG]<" + message + ">", "logFile.txt");break;//se pone break porque sino sigue corriendo las siguentes lineas, y unicamente quiero que se corra el caso que coinsida con el nivel de severidad. 
        case INFO: 
            writeOnFile("[INFO]<" + message + ">", "logFile.txt");break;
        case WARNING: 
            writeOnFile("[WARNING]<" + message + ">", "logFile.txt");break;
        case ERROR: 
            writeOnFile("[ERROR]<" + message + ">", "logFile.txt");break;
        case CRITICAL: 
            writeOnFile("[CRITICAL]<" + message + ">", "logFile.txt");break;
        }
    return 0;
}
//(b) Las dos funciones que siguen unicamente escriben en el archivo que esta predeterminado. Usando sobrecarga de funciones es posible que cpp distinga que funcion quiero usar dependiendo de los parametros que le paso. Por eso cuando en main se llama a la funcion logMessage no siempre se corre el mismo codigo. Dependiendo si le pase un string y un int, dos strings y un int o dos strings el codigo corre las dintintas funciones. 
void logMessage (string message, string fileName, int codeLine){
    writeOnFile ("[LINE ERROR]<"+ message  + " in file " + fileName + ", at line "  + to_string(codeLine) + ">", "logFile.txt");
}
void logMessage (string message, string userName){
    writeOnFile ("[SECURITY]<" + message + ", log by " + userName +">", "logFile.txt");
}
int main(){
    //HAGO UNA EJECUCION AUTOMATICA, ES MAS LINDA LA INTERACTIVA :)
    try{
        logMessage("Debug",1);
        logMessage("Info",2);
        logMessage("Warning",3);
        logMessage("Error",4);
        logMessage("Critical",5);
        logMessage("Line error","file name",1);
        logMessage("Security","User name");
        logMessage("Runtime error",6);//para probar el programa interactivo comentar esta linea. 
    }
    catch(const runtime_error& e){// el error se lanza desde dentro de la funcion y se atrapa en main para que se corte el programa, de lo contrario se imprimiria el mensaje de error pero no se cortaria.
        cout << "[ERROR]<"<< e.what()<<">"<<endl;
        return 1; 
    }
    //---------------------------------------------------------------------------
    //COMIENZA EL PROGRAMA INTERACTIVO:
    enum {DEBUG=1, INFO, WARNING, ERROR, CRITICAL,SECURITY, LINE_ERROR};//uso el enum para asignarle un numero a cada una de estas cosas, para evitar que haya errores ortograficos cuando el usuario debe ingresar que tipo de error quiere registrar. Al asociar estos errores con un numero es mas simple utilizar switch para ir cambiando entre los diferentes logMessage dependiendo de lo que ingrese el usuario. 
    int elected;
    string message;
    string name;
    string fileName;
    int code_line;
        try{//pongo try para poder agarrar un error si se le pasa un numero incorrcto a la funcion. Esto podria ser en dos casos, que este fuera del rango de opciones, o que el usuario quiera loggear un error en un numero de linea negativo, lo cual no es posible. Luego al final, catch agarra los errores de tipo runtime error e imprime un mensaje de error, con el mensaje que se seteo con throw cuando se hizo saltar el error. Va a tirar mensajes distintos dependiendo cual fue el error del usuario. Luego el catch devuelve 1 para indicar que hubo un error. 
            while(true){//mientras no se precione el numero 8 (quit) se le sigue preguntando al usuario si quiere registrar mas mensajes en el archivo
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
                    throw runtime_error("That number is not part of the options");  
                }
                else if (8==elected){break;}

                switch (elected){
                    case DEBUG ://Al poner todos estos casos juntos si alguno de estos numeros es el que eligio el usuario se corre la funcion correspondiente. Al principio mi primera intucion fue poner case DEBUG || INFO || etc..., pero al correrlo me di cuenta que nunca entraba en esos casos. 
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
        }
        catch(runtime_error& e){// se hace referencia para no hacer una copia. 
            cout << "[ERROR]<"<< e.what() <<">"<< endl;//imprime los mensajes de los runtime_errors, la funcion .what() permite imprimir el mensaje de cada runtime error dependiendo cual hizo saltar el error.
            return 1;
        }     
    return 0;}