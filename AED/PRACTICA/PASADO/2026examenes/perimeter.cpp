#include <iostream>
#include <initializer_list>
#include <queue>
#include <stack>
using namespace std;
struct Node
{
    int value;
    Node* nodes[2];
    Node(int v) { value = v; nodes[0] = nodes[1] = nullptr; }
};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool find(int x, Node**& p);
    bool ins(int x);
    void ins(std::initializer_list<int> values);
    void print();
    void perimeter();
    void push_y_rotacion(queue<Node*>& cola, Node* n);
    void inorder(Node* n);

private:
    Node* root;
};

CBinTree::CBinTree()
{
    root = nullptr;
}

CBinTree::~CBinTree()
{
}

bool CBinTree::find(int x, Node**& p)
{
    for (p = &root; *p && (*p)->value != x;
        p = &((*p)->nodes[x > (*p)->value]));
    return *p && (*p)->value == x;
}

bool CBinTree::ins(int x)
{
    Node** p;
    if (find(x, p)) return 0;
    *p = new Node(x);
    return 1;
}

void CBinTree::ins(std::initializer_list<int> values)
{
    for (int x : values) ins(x);
}

void CBinTree::print()
{
    std::cout << "inorder: ";
    inorder(root);
    std::cout << "\n";
}

void CBinTree::perimeter()
{
    if (!root) return;
    queue<Node*> cola;
    queue<Node*> hojas;
    queue<Node*> izq;
    stack<Node*> der;
    cola.push(root);
    int  cola_size = cola.size();
    while (!cola.empty()) {

            izq.push(cola.front());
            der.push(cola.back());

        Node* tmp_izq = cola.front();
        Node* tmp_der = cola.back();
        for (int i = 0; i < cola_size; i++) {
            Node* tmp_h = cola.front();
            if (tmp_h->nodes[0]) cola.push(tmp_h->nodes[0]);
            if (tmp_h->nodes[1]) cola.push(tmp_h->nodes[1]);
            if (tmp_h != tmp_izq && tmp_h != tmp_der) { // si el nodo no se encuentra en los extremos:
                if (!tmp_h->nodes[0] || !tmp_h->nodes[1]) {  // y si no tiene hizo izquierdo o derecho           
                    push_y_rotacion(hojas, tmp_h);// se pushea en la cola de hojas
                }    
            } 
            cola.pop();
        }
        cola_size = cola.size();

    }
    for (; !izq.empty(); ) {
        cout << izq.front()->value << " ";
        izq.pop();
    }
    for (; !hojas.empty(); ) {
        cout << hojas.front()->value << " ";
        hojas.pop();
    }
    for (; !der.empty() && der.top() != root; ) {
        cout << der.top()->value << " ";
        der.pop();
    }


}
void CBinTree::push_y_rotacion(queue<Node*>& cola, Node* n) {
    if (cola.empty()) {
        cola.push(n);
        return;
    }
    int back_cola = cola.back()->value;
    int num_insertar = n->value;
    if (num_insertar >= back_cola) {
        cola.push(n);
        return;
    }
    else {
        bool insertado = false;
        int size_cola = cola.size();
        for (int i = 1; i <= size_cola; i++) {
            if (num_insertar < cola.front()->value && !insertado) {
                cola.push(n);
                insertado = true;
            }
            cola.push(cola.front());
            cola.pop();
        }
    }
}

void CBinTree::inorder(Node* n)
{
    if (!n) return;
    inorder(n->nodes[0]);
    std::cout << n->value << " ";
    inorder(n->nodes[1]);
}


int main()
{
    // Caso 1: arbol completo
    std::cout << "Caso 1: arbol completo" << std::endl;
    CBinTree t1;
    t1.ins({ 50,
             30, 70,
             20, 40, 60, 80,
             15, 25, 35, 45, 55, 65, 75, 90,
             12, 17, 22, 28, 32, 38, 42, 48, 52, 58, 62, 68, 72, 78, 85, 95 });
    t1.print();
    std::cout << "esperado:  50 30 20 15 12 17 22 28 32 38 42 48 52 58 62 68 72 78 85 95 90 80 70\n";
    std::cout << "perimeter: ";
    t1.perimeter();
    std::cout << "\n" << std::endl;

    // Caso 2: arbol con ultimo nivel incompleto
    std::cout << "Caso 2: arbol con ultimo nivel incompleto" << std::endl;
    CBinTree t2;
    t2.ins({ 50,
             30, 70,
             20, 40, 60, 80,
             15, 25, 35, 45, 55, 65, 75, 90,
             12, 22, 28, 38, 42, 48, 52, 62, 68, 78, 85, 95 });
    t2.print();
    std::cout << "esperado:  50 30 20 15 12 22 28 35 38 42 48 52 55 62 68 75 78 85 95 90 80 70\n";
    std::cout << "perimeter: ";
    t2.perimeter();
    std::cout << "\n" << std::endl;

    return 0;
}




