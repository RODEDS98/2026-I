#include <iostream>

struct CNode {
    int value, i, j;
    CNode* next;
    CNode(int i, int j, int val) { value = val; this->i = i; this->j = j; next = nullptr; }
};

class CSparseMatrix {
private:
    CNode* head;
    int M, N;
public:
    CSparseMatrix(int m, int n) { head = nullptr; M = m; N = n; }
    ~CSparseMatrix()
    {
        CNode* next_node;
        for (CNode* current = head; current; current = next_node) {
            next_node = current->next;
            delete current;
        }
    }
    bool find(int i, int j, CNode**& p) {
        for (p = &head; *p && (*p)->i <= i; p = &((*p)->next)) {
            if ( (*p)->i==i && (*p)->j==j ) {
                return true;
            }
        }
        return false;
    }
    void set(int i, int j, int val) {
        CNode** p;
        if (find(i, j, p)) {
            if (val != 0) {
                (*p)->value = val;
                return;
            }
            else {
                CNode* tmp = *p;
                *p = (*p)->next;
                delete tmp;
                return;
            }
        }
        if (val != 0) {
            *p = new CNode(i, j, val);
        }

    }
    int get(int i, int j) {
        CNode** p;
        if (!find(i, j, p)) return 0;
        return (*p)->value;
    }

    void print() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << get(i, j) << " ";
            }
            std::cout << '\n';
        }
    }
};

int main() {
    CSparseMatrix csm(10, 10);


    csm.set(9, 9, 5); csm.print();
    csm.set(9, 9, 0); csm.print();

    return 0;
}
