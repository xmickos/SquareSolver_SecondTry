#include "quadro_heads.hpp"
#include <assert.h>

/// @brief This file contains all source code for funcs presented in quadro_heads.hhp.

// struct debug_names{
//     char name[4] = "";
//     double *ref = nullptr;
//
// };

int user_input(double *aref, double *bref, double *cref){
    DEBUG_ECHO();

    NULLPTR_ERROR_CHECK(aref);
    NULLPTR_ERROR_CHECK(bref);
    NULLPTR_ERROR_CHECK(cref);

    printf("\nInput your coeffs, one by one separated by a space.\n");

    while(scanf("%lf %lf %lf", aref, bref, cref) != 3){
        while(!getchar());
        printf("\nPlease repeat the input.\n");
        #ifdef DEBUG
            printf("[DEBUG][%s, line: %d]: Current input is: %f, %f, %f\n", __func__, __LINE__, *aref, *bref, *cref);
        #endif
        *aref = NAN;
        *bref = NAN;
        *cref = NAN;
    }

/*     while(scanf_count != 3){
//     scanf_count = 0;
//
//     if(scanf("%lf", aref) > 0) scanf_count++;
//     printf("[DEBUG][%s, line: %d]: input: a = %f, b = %f, c = %f\n",__func__, __LINE__, *aref, *bref, *cref);
//     while(getchar() != '\0');
//     if(scanf("%lf", bref) > 0) scanf_count++;
//     printf("[DEBUG][%s, line: %d]: input: a = %f, b = %f, c = %f\n",__func__, __LINE__, *aref, *bref, *cref);
//     while(!getchar());
//     if(scanf("%lf", cref) > 0) scanf_count++;
//     while(!getchar());
//     } */

    #ifdef DEBUG
        printf("[DEBUG][%s, line: %d]: input: a = %.3f, b = %.3f, c = %.3f.\n",__func__, __LINE__, *aref, *bref, *cref);
    #endif

    return 0;
}

bool is_equal(double x, double y, double border){
    DEBUG_ECHO();
    // 'is_equal' func is needed to check that |x - y| is lower than eps.

    if(!isfinite(x)){
        printf("[%s, line: %d] x is NAN or infinite number", __func__, __LINE__);
        printf("[%s, line %d] x was set to 0.0\n", __func__, __LINE__);
        x = 0.0;
    }
    if(!isfinite(y)){
        printf("[%s, line: %d] y is NAN or infinite number", __func__, __LINE__);
        printf("[%s, line %d] y was set to 0.0\n", __func__, __LINE__);
        y = 0.0;
    }

    return fabs(x - y) < border;
}

double comp_discr(double a, double b, double c){
    DEBUG_ECHO();
    #ifdef DEBUG
        printf("[DEBUG][%s, line: %d]: input args are: %f, %f, %f\n", __func__, __LINE__, a, b, c);
        printf("[DEBUG][%s, line: %d]: d is %f\n", __func__, __LINE__, b * b - 4.0 * a * c);
    #endif
    // 'comp_discr' func is needed to compute the equation`s discriminant

    // проверки на Input
    NAN_OR_INF_CHECK(a);
    NAN_OR_INF_CHECK(b);
    NAN_OR_INF_CHECK(c);

    return ((b * b) - 4.0 * a * c);
}

int solve_linear(double b, double c, double *firstsol, double *secondsol){
    DEBUG_ECHO();
    //'solve_linear' func is needed to solve a linear equation b*x + c = 0

    NAN_OR_INF_CHECK(b);
    NAN_OR_INF_CHECK(c);

    NULLPTR_ERROR_CHECK(firstsol);
    NULLPTR_ERROR_CHECK(secondsol);


    if(is_equal(b, 0.0, eps)){       // if b = 0.0
        if(is_equal(c, 0.0, eps)){
            printf("Answer: Your equation has infinitely many solutions.\n");   // if a = b = c = 0.0
            return 0;
        }
        else{
            firstsol = nullptr;
            secondsol = nullptr;
            printf("Answer: Your equation has no solutions.\n");
            return 0;
        }
    }
    else{
        *secondsol = - c / b;
        printf("Answer: Your equation solutions:\n\tx = %f.\n", *secondsol);
        return 0;
    }
    return 0;
}

