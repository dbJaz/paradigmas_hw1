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


shared_ptr<Node> create_node(int value){
        shared_ptr<Node> newNode = make_shared<Node>();
        newNode->next= nullptr; 
        newNode->value=value;
        return newNode; 
}
void push_front(shared_ptr<List>& lst, int value){
    shared_ptr<Node> newNode = create_node(value);
    if (lst->head == nullptr){
        lst->head = newNode;
    }else{
        newNode->next = lst->head;
        lst->head= newNode;
    }
    lst->size ++;
    //TE FALTA SIZE++!!!!!!!!!!!
    //Tu print list funciona a partur de list->size, por eso no imprime
}
void push_back(shared_ptr<List>& lst, int value){
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
void insert(int position, shared_ptr<List> lst, shared_ptr<Node> node){
    if (position <= 1){
        if(position<=0){
        cout << "The position given is lower tha 1, the node will be inserted at the beguining of the list"<< endl;}
        if (lst->size> 0){
            node->next = lst->head;
        }
        lst->head = node;
        lst->size ++;
        return;
    }
    if (lst->size < position){
        cout << "The position given exeeds the list size, the node will be inserted at the end in position" + to_string(lst->size) << endl;
        position = lst->size +1;
    }

    shared_ptr<Node> current = lst->head;
    for (int i=1; i<position-1; i++){
        current = current->next;
    }
    node->next = current->next;
    current->next = node;
    lst->size ++;
    return;
}
void erase(int position, shared_ptr<List> lst){
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
void print_list(shared_ptr<List> lst){
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
    cout << "\n\nPruebo push_front \n" ;
    shared_ptr<List> lst_front = make_shared <List>();
    for(int i = 34; i < 40; i++){
        push_front(lst_front,i);
    }
    cout<<"pruebo imprimir la lista de mayor a menor, push_front\n";
    //Anda a la funcion push_front ;)
    print_list(lst_front);

    // pruebo imprimir la lista de menor a mayor. 
    cout << "\n\nPruebo push_back \n" ;
    cout<<"pruebo imprimir la lista de menor a mayor, push_back\n";
    shared_ptr<List> lst_back = make_shared <List>();
    for(int i = 34; i < 40; i++){
        push_back(lst_back,i);
    }
    print_list(lst_back);

//insert
    cout << "\n\nPruebo insert \n" ;
    insert(1,lst_front,create_node(50));
    cout << "Pruebo insertando 50 en la pocicion 1:  " ;
    print_list(lst_front);

    cout << "Pruebo pasando una pocision negativa,70: \n" ;
    insert(-4,lst_front,create_node(70));
    print_list(lst_front);

    cout << "Pruebo pasando una pocision mayor a la lista,80: \n" ;
    insert(10,lst_front,create_node(80));
    print_list(lst_front);

    cout << "Pruebo insertando 60 en la pocicion 4: " ;
    insert(4,lst_front,create_node(60));
    print_list(lst_front);

//erase
    cout << "\nPruebo erase \n" ;
    erase(1,lst_back);
    cout << "Pruebo eliminando  la pocicion 1: " ;
    print_list( lst_back);

    cout << "Pruebo pasando una pocision negativa deberia eliminar la primera posicion: \n" ;
    erase(-4, lst_back);
    print_list( lst_back);

    cout << "Pruebo eliminando  la pocicion 4: " ;
    erase(4, lst_back);
    print_list( lst_back);

    cout << "Pruebo eliminando  la pocicion 2: " ;
    erase(2, lst_back);
    print_list( lst_back);

    cout << "Pruebo eliminando  la pocicion 8: " ;
    erase(8, lst_back);
    print_list( lst_back);




    return 0;
}
