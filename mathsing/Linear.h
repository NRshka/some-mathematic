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
//���������� ��������� ���������� �������
Matrix* getOnesMatrix(size_t n);
Matrix* ATA(Matrix* A);
//���������� �������� ������� ������� ������
Matrix* InverseGauss(Matrix* A);
void print(Matrix* m);
void print(Vector* v);
//��������� ������, ������� ��������
Matrix* multiply(Matrix* a, Matrix* b);
//�������� ������� �� ������
Vector* multiply(Matrix* a, Vector* vec);
//�������� ��� ������� ��� ���, �� ������ �����������������
Matrix* multiplyABT(Matrix* a, Matrix* b);
//������� ������ �������
void clear_mem(Matrix* m);
}

#endif