#include <stdio.h>
#include <math.h>
#include <assert.h>
#define debug_echo(); printf("[DEBUG][%s, %s, line: %d]\n",__FILE__, __func__, __LINE__);

const double eps = 1.0e-3;
const double delta = 0.01;

void user_input(double *aref, double *bref, double *cref);

bool is_equal(double x, double y);

double comp_discr(double a, double b, double c);

void solve_linear(double b, double c, double *firstsol, double *secondsol);

void solve_general_equation(double a, double b, double c, double *firstsol, double *secondsol);

void check_test(double *true_firstsol, double *true_secondsol, double *firstsol,
                double *secondsol, int answer_target, FILE *answers);

void test_reader(FILE *unitest, double *aref, double *bref, double *cref, int *answer_target,
            double *true_firstsol, double *true_secondsol);
