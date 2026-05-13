#include <iostream>
#include <vector>

using namespace std;

template<class T>
class heap {
public:
    heap();
    ~heap();
    void push_back(T val);
    void make_heap(T* ptr1, T* ptr2); // convierte
    void push_heap();
    bool pop_heap();
    void SiftDown(T* p,T* ptr1,T* ptr2);
    void SiftDown(T* x);        // Se usa en el make_heap. El elemento está arriba y "baja" comparándose con sus hijos.
    void SiftUp(T* x);            // Se usa en el push. El elemento nuevo entra al final y "sube" comparándose con su padre.
    void swap(T* A, T* B);
    //sort_heap(); // orden ascendente
    //is_heap(T val);
    //is_heap_until();  //?


private:
    vector<T> v;

};

template <class T>
heap<T>::heap() {

}

template <class T>
heap<T>::~heap() {

}



template <class T>
void heap<T>::push_back(T val) {
    v.push_back(val);
}

template <class T>
void heap<T>::swap(T* A, T* B) {
    if (A == B) return; // Si apuntan al mismo sitio, no hay nada que hacer
    T temp = *A;        // Guardamos el valor de a
    *A = *B;            // Ponemos el valor de b en a
    *B = temp;          // Ponemos el valor guardado (original de a) en b
}


template <class T>
void heap<T>::SiftDown(T* p, T* ptr1, T* ptr2) {
    int rango = ptr2 - ptr1; //  0 1 2  ... rango
    int pos_p = p - ptr1;    //  0 1 p 3 4 5  ... rango
    T* piv_padre = p;
    T* ptr_max = p; // se asume que el maximo es el puntero p 

    int pos_hijo1 = (piv_padre - ptr1) * 2 + 1;
    int pos_hijo2 = (piv_padre - ptr1) * 2 + 2;

    //T* hijo1 = ptr1 + (piv_padre - ptr1) * 2 + 1;
    //T* hijo2 = ptr1 + (piv_padre - ptr1) * 2 + 2;

    while( pos_hijo1 < rango || pos_hijo2 < rango){
        //encontramos el maximo
        //ptr_max = p
        if (2 * pos_p + 1 < rango && *(ptr1 + (2 * pos_p + 1)) > *ptr_max) {        
            ptr_max = ptr1 + (2 * pos_p + 1);
        } 
        if (2 * pos_p + 2 < rango && *(ptr1 + (2 * pos_p + 2)) > *ptr_max) {
            ptr_max = ptr1 + (2 * pos_p + 2);
        }

        if (piv_padre != ptr_max) {
            swap(piv_padre, ptr_max);
            piv_padre = ptr_max;
            ptr_max = piv_padre;
            pos_hijo1 = (piv_padre - ptr1) * 2 + 1;
            pos_hijo2 = (piv_padre - ptr1) * 2 + 2;
        }
        else break;

    } 
}


template <class T>
void heap<T>::make_heap(T* ptr1, T* ptr2) { // convierte cualquier intervalo de punteros en un array. Se usara el algoritmo floyd
    if (ptr1 == ptr2 || ptr1 > ptr2 ) return;
    // vamos hasta el ultimo padre:
    int pos_last_element = ptr2 - ptr1;
    T* last_f = ptr1 + (pos_last_element - 1) / 2;  //   *  **   (*)***   **
    // recorreremos todos los punteros anteriores en orden...   //   *  **  (*)***   **
    for ( T* p = last_f ; p >= ptr1 ; p--) {
        SiftDown( p , ptr1 , ptr2 );
    }  

}

template <class T>
void heap<T>::push_heap() {
    iterator<T> it1;

    return T();
}

template <class T>
bool heap<T>::pop_heap() {
    return 0;
}

template <class T>
void heap<T>::SiftDown(T* x) {        // Se usa en el make_heap. El elemento está arriba y "baja" comparándose con sus hijos.
    
    return T();
}

template <class T>
void heap<T>::SiftUp(T* x) {            // Se usa en el push. El elemento nuevo entra al final y "sube" comparándose con su padre.
    return T();

}

// Función auxiliar para imprimir el arreglo
void imprimirArreglo(const vector<int>& v) {
    for (int x : v) cout << "[" << x << "] ";
    cout << endl;
}


int main()
{
    vector<int> prueba = { 11,13,8,20,5,10,9,1,3,50,4 };
    cout << prueba[0] << endl;

    cout << "size " << prueba.size() << endl;
    cout << "max size " << prueba.max_size() << endl;
    cout << "capacity " << prueba.capacity() << endl;
    prueba.push_back(100);
    cout << "size " << prueba.size() << endl;
    cout << "max size " << prueba.max_size() << endl;
    cout << "capacity " << prueba.capacity() << endl;

    cout << endl;

    vector<int>::iterator it = prueba.begin();
    cout << *(it + 0) << endl;
    cout << prueba.back() << endl;

    //cout<< prueba.front()  <<endl;

    // 1. Datos de prueba (Desordenados)
    vector<int> prueba2 = { 11, 13, 8, 20, 5, 10, 9, 1, 3, 50, 4 };
    heap<int> miHeap;

    cout << "--- PRUEBA DE MAKE_HEAP (Algoritmo de Floyd) ---" << endl;
    cout << "Arreglo original: " << endl;
    imprimirArreglo(prueba2);

    // 2. Aplicar make_heap sobre el vector 'prueba'
    // Usamos punteros al inicio y al final como pide tu función
    miHeap.make_heap(&prueba2[0], &prueba2[0] + prueba2.size());

    cout << "\nArreglo despues de make_heap (Estructura de Max-Heap):" << endl;
    imprimirArreglo(prueba2);

    // 3. Verificación de la propiedad de Max-Heap
    cout << "\nVerificacion de niveles:" << endl;
    cout << "Raiz (Maximo): " << prueba2[0] << " (Debe ser 50)" << endl;
    cout << "Hijos de " << prueba2[0] << ": " << prueba2[1] << " y " << prueba2[2] << endl;

    if (prueba2[0] >= prueba2[1] && prueba2[0] >= prueba2[2]) {
        cout << "\nRESULTADO: ¡Propiedad de Max-Heap cumplida con exito!" << endl;
    }
    else {
        cout << "\nRESULTADO: Hay un error en la jerarquia." << endl;
    }

    return 0;



}
