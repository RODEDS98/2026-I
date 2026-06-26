#include <iostream>
#include <stack>
#include <queue>
#include <algorithm> // Para std::max
using namespace std;

// 1. El Nodo ahora incluye la altura
struct AVLNode {
	int v;
	AVLNode* left;
	AVLNode* right;
	int height; // Altura del subárbol con raíz en este nodo
	AVLNode(int _v) {
		left = right = 0;
		v = _v;
		height = 1; // Un nodo hoja siempre tiene altura 1
	}
};

class AVLTree {
	AVLNode* root;
	bool lado_reemp;

	// --- FUNCIONES AUXILIARES DE AVL ---

	// Obtiene la altura de un nodo (0 si es nulo)
	int height(AVLNode* p) {
		if (p == nullptr) return 0;
		return p->height;
	}

	// Actualiza la altura de un nodo basado en sus hijos
	void updateHeight(AVLNode* p) {
		if (p != nullptr) {
			p->height = 1 + std::max(height(p->left), height(p->right));
		}
	}

	// Calcula el Factor de Balance (Altura(Derecha) - Altura(Izquierda))
	int getBalanceFactor(AVLNode* p) {
		if (p == nullptr) return 0;
		return height(p->right) - height(p->left);
	}

	// --- ROTACIONES ---

	// Rotación Simple a la Izquierda (Caso RR)
	AVLNode* rotateLeft(AVLNode* x) {
		AVLNode* y = x->right;
		AVLNode* T2 = y->left;
		
		y->left = x;
		x->right = T2;
		
		updateHeight(x); // Actualiza x primero (ahora es hijo)
		updateHeight(y); // Actualiza y después (ahora es padre)
		
		return y; // y es la nueva raíz del subárbol
	}

	// Rotación Simple a la Derecha (Caso LL)
	AVLNode* rotateRight(AVLNode* y) {
		AVLNode* x = y->left;
		AVLNode* T2 = x->right;
		
		x->right = y;
		y->left = T2;
		
		updateHeight(y); // Actualiza y primero (ahora es hijo)
		updateHeight(x); // Actualiza x después (ahora es padre)
		
		return x; // x es la nueva raíz del subárbol
	}
	
	// --- MÉTODOS PÚBLICOS ---

public:
	AVLTree() {
		root = 0;
		lado_reemp = 0;
	}
	~AVLTree() {
		cout << "Comienza liberacion" << endl;
		this->clear(root);
		root = 0;
		cout << "Termina liberacion" << endl;
	}
	
