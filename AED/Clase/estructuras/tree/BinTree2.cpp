#include <iostream>

struct CNode
{
    CNode(int _v)
    { v = _v; nodes[0] = nodes[1] = 0; }
    int v;
    CNode* nodes[2];
};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool find(int x, CNode**& p);
    bool ins(int x);
    bool rem(int x);
    CNode** rep(CNode** p);
    void inorder(CNode* n);
    void print();
    int height1(CNode* n);
    void h1(CNode* n, int h, int& maxh);
    int height2(CNode* n);
private:
    CNode* root;
    bool brep;
};

CBinTree::CBinTree()
{   root = 0;   brep = 0; }

CBinTree::~CBinTree()
{}

bool CBinTree::find(int x, CNode**& p)
{
    for ( p = &root; *p && (*p)->v != x;
         p = &( (*p)->nodes[(*p)->v < x] ) );
    return *p != 0;
}
bool CBinTree::ins(int x)
{
    CNode** p;
    if ( find(x,p) ) return 0;
    *p = new CNode(x);
    return 1;
}

bool CBinTree::rem(int x)
{
    CNode** p;
    if ( !find(x,p) ) return 0;
    
    if ( (*p)->nodes[0] && (*p)->nodes[1] )//caso 2
    {
        CNode** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    CNode* t = *p;
    *p = (*p)->nodes[ (*p)->nodes[1] != 0 ];
    delete t;
    return 1;
}

CNode** CBinTree::rep(CNode** p)
{
    CNode** q = p;
    for ( q = &((*q)->nodes[!brep]); (*q)->nodes[brep];
          q = &((*q)->nodes[brep]) ) ;
    brep = !brep;
    return q;
}

/*
 CNode** CBinTree::rep(CNode** p)
 {
     CNode** q = p;
     q = &((*q)->nodes[brep]);
     while ( (*q)->nodes[!brep] )
         q = &((*q)->nodes[!brep]);
     brep = !brep;
     return q;
 }

 */

void CBinTree::print()
{
    inorder(root);
    std::cout<<" h = "<<height1(root);
    std::cout<<"\n";
}

void CBinTree::inorder(CNode* n)
{
    if ( !n ) return;
    inorder(n->nodes[0]);
    std::cout<<n->v<<" ";
    inorder(n->nodes[1]);
}

int CBinTree::height1(CNode* n)
{
    int maxh = 0;
    h1(root, 1, maxh);
    return maxh;
}

void CBinTree::h1(CNode* n, int h, int& maxh)
{
    if ( !n ) return;
    if ( h > maxh ) maxh = h;
    h1(n->nodes[0], h+1, maxh);
    h1(n->nodes[1], h+1, maxh);
}

int CBinTree::height2(CNode* n)
{
    
    return 0;
}

int main()
{
    CBinTree t;
    t.ins(60); t.print();
    t.ins(30); t.print();
    t.ins(70); t.print();
    t.ins(20); t.print();
    t.ins(40); t.print();
    t.ins(65); t.print();
    t.ins(80); t.print();
    t.ins(75); t.print();
    t.rem(20); t.print();
    t.rem(40); t.print();
    t.rem(65); t.print();
    t.rem(60); t.print();
}
