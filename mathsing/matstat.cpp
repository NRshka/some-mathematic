#include <iostream>
#include "Linear.h"
#include "MatStat.h"

using namespace std;

double Mean(Variable* var) {
	double expVal = 0.0;
	for (size_t i = 0; i < var->dimensions; i++)
		expVal += var->probabilities[i] * var->values[i];

	return expVal;
}

double Variance(Variable* var) {
	double variance = 0.0;
	for (size_t i = 0; i < var->dimensions; i++)
		variance += var->probabilities[i] * (var->values[i] - expVal) * (var->values[i] - expVal);

	return variance;
}

ExpVar MD(Variable* var) {
	double expVal = 0.0;
	for (size_t i = 0; i < var->dimensions; i++)
		expVal += var->probabilities[i] * var->values[i];
	
	double variance = 0.0;
	for (size_t i = 0; i < var->dimensions; i++)
		variance += var->probabilities[i] * (var->values[i] - expVal) * (var->values[i] - expVal);
	
	return ExpVar({ expVal, variance });
}

double covariation(Variable* x, Variable* y) {
	if (x->dimensions != y->dimensions)
		return  -1;

	double sum = 0.0;
	double mean_x = Mean(x);
	double mean_y = Mean(y);
	for (size_t i = 0; i < x->dimensions; i++)
		sum += (x->values[i] - mean_x) * (y->values[i] - mean_y);

	return sum / x->dimensions;
}

/*
double covariationMatrix(Variable* x) {
	ExpVar X_md = MD(x);

	Matrix* m = getMatrix(x->dimensions, y->dimensions);
	for (size_t i = 0; i < x->dimensions; i++)
		m->matrix[i * x->dimensions + i] = X_md.variance;
	
	for (size_t n = 1; n < x->dimensions; n++) {
		for (size_t m = n + 1; m < x->dimensions; m++) {
			m->matrix[n*x->dimensions +m] = 
		}
	}
}
*/