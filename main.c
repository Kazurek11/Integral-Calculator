#include <stdio.h>
#include <stdlib.h>
#include "numerical_integration.h"

int main(void) {
    /* Input integration limits */
    printf("Enter integration start point: ");
    if (scanf("%lf", &integration_start) != 1) {
        fprintf(stderr, "Error: Invalid input for start point\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter integration end point: ");
    if (scanf("%lf", &integration_end) != 1) {
        fprintf(stderr, "Error: Invalid input for end point\n");
        return EXIT_FAILURE;
    }
    
    /* Display results for all test functions */
    printf("\n=== Numerical Integration Results ===\n");
    
    printf("\nFunction 1: f(x) = -3.13x³ + 14.5x² - 6x + 7\n");
    printf("Rectangle rule:    %.6f\n", rectangle_rule(function_1));
    printf("Trapezoidal rule:  %.6f\n", trapezoidal_rule(function_1));
    printf("Monte Carlo:       %.6f\n", monte_carlo_integration(function_1));
    
    printf("\nFunction 2: f(x) = cos(2x²)/2 * sin(8x²) - 3cos(5+x) + 1\n");
    printf("Rectangle rule:    %.6f\n", rectangle_rule(function_2));
    printf("Trapezoidal rule:  %.6f\n", trapezoidal_rule(function_2));
    printf("Monte Carlo:       %.6f\n", monte_carlo_integration(function_2));
    
    printf("\nFunction 3: f(x) = 0.1x³ + 2x² + 0.5x + 5\n");
    printf("Rectangle rule:    %.6f\n", rectangle_rule(function_3));
    printf("Trapezoidal rule:  %.6f\n", trapezoidal_rule(function_3));
    printf("Monte Carlo:       %.6f\n", monte_carlo_integration(function_3));
    
    printf("\nFunction 4: f(x) = x³sin(2x) + cos(x)\n");
    printf("Rectangle rule:    %.6f\n", rectangle_rule(function_4));
    printf("Trapezoidal rule:  %.6f\n", trapezoidal_rule(function_4));
    printf("Monte Carlo:       %.6f\n", monte_carlo_integration(function_4));
    
    return EXIT_SUCCESS;
}