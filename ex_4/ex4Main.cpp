#include<iostream>
#include<string>
#include <chrono>
using namespace std;

//el char en promedio tarda la mitad de tiempo, mucho menos de la mitad. Se puede ver corriendo las funciones cuanto le tarda a cada una de ellas. 

bool compareStr(const string s1, const string s2, int i=0){
    if (s1[i]!=s2[i] || i > s1.length() || s1.length() != s2.length()){
        return false; 
    }else if(i==s1.length()){
        return true;
    }
    return compareStr (s1,s2,i+1);
}
 bool compareChar(char* s1, char* s2, int i=0){
    if(s1[i]!=s2[i]){
        return false;
    }
    if(s1[i] == '\0'){
        if(s2[i]== '\0'){
            return true;
        }
        return false;
    }
    if(s2[i]== '\0'){
        if(s1[i]== '\0'){
            return true;
        }
        return false;
    }
    return compareChar(s1,s2,i+1);
}
// bool  efficient_compareChar( char* s1,  char* s2, int i=0){
//     if(s1[i]!=s2[i]){
//         return false;
//     }
//     if(s1[i] == '\0'){
//         if(s2[i]== '\0'){
//             return true;
//         }
//         return false;
//     }
//     if(s2[i]== '\0'){
//         if(s1[i]== '\0'){
//             return true;
//         }
//         return false;
//     }
//     return efficient_compareChar(s1,s2,i+1);
// }

int main(){
    const string s1 = "Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    const string s2 = "Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    // const string s3 = "Modifique el código del ejercicio 4.2 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    // const string s4 = "Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de";

    // cout<<"Test: these strings are identical, it should say they are. Result: " <<endl;
    // if( compareStr(s1,s2)==true){
    //     cout<<"The strings are identical"<<endl;
    // }else{cout<<"The strings are not identical"<<endl;}

    // cout<<"\nTest: these strings differ by one character but have the same size, it should say they are different. Result: " <<endl;
    // if( compareStr(s1,s3)==true){
    //     cout<<"The strings are identical"<<endl;
    // }else{cout<<"The strings are not identical"<<endl;}

    // cout<<"\nTest: these strings differ and do not have the same size, it should say they are different. Result: " <<endl;
    // if( compareStr(s1,s4)==true){
    //     cout<<"The strings are identical"<<endl;
    // }else{cout<<"The strings are not identical"<<endl;}

    // auto startTime =  chrono::high_resolution_clock::now();
    //  compareStr(s1,s2);
    // auto endTime =  chrono::high_resolution_clock::now();
    // auto elapsedTime =  chrono::duration_cast< chrono::nanoseconds>(endTime - startTime);
    // cout << "\n\nA miProcesoAMedir le tomó:" << elapsedTime.count() << "nanosegundos" <<  endl;

    cout <<"\n\nCOMPARE CHARS";
    char* s5 = "Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    char* s6 = "Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    char* s7 = "Modifique el código del ejercicio 4.2 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    char* s8 = "Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de";
    cout<<"Test: these strings are identical, it should say they are. Result: " <<endl;
    if(  compareChar(s5,s6)==true){
        cout<<"The strings are identical"<<endl;
    }else{cout<<"The strings are not identical"<<endl;}

    cout<<"\nTest: these strings differ by one character but have the same size, it should say they are different. Result: " <<endl;
    if(  compareChar(s5,s7)==true){
        cout<<"The strings are identical"<<endl;
    }else{cout<<"The strings are not identical"<<endl;}

    cout<<"\nTest: these strings differ and do not have the same size, it should say they are different. Result: " <<endl;
    if(  compareChar(s5,s8)==true){
        cout<<"The strings are identical"<<endl;
    }else{cout<<"The strings are not identical"<<endl;}
    
    //EXECUTION MEAN TIME USING CHARS
    int numerator=0;
    for(int i=0; i<1000;i++){
        auto startTime =  chrono::high_resolution_clock::now();
        compareChar(s5,s6);
        auto endTime =  chrono::high_resolution_clock::now();
        auto elapsedTime =  chrono::duration_cast< chrono::nanoseconds>(endTime - startTime);
        numerator += elapsedTime.count();}
    int mean = numerator/1000;
    cout << "\n\nA compareChar le tomó:" << mean<< "nanosegundos promedio" <<  endl;

    //EXECUTION MEAN TIME USING STRINGS
    int numerator2=0;
    for(int i=0; i<1000;i++){
        auto startTime =  chrono::high_resolution_clock::now();
        compareStr(s1,s2);
        auto endTime =  chrono::high_resolution_clock::now();
        auto elapsedTime =  chrono::duration_cast< chrono::nanoseconds>(endTime - startTime);
        numerator2 += elapsedTime.count();}
    int mean2 = numerator2/1000;
    cout << "\n\nA comparestr le tomó:" << mean2<< "nanosegundos promedio" <<  endl;
    
}
// (c) Al ejecutar el codigo sin incluir el constexpr, 