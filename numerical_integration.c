#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "numerical_integration.h"

/* Global variables for integration limits */
double integration_start, integration_end;

/* Test function 1: Cubic polynomial */
double function_1(double x) {
    return -3.13 * x * x * x + 14.5 * x * x - 6.0 * x + 7.0;
}

/* Test function 2: Trigonometric function */
double function_2(double x) {
    return cos(2.0 * x * x) / 2.0 * sin(8.0 * x * x) - 3.0 * cos(5.0 + x) + 1.0;
}

/* Test function 3: Polynomial with fractional coefficients */
double function_3(double x) {
    return (1.0 / 10.0) * x * x * x + 2.0 * x * x + (1.0 / 2.0) * x + 5.0;
}

/* Test function 4: Mixed polynomial and trigonometric */
double function_4(double x) {
    return x * x * x * sin(2.0 * x) + cos(x);
}

/* Check if integration limits are essentially equal */
bool are_limits_equal(void) {
    return fabs(integration_start - integration_end) < 1e-10;
}

/* Rectangle rule (midpoint) integration */
double rectangle_rule(MathFunction func) {
    if (are_limits_equal()) {
        return 0.0;
    }
    
    const double step_size = (integration_end - integration_start) / NUM_SUBDIVISIONS;
    const double first_midpoint = integration_start + step_size / 2.0;
    double sum = 0.0;
    
    for (double x = first_midpoint; x < integration_end; x += step_size) {
        sum += func(x);
    }
    
    return sum * step_size;
}

/* Trapezoidal rule integration */
double trapezoidal_rule(MathFunction func) {
    if (are_limits_equal()) {
        return 0.0;
    }
    
    const double step_size = (integration_end - integration_start) / NUM_SUBDIVISIONS;
    double sum = 0.0;
    double current_value = func(integration_start);
    
    for (double x = integration_start; x < integration_end; x += step_size) {
        double next_x = x + step_size;
        if (next_x > integration_end) {
            next_x = integration_end;
        }
        
        double next_value = func(next_x);
        sum += (current_value + next_value) / 2.0 * (next_x - x);
        current_value = next_value;
    }
    
    return sum;
}

/* Monte Carlo integration method */
double monte_carlo_integration(MathFunction func) {
    if (are_limits_equal()) {
        return 0.0;
    }
    
    const double interval_length = integration_end - integration_start;
    const double sample_step = interval_length / NUM_SUBDIVISIONS;
    
    /* Find function's range */
    double min_value = func(integration_start);
    double max_value = min_value;
    
    for (double x = integration_start; x <= integration_end; x += sample_step) {
        double func_value = func(x);
        if (func_value > max_value) max_value = func_value;
        if (func_value < min_value) min_value = func_value;
    }
    
    const double max_positive = (max_value > 0.0) ? max_value : 0.0;
    const double min_negative = (min_value < 0.0) ? min_value : 0.0;
    
    srand(time(NULL));
    
    const int num_points = NUM_SUBDIVISIONS;
    int positive_points_under_curve = 0;
    int points_in_positive_region = 0;
    int negative_points_above_curve = 0;
    int points_in_negative_region = 0;
    
    const bool has_positive_region = max_positive > 0.0;
    const bool has_negative_region = min_negative < 0.0;
    
    /* Monte Carlo sampling */
    if (has_positive_region && has_negative_region) {
        for (int i = 0; i < num_points; i++) {
            double x = integration_start + ((double)rand() / RAND_MAX) * interval_length;
            double func_x = func(x);
            
            /* Check positive region */
            double y_positive = ((double)rand() / RAND_MAX) * max_positive;
            if (y_positive <= func_x && func_x > 0.0) {
                positive_points_under_curve++;
            }
            points_in_positive_region++;
            
            /* Check negative region */
            double y_negative = min_negative + ((double)rand() / RAND_MAX) * (-min_negative);
            if (y_negative >= func_x && func_x < 0.0) {
                negative_points_above_curve++;
            }
            points_in_negative_region++;
        }
    } else if (has_positive_region) {
        for (int i = 0; i < num_points; i++) {
            double x = integration_start + ((double)rand() / RAND_MAX) * interval_length;
            double func_x = func(x);
            
            double y_positive = ((double)rand() / RAND_MAX) * max_positive;
            if (y_positive <= func_x && func_x > 0.0) {
                positive_points_under_curve++;
            }
            points_in_positive_region++;
        }
    } else if (has_negative_region) {
        for (int i = 0; i < num_points; i++) {
            double x = integration_start + ((double)rand() / RAND_MAX) * interval_length;
            double func_x = func(x);
            
            double y_negative = min_negative + ((double)rand() / RAND_MAX) * (-min_negative);
            if (y_negative >= func_x && func_x < 0.0) {
                negative_points_above_curve++;
            }
            points_in_negative_region++;
        }
    }
    
    /* Calculate integral components */
    double positive_integral = 0.0;
    if (has_positive_region && points_in_positive_region > 0) {
        double positive_rectangle_area = interval_length * max_positive;
        positive_integral = ((double)positive_points_under_curve / points_in_positive_region) * positive_rectangle_area;
    }
    
    double negative_integral = 0.0;
    if (has_negative_region && points_in_negative_region > 0) {
        double negative_rectangle_area = interval_length * (-min_negative);
        negative_integral = ((double)negative_points_above_curve / points_in_negative_region) * negative_rectangle_area;
    }
    
    return positive_integral - negative_integral;
}