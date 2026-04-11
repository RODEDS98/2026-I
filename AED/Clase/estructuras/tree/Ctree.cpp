#include <iostream>
#include <queue>
using namespace std;

template<class T>
struct Cnode{
	Cnode(T v,Cnode* der=nullptr, Cnode*izq=nullptr);
	
	T v;
	Cnode* nodes[2];  //{ ptr1 , ptr2 }
	
};

/*
class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool find(int x, CNode**& p);  //hecho solo
    bool ins(int x);			   //hecho solo
    bool rem(int x);			   //hecho solo
    CNode** rep(CNode** p);		   //falta 
    void inorder(CNode* n);		   //hecho copia
    void preorder(CNode* n);	   //hecho solo
    void postorder(CNode* n);	   //hecho solo
    void print();				   //hecho solo
    T height1(Cnode<T>* n);             //hecho solo
    void h1(Cnode<T>* n, T h, T& maxh); //hecho solo
    T height2(Cnode<T>* n);             //hecho
    void print_levels();
    void levels(Cnode<T>* n);
private:
    CNode* root;
    bool brep;
}; 
    int height1(CNode* n);
    void h1(CNode* n, int h, int& maxh);
    int height2(CNode* n);
*/


template<class T>
Cnode<T>::Cnode(T v,Cnode* der, Cnode*izq){   
	this -> v  = v;
	*(this->nodes) = der; 
	*(this->nodes+1) = izq;
}

template<class T>
struct Ctree
{
    Ctree();
    ~Ctree();
    bool find( T x , Cnode<T>** &p );
    bool ins(T x);
    bool rem(T x);
    Cnode<T>** rep(Cnode<T>** p);
    void inorder(Cnode<T>* p);
    void preorder(Cnode<T>* p);
    void postorder(Cnode<T>* p);
    void print();
    T height1(Cnode<T>* n);
    void h1(Cnode<T>* n, T h, T& maxh);
    T height2(Cnode<T>* n);
    void print_levels();
    void levels(Cnode<T>* n);
	
    

    Cnode<T>* root;
	bool brep;
};

template<class T>
Ctree<T>::Ctree(){
    root = nullptr;
    brep = 0;
}

template<class T>
Ctree<T>::~Ctree(){
 
}

template<class T>
Cnode<T>** Ctree<T>::rep(Cnode<T>** p){
    //por el camino menor
    Cnode<T>** q = p;
    q = &((*q) -> nodes[!brep]);
    for(  ; (*q) -> nodes[brep]  ; q = &((*q) -> nodes[brep] ));
    brep=!brep;
    return q;
}


template<class T>
bool Ctree<T>::find( T x , Cnode<T>** &p ){
    
    p= &root;                                    //    x > (*p) -> v  
    for( ; *p && (*p) -> v != x ; p = &( (*p) -> nodes[x > (*p) -> v ] ) );
    return *p;
}

template<class T>
bool Ctree<T>::ins(T x){
    Cnode<T>** p; 
    if(find(x,p)) return 0;
    *p= new Cnode<T>(x);
    return 1;
}

template<class T>
bool Ctree<T>::rem(T x){

	Cnode<T>** p;
    if(!find(x,p)) return 0; // si no lo encontramos retornamos 0

    // caso en donde tienen 2 nodos
    if( (*p)->nodes[0] != nullptr && (*p)->nodes[1] != nullptr ){
    	Cnode<T>** r = rep(p);
    	(*p) -> v = (*r)->v ;
    	p = r;  
    } 
    Cnode<T>* tmp = *p;
	// caso donde tienen un solo nodo izquierda // caso donde tienen un solo nodo derecha
	*p = (*p)->nodes[ !( (*p) -> nodes[0] ) ]; 
    // caso donde no tienen nodos hijos
    
    delete tmp;

    return 1;
}

template<class T>
void Ctree<T>::inorder(Cnode<T>* p){
	if(!p) return;
	inorder(p->nodes[0]);
	cout<<" "<<p->v;
	inorder(p->nodes[1]);

}

template<class T>
void Ctree<T>::preorder(Cnode<T>* p){
	if(!p) return;
	preorder(p->nodes[0]);	
	preorder(p->nodes[1]);
	cout<<" "<<p->v<<endl;

}	

template<class T>
void Ctree<T>::postorder(Cnode<T>* p){
	if(!p) return;
	cout<<" "<<p->v;
	postorder(p->nodes[0]);	
	postorder(p->nodes[1]);
}	


template<class T>
void Ctree<T>::print(){
	inorder(root);
	cout<<" h = "<<height1(root)<<endl;
	cout<<endl;
}

template<class T>
T Ctree<T>::height1(Cnode<T>* n){
    T maxh=0;
    h1(n,1,maxh);
    return maxh;
}

template<class T>
void Ctree<T>::h1(Cnode<T>* n, T h, T& maxh){
    //entramos a cada nodo
    if(!n) return;
    if(h>maxh)
        maxh=h;
    h1(n->nodes[0],h++,maxh);
    h1(n->nodes[1],h++,maxh);
}

template<class T>
T Ctree<T>::height2(Cnode<T>* n){  // falta analizar
    if (!n) return 0;
    int l = height2(n->nodes[0]), r = height2(n->nodes[1]);
    return max(l,r)+1;
}

template<class T>   
void Ctree<T>::print_levels(){    
    cout<<endl;
    levels(root);
    cout<<endl;
}

template<class T>
void Ctree<T>::levels(Cnode<T>* n){    // falta analizar
    if ( !n ) return;
    queue<Cnode<T>*> q;
    q.push(n);
    while ( !q.empty() )
    {
        Cnode<T>* x = q.front();
        cout<<x->v<<" ";
        if ( x->nodes[0] ) q.push(x->nodes[0]);
        if ( x->nodes[1] ) q.push(x->nodes[1]);
        q.pop();
    }
}



int main(){
	Cnode<int>* ptr_prueba;
	Cnode<int> node_1(1);
	ptr_prueba = &node_1;
	
	Ctree<int>* prueba2;
	Ctree<int> arbol;
	prueba2= &arbol;
	//prueba2->ins(1);
	arbol.ins(1);arbol.print();
	arbol.ins(3);arbol.print();
	arbol.ins(5);arbol.print();
	arbol.ins(7);arbol.print();
	arbol.ins(2);arbol.print();
	arbol.ins(4);arbol.print();
	arbol.ins(6);arbol.print();
	arbol.ins(8);arbol.print();
	arbol.rem(3);arbol.print();
	//arbol.postorder();
	return 0;
}