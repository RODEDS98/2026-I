#include <iostream>
#include <cmath>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v;
        nodes[0] = nodes[1] = 0;
        height = 0;
        balance = 0;
    }
    int value;
    int height;
    int balance;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    bool Insert(int x);
    bool Insert(int *v, int n);
    void Print();
    
    void preprocess();          // Preprocesar árbol (calcular alturas/balances)
    void InsertAndCheck(int x); // Insertar y verificar desbalances

private:
    bool Find(int x, CBinNode**& p);
    void InOrder(CBinNode* n);
    
    // Funciones auxiliares (PARA IMPLEMENTAR)
    int calculateHeight(CBinNode* n);
    void calculateHeights(CBinNode* n);
    void calculateBalances(CBinNode* n);
    void checkPathBalances(CBinNode* n, int x);
    
    CBinNode* m_root;
};

CBinTree::CBinTree()
{
    m_root = 0;
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for ( p = &m_root ;
         *p && (*p)->value != x ;
         p = &( (*p)->nodes[ (*p)->value < x ] ) );
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinNode(x);
    return 0;
}

bool CBinTree::Insert(int *v, int n)
{
    bool b = 1;
    for ( int i = 0; i < n; ++i )
        b &= Insert(v[i]);
    return b;
}

void CBinTree::InOrder(CBinNode* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout<<"\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCIONES A IMPLEMENTAR
////////////////////////////////////////////////////////////////////////////////////////////////////////

void CBinTree::preprocess()
{
    calculateHeights(m_root);
    calculateBalances(m_root);
}

void CBinTree::calculateHeights(CBinNode* n)
{
    // calcular alturas y almacenar en n->height
}

void CBinTree::calculateBalances(CBinNode* n)
{
    // calcular balances y almacenar en n->balance
    // altura_izq - altura_der
}

void CBinTree::checkPathBalances(CBinNode* n, int x)
{
    // Verifica desbalances en el camino de inserción del valor x

    // Si en un nodo, |balance| > 1: imprimir: "Desbalance en nodo [valor]"
    // Si ningún nodo se desbalanceó: imprimir "Inserción balanceada"
}

void CBinTree::InsertAndCheck(int x)
{
    // Inserta un valor y verifica si causó desbalances
    cout << "Insertando " << x << "...\n";
    Insert(x);
    checkPathBalances(m_root, x);
    cout << "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t;
    
    // Árbol inicial balanceado (3 niveles, 7 nodos)
    cout << "============================================\n";
    cout << "Construyendo árbol inicial (3 niveles)\n";
    cout << "============================================\n";
    int v[] = {50, 30, 70, 20, 40, 60, 80};
    t.Insert(v, 7);
    t.Print();
    cout << "\n";
    
    // Preprocesar árbol
    cout << "Preprocesando árbol...\n";
    t.preprocess();
    cout << "✓ Árbol preprocesado\n\n";
    
    // Inserciones incrementales
    cout << "============================================\n";
    cout << "INSERCIONES INCREMENTALES\n";
    cout << "============================================\n\n";
    
    t.InsertAndCheck(10);
    t.InsertAndCheck(5);
    t.InsertAndCheck(90);
    t.InsertAndCheck(95);
    t.InsertAndCheck(100);
    
    return 0;
}