	bool ins(int x) { // Revisar
		// Pila para guardar punteros a los punteros del camino
		stack<AVLNode**> path;
		AVLNode** pp = &root;

		// 1. Encontrar la ubicación y guardar el camino
		while (*pp != nullptr) {
			path.push(pp); // Guarda el puntero al puntero del padre
			if (x < (*pp)->v) {
				pp = &((*pp)->left);
			} else if (x > (*pp)->v) {
				pp = &((*pp)->right);
			} else {
				return false; // Duplicado
			}
		}

		*pp = new AVLNode(x); // Inserta el nuevo nodo
		
		// 2. Desenrollar la pila, actualizar alturas y rebalancear
		while (!path.empty()) {
			pp = path.top();
			path.pop();
			AVLNode* node = *pp; // El nodo ancestro actual

			updateHeight(node);
			int balance = getBalanceFactor(node);

			// Rebalancear si es necesario
			
			// Caso Izquierda-Izquierda (LL) o Izquierda-Derecha (LR)
			if (balance < -1) { 
				if (getBalanceFactor(node->left) > 0) { // Caso LR
					node->left = rotateLeft(node->left);
				}
				*pp = rotateRight(node); // Caso LL (o LL después de LR)
			}
			// Caso Derecha-Derecha (RR) o Derecha-Izquierda (RL)
			else if (balance > 1) { 
				if (getBalanceFactor(node->right) < 0) { // Caso RL
					node->right = rotateRight(node->right);
				}
				*pp = rotateLeft(node); // Caso RR (o RR después de RL)
			}
		}
		return true;
	}


// 3. Eliminación con rebalanceo usando una pila
	bool rem(int x) {
		stack<AVLNode**> path;
		AVLNode** p = &root;
		
		// 1. Encontrar el nodo y guardar el camino
		while (*p != nullptr && (*p)->v != x) {
			path.push(p);
			if (x < (*p)->v)
				p = &((*p)->left);
			else
				p = &((*p)->right);
		}
		
		if (!(*p)) return false; // No encontrado
		path.push(p); // Guarda el puntero al nodo a eliminar

		// 2. Manejar el caso de 2 hijos (copiar sucesor)
		if ((*p)->left && (*p)->right) {
			AVLNode** q = fnd_reemp(p, path); 
			(*p)->v = (*q)->v;
			p = q; // 'p' ahora apunta al sucesor original
		}

		// 3. Eliminar el nodo (que ahora tiene 0 o 1 hijo)
		AVLNode* t = *p;
		*p = t->left ? t->left : t->right;
		delete t;

		// 4. Desenrollar la pila y rebalancear TODO el camino hacia la raíz
		while (!path.empty()) {
		    
			AVLNode** pp = path.top();
			path.pop();
			if ( !(*pp) ) continue;
			
			AVLNode* node = *pp;
    		updateHeight(*pp); // Forzamos la actualización de las alturas de sus hijos primero
            int balance = getBalanceFactor(*pp);
            
            if (balance < -1) {
                if (getBalanceFactor((*pp)->left) > 0)
                    (*pp)->left = rotateLeft((*pp)->left);
            
                *pp = rotateRight(*pp);
            }
            else if (balance > 1) {
                if (getBalanceFactor((*pp)->right) < 0)
                    (*pp)->right = rotateRight((*pp)->right);
            
                *pp = rotateLeft(*pp);
            }
		}
		return true;
	}

        	/*
                                                        			
                                                        			stack<AVLNode**> aux = path;
                                                                    cout << "Camino:" << endl;
                                                                    while (!aux.empty()) {
                                                                        AVLNode** x = aux.top();
                                                                        aux.pop();
                                                                        if (*x)  cout << (*x)->v << endl;
                                                                    }
                                                                    */

	// 4. fnd_reemp modificado para añadir al 'path'
    AVLNode** fnd_reemp(AVLNode** p, stack<AVLNode**>& path)
    {
        AVLNode** q;
        
        if (!lado_reemp){
            q = &((*p)->right);
            path.push(q);
            while ((*q)->left){
                q = &((*q)->left);
                path.push(q);
            }
        }
        else{
            q = &((*p)->left);
            path.push(q);
            while ((*q)->right){
                q = &((*q)->right);
                path.push(q);
            }
        }
    
        lado_reemp = !lado_reemp;
        return q;
    }
    
	bool find(int x, AVLNode**& p) {
		while (*p && (*p)->v != x) {
			if (x < (*p)->v)
				p = &((*p)->left);
			else
				p = &((*p)->right);
		}
		return *p;
	}

	void print() {
		preorder(root);
		cout << endl;
	}

	void preorder(AVLNode* p) {
		if (!p) return;
		cout << p->v << ' ';
		preorder(p->left);
		preorder(p->right);
	}
	void inorder(AVLNode* p) {
		if (!p) return;
		inorder(p->left);
		cout << p->v << ' ';
		inorder(p->right);
	}

	void inorderST() {
		std::stack<AVLNode*> pila;
		AVLNode* actual = root;
		std::cout << "In-Orden con Stack: ";
		while (actual != 0 || !pila.empty()) {
			while (actual != 0) {
				pila.push(actual);
				actual = actual->left;
			}
			actual = pila.top();
			pila.pop();
			std::cout << actual->v << " ";
			actual = actual->right;
		}
		std::cout << std::endl;
	}

