
#include <iostream>
#include <thread> 
using namespace std;

void F2(int* M, int d, int* sum) {
    for (int* p = M; p < M + d ; p++) 
        *sum += *p;
}

int main()
{
    int suma =0;
 
    int d = 16;
    int arr[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    unsigned int n_threads = thread::hardware_concurrency();
    int segmento = d / n_threads;

    vector<thread> hilos(n_threads);
    
    int sum[n_threads];
    
    for (int i = 0; i < n_threads; i++)   // inicializacion de array SUMA con n ceros
        sum[i] = 0;
    
    for (int i = 0; i < n_threads; i++) 
        hilos[i] = thread(F2, arr + i*segmento , segmento, sum+i);         // iniciar threads
    
    int rpta=0;
    
    for (int i = 0; i < n_threads; i++)          // capturar threads             
        hilos[i].join();
    
    for (int i = 0; i < n_threads; i++)    // sumar localmente
        rpta += sum[i];
    
    cout<< rpta  ;

}


/*    
    int sum2=0;
    for (int i = 1; i <= 16; i++) {
        sum2+=i;
    } cout<< sum2 ;
*/
