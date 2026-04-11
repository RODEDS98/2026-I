#include <iostream>
#include <stdexcept>
using namespace std;

class Node
{
public:
    Node(int value);

    int data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList
{
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    
    void push_front(int value);
    void push_back(int value);
    void pop_front();
    void pop_back();
    void print();
    
    Node* get_head();
    Node* get_tail();
    
    void split_list(Node* pivot);

private:
    Node* head;
    Node* tail;
};

Node::Node(int value)
{
    data = value;
    next = 0;
    prev = 0;
}

DoublyLinkedList::DoublyLinkedList()
{
    head = 0;
    tail = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    while (head)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void DoublyLinkedList::push_front(int value)
{
    Node* newNode = new Node(value);
    if (head == 0)
        head = tail = newNode;
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoublyLinkedList::push_back(int value)
{
    Node* newNode = new Node(value);
    if (tail == 0)
        head = tail = newNode;
    else
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void DoublyLinkedList::pop_front()
{
    if (head == 0)
        throw std::runtime_error("The list is empty");
    
    Node* temp = head;
    head = head->next;
    if (head)
        head->prev = 0;
    else
        tail = 0;
    delete temp;
}

void DoublyLinkedList::pop_back()
{
    if (tail == 0)
        throw std::runtime_error("The list is empty");
    
    Node* temp = tail;
    tail = tail->prev;
    if (tail)
        tail->next = 0;
    else
        head = 0;
    delete temp;
}

void DoublyLinkedList::print()
{
    Node* current = head;
    while (current)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

Node* DoublyLinkedList::get_head()
{   return head;    }

Node* DoublyLinkedList::get_tail()
{   return tail;    }

void DoublyLinkedList::split_list(Node* pivot)
// todos los menores a la izquierda del pivot
//los mayores a la derecha
// el pivot al medio y con el numero central
{
    //ordenar
    cout<<"split"<<endl;
    // caso inicial
    Node** p = &(get_head()->next);
    Node* tail_temp = tail;
    cout<<"split2"<< (*p)->data <<endl;
    if(!(*p)){
        cout<<"hay 1 elemento"<<endl;
    }
    if(pivot == (*p)->prev){
        cout<<"el pivote es la cabeza"<<endl;
        head = *p;
        cout<<"head"<<(*p)->data <<endl;
        head->prev=nullptr;
        p = &((*p)->next);
        cout<<"*p "<<(*p)->data <<endl;
                for(Node* r = head ; r<tail ; r=r->next ){
        cout<< r->data<<" ";
    }
    }
     cout<<"*p "<<(*p)->data <<endl;
    if(!(*p)){ cout<<"2 elementos"<<endl;}  // si solo habian 2 elementos se sale ? falta anidar el unico 
    
    cout<<"2 "<<(*p)->data<<endl;
    Node** menor;
    //ingresar el nodo al elemento mayor encontrado
    if((*p)->prev->data < pivot -> data ){    
        for( ; (*p) && (*p)->data < pivot->data && (*p) != tail  ; p = &((*p)->next) );
        
        Node* tmp_luegomayor = *p;  
        *p=pivot;
        pivot->prev= tmp_luegomayor->prev;
        pivot->next = tmp_luegomayor;
        tmp_luegomayor->prev=pivot; 
        menor=p;
    }   
    
    else{
        pivot->next = (*p)->prev;
        (*p)->prev->prev = pivot;
        p=&((*p)->next);
        for( ; (*p) && (*p)->data > pivot->data && (*p) != tail  ; p = &((*p)->next) );
        Node* tmp = *p; //guardamos
        *p = tmp->next;
        tmp->next->prev = tmp->prev;

        
        tmp->prev =nullptr;
        tmp->next= pivot;
        pivot->prev=tmp;
        head=tmp;
        menor= &((tmp)->next);
        p=&((*p)->next);
        
    }
    // si es menor se abre un espacio detras del pivote, 
        menor=p;
        for(Node* r = head ; r<tail ; r=r->next ){
        cout<< r->data<<" ";
    }
   
    
    p = &((*p)->next);
    // si es mayor se pone al final.
    cout<<"split 3"<<endl;
    cout<<"primer for"<< (*p)->data <<endl;
    
    cout<<"menor"<< (*menor)->data <<endl; 
    for(Node* r = head ; r<tail ; r=r->next ){
        cout<< r->data<<" ";
    }
   
    while((*p)->next != nullptr ){
       
        cout<<"split 4"<<endl;
        for( ; (*p)->next != nullptr && (*p)->data > pivot->data ; p = &((*p)->next) ); //hay que guardar la primera pos de tail para usarla como tope
        // si es menor se abre un espacio detras del pivote,
        Node* tmp = *p; //guardamos
        *p = tmp->next;
        tmp->next->prev = tmp->prev;

        *menor= tmp;
        tmp->prev = pivot->prev;
        tmp->next= pivot;
        pivot->prev=tmp;

        menor= &((*p)->next);
        p=&((*p)->next);
        // si es mayor se sigue.
        cout<<"for interno"<< (*p)->data <<endl;
        for(Node* r = head ; r<tail ; r=r->next ){
            cout<< r->data<<" ";
        }break;

        //code go here
    }
    if((*p)->data < pivot->data  ){
        Node* tmp = *p;
        *p=nullptr;
        *menor=tmp;
        tmp->prev = pivot->prev;
        tmp->next= pivot;
        pivot->prev = tmp;
    }
}

int main()
{
    DoublyLinkedList l;
    l.push_back(43);    l.push_back(67);    l.push_back(34);
    l.push_back(20);    l.push_back(71);    l.push_back(12);
    l.push_back(61);    l.push_back(77);    l.push_back(68);
    l.push_back(3);     l.push_back(26);    l.push_back(70);
    l.push_back(74);    l.push_back(88);    l.push_back(57);
    l.print();
    cout<<"push terminado"<<endl;
    l.split_list(l.get_head());    return 0; l.print();
    l.split_list(l.get_tail());     l.print();
    l.split_list(l.get_head());     l.print();
    l.split_list(l.get_tail());     l.print();

    
}