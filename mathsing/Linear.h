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
Matrix* ATA(Matrix* A);
}

#endif