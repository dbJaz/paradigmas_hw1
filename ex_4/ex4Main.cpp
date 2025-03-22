#include<iostream>
#include <chrono>
using namespace std;

// Mis funciones de comparacion son usando char ya que despues de una investigacion y leer comentarios de programadores, llegue a la conclusion que para este objetivo es mas util usar tipo char que string. 
//El string resulta mas facil de manejar, tienen mas metodos y son mas confiable mientras que los chars son mucho mas rapidos y eficientes ya que no deben estar accediendo a una biblioteca y no tienden a hacer copias ya que tienen punteros. 

 bool compareChar(const char* s1, const char* s2, int i=0){//se pasan ambas cadenas como constantes porque no las voy a modificar, y se pasan como punteros para que se pueda acceder al caracter en la posicion i de la cadena. 
    if(s1[i]!=s2[i] || (s1[i] == '\0' && s2[i]!=0) || (s2[i] == '\0' && s1[i]!=0)){
        return false;
    }
    else if (s1[i] == '\0' && s2[i] == '\0'){
        return true;
    }
    return compareChar(s1,s2,i+1);
}
constexpr bool  efficient_compareChar( const char* s1,  const char* s2, int i=0){ //exactyamente la misma funcion de antes pero se le agrega constexpr para que se calcule en tiempo de compliacion, y cuando el usuario quiera acceder a la informacion el programa corra mucho mas rapido ya que no se debe poner a calcular. El tiempo que tarda cada una de las funciones se compara mas adelante. 
    if(s1[i]!=s2[i] || (s1[i] == '\0' && s2[i]!=0) || (s2[i] == '\0' && s1[i]!=0)){
        return false;
    }
    else if (s1[i] == '\0' && s2[i] == '\0'){
        return true;
    }
    return efficient_compareChar(s1,s2,i+1);
}
int main(){
    const char* s5 = "Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
     const char* s6 = "Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    const char* s7 = "Modifique el código del ejercicio 4.2 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    const char* s8 = "Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de";
    constexpr const char* s9="Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    constexpr const char* s10="Modifique el código del ejercicio 4.1 para que la comparación de los textos sev realice en tiempo de compilación y obtenga el tiempo de ejecución";
    //arme cadenas para probar las funciones. Las ultimas dos tienen constexpr delante porque son las que se les pasara a la funcion eficiente, y le indica al compliador que las cadenas sean evaluadas en tiempo de compilacion.
    cout << "TESTS:"<<endl;
    cout<<" Test: these strings are identical, it should say they are. Result: " <<endl;
    if(  compareChar(s5,s6)==true){
        cout<<"     The strings are identical"<<endl;
    }else{cout<<"       The strings are not identical"<<endl;}

    cout<<"\n   Test: these strings differ by one character but have the same size, it should say they are different. Result: " <<endl;
    if(  compareChar(s5,s7)==true){
        cout<<"     The strings are identical"<<endl;
    }else{cout<<"       The strings are not identical"<<endl;}

    cout<<"\n   Test: these strings differ and do not have the same size, it should say they are different. Result: " <<endl;
    if(  compareChar(s5,s8)==true){
        cout<<"     The strings are identical"<<endl;
    }else{cout<<"       The strings are not identical"<<endl;}
    cout<<"\n----------------------------------------------------------"<<endl;
    cout << "\nMEAN TIME:"<<endl; //para que el tiempo de ejecucion se value de una manera veridica y confiable hago 1000 repeticiones y calculo el promedio.
    //EXECUTION MEAN TIME USING CHARS
    int numerator=0;
    for(int i=0; i<1000;i++){
        auto startTime =  chrono::high_resolution_clock::now();
        bool trial= compareChar(s5,s6);
        auto endTime =  chrono::high_resolution_clock::now();
        auto elapsedTime =  chrono::duration_cast< chrono::nanoseconds>(endTime - startTime);
        numerator += elapsedTime.count();}
    int mean = numerator/1000;
    cout << "It took compareChar: " << mean<< " mean nanoseconds " <<  endl;

    //EXECUTION MEAN TIME USING eficient 
    int numerator2=0;
    for(int i=0; i<1000;i++){
        auto startTime =  chrono::high_resolution_clock::now();
        constexpr const bool trial2 = efficient_compareChar(s9,s10);
        auto endTime =  chrono::high_resolution_clock::now();
        auto elapsedTime =  chrono::duration_cast< chrono::nanoseconds>(endTime - startTime);
        numerator2 += elapsedTime.count();}
    int mean2 = numerator2/1000;
    cout << "\nIt took eficient_compareChar: " << mean2<< " mean nanoseconds\n" <<  endl;
    
}