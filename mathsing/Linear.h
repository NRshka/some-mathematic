#ifndef LINEAR_H_
#define LINEAR_H_
#include <stdlib.h>


namespace Linear{
typedef struct {
	double* vec;
	size_t len;
	double sum() {
		double s = 0.0;
		for (size_t i = 0; i < len; i++)
			s += vec[i];
		return s;
	}
} Vector;

typedef struct {
	double* matrix;
	size_t rows;
	size_t columns;
} Matrix;
typedef struct{
	size_t count_dim;
	size_t* counts;
	double* matrix;
} NMatrix;

Matrix* getMatrix(size_t rows, size_t columns);
Matrix* getZerosMatrix(size_t rows, size_t columns);
NMatrix* getNMatrix(size_t count_dim, ...);
NMatrix* getZerosNMatrix(size_t count_dim, ...);
NMatrix* getOnesNMatrix(size_t count_dim, size_t dims);
//���������� ��������� ���������� �������
Matrix* getOnesMatrix(size_t n);
Vector* getOnesVector(size_t n);
Matrix* ATA(Matrix* A);
//���������� �������� ������� ������� ������
Matrix* InverseGauss(Matrix* A);
void print(Matrix* m);
void print(Vector* v);
//��������� ������, ������� ��������
Matrix* multiply(Matrix* a, Matrix* b);
//�������� ������� �� ������
Vector* multiply(Matrix* a, Vector* vec);
Vector* multiply(Vector*vec, Matrix* a);
Vector* minus(Vector* a, Vector* b);
//�������� ��� ������� ��� ���, �� ������ �����������������
Matrix* multiplyABT(Matrix* a, Matrix* b);
//������� ������ �������
void clear_mem(Matrix* m);
void clear_mem(size_t count, Vector* v1, ...);
}

#endif