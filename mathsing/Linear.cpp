#include "Linear.h"

using namespace Linear;
//TODO: что лучще - кидать ошибку или возвращать нуль? с++ или с?
Matrix* Linear::getMatrix(size_t rows, size_t columns) {
	Matrix* m = (Matrix*)malloc(sizeof(Matrix));
	m->matrix = (double*)malloc(rows*columns * sizeof(double));

	if (!(m && m->matrix))
		return NULL;

	m->rows = rows;
	m->columns = columns;

	return m;
}

Matrix* Linear::getZerosMatrix(size_t rows, size_t columns) {
	Matrix* m = getMatrix(rows, columns);
	if (m == NULL)
		return NULL;
	for (size_t i = 0; i < rows*columns; i++)
		m->matrix[i] = 0.0;
	
	return m;
}

Matrix* Linear::ATA(Matrix* A) {
	Matrix* res = getZerosMatrix(A->columns, A->columns);
	for (size_t i = 0; i < A->rows; i++) {
		for (size_t j = 0; j < A->columns; j++) {
			for(size_t k = 0; k < A->columns; k++) {
				res->matrix[i * res->columns + j] += A->matrix[i * A->columns + k] * A->matrix[j * A->columns + k];
			}
		}
	}
	return NULL;
}