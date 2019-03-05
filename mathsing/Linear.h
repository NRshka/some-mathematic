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
//Возвращает единичную квадратную матрицу
Matrix* getOnesMatrix(size_t n);
Matrix* ATA(Matrix* A);
//Нахождение обратной матрицы методом Гаусса
Matrix* InverseGauss(Matrix* A);
void print(Matrix* m);
}

#endif