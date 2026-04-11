
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class heap{
    public:
        heap();
        ~heap();
        void push_back(T val);
        void make_heap(T val); // convierte
        void push_heap();
        bool pop_heap();
        //sort_heap(); // orden ascendente
        //is_heap(T val);
        //is_heap_until();  //?
        
        
    private:
        vector<T> v;
    
};

template <class T>
void heap<T>::push_back(T val){
    return v.push_back(val);
}
template <class T>        
void heap<T>::make_heap(T val){ // convierte
    return T();
} 
        
template <class T>
void heap<T>::push_heap(){
    iterator<T> it1;
    
    return T();
}
        
template <class T>        
bool heap<T>::pop_heap(){
    return 0;
}

int main()
{
    vector<int> prueba= {11,13,8,20,5,10,9,1,3,50,4};
    cout << prueba[0]<<endl ;

    cout <<"size " << prueba.size()<<endl;
    cout <<"max size " << prueba.max_size()<<endl;
    cout <<"capacity " << prueba.capacity()<<endl;
    prueba.push_back(100);
    cout <<"size " << prueba.size()<<endl;
    cout <<"max size " << prueba.max_size()<<endl;
    cout <<"capacity " << prueba.capacity()<<endl;
    
    cout << endl;
    
    vector<int>::iterator it = prueba.begin();
    cout<< *(it+0)  <<endl;
    cout<< prueba.back() << endl;
    
    //cout<< prueba.front()  <<endl;
    return 0;
    
    
    
    
}