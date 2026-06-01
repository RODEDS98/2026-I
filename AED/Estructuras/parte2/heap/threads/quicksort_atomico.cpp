#include <iostream>
#include <vector>
#include <thread>
#include <atomic> // ¡La clave para cumplir tu idea de forma segura!

using namespace std;

void miSwap(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

// Pasamos 'hilos_activos' POR REFERENCIA (&) usando std::atomic
void quicksortRThreads(vector<int> &arr, int bajo, int alto, atomic<int> &hilos_activos, int total_nucleos) {
    if (bajo < alto) {
        int i = bajo - 1;
        for (int j = bajo; j < alto; j++) {
            if (arr[alto] > arr[j]) {
                i++;
                if (j != i) {
                    miSwap(arr[i], arr[j]);
                }
            }
        }
        miSwap(arr[i + 1], arr[alto]);

        // REINCORPORACION DINAMICA DE NUCLEOS
        hilos_activos++;

        if (hilos_activos <= total_nucleos) {

            thread hilo_izquierdo(quicksortRThreads, ref(arr), bajo, i, ref(hilos_activos), total_nucleos);

            quicksortRThreads(arr, i + 2, alto, ref(hilos_activos), total_nucleos);            
            hilo_izquierdo.join(); 
            
            hilos_activos--; 
        } 
        else { // Si está llena

            hilos_activos--;             
            quicksortRThreads(arr, bajo, i, ref(hilos_activos), total_nucleos);
            quicksortRThreads(arr, i + 2, alto, ref(hilos_activos), total_nucleos);

        }
    }
}

int main() {
    vector<int> datos = {10, 9, 7, 8, 1, 2, 3, 4, 5};
    
    int total_nucleos = thread::hardware_concurrency();
    cout << "Nucleos de tu CPU: " << total_nucleos << endl;

    // Empezamos con 1 hilo activo (el hilo main que está corriendo)
    atomic<int> hilos_activos = 1; 

    // Llamamos pasándole la referencia del contador atómico
    quicksortRThreads(datos, 0, datos.size() - 1, hilos_activos, total_nucleos);
    
    cout << "Arreglo ordenado: ";
    for (int x : datos) cout << x << " ";
    cout << endl;
    
    return 0;
}