	void Levels(AVLNode* p) {
		if (!p) return;
		queue<AVLNode*> q;
		q.push(p);
		while (!q.empty()) {
			AVLNode* c = q.front();
			cout << c->v << "(h=" << c->height << ", b=" << getBalanceFactor(c) << ") ";
			if (c->left) q.push(c->left);
			if (c->right) q.push(c->right);
			q.pop();
		}
	}

	void PrintLevels() {
		cout << endl << "Recorrido por Niveles (valor, altura, balance):" << endl;
		Levels(root);
		cout << endl;
	}

	// 5. La altura máxima ahora es trivial
	int alturaMax() {
		return height(root);
	}

	void clear(AVLNode* p) {
		if (!p) return;
		clear(p->left);
		clear(p->right);
		delete p;
		// Quitado el cout para que la salida del destructor sea más limpia
	}
	
	AVLNode* get_root() { return root; }
};

int main() {
    AVLTree t;

    t.ins(30);
    t.ins(20);
    t.ins(10);

    std::cout << "CASO 1: ROTACION SIMPLE A LA DERECHA (II)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 20 10" << std::endl;
    std::cout << "  -> ESPERADO :  preorder 20 10 30" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    t.ins(40);
    t.ins(50);

    std::cout << "CASO 2: ROTACION SIMPLE A LA IZQUIERDA (DD)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 20 10 40 50" << std::endl;
    std::cout << "  -> ESPERADO :  preorder 20 10 40 30 50" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    t.ins(5);
    t.ins(8);

    std::cout << "CASO 3: ROTACION DOBLE IZQUIERDA-DERECHA (ID)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 20 10 5 8 40 50" << std::endl;
    std::cout << "  -> ESPERADO :  preorder 20 8 5 10 40 30 50" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    t.ins(45);
    t.ins(42);

    std::cout << "CASO 4: ROTACION DOBLE DERECHA-IZQUIERDA (DI)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 20 10 5 8 40 50 45 42" << std::endl;
    std::cout << "  -> ESPERADO :  preorder 20 8 5 10 40 30 45 42 50" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    t.rem(50);

    std::cout << "CASO 5: ELIMINACION NODO HOJA (50)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 20 10 5 8 40 45 42" << std::endl;
    std::cout << "  -> ESPERADO :  preorder 20 8 5 10 40 30 45 42" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    t.rem(45);

    std::cout << "CASO 6: ELIMINACION NODO CON UN HIJO (45)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 20 10 5 8 40 42" << std::endl;
    std::cout << "  -> ESPERADO :  preorder 20 8 5 10 40 30 42" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    t.rem(20);

    std::cout << "CASO 7: ELIMINACION NODO CON DOS HIJOS (20)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 10 5 8 40 42" << std::endl;
    std::cout << "  -> ESPERADO :  preorder 10 8 5 40 30 42" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    t.ins(25);
    t.ins(28);

    std::cout << "CASO 8: INSERCION CON ROTACION EN CASCADA (25, 28)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 10 5 8 25 28 40 42" << std::endl;
    std::cout << "  -> ESPERADO :  preorder 10 8 5 40 28 25 30 42" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    t.rem(42);

    std::cout << "CASO 9: ELIMINACION QUE PROVOCA ROTACION DOBLE (42)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 10 5 8 25 28 40 " << std::endl;
    std::cout << "  -> ESPERADO :  preorder 10 8 5 28 25 40 30" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    t.rem(10);

    std::cout << "CASO 10: ELIMINACION DE LA RAIZ PRINCIPAL (10)" << std::endl;
    std::cout << "  -> SIN AVL  :  preorder 30 8 5 25 28 40 " << std::endl;
    std::cout << "  -> ESPERADO :  preorder 28 8 5 25 40 30" << std::endl;
    std::cout << "  -> OBTENIDO :  "; t.print();
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    return 0;


}