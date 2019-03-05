#include "Linear.h"

using namespace Linear;
//TODO: ��� ����� - ������ ������ ��� ���������� ����? �++ ��� �?
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

Matrix* Linear::getOnesMatrix(size_t n) {
	Matrix* m = getZerosMatrix(n, n);
	if (m == NULL)
		return NULL;

	for (size_t i = 0; i < n*n; i += n)
		m->matrix[i] = 1;

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

	return res;
}

Matrix* Linear::InverseGauss(Matrix* A) {
	Matrix* E = getOnesMatrix(A->rows);
	if (E == NULL)
		return NULL;

	for (size_t i = 0; i < A->rows; i++) {
		double divider = A->matrix[i*A->columns];//��, �� ��� �����
		for (size_t j = 0; j < A->columns; j++)
			A->matrix[i*A->columns + j] /= divider;
		

	}

	return NULL;
}