#include<iostream>
using namespace std;

int main(){
    int n; 
    cout << "Enter a whole number greater than 1" << endl; 
    cin >> n;
    if (n<1){
        cout << "The number selected inst greater than 1" << endl;
        return 1;
    }
    int** myMatrix = sqrMatrix(n);
    printMatrix(n,myMatrix);
    deleteMatrix(n,myMatrix);
    return 0;
}
int** sqrMatrix(int n){
    int counter=1;
    try{
        int** myMatrix = new int*[n];
        for (int i=0; i<n; i++){
            int* vector = new int[n];
            for (int j=0; j<n;j++){
                vector[j]=counter;
                counter ++;
            }
            myMatrix[i]=vector;

        }
        return myMatrix;}
    catch (const bad_alloc&){
        throw runtime_error("Memory coundlnt be allocated");
        return nullptr;
    }
}
void printMatrix(int n,int** myMatrix){
    if (myMatrix == nullptr){
        cout << "Error, null matrix" << endl;
    }
    int contador = n-1;
    for (int i=n-1; i>-1; i--){
        cout << "M [" << contador+1 << "][" << i+1 << "] = " << myMatrix[contador][i]<< " "<< endl;
        if (contador != 0 && i == 0){
            contador --;
            i=n;
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