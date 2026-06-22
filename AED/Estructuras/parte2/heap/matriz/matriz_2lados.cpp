
#include <iostream>
#include <vector>
using namespace std;
struct CNode {
    int v;
    int x;
    int y;
    CNode* next;
    CNode* down;
    CNode(int x , int y, int val) {
        this->x = x;
        this->y = y;
        v = val;
        next = nullptr;
        down = nullptr;
    }
};

class CSparseMatrix {
    private:
        std::vector<CNode*> fila_vector;
        std::vector<CNode*> columna_vector;
        int fil, col;
        public:

        CSparseMatrix(int m, int n) {
            fil = m, col = n;
            fila_vector.resize(fil);
            columna_vector.resize(col);

            for (int i = 0; i < fila_vector.size(); i++)
                fila_vector[i] = nullptr;
            for (int i = 0; i < columna_vector.size(); i++)
                columna_vector[i] = nullptr;
        }

        ~CSparseMatrix() {
            for (int i = 0; i < fila_vector.size(); i++) {
                CNode* next = fila_vector[i];
                for (CNode* current = next; current; current = next) {
                    next = current->next;
                    delete current;
                }
                fila_vector[i] = nullptr;
            }
            
            for (int j = 0; j < columna_vector.size(); j++) {
                columna_vector[j] = nullptr;
            }

        }

        bool findx(int i, int j, CNode**& p) {
            p = &fila_vector[i];
            for (; *p && (*p)->y < j ; p = &((*p)->next));
            return *p && (*p)->y == j ;
        }

        bool findy(int i, int j, CNode**& p) {
            p = &columna_vector[j];
            for (; *p && (*p)->x < i; p = &((*p)->down));
            return *p && (*p)->x == i;
        }

        void set(int i, int j, int val) {
            if (i > fil || j > col) return ;            
            CNode** p_1;
            CNode** p_2;
            if (findx(i, j, p_1)) {                
                if (val != 0)
                    (*p_1)->v = val ;
                else {
                    findy(i, j, p_2);
                    //borrar pero falta juntar el otro extremo
                    CNode* tmp = *p_1;
                    CNode* tmp2 = *p_2;
                    (*p_1) = (*p_1)->next;
                    (*p_2) = (*p_2)->down;
                    delete tmp;
                }

            }
            else if (val != 0) {
                findy(i, j, p_2);
                // guardado
                CNode* tmp = *p_1;  
                CNode* tmp2 = *p_2;

                //parte del eje y
                CNode* nuevo = new CNode(i,j, val);
                *p_1 = nuevo;
                nuevo->next = tmp;

                //parte del eje x                
                *p_2 = nuevo;
                nuevo->down = tmp2;
                
            } // Si no se encuentra y fuera cero no se hace nada
        }
        int get(int i, int j) {
            CNode** p = nullptr;
            if (findx(i, j, p)) return (*p)->v;
            return 0;
        }

        void print() {
            for (int i = 0; i < fil; i++) {
                for (int j = 0; j < col; j++) {
                    std::cout << get(i, j) << " ";
                }
                std::cout << '\n';
            }
        }
    };

int main() {
    CSparseMatrix matrix(10, 9);
    matrix.set(1, 1, 5);
    matrix.set(5, 3, 9);
    matrix.print();
    return 0;
}
