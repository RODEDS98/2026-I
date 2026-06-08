#include <iostream>
#include <list>
using namespace std;

class Elemento {  // element  [0]-0-0-0-0-0-0-0
	
	Elemento(int f, int c ,int v){
		this->f = f;
		this->c = c;
		this->v = v;
	}
	
	int f;
	int c;
	int v;	  // functor ?
	
};

template<Class M>
class Adaptador1 { // list adapter
	list<M> data;
	
	void insert(const T& value) { // 1.1 solo pushea en la lista, sin orden 
		data.push_back(value);    // (recordando que el valor pusheado es de tipo Elemento
	}
	
	T* get(const T& key) {          // 2.1 solo pushea en la lista, sin orden 
		for(auto& i:key){
			if(i == key) return i;
		}
		return nullptr;
	}
	
	bool remove(const T& value) {
		auto it = std::find(data.begin(),data.end() , value );
		if(it == data.end()) return false
		data.erase(it);
		return true;
	}
	
	

	T* find(const T& key) {         
		
	}
	
};


// hash
template<class T, class L, class F, int Z>
class Adaptador2 {
	private:
	L arr[Z];
	F H_func;
	
	public:
	void insert(const T& value) {        // 1.0 busca el indice correcto con la funcion e ingresa
		int indice = H_func (value) % Z; // aqui solo hace que cuando el H_funcion() use este operador 
		arr[indice].insert(value);	     // haga que el contenedor que es pasado por parametro hashee
	}
	
	T* find(const T& key) {
		int indice = H_func (value) % Z;		
		return arr[indice].get(key); 
	}	
	//  return arr[indice].find(key);  _ 2.0 Seria asi pero... 
	//  estamos encapsulando, no podemos tocar la lista ya que apenas fue creada en el adaptador 1 
	
	bool remove(const T& value) {         // 3.0 remueve
		int indice = H_func (value) % Z;
		bool existe = arr[indice].remove(value);
		return existe;
	}
};

class H_funcion {  
	
	operator ()(const Elemento& elem){
		return elem.f*31 + elem.c;
	}


};

class Adaptador3 {  // matrix
	Adaptador2 < Elemento , Adaptador1<Elemento> ,  H_func , 100> hash;
	
};

int Main(){

	std::cout << "=== Probando mi Tabla Hash desde Cero ===" << std::endl;

	
	return 0;
}
