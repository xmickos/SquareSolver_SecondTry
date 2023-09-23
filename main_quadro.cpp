#include <stdio.h>
#include <math.h>
#include <assert.h>
const double eps = 1.0e-5;
// Вопросы:
// Докстринги нужны в С++?
// Всегда ли нужно класть программу когда найден nullptr? Что с ним делать, если он появился
// Не в главной функции ?
// Чем инициализировать double`ы?
// Компилятор не знает старых флагов – что делать ?
// Что делать, если в побочной функции выяснилось что аргумент infinite? Остановить программу? Как? – assert

// Дописать функции input`a для debug и для user режимов.
// Дописать везде проверки, а затем assert`ы и 'isfinite'
// Разбить программу на три файла
// Сделать make-файл ~~~
// Разобраться с github`ом
// Сделать debug и user режим
// Обрабатывать случай a !=0, c == 0 как линейное уравнение .


bool is_equal(double x, double y){
    // 'is_equal' func is needed to check that |x - y| is lower than eps.

    if(!isfinite(x)){
        printf("[is_equal, line: %d] x is NAN or infinite number", __LINE__);
        printf("[is_equal, line %d] x was set to 0.0\n", __LINE__);
        x = 0.0;
    }
    if(!isfinite(y)){
        printf("[is_equal, line: %d] y is NAN or infinite number", __LINE__);
        printf("[is_equal, line %d] y was set to 0.0\n", __LINE__);
        y = 0.0;
    }

    return fabs(x - y) < eps;
}

double comp_discr(double a, double b, double c){
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


    return (b * b) - 4.0 * a * c;
}

void solve_linear(double b, double c, double *firstsol, double *secondsol){
    //'solve_linear' func is needed to solve a linear equation b*x + c = 0

    // проверки на input
    if(!isfinite(b)){
        printf("[solve_linear, line: %d] b is NAN or infinite!\n", __LINE__);
        return;
    }
    if(!isfinite(c)){
        printf("[solve_linear, line: %d] c is NAN or infinite!\n", __LINE__);
        return;
    }
    if(firstsol == nullptr){
        printf("[solve_linear, line: %d] firstsol is nullptr!\n", __LINE__);
        return;
    }
    if(secondsol == nullptr){
        printf("[solve_linear, line: %d] secondsol is nullptr!\n", __LINE__);
        return;
    }


    if(is_equal(b, 0.0)){       // если b == 0
        if(is_equal(c, 0.0)){
            printf("Answer: Your equation has infinitely many solutions.\n");
        }
        else{
            printf("Answer: Your equation has no solutions.\n");
        }
    }
    else{
    *firstsol = - c / b;
    *secondsol = - c / b;
    printf("Answer: Your equation has two equal solutions: x = %f.\n", *firstsol);
    }

}

void solve_quadratic(double a, double b, double c, double *firstsol, double *secondsol){
    // 'solve_quadratic' func is needed to work with a != 0 case.

    // проверки на Input

    if(!isfinite(a)){
        printf("[solve_quadratic, line: %d] c is NAN or infinite!\n", __LINE__);
        return;
    }
    if(!isfinite(b)){
        printf("[solve_quadratic, line: %d] b is NAN or infinite!\n", __LINE__);
        return;
    }
    if(!isfinite(c)){
        printf("[solve_quadratic, line: %d] c is NAN or infinite!\n", __LINE__);
        return;
    }

    double d = comp_discr(a, b, c);

    if(d < 0.0){
        firstsol = nullptr;
        secondsol = nullptr;
        printf("Answer: Your equations has no solutions.\n");
        return;
    }
    if(is_equal(d, 0.0)){       // d == 0
        *firstsol = -b / 2.0 * a;
        secondsol = nullptr;
        printf("Answer: Your equation has one solution: x = %f", *firstsol);
        return;
    }
    if(d > 0.0){              // d > 0
        *firstsol = - (b + sqrt(d)) / 2.0 * a;
        *secondsol = - (b - sqrt(d)) / 2.0 * a;
        printf("Answer: Your equation has two different solutions:\n\tx_1 = %f,\n\tx_2 = %f\n", *firstsol, *secondsol);
        return;
    }

}

void solve_general_equation(double a, double b, double c, double *firstsol, double *secondsol){
    // 'solve_general_equation' func redirects the calculation progress due to coefficients values.

    // проверки на input
    if(!isfinite(a)){
        printf("[solve_general_equation, line: %d] c is NAN or infinite!\n", __LINE__);
        return;
    }
    if(!isfinite(b)){
        printf("[solve_general_equation, line: %d] b is NAN or infinite!\n", __LINE__);
        return;
    }
    if(!isfinite(c)){
        printf("[solve_general_equation, line: %d] c is NAN or infinite!\n", __LINE__);
        return;
    }
    if(firstsol == nullptr){
        printf("[solve_general_equation, line: %d] firstsol is nullptr!\n", __LINE__);
        return;
    }
    if(secondsol == nullptr){
        printf("[solve_general_equation, line: %d] secondsol is nullptr!\n", __LINE__);
        return;
    }


    if(is_equal(a, 0.0)){ // Если уравнение линейное
        solve_linear(b, c, firstsol, secondsol);
    }
    else{                     // Если уравнение квадратное
        solve_quadratic(a, b, c, firstsol, secondsol);
    }
}

int main(){

    double aref = NAN, bref = 0.0, cref = 0.0, firstsol = 0.0, secondsol = 0.0;

    // Input func for user mode
    // Input func for debug mode

    solve_general_equation(aref, bref, cref, &firstsol, &secondsol);
    return 0;
}
