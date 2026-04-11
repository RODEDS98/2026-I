#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    bool Insert(int x);
    bool Insert(int* v, int n);
    void Print();
    void ThreadWorker(/* parametros aqui */);
    int TreeSum();

private:
    bool Find(int x, CBinNode**& p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
};

CBinTree::CBinTree()
{
    m_root = 0;
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}

bool CBinTree::Insert(int* v, int n)
{
    bool b = 1;
    for (int i = 0; i < n; ++i)
        b &= Insert(v[i]);
    return b;
}

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    std::cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    std::cout << "\n";
}

void CBinTree::ThreadWorker(/* parametros aqui */)
{

}

int CBinTree::TreeSum()
{
    return 0;
}


int main()
{
    CBinTree t;
    int v[63] = { 57, 17, 83, 9, 28, 71, 95, 04, 12, 20, 33, 60, 79, 88, 99, 02, 06, 10, 14, 18, 22, 30, 36, 58, 63, 75, 82, 86, 90, 97, 102, 1, 3, 5, 7, 8, 11, 13, 15, 16, 19, 21, 23, 29, 31, 34, 38, 55, 59, 62, 70, 72, 78, 81, 83, 85, 89, 92, 94, 96, 98, 101, 104 };
    t.Insert(v, 63);
    std::cout << "La suma es: " << t.TreeSum() << "\n";
}
