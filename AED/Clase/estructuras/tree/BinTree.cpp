#include <iostream>

struct CNode
{
    CNode(int _v)
    { v = _v; left = right = 0; }
    int v;
    CNode *left, *right;
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
    p = &root;
    while ( *p && (*p)->v != x )
        if ( (*p)->v < x )
            p = &( (*p)->right );
        else
            p = &( (*p)->left );
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
    
    if ( (*p)->left && (*p)->right )//caso 2
    {
        CNode** q = rep(p);
        (*p)->v = (*q)->v;
        p = q;
    }
    CNode* t = *p;
    if ( (*p)->right )
        *p = (*p)->right;
    else
        *p = (*p)->left;
    delete t;
    return 1;
}

/*
 bool CBinTree::rem(int x)
 {
     CNode** p;
     if ( !find(x,p) ) return 0;
     
     if ( (*p)->left && (*p)->right )//caso 2
     {
         CNode** q = rep(p);
         (*p)->v = (*q)->v;
         p = q;
     }
     
     if ( ( (*p)->left && !(*p)->right ) ||
          ( !(*p)->left && (*p)->right ) )
     {
         CNode* t = *p;
         if ( (*p)->right )
             *p = (*p)->right;
         else
             *p = (*p)->left;
         delete t;
     }
     
     if ( !(*p)->left && !(*p)->right )
     {
         delete *p;
         *p = 0;
     }
     return 1;
 }

 */

CNode** CBinTree::rep(CNode** p)
{
    CNode** q = p;
    if ( brep == 1 )
    {
        q = &((*q)->right);
        while ( (*q)->left )
            q = &((*q)->left);
    }
    else
    {
        q = &((*q)->left);
        while ( (*q)->right )
            q = &((*q)->right);
    }
    brep = !brep;
    return q;
}

void CBinTree::print()
{
    inorder(root);
    std::cout<<"\n";
}

void CBinTree::inorder(CNode* n)
{
    if ( !n ) return;
    inorder(n->left);
    std::cout<<n->v<<" ";
    inorder(n->right);
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
