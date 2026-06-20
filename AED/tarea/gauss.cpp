#include <iostream>
#include <cmath>

struct Node
{
	double val;
	int row, col;
	Node* right;
	Node* down;

	Node(double VAL, int x = 0, int y = 0)
	{
		val = VAL;
		row = x;
		col = y;
		right = down = nullptr;
	}
};

struct SparseMatrix
{
	Node** vh;
	Node** vv;

	int nrows, ncolumns;

	SparseMatrix(int rows, int columns)
	{
		nrows = rows;
		ncolumns = columns;

		vh = new Node * [nrows];
		vv = new Node * [ncolumns];

		for (Node** i = vh; i < vh + rows; i++) *(i) = nullptr;
		for (Node** i = vv; i < vv + columns; i++) *(i) = nullptr;
	}

	~SparseMatrix()
	{
		clear();
	}

	void clear()
	{
		for (Node** i = vh; i < vh + nrows; i++)
		{
			Node* curr = *i;
			while (curr)
			{
				Node* t = curr->right;
				delete curr;
				curr = t;
			}
		}

		delete[] vh;
		delete[] vv;
	}

	bool findh(int x, int y, Node**& h)
	{
		h = (vh + x);

		while (*h && (*h)->col < y)
		{
			h = &((*h)->right);
		}

		return (*h && (*h)->col == y);
	}

	bool findv(int x, int y, Node**& v)
	{
		v = (vv + y);

		while (*v && (*v)->row < x)
		{
			v = &((*v)->down);
		}

		return (*v && (*v)->row == x);
	}

	void ins(int x, int y, Node** h, Node** v, double val)
	{
		Node* t = new Node(val, x, y);

		t->right = *h;
		*h = t;

		t->down = *v;
		*v = t;
	}

	bool rem(int x, int y, Node** h, Node** v)
	{
		Node* t = *h;

		*h = t->right;
		*v = t->down;

		delete t;

		return true;
	}

	double get(int x, int y)
	{
		if (x < 0 || x >= nrows || y < 0 || y >= ncolumns) return 0.0;

		Node** h = nullptr;

		if (findh(x, y, h))
		{
			return (*h)->val;
		}

		return 0.0;
	}

	void set(int x, int y, double val)
	{
		if (x < 0 || x >= nrows || y < 0 || y >= ncolumns) return;

		Node** h = nullptr;
		Node** v = nullptr;

		bool flag_h = findh(x, y, h);
		bool flag_v = findv(x, y, v);

		if (flag_h)
		{
			if (val == 0.0)
			{
				rem(x, y, h, v);
			}
			else
			{
				(*h)->val = val;
			}
		}
		else
		{
			if (val != 0.0)
			{
				ins(x, y, h, v, val);
			}
		}
	}

	struct objx
	{
		SparseMatrix* m;
		int x, y;

		objx(SparseMatrix* tm, int tx, int ty)
		{
			m = tm;
			x = tx;
			y = ty;
		}

		void operator = (double k)
		{
			m->set(x, y, k);
		}

		operator double() {
			return m->get(x, y);
		}
	};

	objx operator()(int x, int y)
	{
		return objx(this, x, y);
	}

	void print()
	{
		std::cout << "matriz([";
		for (int filas = 0; filas < nrows; filas++)
		{
			if (filas > 0) std::cout << "     ";
			std::cout << "[";
			for (int columnas = 0; columnas < ncolumns; columnas++)
			{
				if (columnas == ncolumns - 1) std::cout << " | ";
				printf("%.1f", get(filas, columnas));
				if (columnas < ncolumns - 1 && columnas != ncolumns - 2) std::cout << ", ";
			}
			std::cout << "]";
			if (filas < nrows - 1) std::cout << ",\n";
		}
		std::cout << "])\n" << std::endl;
	}
};

void eliminacionGaussiana(SparseMatrix& mCientifica)
{
	int nNativo = mCientifica.nrows;

	mCientifica.print();

	for (int i = 0; i < nNativo; i++)
	{
		if (mCientifica.get(i, i) == 0.0)
		{
			for (int k = i + 1; k < nNativo; k++)
			{
				if (mCientifica.get(k, i) != 0.0)
				{
					for (int j = 0; j < mCientifica.ncolumns; j++)
					{
						double vNodo = mCientifica.get(i, j);
						mCientifica(i, j) = mCientifica.get(k, j);
						mCientifica(k, j) = vNodo;
					}
					std::cout << "IntercambioFilas(f" << i << ", f" << k << ")\n";
					mCientifica.print();
					break;
				}
			}
		}

		double coeficientePivote = mCientifica.get(i, i);
		if (coeficientePivote == 0.0) continue;

		for (int k = i + 1; k < nNativo; k++)
		{
			double multiplicador = mCientifica.get(k, i) / coeficientePivote;
			if (multiplicador != 0.0)
			{
				std::cout << "OP: f" << k << " = f" << k << " - (" << multiplicador << ") * f" << i << "\n";
				for (int j = i; j < mCientifica.ncolumns; j++)
				{
					mCientifica(k, j) = mCientifica.get(k, j) - multiplicador * mCientifica.get(i, j);
				}
				mCientifica.print();
			}
		}
	}

	double* arregloSoluciones = new double[nNativo];
	for (int i = 0; i < nNativo; i++) arregloSoluciones[i] = 0.0;

	for (int i = nNativo - 1; i >= 0; i--)
	{
		double sumatoriaAcumulada = mCientifica.get(i, mCientifica.ncolumns - 1);
		for (int j = i + 1; j < nNativo; j++)
		{
			sumatoriaAcumulada = sumatoriaAcumulada - mCientifica.get(i, j) * arregloSoluciones[j];
		}
		if (mCientifica.get(i, i) == 0.0)
		{
			std::cout << "MatrizSingularError" << std::endl;
			delete[] arregloSoluciones;
			return;
		}
		arregloSoluciones[i] = sumatoriaAcumulada / mCientifica.get(i, i);
	}

	std::cout << "SolucionesEncontradas:" << std::endl;
	char mapeoLetras[3] = { 'x', 'y', 'z' };
	for (int i = 0; i < nNativo && i < 3; i++)
	{
		std::cout << "  " << mapeoLetras[i] << " : " << arregloSoluciones[i] << std::endl;
	}

	delete[] arregloSoluciones;
}

int main()
{
	SparseMatrix matrix(3, 4);

	matrix(0, 0) = 2.0;  matrix(0, 1) = -1.0; matrix(0, 2) = 1.0;  matrix(0, 3) = 6.0;
	matrix(1, 0) = 1.0;  matrix(1, 1) = 3.0;  matrix(1, 2) = -2.0; matrix(1, 3) = -3.0;
	matrix(2, 0) = 3.0;  matrix(2, 1) = -2.0; matrix(2, 2) = 5.0;  matrix(2, 3) = 13.0;

	eliminacionGaussiana(matrix);
	return 0;
}
