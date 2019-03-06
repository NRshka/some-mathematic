#include "Linear.h"
#include <iostream>
#include <stdarg.h>

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

Vector* Linear::getOnesVector(size_t n) {
	Vector* v = (Vector*)malloc(sizeof(Vector));
	v->vec = (double*)malloc(n* sizeof(double));

	if (!(v && v->vec))
		return NULL;

	for (size_t i = 0; i < n; i++)
		v->vec[i] = 0.0;
}

void Linear::clear_mem(Matrix* m) {
	free(m->matrix);
	free(m);
}

void Linear::clear_mem(size_t count, Vector* v1, ...) {
	va_list vectors;
	va_start(vectors, count);
	for (; count > 0; count--) {
		Vector* v = va_arg(vectors, Vector*);
		free(v->vec);
		free(v);
	}
}

Matrix* Linear::ATA(Matrix* A) {
	Matrix* res = getZerosMatrix(A->columns, A->columns);
	//TODO �������� �� NULL ������
	for (size_t i = 0; i < A->columns; i++) {
		for (size_t j = 0; j < A->columns; j++) {
			for(size_t k = 0; k < A->rows; k++) {
				res->matrix[i * res->columns + j] += A->matrix[k * A->columns + i] * A->matrix[k * A->columns + j];
			}
		}
	}

	return res;
}

void Linear::print(Matrix* m) {
	for (size_t i = 0; i < m->columns*m->rows; i++) {
		cout << m->matrix[i] << ' ';
		if ((i + 1) % m->columns == 0)
			cout << endl;
	}
}

void Linear::print(Vector* v) {
	for (size_t i = 0; i < v->len; i++)
		cout << v->vec[i] << ' ';
	cout << endl;
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

Vector* Linear::multiply(Matrix* a, Vector* vec) {
	if (a->columns != vec->len)
		return NULL;

	//TODO: ������� �������� ������� ��� ����� �� ���������� ������� � ��������� ������
	Vector* res = (Vector*)malloc(sizeof(Vector));
	res->len = vec->len;
	res->vec = (double*)malloc(vec->len * sizeof(double));
	for (size_t i = 0; i < res->len; i++)
		res->vec[i] = 0.0;

	for (size_t i = 0; i < a->rows*a->columns; i++)
		res->vec[i / res->len] += a->matrix[i] * vec->vec[i%vec->len];

	return res;
}

Vector* Linear::multiply(Vector* vec, Matrix* a) {
	if (a->rows != vec->len)
		return NULL;

	//TODO: ������� �������� ������� ��� ����� �� ���������� ������� � ��������� ������
	Vector* res = (Vector*)malloc(sizeof(Vector));
	res->len = vec->len;
	res->vec = (double*)malloc(vec->len * sizeof(double));
	for (size_t i = 0; i < res->len; i++)
		res->vec[i] = 0.0;

	for (size_t i = 0; i < a->rows*a->columns; i++)
		res->vec[i % res->len] += a->matrix[i] * vec->vec[i / vec->len];

	return res;
}

Vector* Linear::minus(Vector* a, Vector* b) {
	if (a->len != b->len)
		return NULL;

	Vector* res = (Vector*)malloc(sizeof(Vector));
	res->len = a->len;
	res->vec = (double*)malloc(res->len * sizeof(double));
	if (res == NULL || res->vec == NULL)
		return NULL;

	for (size_t i = 0; i < a->len; i++)
		res->vec[i] = a->vec[i] - b->vec[i];

	return res;
}

Matrix* Linear::multiplyABT(Matrix* a, Matrix* b) {
	if (a->columns != b->columns)
		return NULL;

	Matrix* res = getZerosMatrix(a->rows, b->rows);
	//TODO �������� �� NULL ������
	for (size_t i = 0; i < a->rows; i++) {
		for (size_t j = 0; j < b->rows; j++) {
			for (size_t k = 0; k < b->columns; k++) {
				res->matrix[i * res->columns + j] += a->matrix[i * a->columns + k] * b->matrix[j * b->columns + k];
			}
		}
	}

	return res;
}