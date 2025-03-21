#include <iostream>
#include <memory>
using namespace std;

struct Node{
    int value;
    shared_ptr<Node> next;
};
struct List{
    int size; 
    shared_ptr<Node> head;
} ;

//Para implemetar todas las funciones basicas de una lista elegi usar shared pointers en luagar de unique pointers porque me parecieron mas simples de manejar, debido a que puedo tener mas de un elemento apuntandolos y no debo usar move(). 
shared_ptr<Node> create_node(int value){ //Hago una funcion que pasandole el valor que se quiere ingresar e el nodo, lo incialice apuntando a null pointer ya que aun no esta metido dentro de una lista y no hay ningun nodo siguiente. Tambien se inciializa el valor del nodo al pasado. 
        shared_ptr<Node> newNode = make_shared<Node>();
        newNode->next= nullptr; 
        newNode->value=value;
        return newNode; 
}
void push_front(shared_ptr<List>& lst, int value){ // para insertar un nodo al comienzo de una lista, se pide que se pasa la direccion a la lista, y el valor que se quiere insertar al comienzo. Hago referencia a la lista para no hacer una copia. 
    shared_ptr<Node> newNode = create_node(value);
    if (lst->head == nullptr){//se se pasa una lista vacia, simplemente se cambia la cabeza de lista al nuevo nodo , de no ser asi, primero hay que hacer que edl nuevo nodo apunte a la cabeza de lista. y luego reemplazar la cabeza de lista por el nuevo nodo. De hacerlo alrevez, cuando nada esta apuntando al shared  pointer que estaba en la cabeza de lista, se va a eliminar automaticamente.
        lst->head = newNode;
    }else{
        newNode->next = lst->head;
        lst->head= newNode;
    }
    lst->size ++;
}
void push_back(shared_ptr<List>& lst, int value){//similarmente a la anterior si esta vacia se la cabeza de lista se actualiza al nuevo nodo. De no ser asi, se crea el puntero current para recorrer la lista hasta el final, hasta que el siguiente de current sea null. Alli se agrega el nuevo nodo despues de current
    shared_ptr<Node> newNode = create_node(value);
    if (lst->head == nullptr){
        lst->head = newNode;
    }else{
        shared_ptr<Node> current = lst->head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
    }
    lst->size++;
}
void insert(int position, shared_ptr<List> lst, shared_ptr<Node> node){// para insertar un nodo en el medio primero hayq eu chequear que la posiscion que se paso es valida, no puede ser 0 o mas chica y no debe exeder el tamaño de la lista. En estos casos especiaales informa al usuario de o sucedido y dependiendo si se paso o si puso un numero negativo se va a insertar el nodod al final o principio de la lista.  

    if (position <= 1){
        if(position<=0){
        cout << "[ERROR]<The position given is lower than 1, the node will be inserted at the beguining of the list>"<< endl;}
        if (lst->size> 0){
            node->next = lst->head;
        }
        lst->head = node;
        lst->size ++;
        return;//si la posiscion es 1 o 0 asigna el nodo y termina.
    }
    if (lst->size < position){
        cout << "[ERROR]<The position given exeeds the list size, the node will be inserted at the end in position " <<lst->size <<">" << endl;
        position = lst->size +1;//se reajusta la posiscion para que sea la posicion siguiente al final de la lista.
    }

    shared_ptr<Node> current = lst->head;// creo una variable para iterar y llegar al puntero previo a la posicion dada 
    for (int i=1; i<position-1; i++){
        current = current->next;
    }
    node->next = current->next;
    current->next = node;
    lst->size ++;
    return;
}
void erase(int position, shared_ptr<List>& lst){//para eliminar un noso hay que primero descartar los casos imposibles de la posicion y reacomodarlo a dopnde corresponde.
    if (lst->size == 0){
        cout << "The list is already empty"<<endl;
        return;}
    if (position<=1){
        if(position<=0){
            cout << "The position given is lower than 1, the node deleted will be the list head"<< endl;}
        if (lst->size>1){
            lst->head=lst->head->next;
        }else{
            lst->head->next = nullptr;
            lst->head=nullptr;}
        lst->size--;
        return;
    }
    if (position > lst->size){
        cout << "The position given exeeds the list size, the last node will be deleted" << endl;
        position = lst->size; 
    }
    shared_ptr<Node> current = lst->head;
    for (int i=1; i<position-1 ;i++){
        current=current->next;
    }
    if (current->next->next == nullptr){
        current->next = nullptr;
        lst->size --;
        return;
    }
    current->next = current->next->next; 
    lst->size --;
    return;
}
void print_list(shared_ptr<List> lst){//Para imprimir la lista, se itera hasta el ultimo nodo. Si es el primer nodo no se le agrega la flecha adelante y si es el ultimo (el largo de la lista menos uno porque se empieza en 0) cambio de linea por prolijidad.
    shared_ptr<Node> current = lst->head;
    for (int i=0; i<lst->size; i++){
        if (i== 0){
            cout << current->value;
        }else if (i == lst->size -1){
            cout << "->" + to_string(current->value) << endl;
        }else{
            cout << "->" + to_string(current->value) ;
        }
        current=current->next;
    }
}

int main()
{
    // pruebo imprimir la lista de mayor a menor. 
    cout << "\nPush_front \n" ;
    shared_ptr<List> lst_front = make_shared <List>();
    for(int i = 34; i < 40; i++){
        push_front(lst_front,i);
    }

    cout<<" Print list from highest to lower, push_front:    ";
    //Anda a la funcion push_front ;)
    print_list(lst_front);

    // pruebo imprimir la lista de menor a mayor. 
    cout<<"\n|--------------------------------------------------------------------------------------|";
    cout << "\nPush_back \n" ;
    cout<<" Print list from lower to highest, push_back:    ";
    shared_ptr<List> lst_back = make_shared <List>();
    for(int i = 34; i < 40; i++){
        push_back(lst_back,i);
    }
    print_list(lst_back);

    //insert
    cout<<"\n|--------------------------------------------------------------------------------------|";
    cout << "\nInsert \n" ;
    insert(1,lst_front,create_node(50));
    cout << "   Test: Insert 50 in position 1: " ;
    print_list(lst_front);

    cout << "   Test: Passing a negative number and inserting 70: \n" ;
    insert(-4,lst_front,create_node(70));
    print_list(lst_front);

    cout << "   Test: Passing a posotion greater than the list size and inserting 80: \n" ;
    insert(10,lst_front,create_node(80));
    print_list(lst_front);

    cout << "   Test: Insert 60 in position 4:  " ;
    insert(4,lst_front,create_node(60));
    print_list(lst_front);
    cout<<"\n|--------------------------------------------------------------------------------------|";
    //erase
    cout << "\nErase \n" ;
    erase(1,lst_back);
    cout << "   Test: erase position 1: " ;
    print_list( lst_back);

    cout << "   Test: Pass a negative position:  "<<endl ;
    erase(-4, lst_back);
    print_list( lst_back);

    cout << "   Test: erase position 4, last one: " ;
    erase(4, lst_back);
    print_list( lst_back);

    cout << "   Test: erase position 2, in the middle:  " ;
    erase(2, lst_back);
    print_list( lst_back);

    cout << "   Test: erase position 8 wich is greater than list size: " ;
    erase(8, lst_back);
    print_list( lst_back);

    return 0;
}
