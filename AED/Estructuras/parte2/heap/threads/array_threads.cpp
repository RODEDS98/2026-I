#include <SFML/Graphics.hpp>
#include <iostream>
#include <initializer_list>
#include <queue>
#include <stack>
#include <string> 

#include <thread> 

using namespace std;

void F1(int* M, int d) {
    for (int* p = M; p < M + d ; p = p + d) {
        cout << *p<<" ";
    }
}


int main()
{
    int d = 16;
    int arr[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    unsigned int n_threads = thread::hardware_concurrency();
    int segmento = d / n_threads;
    vector<thread> hilos(n_threads);


    for (int i = 0; i < n_threads; i++) {
        hilos[n_threads] = thread(F1, arr+i+(i*segmento) , segmento);
    }

    for (int i = 0; i < n_threads; i++) {
        hilos[i].join();
    }

}
