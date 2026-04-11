#include <iostream>
using namespace std;

class cDeque
{
  private:
    int* *mapa=NULL;
    int **M_INI=NULL;
    int **M_FIN=NULL;
    int *V_INI=NULL;
    int *V_FIN=NULL;
    int dim;
    
  public:
   
    void push_front(int n);
    void push_back(int n);
    int pop_front();
    int pop_back();
    int &operator[](int id);
    void print();
    void expandir(int dim);
   
    
    cDeque()
    {
      dim=11;
      mapa=new int*[dim]; 
      /*for( int**p=mapa ; p< mapa+10 ;p++ ){
          cout<<"p "<<p<<endl;
      }*/
      
      M_INI=mapa+5;
      M_FIN=M_INI;
    }
};

void cDeque::push_front(int n)
{
  if(!V_INI) // V_INI == NULL
  {
    M_INI=mapa+5;
    M_FIN=M_INI;
    *M_INI= new int[11];
    V_INI=*M_INI+5;
    V_FIN=V_INI;
    *V_INI=n;
  }
  else if(V_INI==*M_INI)
  {
    if(M_INI==mapa)
    {
      cout << "LIMITES LLENOS";
      return;
    }
    
    M_INI--;
    *M_INI= new int[11];
    V_INI=*M_INI+10;
    *V_INI=n;
  }
  else
  {
    V_INI--;
    *V_INI=n;
  }
  /*for( int**p=mapa ; p< mapa+10 ;p++ ){
          cout<<"p 2 "<<*p<<endl;
    } */
}
void cDeque::push_back(int n)
{
  if(!V_FIN)
  {
    M_INI=mapa+5;
    M_FIN=M_INI;
    *M_INI= new int[11];
    V_INI=*M_INI+5;
    V_FIN=V_INI;
    *V_INI=n;
  }
  else if(V_FIN==*M_FIN+10)
  {
    if(M_FIN==mapa+10)
    {
      cout << "LIMITES LLENOS";
      return;
    }
    M_FIN++;
    *M_FIN= new int[11];
    V_FIN=*M_FIN;
    *V_FIN=n;
  }
  else
  {
    V_FIN++;
    *V_FIN=n;
  }
}
int cDeque::pop_front()
{
  int retorno=0;
  if(!V_INI)
  {
    cout << "No hay elementos" << endl;
    return -1;
  }
  else if(V_INI==V_FIN)
  {
    retorno=*V_INI;
    V_INI=NULL;
    V_FIN=NULL;
    delete [] *M_INI;
  }
  else if(V_INI==*M_INI+10)
  {
    retorno=*V_INI;
    delete [] *M_INI;
    M_INI++;
    V_INI=*M_INI;
  }
  else
  {
    retorno=*V_INI;
    V_INI++;
  }
  return retorno;
}
int cDeque::pop_back()
{
  int retorno=0;
  if(!V_FIN)
  {
    cout << "No hay elementos" << endl;
    return -1;
  }
  else if(V_INI==V_FIN)
  {
    retorno=*V_INI;
    V_INI=NULL;
    V_FIN=NULL;
    delete [] *M_INI;
  }
  else if(V_FIN==*M_FIN)
  {
    retorno=*V_FIN;
    delete [] *M_FIN;
    M_FIN--;
    V_FIN=*M_FIN+10;
  }
  else
  {
    retorno=*V_FIN;
    V_FIN--;
  }
  return retorno;
}
int &cDeque::operator[](int id)
{
  if(!V_INI)
  {
    cout << "No hay elementos" << endl;
    return *V_INI;
  }
  int elem_faltan = (V_INI-*M_INI);
  int n_id = id+ elem_faltan;
  return *(*(M_INI+(n_id/11))+n_id%11);
}
void cDeque::print(){
    cout<<" _____Nuevo print" <<endl;
    int dim = 11;
    int** i = M_INI; 
    cout<<" i: "<< i<<endl ;
    
    for(int* j=V_INI; j <= V_FIN && j <= *i + dim -1; j++ ){
            cout<<" -1-- j: "<< j << "  *j: " << *j<<endl;
    }
    i++;
    //cout<<"x"<<endl;
    if(i<=M_FIN ){  //cout<<"x"<<endl;
        while( i != M_FIN){
            cout<<" i: "<< i<<endl;
            for(int* j =*i  ; j <= V_FIN && j <= *i + dim -1  ; j++ ){
                cout<<" -2-- j: "<< j << "  *j: " << *j<<endl;
            }
            i++;
        }
        cout<<" i: "<< i<<endl;
        for(int* j=*M_FIN; j <= V_FIN && j <= *i + dim -1; j++ ){
                cout<<" -3-- j: "<< j << "  *j: " << *j<<endl;
        }    
    }
}
                                //              xxxxxxxxxxx       
void cDeque::expandir(int dim){    //         xxxxx,xxxxxXxxxxx,xxxxxx    22/2= 11 ,  11/2= 5 
    int** mapa2= new int*[dim*2];
    int pos= (dim*2/2) - (dim/2);
    int** M_INI_2= mapa2 + pos;
    M_INI = M_INI_2;
    M_FIN = M_INI+dim-1;
    
    for(int** p = mapa; p < mapa + dim; p++ ){
        *M_INI_2 = *p;
        M_INI_2++;
    }
    
    
}
    


int main() 
{
  cDeque prueba;
  cDeque* p = &prueba;

  prueba.push_back(1);p->print();
  prueba.push_back(2);p->print();
  prueba.push_back(3);p->print();
  prueba.push_back(4);p->print();
  prueba.push_back(5);p->print();
  prueba.push_back(6);p->print();
  prueba.push_back(7);p->print();
  prueba.push_back(8);p->print();
  prueba.push_front(100);p->print();
  prueba.push_front(200);p->print();
  prueba.push_front(300);p->print();
  prueba.push_front(400);p->print();
  prueba.push_front(500);p->print();
  prueba.push_front(600);p->print();
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_back() << endl;
  cout << prueba.pop_front() << endl;
  cout << prueba.pop_front() << endl;
  cout << prueba.pop_front() << endl;
  cout << prueba.pop_front() << endl;
  cout << prueba.pop_front() << endl;
  cout << prueba.pop_front() << endl;
}