#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* izq;
    Node* der;
    Node(int v);
    Node(Node* izq, Node* der);
};

Node::Node(int data) {
    this->data = data;
    this->izq = nullptr;
    this->der = nullptr;
}

Node::Node(Node* izq, Node* der) {
    this->data = izq->data + der->data;
    this->izq = izq;
    this->der = der;
}

// =================== CLASE COLA ===================
template<class T>
struct Cola {
    T A[40];
    T* Tail = nullptr;
    T* Head = nullptr;

    bool vacio();
    bool lleno();
    bool push(T a);
    bool pop(T& a);
};

template<class T>
bool Cola<T>::vacio() {
    return (Tail == nullptr);
}

template<class T>
bool Cola<T>::lleno() {
    int dim = sizeof(A) / sizeof(*A);
    if (!vacio()) {
        if (Head < Tail)
            return (Tail - Head == dim - 1);
        else
            return (!(Head - Tail - 1));
    }
    return false;
}

template<class T>
bool Cola<T>::push(T a) {
    int dim = sizeof(A) / sizeof(*A);
    if (vacio()) {
        if (Head == nullptr) {
            Head = A;
            *Head = a;
            Tail = Head;
            return true;
        }
        else {
            Tail = Head;
            *Tail = a;
            return true;
        }
    }
    else if (!lleno()) {
        if (Head <= Tail) {
            if (Tail != A + dim - 1) {
                Tail++;
                *Tail = a;
                return true;
            }
            else {
                Tail = A;
                *Tail = a;
                return true;
            }
        }
        else if (Tail < Head && Head - Tail != 1) {
            Tail++;
            *Tail = a;
            return true;
        }
    }
    cout << "Cola llena\n";
    return false;
}

template<class T>
bool Cola<T>::pop(T& a) {
    int dim = sizeof(A) / sizeof(*A);
    if (vacio()) {
        cout << "Cola vacía\n";
        return false;
    }
    else if (Head == Tail) {
        a = *Head;
        Head++;
        Tail = nullptr;
        return true;
    }
    else if (Head < Tail) {
        a = *Head;
        Head++;
        return true;
    }
    else if (Tail < Head) {
        if (Head != A + dim - 1) {
            a = *Head;
            Head++;
            return true;
        }
        else {
            a = *Head;
            Head = A;
            return true;
        }
    }
    return false;
}


class Arbol {
public:
    Arbol() { root = nullptr; }

    Node* get_root() { return root; }

    Node* construir(int* A, int* B);
    void print(Node* n, int nivel = 0);
    void inorder(Node* n);
    void preorder(Node* n);
    void postorder(Node* n);

private:
    Node* root;
};

Node* Arbol::construir(int* A, int* B) {
    Cola<Node*> cola;

    for (int* p = A; p < B; p++) {
        Node* nodo = new Node(*p);
        cola.push(nodo);
    }

    while (true) {
        Node* a;
        Node* b;

        if (!cola.pop(a)) break;
        if (!cola.pop(b)) {
            root = a;
            return a;
        }

        Node* nodo = new Node(a, b);
        cola.push(nodo);

        if (cola.Head == cola.Tail) {
            Node* r;
            cola.pop(r);
            root = r;
            return r;
        }
    }
    return nullptr;
}


void Arbol::print(Node* n, int nivel) {
    if (!n) return;

    print(n->der, nivel + 1);

    for (int i = 0; i < nivel; i++)
        cout << "     ";  // espacios
    cout << n->data << "\n";

    print(n->izq, nivel + 1);
}


void Arbol::inorder(Node* n) {
    if (!n) return;
    inorder(n->izq);
    cout << n->data << " ";
    inorder(n->der);
}

void Arbol::preorder(Node* n) {
    if (!n) return;
    cout << n->data << " ";
    preorder(n->izq);
    preorder(n->der);
}

void Arbol::postorder(Node* n) {
    if (!n) return;
    postorder(n->izq);
    postorder(n->der);
    cout << n->data << " ";
}

int main() {
    int dim = 16;
    int Arr[dim] = { 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29 };


    for (int* p = Arr; p < Arr + dim; p++)
        cout << *p << " ";
    cout << "\n\n";

    Arbol A;
    A.construir(Arr, Arr + dim);

    cout << "Árbol :\n";
    A.print(A.get_root());

    cout << "\nInorder: ";
    A.inorder(A.get_root());
    cout << "\nPreorder: ";
    A.preorder(A.get_root());
    cout << "\nPostorder: ";
    A.postorder(A.get_root());

    cout << endl;
    return 0;
}