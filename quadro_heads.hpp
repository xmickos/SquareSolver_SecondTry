#include <stdio.h>
#include <math.h>
#include <assert.h>

#ifdef NDEBUG
#define DEBUG_ECHO(); printf("[DEBUG][%s, %s, line: %d]\n",__FILE__, __func__, __LINE__);
#else
#define DEBUG_ECHO(); ;
#endif

#ifdef DEBUG
#define NAN_OR_INF_CHECK(name);     if(!isfinite(name)){                                        \
        printf("[%s, line: %d] #name is NAN or infinite!\n", __func__, __LINE__);               \
        exit(-1);                                                                               \
    }                                                                                           \
#endif
#endif

#ifndef DEBUG
#define NAN_OR_INF_CHECK(name); ;
#endif

#define NULLPTR_ERROR_CHECK(aref);     if(aref == nullptr){                                     \
        printf("[%s, line: %d]: #aref is nullptr!\n", __func__, __LINE__);                      \
        return -1;                                                                              \
    }                                                                                           \

#define ERROR_MESSAGE(); printf("[Error, line: %d] %s shared wrong params!\n", __LINE__, __func__);

#define TEST_PASSED_MESSAGE(); fprintf(test_answers, "[DEBUG][%s, line: %d] Test passed         \
successfully! true_first is %f, true_second is %f\n",                                           \
                    __func__, __LINE__, *true_firstsol, *true_secondsol);                       \

#define TEST_CHECK(condition, target);     if(answer_target == target){                         \
        if(condition) fprintf(test_answers, "[DEBUG][%s, line: %d] Test passed                  \
                        successfully! true_first is %f, true_second is %f\n", __func__,         \
                        __LINE__, *true_firstsol, *true_secondsol);                             \
        return 0;                                                                               \
    }                                                                                           \


/// @brief eps and delta variables are used to compare double numbers with a given precision.

const double eps = 1.0e-3;
const double delta = 0.01;

/**
* @brief Used for keyboard user`s input. Input coefficients must be in format like "5.2 -0.17 27.52"
* without any other separating character.
* \param aref pointer to variable "a" coefficient. Do not try to use with aref = nullptr.
* \param bref pointer to variable "a" coefficient. Do not try to use with aref = nullptr.
* \param cref pointer to variable "a" coefficient. Do not try to use with aref = nullptr.
*/

int user_input(double *aref, double *bref, double *cref);

/**
*   @brief Used for compare double numbers with a given precision.
*/

bool is_equal(double x, double y);

/**
 * @brief Used for computing equation`s discriminant. No pointers are needed.
 *
 * @param a double variable. Do not try to use with inf or NAN.
 * @param b double variable. Do not try to use with inf or NAN.
 * @param c double variable. Do not try to use with inf or NAN.
 * @return double
 */

double comp_discr(double a, double b, double c);

/**
 * @brief 'solve_quadratic' func is needed to work with a != 0 case.
 *
 * @param b value of b coeff.
 * @param c value of c coeff.
 * @param firstsol pointer to first solution variable. Do not use with firstsol = nullptr.
 * @param secondsol pointer to second solution variable. Do not use with secondsol = nullptr.
 */

int solve_linear(double b, double c, double *firstsol, double *secondsol);

/**
 * @brief General function that used to split computations in different cases with a, b, c = or != 0.
 *
 * @param a value of a coeff.
 * @param b value of b coeff.
 * @param c value of c coeff.
 * @param firstsol pointer to first solution variable. Do not use with firstsol = nullptr.
 * @param secondsol pointer to second solution variable. Do not use with secondsol = nullptr.
 */

int solve_general_equation(double a, double b, double c, double *firstsol, double *secondsol);

/**
 * @brief Debug mode function. Used for checking program`s answers to test examples from tests.txt and write results in logfile.
 *
 * @param true_firstsol pointer to true value of first equation solution. Need to be readed from tests.txt
 * @param true_secondsol pointer to true value of second equation solution. Need to be readed from tests.txt
 * @param firstsol computed value of first equation solution. Need to be comparated with true_firstsol
 * @param secondsol computed value of second equation solution. Need to be comparated with true_secondsol
 * @param answer_target debugging variable required to determine the result of calculations. Cases: -1 = inf solutions,
 * 0 = no solutions, 1 = one solution, 2 = two solutions.
 * @param answers a file pointer used to record test results.
 */

int check_test(double *true_firstsol, double *true_secondsol, double *firstsol,
                double *secondsol, int answer_target, FILE *answers);

/**
 * @brief 'test_reader' func reads a a,b,c coeffs values to move them into solve_general_equation() func.
 *
 * @param unitest a file pointer to tests.txt file with tests.
 * @param aref double pointer variable. Do not try to use with inf or NAN.
 * @param bref double pointer variable. Do not try to use with inf or NAN.
 * @param cref double pointer variable. Do not try to use with inf or NAN.
 * @param answer_target debugging variable required to determine the result of calculations. Cases: -1 = inf solutions,
 * 0 = no solutions, 1 = one solution, 2 = two solutions.
 * @param true_firstsol pointer to true value of first equation solution. Need to be readed from tests.txt
 * @param true_secondsol pointer to true value of second equation solution. Need to be readed from tests.txt
 */

void test_reader(FILE *unitest, double *aref, double *bref, double *cref, int *answer_target,
            double *true_firstsol, double *true_secondsol);

/**
 * @brief This func works with case a != 0 and c != 0.
 *
 * @param a "a" param of equation. Do not use with a = NULL;
 * @param b "b" param of equation. Do not use with b = NULL;
 * @param c "c" param of equation. Do not use with c = NULL;
 * @param firstsol pointer to first solution variable. Do not use with firstsol = nullptr.
 * @param secondsol pointer to first solution variable. Do not use with firstsol = nullptr.
 * @return int
 */

int solve_quadratic(double a, double b, double c, double *firstsol, double *secondsol);
