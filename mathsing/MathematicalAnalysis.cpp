#include "MatAnalysis.h"





double SimpsonsIntegral(double(*func)(double x), double a, double b, double n) {
	double h = (b - a) / (2 * n);
	double integral = func(a) + func(b);

	//все нечётные точки
	for (size_t i = 1; i < 2 * n; i += 2)
		integral += 4 * func(a + h * i);
	//все чётные точки
	for (size_t i = 2; i < (2 * n - 1); i += 2)
		integral += 2 * func(a + h * i);

	return integral;
}