#include<iostream>
using namespace std;
// (a) La idea fue hacer vector de vectores (una matriz), y para lograr rellenar la matriz con los valores solicitados, incorpore un contador que vaya aumentando en 1 para incorporar cada valor en las pociciones de 1 a n del vector chico. Osea que como los vectores se van agregando de a uno, al final del vector general (que terminaria siendo la matriz), los numeros quedarian en el orden solicitado. 
//Si todos los punteros para los vectores se alocan correctamente en la memoria, la funcion devuelve una matriz. En el caso que falle se informa que el contenido no pudo ser guardado de manera correcta.

int** sqrMatrix(int n){
    int counter=1;//inicializo el contador, que van a ser los valores de cada pocision de mi matriz. 
    try{
        int** myMatrix = new int*[n];//guardo memoria para la matriz de vectores
        for (int i=0; i<n; i++){//Hago un for para asignar un vector a cada posicion de la matriz
            int* vector = new int[n];// guardo memoria para los vectores
            for (int j=0; j<n;j++){//hago un for para asignar un numero entero a cada posicion del vector, los valores.
                vector[j]=counter;
                counter ++;//aumento el contador para que el valor siguiente sea 1 mas que el anterior. 
            }
            myMatrix[i]=vector;//agrego el vector a la matriz

        }
        return myMatrix;}
    catch (const bad_alloc&){ //error en la alocacion de memoria.
        throw runtime_error("Memory coundlnt be allocated");
    }
}
//(b) Para imprimir la matriz desde el ultimo indice hasta el primero, la idea es poner un contador, que sea paralas  filas y unicamente baje cuando el contador de las columnas llegue a 0, osea hasta la primera columna. Alli, se reduce en una unidad el contador de las filas y se reinicia es de las columnas.Asi se logra recorrer la matriz del final al incio. 
//El contador se inicializa en n-1 porque los indices de la matriz van de 0 a n-1, para imprimir los indices como solicita el ejercicio se aumenta en una unidad esto a la hora de imprimir los indices. 
void printMatrix(int size ,int** myMatrix){
    if (myMatrix == nullptr){ //si la matriz esta vacia, te avisa que esta vacia y finaliza la funcion
        cout << "Error, null matrix" << endl;
        return;
    }
    int row = size-1;//El contador se inicializa en n-1 porque los indices de la matriz van de 0 a n-1
    for (int column=size-1; column>-1; column--){
        cout << "M [" << row+1 << "][" << column+1 << "] = " << myMatrix[row][column]<< " "<< endl;
        if (row != 0 && column == 0){//cuando se llega a la primera columna, se reinicia el contador de las columnas y se reduce en una unidad el de las filas. Esto sucede siempre que no este en la primera pocision([0][0]), alli se termina el for ya que la columna es 0 y termina la funcion. 
            row --;
            column=size;
        }     
    }
    return;
}
void deleteMatrix(int n, int** myMatrix){
    if (myMatrix == nullptr){
        delete[] myMatrix;
        return;
    }
    for (int i=0; i<n ;i++){
        delete[] myMatrix[i];
    }
    delete[] myMatrix;
    return;
}

int main(){
    int n; 
    cout << "Enter a whole number greater than 1" << endl; //se imprime lo que quiero que entre en el input 
    cin >> n; // se pide el input y se asigna a la variable de numero entero n
    try{
        if (n<1){ // si n es negativo tira error. 
            throw ("The number selected isn´t greater than 1" );
        }
        int** myMatrix = sqrMatrix(n);
        int** nullMatrix = nullptr;
        printMatrix(n,myMatrix);// imprime la matriz
        printMatrix(0,nullMatrix);// pueba matriz vacia
        printMatrix(4,nullMatrix);// prueba matriz vacia pasandole un parametro valido
        deleteMatrix(n,myMatrix);}//libera la memoria reservada para myMatrix. 
        catch(char const* e){//atrapa el throw previo e imprime su mensaje. 
            cout << "<[ERROR]"<< e <<">"<< endl;
        }
        return 0;
}