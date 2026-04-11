#include <iostream>
#include <stack>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CAVLNode
{
    CAVLNode(int _v)
    {   value = _v; 
        nodes[0] = nodes[1] = 0;
        altura = 1;
    }
    int value;
    CAVLNode* nodes[2];
    int altura;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CAVLTree
{
public:
    CAVLTree();
    ~CAVLTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    int MaxNodeHeight(CAVLNode* n);
    int MaxHeight();
    void balanceo(std::stack<CAVLNode**> & estructura);

private:
    bool Find(int x, CAVLNode**& p , std::stack<CAVLNode**> & estructura);
    CAVLNode** Rep(CAVLNode** p);
    void InOrder(CAVLNode* n);
    CAVLNode* m_root;
};

CAVLTree::CAVLTree()
{   m_root = 0;
}

CAVLTree::~CAVLTree()
{}

void CAVLTree::balanceo(std::stack<CAVLNode**> & estructura){
    //encontrar el de peso 2
    int A=0;
    int C=0;
    CAVLNode** A_ptrx2;
    //CAVLNode** B_ptr;
    CAVLNode** C_ptrx2;
    //EL FOR ELIMINARA EL TOP DEL STACK
    for( ; !estructura.empty() ; estructura.pop() ){
        int alt_izq=0;
        int alt_der=0;
        //(*(estructura.top()))->altura = ((*(estructura.top()))->altura + 1;
        
    // SE RESTAN LAS ALTURAS DE EL NODO TOP() EN LA PILA
        if((*(estructura.top()))->nodes[0]){
            alt_izq = ((*(estructura.top()))->nodes[0])->altura;  
            cout<< (*(estructura.top()))->value <<" for_1 altura [0]" <<endl;
        }
        if((*(estructura.top()))->nodes[1]){
            alt_der = ((*(estructura.top()))->nodes[1])->altura;
            cout<< (*(estructura.top()))->value << " for_1 altura [1] " <<endl;
        }
        // SE INCREMENTAN LAS ALTURAS    
        int altura_max;
        if(alt_der == alt_izq && alt_izq==0 && !((*(estructura.top()))->nodes[0]) ) return;
        if(alt_der >= alt_izq ){
            (*(estructura.top()))->altura = alt_der+1;
        }
        else{
            (*(estructura.top()))->altura = alt_izq+1;
        }//((*(estructura.top()))->altura  =  (alt_der-alt_izq);
        
        cout<<"      altura:   " <<  (*(estructura.top()))->altura  << endl;
        
        if( alt_der-alt_izq == -2 ){
            C= -2;
            break;    
        } 
        if( alt_der-alt_izq == 2){
            A=2;
            break; 
        }
        
    } 
    
    if (estructura.empty()) return ;  // no se encontro un 2
    cout<<"         NO BREAK  " <<endl;
    
    if (A==2){
        cout<<"         CASO A  " <<endl;    
        A_ptrx2 = estructura.top() ;
        int alt_der = 0;
        int alt_izq = 0;
        
        if ((*A_ptrx2)->nodes[1]->nodes[1]){
            alt_der = (*A_ptrx2)->nodes[1]->nodes[1]->altura;
        }
        if ((*A_ptrx2)->nodes[1]->no|des[0]){
            alt_izq = (*A_ptrx2)->nodes[1]->nodes[0]->altura;
        }
        
        int dif = alt_der - alt_izq;
        
        if ( dif == 1 ){    //CASO  RR
                
            CAVLNode* tmp_A = *A_ptrx2 ;          //guardamos la dir de A (peso 2)
            
            CAVLNode* B_ptr = (*A_ptrx2)->nodes[1];
            //CAVLNode* C_ptr = (*A_ptr)->nodes[1];

            *A_ptrx2 = B_ptr;        // Se apunta a B como sub root
            CAVLNode* tmp_B_left = B_ptr->nodes[0] ;  //guardamos el hijo izq de B
             
            B_ptr->nodes[0] = tmp_A ;
            tmp_A->nodes[1] =tmp_B_left ; 
            cout<<"A = -2 , dif "<<endl;
        }
        else if ( dif == -1 ){  //CASO  LR
            cout<<"completar"<<endl;
        } 
    }

    else if (C==-2){
        cout<<"         CASO C  " <<endl;   //CASO  XL
        C_ptrx2 = estructura.top() ;
        int alt_der = 0;
        int alt_izq = 0;
        if ((*C_ptrx2)->nodes[0]->nodes[1]){
            alt_der = (*C_ptrx2)->nodes[0]->nodes[1]->altura;
        }
        if ((*C_ptrx2)->nodes[0]->nodes[0]){
            alt_izq = (*C_ptrx2)->nodes[0]->nodes[0]->altura;
        }
        

        int dif = alt_der - alt_izq;
        cout<<"         CASO C especificaciones  " <<endl;  
        if (dif == -1 ){  //CASO  LL
            cout<<"completar"<<endl;
        }
        else if (dif == 1 ){   //CASO  RL
            cout<<"completar"<<endl;
        }   
    }

//  (REPETIDO ) SEGUIR EL CAMINO DEL STACK QUE AUN TIENE ELEMENTOS:
    
        //EL FOR ELIMINARA EL TOP DEL STACK
    for( ; !estructura.empty() ; estructura.pop() ){
        int alt_izq=0;
        int alt_der=0;
        //(*(estructura.top()))->altura = ((*(estructura.top()))->altura + 1;
        
    // SE RESTAN LAS ALTURAS DE EL NODO TOP() EN LA PILA
        if((*(estructura.top()))->nodes[0]){
            alt_izq = ((*(estructura.top()))->nodes[0])->altura;  
        }
        if((*(estructura.top()))->nodes[1]){
            alt_der = ((*(estructura.top()))->nodes[1])->altura;
        }
        // SE INCREMENTAN LAS ALTURAS    
        int altura_max;
        if(alt_der == alt_izq && alt_izq==0 && !((*(estructura.top()))->nodes[0]) ) return;
        if(alt_der >= alt_izq ){
            (*(estructura.top()))->altura = alt_der+1;
        }
        else{
            (*(estructura.top()))->altura = alt_izq+1;
        }//((*(estructura.top()))->altura  =  (alt_der-alt_izq);
        
        
    } 
    
    
    return ;
}

bool CAVLTree::Find(int x, CAVLNode** &p, std::stack<CAVLNode**> & estructura )
{
    for ( p = &m_root ; *p && (*p)->value != x ; p = &( (*p)->nodes[ (*p)->value < x ] ) ){
        estructura.push(p);
    }
    return *p && (*p)->value == x;
}

bool CAVLTree::Insert(int x)
{
    std::stack<CAVLNode**> pila_nodos; 
    CAVLNode** p;
    cout<<"antes find"<<endl;
    if ( Find(x,p,pila_nodos) ) return 0;
    cout<<"despues find"<<endl;
    // balanceo
    *p = new CAVLNode(x);
    cout<<"inserta el nodo"<<endl;
    balanceo(pila_nodos);
    cout<<"-- termina balanceo:   "<<  x <<endl;
    
    return 0;
}

bool CAVLTree::Remove(int x)
{
    std::stack<CAVLNode**> pila_nodos;
    CAVLNode** p;
    if ( !Find(x,p,pila_nodos)) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CAVLNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CAVLNode* t = *p;
    *p = (*p)->nodes[ !(*p)->nodes[0] ];
    delete t;
    return 1;
}

CAVLNode** CAVLTree::Rep(CAVLNode** p)
{
    bool b = rand()%2;
    for( p = &( (*p)->nodes[b] ); (*p)->nodes[!b]; p = &( (*p)->nodes[!b] ) );
    return p;
}

void CAVLTree::InOrder(CAVLNode* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

void CAVLTree::Print()
{
    InOrder(m_root);
    cout<<endl;
}

//======================================================
void MaxNodeHeightThread(CAVLNode* n, int& height)
{
    height = 0;
}
//======================================================

int CAVLTree::MaxNodeHeight(CAVLNode* n)
{
    int h;
    MaxNodeHeightThread(n,h);
    return h;
}

int CAVLTree::MaxHeight()
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    cout<<"INICIO"<<endl;
    int v[150] = {239, 389, 128, 46, 235, 65, 423, 417, 121, 451, 396, 331, 158, 100, 95, 353, 470, 207, 453, 156, 98, 160, 373, 44, 313, 284, 152, 131, 236, 340, 369, 408, 411, 174, 141, 69, 96, 451, 259, 28, 234, 158, 168, 100, 379, 1, 487, 307, 182, 486, 385, 221, 30, 305, 41, 115, 415, 227, 166, 85, 220, 446, 127, 66, 316, 298, 144, 446, 65, 425, 241, 160, 215, 346, 212, 341, 44, 452, 226, 168, 132, 230, 448, 173, 174, 483, 59, 237, 436, 28, 472, 2, 142, 194, 203, 355, 410, 78, 418, 489, 220, 258, 19, 411, 373, 216, 311, 31, 411, 357, 334, 205, 118, 471, 252, 291, 389, 40, 389, 437, 36, 134, 475, 401, 448, 133, 30, 251, 456, 220, 417, 302, 256, 34, 120, 115, 318, 459, 110, 251, 392, 360, 261, 389, 450, 122, 308, 188, 212, 37};
    
    CAVLTree t;
    for ( int i = 0; i < 150; i++ )
        t.Insert(v[i]);
    t.Print();

    cout<<"Max Height is: "<<t.MaxHeight()<<endl;
    
    bool ab = true;
    cout<< ab <<endl;
    bool ac = false;
    cout<< ac <<endl;
    
}


