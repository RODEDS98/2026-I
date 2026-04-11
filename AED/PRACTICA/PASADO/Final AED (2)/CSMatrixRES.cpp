#include <iostream>
#include <map>
using namespace std;
template<class T, T N>  
class CSMatrix
{
    public:
        CSMatrix(int dx, int dy);
        bool set(int x, int y, int value);
        int get(int x, int y);
        void print();
        //bool find(int x, int y, int value);
        
    private:
        // matrix
        map< int , map<int,int> > matrix; 
        int dimx, dimy;
};

template<class T, T N>
CSMatrix<T,N>::CSMatrix(int dx, int dy)
{
    dimx = dx; dimy = dy;
}

template<class T, T N>
bool CSMatrix<T,N>::set(int x, int y, int value)
{   
    auto i = matrix.find(x); // se busca en el 1er mapa
    
    if(i != matrix.end()){  // si lo encontro 
        auto j = (i->second).find(y);  // busca en el 2do mapa anidado
        if( j != (i->second).end() ){  // si lo encontro
            //se encontro se debe cambiar su valor si no es el nulo
            if(j->second != N){
                j->second = value;
            }
            else{
                //remover por elemento nulo
                (i->second).erase(y);
            }
        }
        else{
            // se debe insertar en el mapa existente
            (i->second)[y] =  value;
        }
    }
    else{
        // se debe crear el mapa e  insertar
        map<int,int> tmp;
        tmp.insert({y,value});  // NOTACION      objeto. insert ({  elemento primero , elemento segundo   })
        matrix.insert( {x , tmp} );
    }

    return 0;
}


template<class T, T N>
int CSMatrix<T,N>::get(int x, int y)
{
    auto i = matrix.find(x);
    if(i != matrix.end()){  // si lo encontro 
        auto j = (i->second).find(y);  // busca en el 2do mapa anidado
        if( j != (i->second).end() ){  // si lo encontro
             return j->second;  // se evita matrix[x][y]  porque crea objetos con valores predeterminados... 
        }
    }
    return N;
}

template<class T, T N>
void CSMatrix<T,N>::print()
{
    std::cout << "\n";
    for (int x = 0; x < dimx; x++)
    {
         for (int y = 0; y < dimy; y++)
        {
            std::cout << get(x,y) << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main()
{
    CSMatrix<int,0> m(8,8);

    m.set(2, 1, 5);
    m.set(2, 3, 2);
    m.set(2, 5, 7);
    m.set(5, 3, 9);
    m.set(7, 3, 12);
    m.set(1, 4, 3);
    m.set(2, 4, 0);
    m.set(5, 5, 8);
    m.set(3, 6, 1);
    m.print();
    m.set(1, 4, 0);
    m.set(2, 3, 0);
    m.set(4, 3, 0);
    m.set(0, 1, 0);
    m.print();
    std::cout << "\n 0,0 => " << m.get(0, 0);
    std::cout<< "\n 3,5 => " << m.get(3, 5);
    std::cout<< "\n 7,3 => " << m.get(7, 3);
 }
