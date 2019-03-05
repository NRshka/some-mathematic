#ifndef LINEAR_H_
#define LINEAR_H_
#include <stdlib.h>


namespace Linear{
typedef struct {
	double* vec;
	size_t len;
} Vector;

typedef struct {
	double* matrix;
	size_t rows;
	size_t columns;
} Matrix;

Matrix* getMatrix(size_t rows, size_t columns);
Matrix* getZerosMatrix(size_t rows, size_t columns);
//¬озвращает единичную квадратную матрицу
Matrix* getOnesMatrix(size_t n);
Matrix* ATA(Matrix* A);
//Ќахождение обратной матрицы методом √аусса
Matrix* InverseGauss(Matrix* A);
void print(Matrix* m);
void print(Vector* v);
//”множение матриц, наивный алгоритм
Matrix* multiply(Matrix* a, Matrix* b);
//”множить матрицу на вектор
Vector* multiply(Matrix* a, Vector* vec);
//умножить два матрицы при том, чт втора€ транспонированна€
Matrix* multiplyABT(Matrix* a, Matrix* b);
//чистить пам€ть матрицы
void clear_mem(Matrix* m);
}

#endif