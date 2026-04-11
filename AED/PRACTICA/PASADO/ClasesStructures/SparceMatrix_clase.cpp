//matriz
//matriz
#include <iostream>
using namespace std;

template <class T>
class node{
    public:
        node(int x,int y,T v){
            this->x=x;
            this->y=y;
            this->v=v;
        }
        void set_v(T valor){
            v=valor;
        }
        T get_v(){
            return v;
        }
        T get_y(){
            return y;
        }
        T get_x(){
            return x;
        }
        node<T>* abjo;
        node<T>* drcha;
    private:
        int x;
        int y;
        int v;

};

template <class T, T NE>
class CSMatrix{
    public:
        CSMatrix(int dim_x ,int dim_y){
            Ejex = new node<T>*[dim_x];
            Ejey = new node<T>*[dim_y]; 
            for (int i = 0; i < dim_y; i++)
                Ejey[i] = nullptr;
            for (int i = 0; i < dim_y; i++)
                Ejey[i] = nullptr;
            this->dim_x=dim_x;
            this->dim_y=dim_y;

        }
        
        bool find_x(int x,int y, T value,node<T>** &p);
        bool find_y(int x,int y, T value,node<T>** &q);
        void insertar(int x, int y, T value);
        void remover(int x, int y, T value);
        void set(int x, int y, T value);
        T get(int x, int y);

        void print();
        
    private:
        node<T>** Ejex = NULL ;
        node<T>** Ejey = NULL ;
        int dim_x;
        int dim_y;

};


template <class T, T NE>
bool CSMatrix< T,  NE>::find_x(int x,int y, T value, node<T>** &p){
    //p = Ejex+x;
    cout<< " find_x "<<endl;
                    // nos posicionamos en el indice correcto del array
    if( *(Ejex+x) ){   // verificamos si hay un nodo existente 
    cout<< " eje "<<endl;
        p = (Ejex+x);
        for(  ; (*p) && (*p)->get_y() < y ; p = &( (*p) -> abjo ) );     //recorremos con puntero doble
    }
    cout<< " find_y fin"<<endl;
    return p && (*p) && (*p)->get_y() == y;
}

template <class T, T NE>
bool CSMatrix< T,  NE>::find_y(int x,int y, T value,node<T>** &q){
    //q = Ejey;
                    // nos posicionamos en el indice correcto del array
    if( *(Ejey+y) ){   // verificamos si hay un nodo existente 
        q = (Ejey+y);
        for(  ; (*q) && (*q)->get_x() < x ; q = &( (*q) -> drcha ) ); //recorremos con puntero doble
    }
    cout<< " find_x fin"<<endl;
    return q && (*q) && (*q)->get_x() == x ;
}

