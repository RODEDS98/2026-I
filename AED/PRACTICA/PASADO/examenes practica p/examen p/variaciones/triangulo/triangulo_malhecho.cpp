#include <iostream>
#include <deque> //Adicional
#include <queue>
#include <stack>
using namespace std;

struct CNode
{
	CNode(int _v)
	{
		v = _v; left = right = 0;
	}
	int v;
	CNode* left, * right;
};

class CBinTree
{
public:
	CBinTree();
	~CBinTree();
	bool find(int x, CNode**& p);
	bool ins(int x);
	void inorder(CNode* n);
	void inorder_mod(CNode* n, int min, int max);
	void print();
	int get_altura(CNode* n);
	void printRange(int min, int max);
	void print_nivel();
	void contarNodosPorNivel(CNode* n, int k);
	void print_inv(CNode* p);
	void vecinos_body(int x,int k);
	void vecinos(CNode* n, queue<CNode*> &q, int val, int k);
	void zig_zag();
	void triangulo();
	void derecha(CNode* n,int &i);
	void bordes(CNode* n,int& i, int& j, CNode*& m);
private:
	CNode* root;
	void deleteTree(CNode* n);
};

CBinTree::CBinTree()
{
	root = 0;
}

CBinTree::~CBinTree()
{
	deleteTree(root);
}



void CBinTree::deleteTree(CNode* n)
{
	if (!n) return;
	deleteTree(n->left);
	deleteTree(n->right);
	delete n;
}

int CBinTree::get_altura(CNode* n) {

	if (!n) return 0;	
	
	int izq = get_altura(n->left);
	int der = get_altura(n->right);

	if (der >= izq) return der+1;
	return izq+1;

}

void CBinTree::bordes(CNode* n,int &i, int& j, CNode* &m) {
	if (!(n->left)) return;
	if (n == root) {
		bordes(n->left, i,j,m);
		return;
	}

	for (int k=i ;k>0 ; k-- ) {
		cout << "   ";
	}	
	cout << n->v ;
	i--;

	for (int k = j; k > 0; k--) {
		cout << " ";
	}
	j=j*2;

	CNode* m_tmp = m;
	if (m_tmp) {

		//extra
		if(m_tmp)cout << m_tmp->v << endl;

		if (m_tmp->right->right) {
			m_tmp = m_tmp->right;
		}
		else m_tmp = nullptr;
	}
	cout << endl;


	bordes(n->left,i,j, m_tmp);
}
void CBinTree::derecha(CNode* n,int &i) {
	if (!n) return;

}

void CBinTree::triangulo()
{
	cout << "Triangulo : " << endl;
	int altura = get_altura(root);
	int n_nodos_lastnivel = 1;
	for (int i = 0; i < altura; i++) {
		n_nodos_lastnivel *= 2;
	}
	cout <<"nodos en el ultimo nivel : " << n_nodos_lastnivel << endl << endl << endl;
	int i = n_nodos_lastnivel/2;
	int j = 3;
	CNode* m = nullptr;

	if (root) {
		if (root->right) m = root->right;
		for (int j = i; j > 0; j--) {
			cout << "   ";
		}
		cout << root->v << endl;
	}
	i--;
	j=1+j;

	bordes(root, i, j,m);

	for (int j = i/2; j > 0; j--) {
		cout << "    ";
	}

	queue<CNode*> q;
	q.push(root);
	int nivel = 0;

	while (!q.empty()) {
		int cantidad = q.size();
		if (nivel == altura-1) {
			for (int i = 0; i < cantidad; i++) {
				CNode* actual = q.front();
				cout << actual->v << " ";
				q.push(actual);
				q.pop();
			}
			break;
		}
		for (int i = 0; i < cantidad; i++) {
			CNode* actual = q.front();
			if (actual->left) q.push(actual->left);
			if (actual->right) q.push(actual->right);
			q.pop();
		}
		nivel++;
		

	}
	cout << endl << endl;
}

bool CBinTree::find(int x, CNode**& p)
{
	p = &root;
	while (*p && (*p)->v != x)
		if ((*p)->v < x)
			p = &((*p)->right);
		else
			p = &((*p)->left);
	return *p != 0;
}

bool CBinTree::ins(int x)
{
	CNode** p;
	if (find(x, p)) return 0;
	*p = new CNode(x);
	return 1;
}

void CBinTree::print()
{
	inorder(root);
	std::cout << "\n";
}

