#include <iostream>
#include <list>

using namespace std;

//si no se puede hacer un recorrido del array para hallar los mallores, entonces talvez si se alamacenan los valores en un hashtable se puedan extrar los valores mayores de alli
template<class T, class I, class F, int Sz>
class ChashTable {
public:
    ChashTable() { hs = new I[Sz]; }
    void ins(int x);
    void del(int x);

    I& add_list(int i) { return hs[i]; }
private:
    F fs;
    I* hs;
};

template<class T, class I, class F, int Sz>
void ChashTable<T, I, F, Sz>::ins(int x) {
    int i = fs(x) % Sz;
    hs[i].ins(x);
}

template<class T, class I, class F, int Sz>
void ChashTable<T, I, F, Sz>::del(int x) {
    int i = fs(x) % Sz;
    hs[i].del(x);
}

struct sfx {
    int operator()(int x) { return x; };
};

class Clist {
public:
    void ins(int x) { data.push_back(x); }
    void del(int x) { data.remove(x); }
    void print() {
        for (auto x : data) {
            cout << x << " ";
        }
    }
private:
    list<int > data;
};

int HijoIzq(int i) { return 2 * i + 1; }
int HijoDer(int i) { return 2 * i + 2; }

void XMayores(int heap[], int size, int x)
{
    int* p = heap;
    list<int> izq;
    list<int> der;
    cout << "soy la cabeza: " << *p << endl;

    for (int i = 0;i < 15 / 2;i++) {
        izq.push_back(*(p + HijoIzq(i)));
        cout << "izquierdo: " << *(p + HijoIzq(i)) << endl;
        der.push_back(*(p + HijoDer(i)));
        cout << "derecho: " << *(p + HijoDer(i)) << endl;
    }





}

int main()
{
    ChashTable<int, Clist, sfx, 15> table1;
    ChashTable<int, Clist, sfx, 15> table2;
    ChashTable<int, Clist, sfx, 15> table3;
    int heap1[15] = { 95, 83, 90, 75, 80, 89, 70, 60, 65, 55, 45, 87, 40, 35, 25 };
    int heap2[15] = { 100, 95, 90, 80, 85, 88, 75, 70, 78, 82, 83, 86, 73, 72, 71 };
    int heap3[15] = { 98, 95, 92, 91, 85, 80, 75, 70, 88, 82, 83, 78, 76, 73, 72 };

    XMayores(heap1, 15, 4);
    XMayores(heap2, 15, 4);
    XMayores(heap3, 15, 4);

    for (int i = 0;i < 15;i++) {
        table1.ins(heap1[i]);
    }

    for (int i = 0;i < 15;i++) {
        table2.ins(heap2[i]);
    }

    for (int i = 0;i < 15;i++) {
        table3.ins(heap3[i]);
    }


    return 0;
}