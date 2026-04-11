#include <iostream>
#include <deque>
#include <vector>

template <class T>
class CMaxHeap3
{
public:
    void push(int n);
    int top();
    void pop();
    void print();
    void swap(T &a,T &b);
    void cabeceo(int i);
    void hundimiento(int i);
private:
    std::deque<T> heap;
};

template <class T>
void CMaxHeap3<T>::swap(T &a,T &b){
    T tmp=a;
    a=b;
    b=tmp;
}

template <class T>
int CMaxHeap3<T>::CMaxHeap3::top()
{
    if(heap.empty()) return -1;
    return  heap.front();
}

template <class T>
void CMaxHeap3<T>::cabeceo(int i){
    //caso inicial, 1 solo elemento
    int pos_padre = (i-1)/3;
    int piv = i;
    for(  ; piv > 0 && heap[piv] > heap[pos_padre] ;   ){
            swap( heap[piv] , heap[pos_padre] );
            piv = pos_padre;
            pos_padre = (pos_padre-1)/3;
    }
    
}

template <class T>
void CMaxHeap3<T>::hundimiento(int i) {
    int n = heap.size();
    while (true) {
        int hijo1 = 3*i + 1;
        int hijo2 = 3*i + 2;
        int hijo3 = 3*i + 3;
        // si no tiene hijos, salimos
        
        if (hijo1 >= n) break;
        int max = hijo1;
        
        if (hijo2 < n && heap[hijo2] > heap[max]) max = hijo2;
        if (hijo3 < n && heap[hijo3] > heap[max]) max = hijo3;
            
        // comparar con el mayor hijo
        if (heap[max] > heap[i]) {
            swap(  heap[i]  , heap[max]  );
            i = maxx;
        else break;
    }
}


template <class T>
void CMaxHeap3<T>::CMaxHeap3::push(int x){
    heap.push_back(x);
    cabeceo(heap.size()-1);
}

template <class T>
void CMaxHeap3<T>::CMaxHeap3::pop(){
    
    if(heap.empty()) return;
    heap.front() = heap.back();
    heap.pop_back();
    if(!heap.empty()) hundimiento(0);
}

template <class T>
void CMaxHeap3<T>:: CMaxHeap3::print()
{
    for ( auto i = heap.begin(); i != heap.end(); ++i )
        std::cout<<*i<<" ";
    std::cout<<"\n";
}

int main()
{
    CMaxHeap3<int> h;
    std::vector<int> vpush = {30,35,40,50,43,36,60,51,70,90,66,77,23,21,49,88,73};
    for (auto i : vpush)
        h.push(i);
    h.print();
    for (int j = 0; j < 5; j++)
        h.pop();
    h.print();
}