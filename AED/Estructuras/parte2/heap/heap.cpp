#include <iostream>
#include <vector>

using namespace std;

// Función auxiliar para imprimir el arreglo
void imprimirArreglo( const vector<int>& v) {
    cout << " imprimiendo: ";
    for (int x : v) cout << "[" << x << "] ";
    cout << endl;
}

template<class T>
void imprimirRango(T* ptr1, T* ptr2) {
    T* actual = ptr1;
    int pot = 1;
    int i = pot;
    while (actual <= ptr2) {        
        cout << "[" << *actual << "] ";
        if ( (i == pot) ) {
            cout << endl;
            i = 1;
            actual++;
            pot = pot * 2;
            continue;
        }

        actual++;
        i++;
    }
    cout << endl;
}


template<class T>
class heap {
public:
    heap();
    ~heap();
    void push_back(T val);
    void make_heap(T* ptr1, T* ptr2); // convierte
    void push_heap(int val);
    bool pop_heap();
    void SiftDown(T* p,T* ptr1,T* ptr2);
    void SiftDown(int x);        // Se usa en el make_heap. El elemento está arriba y "baja" comparándose con sus hijos.
    void SiftUp(int x);            // Se usa en el push. El elemento nuevo entra al final y "sube" comparándose con su padre.
    void swap(T* A, T* B);

    //sort_heap(); // orden ascendente
    //is_heap(T val);
    //is_heap_until();  //?
    vector<T> v1;
    vector<T> v = {50,20,10,11,13,8,9,1,3,5,4};

private:
    

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
    SiftUp(v.size()-1);
}

template <class T>
void heap<T>::swap(T* A, T* B) {
    if (A == B) return; // Si apuntan al mismo sitio, no hay nada que hacer
    T temp = *A;        // Guardamos el valor de a
    *A = *B;            // Ponemos el valor de b en a
    *B = temp;          // Ponemos el valor guardado (original de a) en b
}

// 11,13,8,20,5,10,9,1,3,50,4 
template <class T>
void heap<T>::SiftDown(T* p, T* ptr1, T* ptr2) {
    int rango = ptr2 - ptr1; //  0 1 2  ... rango
    int pos_p = p - ptr1;    //  0 1 p 3 4 5  ... rango
    T* piv_padre = p;
    T* ptr_max = p; // se asume que el maximo es el puntero p 

    int pos_hijo1 = (piv_padre - ptr1) * 2 + 1;   //T* hijo1 = ptr1 + (piv_padre - ptr1) * 2 + 1;
    int pos_hijo2 = (piv_padre - ptr1) * 2 + 2;   // T * hijo2 = ptr1 + (piv_padre - ptr1) * 2 + 2;

    while( pos_hijo1 <= rango || pos_hijo2 <= rango){
        //encontramos el maximo
        //ptr_max = p
        cout << *p << endl;
        imprimirRango(ptr1, ptr2);
       
        if (2 * pos_p + 1 <= rango && *(ptr1 + (2 * pos_p + 1)) > *ptr_max) {        
            ptr_max = ptr1 + (2 * pos_p + 1);
        } 
        if (2 * pos_p + 2 <= rango && *(ptr1 + (2 * pos_p + 2)) > *ptr_max) {
            ptr_max = ptr1 + (2 * pos_p + 2);
        }
        if (piv_padre != ptr_max) { // si el padre no es el mayor
            swap(piv_padre, ptr_max);  // swapea con el hijo que si lo es          
            piv_padre = ptr_max;  //   luego actualiza al padre con el mayor de los hijos
            ptr_max = piv_padre;  //   y ptr max tambien asume el valor del padre
            pos_hijo1 = (piv_padre - ptr1) * 2 + 1;        //las posiciones del hijo 1 y 2 se actualizan,    
            pos_hijo2 = (piv_padre - ptr1) * 2 + 2;  //  En el while y en los if se protege para no acceder a invalidos 
            pos_p = piv_padre - ptr1;    //  y se debe actualizar la posicion de pos_p que es un indice tambien.
        }
        else break;
    } 
}
// Se usa en el make_heap. El elemento está arriba y "baja" comparándose con sus hijos.
template <class T>
void heap<T>::SiftDown(int index) {
    int rango = v.size() - 1;
    int max = index;
    int piv = index;

    if (index == v.size() - 1) return;

    while ( v[index]   ) {
       
        if ( piv * 2 + 1 <= rango && v[piv * 2 + 1] > v[max]   ) {
            max = piv * 2 + 1;
        }
        if (piv * 2 + 2 <= rango && v[piv * 2 + 2] > v[max])   {
            max = piv * 2 + 2;
        }
        if (v[max] == v[piv]) { // si el padre no es el mayor
            break;
        }
        else {
            swap( &v[piv] , &v[max]);
            piv = max;
            max = piv;
        }       
    }
}

