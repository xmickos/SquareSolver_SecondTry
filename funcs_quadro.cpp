#include "quadro_heads.hpp"
#include <assert.h>
#define nan_or_inf_check(name);     if(!isfinite(name)){                                        \
        printf("[%s, line: %d] name is NAN or infinite!\n", __func__, __LINE__);                \
        return;                                                                                 \
    }                                                                                           \

// struct debug_names{
//     char name[4] = "";
//     double *ref = nullptr;
//
// };

void user_input(double *aref, double *bref, double *cref){
    #ifdef DEBUG
        debug_echo();
    #endif

    if(aref == nullptr){
        printf("[%s, line: %d]: aref is nullptr!\n", __func__, __LINE__);
        exit(-1);
    }
    if(bref == nullptr){
        printf("[%s, line: %d]: bref is nullptr!", __func__, __LINE__);
        exit(-1);
    }
    if(cref == nullptr){
        printf("[%s, line: %d]: cref is nullptr!", __func__, __LINE__);
        exit(-1);
    }

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
}

bool is_equal(double x, double y, double border){
    #ifdef DEBUG
        debug_echo();
    #endif
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
    #ifdef DEBUG
        debug_echo();
        printf("[DEBUG][%s, line: %d]: input args are: %f, %f, %f\n", __func__, __LINE__, a, b, c);
        printf("[DEBUG][%s, line: %d]: d is %f\n", __func__, __LINE__, b * b - 4.0 * a * c);
    #endif
    // 'comp_discr' func is needed to compute the equation`s discriminant

    // проверки на Input
    if(!isfinite(a)){
        printf("[comp_discr, line: %d] a is NAN or infinite number", __LINE__);
    }
    if(!isfinite(b)){
        printf("[comp_discr, line: %d] b is NAN or infinite number", __LINE__);
    }
    if(!isfinite(c)){
        printf("[comp_discr, line: %d] c is NAN or infinite number", __LINE__);
    }


    return ((b * b) - 4.0 * a * c);
}

void solve_linear(double b, double c, double *firstsol, double *secondsol){
    #ifdef DEBUG
        debug_echo();
    #endif
    //'solve_linear' func is needed to solve a linear equation b*x + c = 0

    #ifdef DEBUG
        nan_or_inf_check(b);
        nan_or_inf_check(c);
    #endif
    if(firstsol == nullptr){
        printf("[solve_linear, line: %d] firstsol is nullptr!\n", __LINE__);
        return;
    }
    if(secondsol == nullptr){
        printf("[solve_linear, line: %d] secondsol is nullptr!\n", __LINE__);
        return;
    }


    if(is_equal(b, 0.0, eps)){       // if b = 0.0
        if(is_equal(c, 0.0, eps)){
            printf("Answer: Your equation has infinitely many solutions.\n");   // if a = b = c = 0.0
            return;
        }
        else{
            firstsol = nullptr;
            secondsol = nullptr;
            printf("Answer: Your equation has no solutions.\n");
            return;
        }
    }
    else{
    *secondsol = - c / b;
    printf("Answer: Your equation solutions:\n\tx = %f.\n", *secondsol);
    }

}

void solve_quadratic(double a, double b, double c, double *firstsol, double *secondsol){
    #ifdef DEBUG
        debug_echo();
    #endif

    // 'solve_quadratic' func is needed to work with a != 0 case.

    nan_or_inf_check(a);
    nan_or_inf_check(b);
    nan_or_inf_check(c);

    double d = comp_discr(a, b, c);
    #ifdef DEBUG
        printf("[DEBUG][%s, line: %d]: d is %f\n",__func__, __LINE__, d);
    #endif

    if(d < 0.0){
        *firstsol = NAN;
        *secondsol = NAN;
        printf("Answer: Your equations has no solutions.\n");
        return;
    }
    if(is_equal(d, 0.0, eps)){       // d == 0
        *firstsol = -b / 2.0 * a;
        secondsol = nullptr;
        printf("Answer: Your equation has one solution: x = %f\n", *firstsol);
        return;
    }
    if(d > 0.0){              // d > 0

        *firstsol = - (b + sqrt(d)) / (2.0 * a);
        *secondsol = - (b - sqrt(d)) / (2.0 * a);
        printf("Answer: Your equation has two different solutions:\n\tx_1 = %f,\n\tx_2 = %f\n", *firstsol, *secondsol);
        return;
    }

}

void solve_general_equation(double a, double b, double c, double *firstsol, double *secondsol){

    // 'solve_general_equation' func redirects the calculation progress due to coefficients values.

    #ifdef DEBUG
        debug_echo();

        printf("[DEBUG][%s, line: %d]: d = %f\n", __func__, __LINE__, b*b-4*a*c);

        nan_or_inf_check(a);
        nan_or_inf_check(b);
        nan_or_inf_check(c);
    #endif
    if(firstsol == nullptr){
        printf("[solve_general_equation, line: %d] firstsol is nullptr!\n", __LINE__);
        return;
    }
    if(secondsol == nullptr){
        printf("[solve_general_equation, line: %d] secondsol is nullptr!\n", __LINE__);
        return;
    }


    if(is_equal(a, 0.0, eps)){ // if a = 0.0
        solve_linear(b, c, firstsol, secondsol);
        return;
    }
    if(is_equal(c, 0.0, eps)){ // a != 0.0 and c = 0.0
        *firstsol = 0.0;
        solve_linear(a, b, firstsol, secondsol);
        printf("\tx = %f\n", *firstsol);
        return;
    }
    else{                     // if a != 0.0 and c != 0.0
        solve_quadratic(a, b, c, firstsol, secondsol);
    }
}

void check_test(double *true_firstsol, double *true_secondsol, double *firstsol,
                double *secondsol, int answer_target, FILE *test_answers){
    debug_echo();

    nan_or_inf_check(*true_firstsol);
    nan_or_inf_check(*true_secondsol);
    nan_or_inf_check(answer_target);


    if(answer_target == 2){
        if(is_equal(*firstsol, *true_firstsol, delta) && is_equal(*secondsol, *true_secondsol, delta))
            fprintf(test_answers, "[DEBUG][%s, line: %d] Test passed successfully! true_first is %f, true_second is %f\n",
                    __func__, __LINE__, *true_firstsol, *true_secondsol);
    }
    if(answer_target == -1){
        if(firstsol == nullptr && secondsol == nullptr)
            fprintf(test_answers, "[DEBUG][%s, line: %d] Test passed successfully! true_first is %f, true_second is %f\n",
                    __func__, __LINE__, *true_firstsol, *true_secondsol);
        return;
    }
    if(answer_target == 0){
        if(isnan(*firstsol) && isnan(*secondsol))
            fprintf(test_answers, "[DEBUG][%s, line: %d] Test passed successfully! true_first is %f, true_second is %f\n",
                    __func__, __LINE__, *true_firstsol, *true_secondsol);
    }
    if(answer_target == 1){
        if(is_equal(*firstsol, *true_firstsol, delta) && secondsol == nullptr)
            fprintf(test_answers, "[DEBUG][%s, line: %d] Test passed successfully! true_first is %f, true_second is %f\n",
                    __func__, __LINE__, *true_firstsol, *true_secondsol);
    }

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
