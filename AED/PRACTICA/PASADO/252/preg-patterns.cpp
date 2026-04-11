#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
mutex cfx;

/*void searchPattern(char matrix[10][10], int* totalPatterns, thread& c1, thread& c2, thread& c3, thread& c4, thread& c5, thread& c6, thread& c7)
{
    int cont0 = 1, cont1 = 1, cont2 = 1, cont3 = 1, cont4 = 1, cont5 = 1, cont6 = 1;

    for (int i = 0;i < 10;i++) {
        for (int j = 0;j < 10;j++) {
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#') {
                if (cont0 == 1) (*totalPatterns)++;
                thread  c1(searchPattern, matrix, *totalPatterns, c1, c2, c3, c4, c5, c6, c7);
                cout << "encontre caso 0:" << cont0 << endl;
                cont0++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i + 1][j] == '#') {
                if (cont1 == 1) (*totalPatterns)++;
                thread  c2(searchPattern, matrix, *totalPatterns, c1, c2, c3, c4, c5, c6, c7);
                cout << "encontre caso 1:" << cont1 << endl;
                cont1++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i][j + 2] == '#') {
                if (cont2 == 1) (*totalPatterns)++;
                thread  c3(searchPattern, matrix, *totalPatterns, c1, c2, c3, c4, c5, c6, c7);
                cout << "encontre caso 2:" << cont2 << endl;
                cont2++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i][j + 2] == '#' && matrix[i + 1][j] == '#') {
                if (cont3 == 1) (*totalPatterns)++;
                thread  c4(searchPattern, matrix, *totalPatterns, c1, c2, c3, c4, c5, c6, c7);
                cout << "encontre caso 3:" << cont3 << endl;
                cont3++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i][j + 2] == '#' && matrix[i - 1][j + 3] == '#') {
                if (cont4 == 1) (*totalPatterns)++;
                thread  c5(searchPattern, matrix, *totalPatterns, c1, c2, c3, c4, c5, c6, c7);
                cout << "encontre caso 4:" << cont4 << endl;
                cont4++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i][j + 2] == '#' && matrix[i - 1][j + 3] == '#' && matrix[i - 1][j + 4]) {
                if (cont5 == 1) (*totalPatterns)++;
                thread  c6(searchPattern, matrix, *totalPatterns, c1, c2, c3, c4, c5, c6, c7);
                cout << "encontre caso 5:" << cont5 << endl;
                cont5++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i - 1][j + 2] == '#' && matrix[i - 1][j + 3] == '#') {
                if (cont6 == 1) (*totalPatterns)++;
                thread  c7(searchPattern, matrix, *totalPatterns, c1, c2, c3, c4, c5, c6, c7);
                cout << "encontre caso 6:" << cont6 << endl;
                cont6++;
            }
        }
    }

    if (c1.joinable()) c1.join();
    if (c2.joinable()) c2.join();
    if (c3.joinable()) c3.join();
    if (c4.joinable()) c4.join();
    if (c5.joinable()) c5.join();
    if (c6.joinable()) c6.join();
    if (c7.joinable()) c7.join();
}*/

void searchPatternsin(char matrix[10][10], int* totalPatterns)
{
    int cont0 = 1, cont1 = 1, cont2 = 1, cont3 = 1, cont4 = 1, cont5 = 1, cont6 = 1;

    for (int i = 0;i < 10;i++) {
        for (int j = 0;j < 10;j++) {
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#') {
                if (cont0 == 1) (*totalPatterns)++;
                cout << "encontre caso 0:" << cont0 << endl;
                cont0++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i + 1][j] == '#') {
                if (cont1 == 1) (*totalPatterns)++;
                cout << "encontre caso 1:" << cont1 << endl;
                cont1++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i][j + 2] == '#') {
                if (cont2 == 1) (*totalPatterns)++;
                cout << "encontre caso 2:" << cont2 << endl;
                cont2++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i][j + 2] == '#' && matrix[i + 1][j] == '#') {
                if (cont3 == 1) (*totalPatterns)++;
                cout << "encontre caso 3:" << cont3 << endl;
                cont3++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i][j + 2] == '#' && matrix[i - 1][j + 3] == '#') {
                if (cont4 == 1) (*totalPatterns)++;
                cout << "encontre caso 4:" << cont4 << endl;
                cont4++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i][j + 2] == '#' && matrix[i - 1][j + 3] == '#' && matrix[i - 1][j + 4]) {
                if (cont5 == 1) (*totalPatterns)++;
                cout << "encontre caso 5:" << cont5 << endl;
                cont5++;
            }
            if (matrix[i][j] == '#' && matrix[i][j + 1] == '#' && matrix[i - 1][j + 2] == '#' && matrix[i - 1][j + 3] == '#') {
                if (cont6 == 1) (*totalPatterns)++;
                cout << "encontre caso 6:" << cont6 << endl;
                cont6++;
            }
        }
    }
}


int main()
{
    int totalPatterns = 0;


    char matrix[10][10] = {
       {'.', '#', '#', '.', '.', '.', '#', '#', '.', '.'},
       {'.', '.', '.', '.', '.', '.', '#', '.', '#', '#'},
       {'.', '.', '#', '#', '.', '.', '.', '.', '#', '.'},
       {'.', '.', '#', '.', '.', '.', '.', '.', '.', '.'},
       {'#', '#', '.', '.', '#', '#', '.', '#', '#', '.'},
       {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
       {'.', '.', '.', '.', '.', '#', '#', '.', '.', '.'},
       {'.', '.', '.', '#', '#', '#', '.', '#', '#', '.'},
       {'.', '#', '#', '#', '.', '.', '.', '#', '.', '.'},
       {'.', '#', '.', '.', '.', '.', '.', '.', '#', '#'}
    };



    // Creación de threads aqui
    thread c1, c2, c3, c4, c5, c6, c7;

    /*c1.join();
    thread c1(prueba,matrix);*/

    // para pasar la matriz a la funcion seria asi:
    //searchPattern(matrix, &totalPatterns, c1, c2, c3, c4, c5, c6, c7);
    searchPatternsin(matrix, &totalPatterns);


    std::cout << "\nTotal de patrones encontrados: " << totalPatterns << std::endl;


    return 0;
}