/*
void heapifydown(int index) {
    int maxIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heap.size() && heap[left] > heap[maxIndex]) {
        maxIndex = left;
    }
    if (right < heap.size() && heap[right] > heap[maxIndex]) {
        maxIndex = right;
    }
    if (maxIndex != index) {
        swap(heap[maxIndex], heap[index]);
        heapifydown(maxIndex);
    }

    // compare left vs max index, compare right vs maxindex
    // update maxIndex 
    // maxINdex != idnex, swap values and hapify down again 

}

*/


// 11,13,8,20,5,10,9,1,3,50,4 
template <class T>
void heap<T>::make_heap(T* ptr1, T* ptr2) { // convierte cualquier intervalo de punteros en un array. Se usara el algoritmo floyd
    cout << " make_heap " << endl;
    imprimirRango(ptr1, ptr2);
    if ( ptr1 == ptr2 || ptr1 > ptr2 ) return;
    // vamos hasta el ultimo padre:
    int pos_last_element = ptr2 - ptr1;
    T* last_f = ptr1 + (pos_last_element - 1) / 2;  //   *  **   (*)***   **
    // recorreremos todos los punteros anteriores en orden...   //   *  **  (*)***   **
    for ( T* p = last_f ; p >= ptr1 ; p--) {
        SiftDown( p , ptr1 , ptr2 );
    }  

}

template <class T>
void heap<T>::push_heap(int val) {
    v.push_back(val);
    SiftUp(v.size() - 1);
}

template <class T>
bool heap<T>::pop_heap() { // Mueve el elemento maximo al final para su eliminacion.
    T* ptr1 = &v[0];
    T* ptr2 = &v[0] + v.size() - 1;
    v[0] = *(ptr2);
    v.pop_back();
    SiftDown(0);
    return 0;
}


template <class T>
void heap<T>::SiftUp(int x) {            // Se usa en el push. El elemento nuevo entra al final y "sube" comparándose con su padre.
    int piv_f = x;
    int max = x;
    while (piv_f>=0) {
        if (v[(piv_f - 1) / 2] < v[piv_f]) {
            swap(&v[(piv_f - 1) / 2], &v[piv_f]);
            piv_f = (piv_f - 1) / 2;
        }
        else break;
    }
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
    miHeap.make_heap(&prueba2[0], &prueba2[0] + prueba2.size()-1);

    cout << "\nArreglo despues de make_heap (Estructura de Max-Heap):" << endl;
    imprimirArreglo(prueba2);

    // 3. Verificación de la propiedad de Max-Heap
    cout << "\nVerificacion de niveles:" << endl;
    cout << "Raiz (Maximo): " << prueba2[0] << " (Debe ser50)" << endl;
    cout << "Hijos de " << prueba2[0] << ": " << prueba2[1] << " y " << prueba2[2] << endl;

    if (prueba2[0] >= prueba2[1] && prueba2[0] >= prueba2[2]) {
        cout << "\nRESULTADO: ¡Propiedad de Max-Heap cumplida con exito!" << endl;
    }
    else {
        cout << "\nRESULTADO: Hay un error en la jerarquia." << endl;
    }

    // 3. Verificación de la propiedad de Max - Heap
    cout << "\n Prueba de pop_heap:" << endl;
    imprimirRango(&(miHeap.v[0]), &(miHeap.v[miHeap.v.size()-1]));
    miHeap.pop_heap();
    imprimirRango(&(miHeap.v[0]), &(miHeap.v[miHeap.v.size() - 1]));

    cout << "\n Prueba de push_heap:" << endl;
    miHeap.push_heap(90);
    imprimirRango(&(miHeap.v[0]), &(miHeap.v[miHeap.v.size() - 1]));

    return 0;
}