void CBinTree::inorder(CNode* n)
{
	if (!n) return;
	inorder(n->left);
	std::cout << n->v << " ";
	inorder(n->right);
}
void CBinTree::vecinos(CNode* n, queue<CNode*> &q, int x, int k)
{
	if (!n) return;

	vecinos(n->left, q, x, k); 

	if( q.size() < k ) {
		q.push(n);
	}
	else if(   abs( (n->v) - x) < abs((q.front()->v) - x)){
		q.push(n);
		q.pop();
	}
	else {

		return;
	}

	vecinos(n->right, q, x, k);
}
void CBinTree::vecinos_body(int x, int k)
{
	std::queue<CNode*> q;
	std::cout << "\n \n\n VECINOS: " << endl;
	vecinos(root, q, x, k);
	for (; !(q.empty()); q.pop()) {
		cout << " " << (q.front())->v;
	}
	std::cout << endl;

	vecinos(root, q, 88, 3);
	for (; !(q.empty()); q.pop()) {
		cout << " " << (q.front())->v;
	}std::cout << endl;

	vecinos(root, q, 76, 2);
	for (; !(q.empty()); q.pop()) {
		cout << " " << (q.front())->v;
	}std::cout << endl;
}






void CBinTree::inorder_mod(CNode* n, int min, int max)
{
	if (!n) return;

	if (n->v >= min) {
		inorder_mod(n->left, min, max);
	}

	if (n->v >= min && n->v <= max) {
		std::cout << n->v << " ";
	}


	if (n->v <= max) {
		inorder_mod(n->right, min, max);
		//std::cout << n->v << " ";
		//return;
	}

	return;
}

void CBinTree::contarNodosPorNivel(CNode* n, int k) {

	if (!n) return;
	queue<CNode*> q;
	q.push(n);
	int nivel = 0;

	while (!q.empty()) {
		int cantidad = q.size(); // Aquí tienes el dato        
		// Si es el nivel actual se imprime la cola   
		if (nivel == k) {
			for (int i = 0; i < cantidad; i++) {
				CNode* actual = q.front();
				cout << actual->v << " ";
				q.push(actual);
				q.pop();
			}
			break;
		}
		// operacion ingresar nuevos nodos mientras se borra su cabeza
		for (int i = 0; i < cantidad; i++) {
			CNode* actual = q.front();
			if (actual->left) q.push(actual->left);
			if (actual->right) q.push(actual->right);
			q.pop();
		}
		nivel++;


	}
}

void CBinTree::zig_zag() {
	stack<CNode*> q;
	stack<CNode*> r;

	if (!root) return;
	bool modo = 0;  // primero hacia la derecha
	int size_x;

	if (!modo) {
		q.push(root);
		size_x = q.size();
	}		
	else {
		r.push(root);
		size_x = r.size();
	}		
	while( !(q.empty()) || !(r.empty()) ){
		

			if( modo) {
				for ( ; !(r.empty()) ; r.pop() ) {
					cout << (r.top())->v << " ";
					if ((r.top())->right) q.push((r.top())->right);
					if ((r.top())->left ) q.push((r.top())->left );	
				}
				cout << endl;
			}

			else {
				for (; !(q.empty()) ; q.pop() ) {
					cout << (q.top())->v  << " ";
					if ((q.top())->left) r.push((q.top())->left);
					if ((q.top())->right) r.push((q.top())->right);
				}
				cout << endl;
			}
			modo = !modo;
		}
}

void CBinTree::printRange(int min, int max)
{
	//cout << " imprimir rango" <<endl;
	inorder_mod(root, min, max);


}

void CBinTree::print_nivel()
{
	cout << endl << " imprimir niveles" << endl;
	contarNodosPorNivel(root, 2);
	std::cout << endl << " IMPRIMIR INV ";
	print_inv(root);
	std::cout << endl << " IMPRIMIR  ";
	inorder(root);
	vecinos_body(33, 4);

}

void CBinTree::print_inv(CNode* p)
{
	if (!p) return;
	print_inv(p->right);
	cout << p->v << " ";
	print_inv(p->left);

}
// 55 51 47 (44) (41) (36) (33) 20
// 55 57


int main()
{
	CBinTree t;
	t.ins(55); t.ins(41); t.ins(77);
	t.ins(33); t.ins(47); t.ins(61);
	t.ins(88); t.ins(20); t.ins(36);
	t.ins(44); t.ins(51); t.ins(57);
	t.ins(65); t.ins(80); t.ins(99);

	cout << "Arbol completo: ";
	t.print();

	std::cout << "\nRango [35, 75]: ";
	t.printRange(35, 75);
	// Salida esperada: 35 40 45 60 62 65 68 70 75

	std::cout << "\nRango [40, 70]: ";
	t.printRange(40, 70);
	// Salida esperada: 40 45 60 62 65 68 70

	std::cout << "\nRango [10, 25]: ";
	t.printRange(10, 25);
	// Salida esperada: 15 20 25

	std::cout << "\nRango [65, 100]: ";
	t.printRange(65, 100);
	// Salida esperada: 65 68 70 75 80 85
	t.print_nivel();
	std::cout << "\n\n";

	std::cout << "\nZIG ZAG" << endl;;
	t.zig_zag();
	t.triangulo();
	return 0;
}
