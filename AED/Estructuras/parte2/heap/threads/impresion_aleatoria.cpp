
#include <iostream>
#include <thread> 
using namespace std;

void F1(int* M, int d) {
    for (int* p = M; p < M + d ; p++) {
        cout << *p<<" ";
    }
}

int main()
{
    int suma =0;
    
 
    int d = 16;
    int arr[d] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    unsigned int n_threads = thread::hardware_concurrency();
    int segmento = d / n_threads;

    vector<thread> hilos(n_threads);

    for (int i = 0; i < n_threads; i++) 
        hilos[i] = thread(F1, arr+ i*segmento , segmento);          //cout<< arr+ (i*segmento)  << " v: "<< *(arr+ i*segmento) <<endl;

    for (int i = 0; i < n_threads; i++) 
        hilos[i].join();

}
