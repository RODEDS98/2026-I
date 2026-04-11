#include <iostream>
#include <map>

class CSMatrix
{
public:
    CSMatrix(int dx, int dy);
    bool set(int x, int y, int value);
    int get(int x, int y);
    void print();
    
private:
    // matrix
    int dimx, dimy;
};

CSMatrix::CSMatrix(int dx, int dy)
{
    dimx = dx; dimy = dy;
}

bool CSMatrix::set(int x, int y, int value)
{
    return 0;
}

int CSMatrix::get(int x, int y)
{
    return 0;
}

void CSMatrix::print()
{
    std::cout << "\n";
    for (int x = 0; x < dimx; x++)
    {
        for (int y = 0; y < dimy; y++)
        {
            std::cout << get(x,y) << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main()
{
    CSMatrix m(8,8);

    m.set(2, 1, 5);
    m.set(2, 3, 2);
    m.set(2, 5, 7);
    m.set(5, 3, 9);
    m.set(7, 3, 12);
    m.set(1, 4, 3);
    m.set(2, 4, 0);
    m.set(5, 5, 8);
    m.set(3, 6, 1);
    m.print();
    m.set(1, 4, 0);
    m.set(2, 3, 0);
    m.set(4, 3, 0);
    m.set(0, 1, 0);
    m.print();
    std::cout << "\n 0,0 => " << m.get(0, 0);
    std::cout<< "\n 3,5 => " << m.get(3, 5);
    std::cout<< "\n 7,3 => " << m.get(7, 3);
 }
