#include "MatAnalysis.h"





double SimpsonsIntegral(double(*func)(double x), double a, double b, double n) {
	double h = (b - a) / n;
	double integral = func(a) + func(b);

	double x = a + h;
	while (x <= b) {
		integral += 4 * func(x);
		x += h;
		if (x >= b)
			break;
		integral += 2 * func(x);
		x += h;
	}

	return (h*integral) / 3.0;
}