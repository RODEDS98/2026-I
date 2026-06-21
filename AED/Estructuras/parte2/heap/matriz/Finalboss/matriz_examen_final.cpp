//  Le añadi functores

#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// Clase adaptadora para std::list
template<class T>
class ListAdapter {
private:
	std::list<T> data;
public:
	void insert(const T& value) {
		data.push_back(value);
	}

	bool find(const T& value) const {
		for (const auto& item : data) {
			if (item == value) return true;
		}
		return false;
	}

	bool remove(const T& value) {
		auto it = std::find(data.begin(), data.end(), value);
		if (it != data.end()) {
			data.erase(it);
			return true;
		}
		return false;
	}

	T* get(const T& key) {
		for (auto& item : data) {
			if (item == key) return &item;
		}
		return nullptr;
	}

	void print() const {
		for (const auto& item : data) {
			std::cout << item << " ";
		}
	}

	bool empty() const {
		return data.empty();
	}
};

// Tabla Hash con templates
template<class T, class S, class F, size_t Z>
class CHashTable {
private:
	S table[Z];
	F hash_function;

public:
	void insert(const T& value) {
		size_t index = hash_function(value) % Z;
		table[index].insert(value);
	}

	bool remove(const T& value) {
		size_t index = hash_function(value) % Z;
		return table[index].remove(value);
	}

	T* find(const T& key) {
		size_t index = hash_function(key) % Z;
		return table[index].get(key);
	}

	void print_hash_table() {
		for (size_t i = 0; i < Z; ++i) {
			if (!table[i].empty()) {
				std::cout << "[" << i << "]: ";
				table[i].print();
				std::cout << std::endl;
			}
		}
	}
};

/*---------------------------------------------*/

// Estructura para elemento de matriz dispersa
struct MatrixElement
{
	int row, col;
	int value;

	MatrixElement(int r = 0, int c = 0, int v = 0)
	{
		row = r;    col = c;    value = v;
	}

	bool operator==(const MatrixElement& other) const
	{
		return row == other.row && col == other.col;
	}
};

// Función hash para MatrixElement
struct MatrixHash
{
	int operator()(const MatrixElement& elem)
	{
		return elem.row * 31 + elem.col;
	}
};

// Adaptador de Sparse Matrix
class SparseMatrix
{                         // template         <  class T  , class S  , class F  , size_t Z  >
private:
	CHashTable<MatrixElement, ListAdapter<MatrixElement>, MatrixHash, 100> hash_table;
	int rows;
	int cols;

public:
	SparseMatrix(int c, int r)
	{
		rows = r;   cols = c;
	}

	void set(int row, int col, int value)
	{
		MatrixElement ME_temporal(row, col, value);
		MatrixElement* tmp = hash_table.find(ME_temporal);

		if (!tmp) {
			if (value != 0) {
				hash_table.insert(ME_temporal);
			}
		}
		else if (tmp) {
			if (value == 0) {
				hash_table.remove(ME_temporal);
			}
			else {
				tmp->value = value;
			}
		}

	}

	int get(int row, int col)
	{
		MatrixElement temp(row,col,0);
		MatrixElement* real = hash_table.find(temp);
		if (real) return real->value;
		else return 0;		
	}

	void print()
	{
		for (int i = 0; i < rows; i ++) {
			for (int j = 0; j < cols; j++) {
				cout <<" " << get(i, j);
			}
			cout << endl;
		}
	}

	/*
	VALIDO SOLO PARA    int a = matrix(x,y); 
	int operator () (int x,int y) {
		MatrixElement temp(x, y, 0);
		MatrixElement* real = hash_table.find(temp);
		if (real) {
			return real->value;
		}
		else return 0;

	}
	*/

	struct objcX {

		objcX(int x, int y, SparseMatrix* mat) {
			this->x = x;
			this->y = y;
			this->mat = mat;
		}

		objcX& operator = (int v) {
			mat->set(x,y,v);
			return *this;
		}

		operator int() const {
			return  mat->get(x, y);		
		}

		private:
			int x;
			int y;
			SparseMatrix* mat;
	};


	objcX operator () (int x, int y) {
		return objcX(x, y, this);;
	}


};

int main()
{
	std::cout << "=== SparseMatrix test ===" << std::endl;

	SparseMatrix matrix(3, 5);  // 3 columnas, 5 filas

	matrix.set(0, 0, 10);
	matrix.set(1, 2, 20);
	matrix.set(2, 1, 30);
	matrix.set(3, 0, 40);
	matrix.set(4, 2, 50);
	matrix.set(2, 2, 60);
	matrix.print(); std::cout << "\n";

	matrix.set(1, 2, 21);
	matrix.set(2, 2, 0);
	matrix.set(2, 1, 31);
	matrix.print(); std::cout << "\n";

	matrix.set(3, 0, 0);
	matrix.set(3, 0, 41);
	matrix.set(4, 2, 0);
	matrix.print(); std::cout << "\n";

	// prueba para los functores 
	int a = matrix(0,0);
	int b = matrix(5,5);
	cout << a <<" " << b << endl;

	
	std::cout << "functores" << endl;
	matrix(0, 0) = 55; // set
	matrix.print();
	matrix(1, 2) = 0;  // rem
	matrix.print();
	matrix(0, 0) = 555; // set
	matrix.print();

	return 0;
}
