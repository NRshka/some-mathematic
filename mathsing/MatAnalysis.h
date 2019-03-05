#ifndef _MAT_ANALYSIS_H_
#define _MAT_ANALYSIS_H_


//расчёт определённого интеграла по формуле Симпсона
//Параметры: математическая функция, нажнияя граница, верхняя граница, размер интервала
double SimpsonsIntegral(double(*func)(double x), double a, double b, double n);



#endif