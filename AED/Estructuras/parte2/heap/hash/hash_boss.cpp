
#include <iostream>
#include <list>
using namespace std;



struct Adaptador1 { // contenedor
	Adaptador1(int f, int c, int v) {
		this->f = f;
		this->c = c;
		this->v = v;
	}
	int f;
	int c;
	int v;
};

template < class M >
struct Adaptador2 {  // lista
	list<M> fila;

	void ins() {

	}
	void rem() {

	}
	bool find() {
		if (fila.empty()) return false;
		for (auto i : fila) {
			if (i==) return true;
		}
		return false
	}


};

template < class M, class L , class F , class Z>
struct Adaptador3 { // hash
	L tabla[Z];

	void ins(const M& value) {
		size_t indice = value    %  Z ; 
		tabla[indice].fila.push()
	}
	void rem() {

	}
	void get() {

	}


};

struct Sparc { // sparce

};





int main() {

}
