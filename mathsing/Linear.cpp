#include "Linear.h"
#include <iostream>

using namespace std;

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

	for (size_t i = 0; i < n*n; i += n + 1)
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

void Linear::print(Matrix* m) {
	for (size_t i = 0; i < m->columns*m->rows; i++) {
		cout << m->matrix[i] << ' ';
		if ((i + 1) % m->rows == 0)
			cout << endl;
	}
}

Matrix* copy(Matrix* m) {
	Matrix* A = (Matrix*)malloc(sizeof(Matrix));
	A->matrix = (double*)malloc(m->rows * m->columns * sizeof(double));
	//TODO NULL error exception
	A->rows = m->rows;
	A->columns = m->columns;
	memcpy(A->matrix, m->matrix, m->rows*m->columns * sizeof(double));

	return A;
}

Matrix* Linear::InverseGauss(Matrix* m) {
	Matrix* A = copy(m);
	Matrix* E = getOnesMatrix(A->rows);
	if (E == NULL || A == NULL)
		return NULL;

	for (size_t i = 0; i < A->rows; i++) {
		double divider = A->matrix[i*A->columns + i];//��, �� ��� �����
		for (size_t j = i; j < A->columns; j++) {
			A->matrix[i*A->columns + j] /= divider;
		}
		//TODO: ��������� ���� ���� � �������, ��� �� ������� �������� ����� �����������
		//�� ������� �������� ����� ���������� ��������
		//���� ��� ���� ��� E
		for (size_t j = 0; j < E->columns; j++)
			E->matrix[i*E->columns + j] /= divider;

		//TODO: � ��������� �������� ����� �� ��������� ����������, �.�. ������� ��� ���������;
		//����������, ����� �� ���������
		for (size_t row = 0; row < A->rows; row++) {
			//���������� �� �� ����� ������� ��� ���������
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

Matrix* Linear::multiply(Matrix* a, Matrix* b) {
	if (a->columns != b->rows)
		return NULL;

	Matrix* res = getZerosMatrix(a->rows, b->columns);

	for (size_t i = 0; i < a->rows; i++) {
		for (size_t j = 0; j < b->columns; j++) {
			for (size_t b_row = 0; b_row < b->rows; b_row++)
				res->matrix[i * res->columns + j] += a->matrix[i*a->columns + b_row] * b->matrix[b_row*b->columns + j];
		}
	}

	return res;
}