template <class T, T NE>
void CSMatrix< T,  NE>::insertar(int x, int y, T value){
    node<T>** p=nullptr;
    node<T>** q=nullptr;
    
    if(x >= dim_x || y >= dim_y) return ;
    
    // Verificamos si las posiciones no son nullptr (no existen nodos alli)
    bool x_vector = *(Ejex+x);
    bool y_vector = *(Ejey+y);//find_x(int x,int y, T value, node<T>** p)
    
    // Si "x" en el array ya existe pero "y" no  ero "x" no 
    if( x_vector && !y_vector ){
        node<T>* tmp = new node<T>(x,y,value);  // insertar en y, sera unico nodo de y 
        //crear nueva eje y 
        *(Ejey+y) = tmp;
        tmp->drcha = nullptr; 
        // insertar en la lista existente x { y0 -> y1 -> y2 -> y3 ...}
        find_x(x,y,value,p);   
        node<T>* p_posterior = *p;
        (*p) = tmp;
        tmp->abjo = p_posterior;
        //
        
    }    
    else if( x_vector && !y_vector ){
        cout<<" xd "<<endl;
    }
    
    else if( x_vector && y_vector ){
        cout<<" existen "<<endl;
        bool f_x = find_x(x, y, value, p);
        bool f_y = find_y(x, y, value, q);
        //cout<<" -- existen "<<endl;
        if(f_x){ // si encontro que la posicion existe , el nodo existe
            cout<<"if "<<endl;
            (*p)->set_v(value);
            return;
        }
        cout<<"no if "<<endl;
        // inserta al nodo nuevo en la lista de su x
        node<T>* tmp = (*p);
        *p = new node<T>(x,y,value);
        cout<<"ss "<<endl;
        (*p)->abjo = tmp;
        cout<<"parte x insertada "<<endl;
        // inserta al nodo nuevo en la lista de su y
        node<T>* tmp_q = (*q);
        *q = (*p);
        (*q)->drcha = tmp_q;  //equivalente a (*p)->drcha = tmp_q;
        
         cout<<" fin existen "<<endl;
    }
    
    else if( !x_vector && !y_vector ){
        cout<< " VACIO "<<endl;
        node<T>* tmp = new node<T>(x,y,value);  // insertar en y, sera unico nodo de y 
        //crear nueva eje y 
        cout<< " NUEVO "<<endl;
        *(Ejey+y) = tmp;
        tmp->drcha = nullptr; 
        // crear nueva eje y
        *(Ejex+x) = tmp;
        tmp->abjo = nullptr;
        cout<< " FIM VACIO "<<endl;
        //
    }
        
    
}
    
   
template <class T, T NE>
void CSMatrix< T,  NE>::remover(int x, int y, T value){
    
    node<T>** p=nullptr;
    node<T>** q=nullptr;
    bool x_vector = *(Ejex+x);
    bool y_vector = *(Ejey+y);
    
    if( !x_vector && !y_vector ){
        cout<<"No se encontro "<< x <<" "<< y<<" ";
        return ;
    }
    
    bool f_x = find_x(x, y, value, p);
    if (f_x){
        //borrar x
        bool f_y = find_y(x, y, value, q);
        node<T>* tmp = (*p);
        *p = tmp->abjo;
        *q = tmp->drcha;
        delete tmp;
    }
    cout <<"No se encontro "<< x <<" "<< y;
    
    
    

}

template <class T, T NE>
void CSMatrix< T,  NE>::set(int x, int y, T value){
    
    if(value == NE){
        cout<<"remover"<<endl;
        remover(x,y,value);
    }
    else{
        insertar(x,y,value);
    }
}

template <class T, T NE>
T CSMatrix< T,  NE>::get(int x, int y){
   // cout<<endl<<"   Get "<< x<<" -- "<< y<<endl;
    
    T tmp;
    node<T>** p =nullptr;
    node<T>** q =nullptr;
                    // nos posicionamos en el indice correcto del array
    if( *(Ejex+x) && *(Ejey+y)  ){   // verificamos si hay un nodo existente , el eje x
       // cout<<"      if Get"<<endl;
        p = Ejex+x;
        q = Ejey+y; 
         //cout<<"      xsc Get"<<endl;
        for(  ; (*p) && (*p)->get_y() < y ; p = &( (*p) -> abjo ) );
        for(  ; (*q) && (*q)->get_x() < x ; q = &( (*q) -> drcha ) );
        //cout<<"      xsc2 Get"<<endl;
        if(  !(*p) && (*p) == (*q)  ) return NE;  // si el nodo encontrado coincide con el eje y , se retorna su valor
        // if(  !(*q) && (*p) == (*q)  ) return NE;
        if( (*p) == (*q) ) return (*p)->get_v(); 
        
    }
    //cout<<"   fin GET"<<endl;
    return NE;
    

}

template <class T, T NE>
void CSMatrix< T,  NE>::print(){         
    cout<<" print "<<endl;
    for(int i=0; i<dim_y ; i++){
        for(int j=0; j<dim_x ; j++)
            cout<< get(j,i) << " "; // ejes invertidos
        cout<<endl;
    }
    
    //cout<< " end print "<<endl;
}   


int main(){
    CSMatrix<int,0> m(5,5);
    for(int i=0; i<5;i++ ){
        m.set(i,i,1);    
    }
    
    m.print();
    cout<<"insertar 0,2"<<endl;
    m.set(0,2,1); 
    m.print();
    cout<<"insertar 0,4"<<endl;
    m.set(0,4,1); 
    m.print();
    cout<<"insertar diagonal negativa"<<endl;
    for(int i=0; i<5; i++ ){
        m.set(4-i,i,2);    
    }
    m.print();
    m.set(0,5,1);
    
    for(int i=0; i<5; i++ ){
        for(int j=0; j<5; j++ ){
             m.set(j,i,0);    
        }   
    }
    m.print();
    
    return 0;
}