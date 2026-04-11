#include <iostream>
#include <queue>

class CSortedQueue
{
public:
    void pushx(int x);
    void popx();
    int frontx();
    void remx(int x);
    void printx();
    std::queue<int> q;
private:
    int A[12];
};
/*
- frontx() debe retornar siempre el menor elemento de la fila
- popx() debe eliminar el menor elemento de la fila
- pushx(int x) debe insertar x, en orden
- remx(int x), debe eliminar todos los elementos iguales a x
- printx(), debe imprimir en una nueva línea todos los elementos de la fila
*/

void CSortedQueue::pushx(int x)
{
    

}

void CSortedQueue::popx()
{
    q.pop();
}

int CSortedQueue::frontx()
{   
    if(q.empty()) {std::cout<<" no hay elementos"; return 0;}
    return q.front();
}

void CSortedQueue::remx(int x)
{
    
    
}

void CSortedQueue::printx(){
    for(std::queue<int> r ; !(r.empty()) ; r.pop() ){
        std::cout <<" "<< r.front() << std::endl;
    }

}

void print(std::queue<int> p){
    std::cout << " imprimiendo queue" <<std::endl;
    for(; !p.empty() ; p.pop() ){
        std::cout<<" "<< p.front() ;
    }
}

int main()
{
    CSortedQueue sq;
    sq.pushx(40); sq.printx();
    sq.pushx(23); sq.printx();
    sq.pushx(51); sq.printx();
    sq.pushx(12); sq.printx();
    sq.pushx(30); sq.printx();
    sq.pushx(5);  sq.printx();
    sq.pushx(40); sq.printx();
    sq.pushx(18); sq.printx();
    
    sq.remx(40);  sq.printx();
    sq.remx(23);  sq.printx();
    sq.remx(12);  sq.printx();
    sq.remx(5);  sq.printx();

    std::cout<<"\nfront => "<<sq.frontx(); sq.popx();
    std::cout<<"\nfront => "<<sq.frontx(); sq.popx();
    sq.printx();
    
    
    
    std::queue<int> p;
    p.front();
    
     std::cout<<"\nfront"<< p.front()<<std::endl; 
    p.push(1);
    p.push(2);
    p.push(3);
    p.push(4);
    std::cout<<"\nfront"<< p.front()<<std::endl; 
    p.pop();
    print(p);  
        p.pop();
    print(p);   
        p.pop();
    print(p);   
        p.pop();
    print(p);   
    std::cout<<"\nfront"<< p.front()<<std::endl;
}
