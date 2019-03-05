#include "Linear.h"
#include <iostream>

using namespace std;

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

<<<<<<< HEAD
<<<<<<< Updated upstream
=======
=======
>>>>>>> feature/InverseMatrix
Matrix* Linear::getOnesMatrix(size_t n) {
	Matrix* m = getZerosMatrix(n, n);
	if (m == NULL)
		return NULL;

	for (size_t i = 0; i < n*n; i += n + 1)
		m->matrix[i] = 1;

	return m;
}

<<<<<<< HEAD
>>>>>>> Stashed changes
=======
>>>>>>> feature/InverseMatrix
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

void Linear::print(Matrix* m) {
	for (size_t i = 0; i < m->columns*m->rows; i++) {
		cout << m->matrix[i] << ' ';
		if ((i + 1) % m->rows == 0)
			cout << endl;
	}
}

Matrix* Linear::InverseGauss(Matrix* A) {
	Matrix* E = getOnesMatrix(A->rows);
	if (E == NULL)
		return NULL;

	print(E);
	for (size_t i = 0; i < A->rows; i++) {
		double divider = A->matrix[i*A->columns + i];//то, на что делим
		for (size_t j = i; j < A->columns; j++) {
			A->matrix[i*A->columns + j] /= divider;
		}
		//TODO: перенести этот цикл в верхний, хтя бы частичн итерации будут выполняться
		//на больших матрицах может получиться экономия
		//хотя это надо для E
		for (size_t j = 0; j < E->columns; j++)
			E->matrix[i*E->columns + j] /= divider;

		//TODO: в последней итерации цикла не происхдит вычислений, т.к. матрица уже вычислена;
		//разбраться, можно ли сократить
		for (size_t row = 0; row < A->rows; row++) {
			//пропускаем ту же самую строчку при вычитании
			if (row == i)
				continue;

			divider = A->matrix[row*A->columns + i];
			for (size_t col = i; col < A->columns; col++)
				A->matrix[row * A->columns + col] -= divider * A->matrix[i*A->columns + col];
			//TODO: same up^
			for (size_t col = 0; col < E->columns; col++)
				E->matrix[row*E->columns + col] -= divider * E->matrix[i*E->columns + col];
		}
	}

	return E;
}