int solve_quadratic(double a, double b, double c, double *firstsol, double *secondsol){
    DEBUG_ECHO();

    NAN_OR_INF_CHECK(a);
    NAN_OR_INF_CHECK(b);
    NAN_OR_INF_CHECK(c);

    double d = comp_discr(a, b, c);
    #ifdef DEBUG
        printf("[DEBUG][%s, line: %d]: d is %f\n",__func__, __LINE__, d);
    #endif

    if(d < 0.0){
        *firstsol = NAN;
        *secondsol = NAN;
        printf("Answer: Your equations has no solutions.\n");
        return 0;
    }
    if(is_equal(d, 0.0, eps)){       // d == 0
        *firstsol = -b / 2.0 * a;
        secondsol = nullptr;
        printf("Answer: Your equation has one solution: x = %f\n", *firstsol);
        return 0;
    }
    if(d > 0.0){              // d > 0
        double square = sqrt(d);
        *firstsol = - (b + square) / (2.0 * a);
        *secondsol = - (b - square) / (2.0 * a);
        printf("Answer: Your equation has two different solutions:\n\tx_1 = %f,\n\tx_2 = %f\n", *firstsol, *secondsol);
        return 0;
    }

    return 0;
}

int solve_general_equation(double a, double b, double c, double *firstsol, double *secondsol){

    // 'solve_general_equation' func redirects the calculation progress due to coefficients values.

    DEBUG_ECHO();

    #ifdef DEBUG
        printf("[DEBUG][%s, line: %d]: d = %f\n", __func__, __LINE__, b*b-4*a*c);
    #endif

    NAN_OR_INF_CHECK(a);
    NAN_OR_INF_CHECK(b);
    NAN_OR_INF_CHECK(c);

    NULLPTR_ERROR_CHECK(firstsol);
    NULLPTR_ERROR_CHECK(secondsol);


    if(is_equal(a, 0.0, eps)){ // if a = 0.0
        if(solve_linear(b, c, firstsol, secondsol)){
            ERROR_MESSAGE();
            return -1;
        }
        return 0;
    }
    if(is_equal(c, 0.0, eps)){ // a != 0.0 and c = 0.0
        *firstsol = 0.0;
        if(solve_linear(a, b, firstsol, secondsol)){
            ERROR_MESSAGE();
            return -1;
        }
        printf("\tx = %f\n", *firstsol);
        return 0;
    }
    else{                     // if a != 0.0 and c != 0.0
        if(solve_quadratic(a, b, c, firstsol, secondsol)){
            ERROR_MESSAGE();
            return -1;
        }
    }

    return 0;
}

int check_test(double *true_firstsol, double *true_secondsol, double *firstsol,
                double *secondsol, int answer_target, FILE *test_answers){
    DEBUG_ECHO();

    NAN_OR_INF_CHECK(*true_firstsol);
    NAN_OR_INF_CHECK(*true_secondsol);
    NAN_OR_INF_CHECK(answer_target);

    TEST_CHECK(is_equal(*firstsol, *true_firstsol, delta) && is_equal(*secondsol, *true_secondsol, delta), 2);
    TEST_CHECK(firstsol == nullptr && secondsol == nullptr, -1);
    TEST_CHECK(isnan(*firstsol) && isnan(*secondsol), 0);
    TEST_CHECK(is_equal(*firstsol, *true_firstsol, delta) && secondsol == nullptr, 1);

    return 0;
}

void test_reader(FILE *unitest, double *aref, double *bref, double *cref, int *answer_target,
            double *true_firstsol, double *true_secondsol){

    if(fscanf(unitest, "%lf %lf %lf %d %lf %lf", aref, bref, cref, answer_target, true_firstsol, true_secondsol) < 4){
        printf("[DEBUG][%s %s, line: %d]: Failed to read new test line from file!\n", __FILE__, __func__, __LINE__);
        exit(-1);
    }

    printf("[DEBUG][%s, %s, line: %d]: a = %f, b = %f, c = %f, true_firstsol = %f, true_secondsol = %f\n",
            __FILE__, __func__, __LINE__,  *aref, *bref, *cref, *true_firstsol, *true_secondsol);

    return;
}
