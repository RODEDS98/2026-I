#include <iostream>

using namespace std;

class Nodo
{
public:
    Nodo(int fil,int col,int dato){
        this->fil=fil;
        this->col=col;
        this->dato=dato;
    }
    int fil;
    int col;
    int dato;
    Nodo* next;
};

template <class T, T N>
class SparseMatrix
{
public:
    SparseMatrix();
    Nodo* Mat = NULL;
    void set(int fil, int col, int dato);
    void print();
    bool find(int fil,int col, Nodo** &pos);
    void rem(Nodo** &pos);
    //void insert(int fil,int col,int dato);
};
template <class T, T N>
SparseMatrix<T, N>::SparseMatrix(){

}

template <class T, T N>
void SparseMatrix<T,N>::rem(Nodo** &pos){
    Nodo* tmp = *pos;
    *pos= tmp->next;
    delete tmp;
}

template <class T, T N>
bool SparseMatrix<T, N>::find( int fil , int col , Nodo** &pos  ){
    
    pos= &Mat;
    // la idea es  que se guarden asi :   (1,1) (1,2) (1,3) (2,1) (4,3) (4,8)
    // por eso primero busca la fila correcta , al primero que cumpla salta al otro for
    for( ; *pos && (*pos)->fil < fil ; pos = &((*pos)->next) );
    
    // cuando salte a este , este posicionara en la posicion para la columna correcta
                                        // se evita pasar a la siguiente fila aqui
                                        //  (*pos)->fil <= fil
    for( ; *pos && (*pos)->col < col && (*pos)->fil <= fil ; pos = &((*pos)->next) );
    return *pos && (*pos)->col == col &&  (*pos)->fil == fil;
}

template <class T, T N>
void SparseMatrix<T, N>::set(int fil, int col, int dato)
{
    Nodo** pos;
    if(dato != N){
        if (find(fil,col,pos)) {
            // Solo cambia el valor , pero cuidado si entra cero.
            (*pos)->dato=dato;
        }
        else{
            //insera un nuevo nodo.
            Nodo* tmp = *pos;
            *pos = new Nodo(fil,col,dato);
            (*pos)->next = tmp;
        }
    }
    else{
        if(!find(fil,col,pos)) return;
        rem(pos);
    }
}

template <class T, T N>  
void SparseMatrix<T, N>::print()
{
    cout << "------Mat-----"<<endl;
    for (Nodo* p = Mat; p; p = p->next)
        cout << "[" << p->fil << "][" << p->col << "] = " << p->dato << endl;
    cout << "------FIN Mat-----"<<endl;
}

int main()
{
    SparseMatrix<int,0> SM;

    int a[10][10] = {   {0,10,20,30,40,50,60,70,80,90},
                        {10,20,30,40,50,60,70,0,80,90},
                        {10,20,30,0,50,60,70,80,90,0},
                        {20,10,90,0,10,20,60,70,80,0},
                        {30,20,90,10,20,30,70,0,80,10},
                        {30,20,0,10,20,30,70,80,90,10},
                        {80,20,20,20,0,60,0,90,90,0},
                        {70,10,30,30,0,70,70,80,80,0},
                        {0,20,30,20,10,70,0,80,80,10},
                        {80,20,90,30,10,0,80,90,90,10},
                    };

    int b[10][10] = {   {10,0,0,0,0,0,0,0,0,0},
                        {0,20,0,0,0,0,0,0,0,0},
                        {0,0,30,0,0,0,0,0,0,0},
                        {0,0,0,40,0,0,0,0,0,0},
                        {0,0,0,0,50,0,0,0,0,0},
                        {0,0,0,0,0,60,0,0,0,0},
                        {0,0,0,0,0,0,70,0,0,0},
                        {0,0,0,0,0,0,0,80,0,0},
                        {0,0,0,0,0,0,0,0,90,0},
                        {0,0,0,0,0,0,0,0,0,100},
                    };

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            SM.set(i, j, a[i][j]);

    SM.print();

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            SM.set(i, j, b[i][j]);

    SM.print();

}