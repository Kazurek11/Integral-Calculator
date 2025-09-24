#ifndef NUMERICAL_INTEGRATION_H
#define NUMERICAL_INTEGRATION_H

#include <stdbool.h>

/* Number of subdivisions for numerical integration */
#define NUM_SUBDIVISIONS 1000000

/* Global variables for integration limits */
extern double integration_start;
extern double integration_end;

/* Function pointer type for mathematical functions */
typedef double (*MathFunction)(double x);

/* Test functions */
double function_1(double x);
double function_2(double x);
double function_3(double x);
double function_4(double x);

/* Numerical integration methods */
double rectangle_rule(MathFunction func);
double trapezoidal_rule(MathFunction func);
double monte_carlo_integration(MathFunction func);

/* Utility functions */
bool are_limits_equal(void);

#endif /* NUMERICAL_INTEGRATION_H */