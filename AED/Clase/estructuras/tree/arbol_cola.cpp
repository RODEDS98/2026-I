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

Node::Node(int data){
    this->data=data;
    this->izq=nullptr;
    this->der=nullptr;
}
Node::Node(Node* izq, Node* der) {
    this->data=  izq->data + der->data, 
    this->izq=izq;
    this->der=der;
}


template<class T>
struct Cola {
    T A[40];
    T* Tail = nullptr;
    T* Head = nullptr;

    bool vacio();
    bool lleno();
    bool push(T a);
    bool pop(T& a);
    void print();
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
        } else {
            Tail = Head;
            *Tail = a;
            return true;
        }
    } else if (!lleno()) {
        if (Head <= Tail) {
            if (Tail != A + dim - 1) {
                Tail++;
                *Tail = a;
                return true;
            } else {
                Tail = A;
                *Tail = a;
                return true;
            }
        } else if (Tail < Head && Head - Tail != 1) {
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
    } else if (Head == Tail) {
        a = *Head;
        Head++;
        Tail = nullptr;
        return true;
    } else if (Head < Tail) {
        a = *Head;
        Head++;
        return true;
    } else if (Tail < Head) {
        if (Head != A + dim - 1) {
            a = *Head;
            Head++;
            return true;
        } else {
            a = *Head;
            Head = A;
            return true;
        }
    }
    return false;
}

template<class T>
void Cola<T>::print() {
    if (vacio()) {
        cout << "Cola vacía\n";
        return;
    }
    cout << "Contenido de la cola:\n";
    if (Head <= Tail) {
        for (T* i = Head; i <= Tail; i++) {
            cout << *i << " ";
        }
    } else {
        for (T* i = Head; i < A + (sizeof(A) / sizeof(*A)); i++) cout << *i << " ";
        for (T* i = A; i <= Tail; i++) cout << *i << " ";
    }
    cout << endl;
}


class Arbol {
public:
    Node* root;

    Arbol() : root(nullptr) {}

    Node* construir(int* ini, int* fin);
    void printTree(Node* root, int nivel = 0);
    void inorder(Node* n);
    void preorder(Node* n);
    void postorder(Node* n);
};

// Construcción tipo árbol de Huffman simple
Node* Arbol::construir(int* ini, int* fin) {
    Cola<Node*> C;

    for (int* p = ini; p != fin; p++) {
        Node* nuevo = new Node(*p);
        C.push(nuevo);
    }

    while (true) {
        Node *a, *b;
        if (!C.pop(a)) break;
        if (!C.pop(b)) {
            root = a;
            return a;
        }

        Node* nuevo = new Node(a, b);
        C.push(nuevo);

        if (C.Head == C.Tail) {
            Node* raiz;
            C.pop(raiz);
            root = raiz;
            return raiz;
        }
    }
    return nullptr;
}

void Arbol::printTree(Node* root, int nivel) {
    if (!root) return;

    for (int i = 0; i < nivel; i++)
        cout << "   ";
    cout << root->data << "\n";

    printTree(root->izq, nivel + 1);
    printTree(root->der, nivel + 1);
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
    int dim=16;
    int Arr[dim] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29};
    
    for(int* p=Arr; p<Arr+dim;p++)
        cout<<*p<<" ";
    cout<<endl;    
    Arbol A;
    A.construir(Arr, Arr + dim);

    cout << "Árbol :\n";
    A.printTree(A.root);

    cout << "\nRecorrido inorder: ";
    A.inorder(A.root);

    cout << "\nRecorrido preorder: ";
    A.preorder(A.root);

    cout << "\nRecorrido postorder: ";
    A.postorder(A.root);

    cout << endl;
    return 0;
}
