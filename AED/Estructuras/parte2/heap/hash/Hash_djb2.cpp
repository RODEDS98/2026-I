// HASH PARA UNA LISTA DE NOMBRES STRING...

#include <iostream>
#include <list>

struct fn1 {
    int operator()(int x) {
        return x * x;
    }
};

struct fn2 {
    unsigned int operator()(std::string x) {
        unsigned int hash = 5381;

        for (char c : x) {
            hash = hash * 33 + c;
        }

        return hash;
    }
};

template<class T>
class xlist {
private:
    std::list<T> data;
public:
    void ins(T x) {
        data.push_back(x);
    }
    void rem(T x) {
        data.remove(x);
    }
    bool find(T x) {
        for (T e : data) {
            if (e == x) return 1;
        }
        return 0;
    }
    /* // SERIA REDUNDANTE PASAR EL MISMO VALOR Y TAMBIEN ES ERRONEO CAMBIAR UNA SEMILLA (ACA LOS NOMBRES SE PASAN A LA FUNCION HASH fn2)
     // Seria erroneo ya que al buscar el nuevo valor en la tabla , la funcion te arrojaria otro casillero... al cambiarlo directamente te quedarias en el mismo casillero
     // y al buscarlo con find daria que no existe ... cuando si existe .

     
    T*  get(T x) {
        for (auto& e : data) {
            if (e == x) return &e;
        }
        return nullptr;
    }
    */

    int get(T x) {
        int i = 0;
        for (auto& e : data) {            
            if (e == x) return i;
            i++;            
        }
        return -1;
    }

    void print() {
        for (T e : data) {
            std::cout << e << ", ";
        }
        std::cout << '\n';
    }
};

template<class T, class S, class F, int Z>
class CHashTable {
private:
    S* data1;
    F fun;
public:
    CHashTable() {
        data1 = new S[Z];
    }
    ~CHashTable() {
        delete[] data1;
    }
    void ins(T x) {
        unsigned int idx = fun(x) % Z;
        data1[idx].ins(x);
    }
    void rem(T x) {
        unsigned int idx = fun(x) % Z;
        data1[idx].rem(x);
    }
    bool find(T x) {
        unsigned int idx = fun(x) % Z;
        return data1[idx].find(x);
    }

    void print() {
        for (int i = 0; i < Z; i++) {
            std::cout << "[" << i << "]: ";
            data1[i].print();
        }
    }  
    /*error
    T*  get(T x) {
        unsigned int idx = fun(x) % Z;
        return data1[idx].get(x);
    }

    
    T operator ()(T a, T b) {
        T* tmp = get(a);
        if (tmp) {
            *tmp = b;
            return *tmp;
        }
        return "El dato no existe";
        

    }
    */

    unsigned int get(T x) {
        int indice = fun(x) % Z;
        int indice_y = data1[indice].get(x);
        if (indice_y  >= 0) {
            std::cout << " ( " << indice << " , "<< indice_y << " ) " << std::endl;
            return indice;
        }
        std::cout <<" No existe " << std::endl;
        return -1;
    }

    bool operator ()(T a, T b) {
        if (find(a)) {
            rem(a);
            ins(b);
            return true;
        }
        return false;

    }

};

int main() {
    CHashTable<std::string, xlist<std::string>, fn2, 31> cht;

    std::string nombres_prueba[] = {
        "Julio Eduardo Pino Charun",
        "Gerardo", "Gerald", "Geraldo",
        "Ana Clara", "Ana Maria", "Ana",
        "Beto", "Carlos Alberto", "Diana",
        "Esteban", "Federico", "Gustavo",
        "Hector", "Isabel", "Javier",
        "Karla", "Luis Fernando", "Maria",
        "Natalia", "Oscar", "Patricia",
        "Quirino", "Rosa", "Sofia",
        "Tomas", "Ursula", "Valeria",
        "Walter", "Ximena", "Yolanda", "Zoe",
        "Linus Torvalds", "Bjarne Stroustrup", "Ada Lovelace"
    };

    int cantidad = sizeof(nombres_prueba) / sizeof(nombres_prueba[0]);

    for (int i = 0; i < cantidad; i++) {
        cht.ins(nombres_prueba[i]);
    }
    
    cht.print();
    /*
    for (int i = 0; i < cantidad; i++) {
        cht.rem(nombres_prueba[i]);
    }
    cht.print();
    */
    std::string Linus = "Linus Torvalds";
    std::cout << cht(Linus, "Linus TorvaldS") << std::endl;
    Linus = "Linus TorvaldS" ;
    cht.print();
    cht.get(Linus);
    return 0;
}
