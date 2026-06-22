#include <iostream>
#include <vector>
using namespace std;
struct CNode {
    int v;
    int y;
    CNode* next;
    CNode(int y, int val) { 
        this->y = y; v = val; next = nullptr; 
    }
};

class CSparseMatrix {
    private:
        std::vector<CNode*> fila_vector;
        int fil, col;
        public:

        CSparseMatrix(int m, int n) {
            fil = m, col = n;
            fila_vector.resize(fil);
            for (int i = 0; i < fila_vector.size(); i++) 
                fila_vector[i] = nullptr;
        }

        ~CSparseMatrix() {
            for (int i = 0; i < fila_vector.size(); i++) {
                CNode* next = fila_vector[i];
                for (CNode* current = next; current; current = next) {
                    next = current->next;
                    delete current;
                }
            }
        }

        bool find(int i, int j, CNode**& p) {
            p = &fila_vector[i];
            for (; *p && (*p)->y < j ; p = &((*p)->next));
            return *p && (*p)->y == j ; 
        }

        void set(int i, int j, int val) {
            CNode** p;
            if (find(i, j, p)) {
                if (val != 0) 
                    (*p)->v = val ;        
                else {
                    CNode* tmp = *p;
                    (*p) = (*p)->next;
                    delete tmp;
                }
          
            }
            else if (val != 0) {
                CNode* tmp = *p;
                CNode* nuevo = new CNode(j, val);
                *p = nuevo;
                nuevo->next = tmp;
            }
        }
        int get(int i, int j) {
            CNode** p = nullptr;     
            if (find(i, j, p)) return (*p)->v;
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
