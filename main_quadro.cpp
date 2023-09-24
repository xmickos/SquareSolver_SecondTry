#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "quadro_heads.hpp"

// Вопросы:
// Докстринги нужны в С++? - В документации
// Всегда ли нужно класть программу когда найден nullptr? Что с ним делать, если он появился
// Не в главной функции ? - документация + assert`ы
// Компилятор не знает старых флагов – что делать ? -Выпилить их
// Что делать, если в побочной функции выяснилось что аргумент infinite? Остановить программу? Как? – assert

// Дописать везде проверки, а затем assert`ы и 'isfinite'
// Разобраться с github`ом
// Запихнуть копипаст из проверок на aref, bref, cref в массив структур с функцией, как предлагалось для стека.


int main(){

    double aref = NAN, bref = NAN, cref = NAN, firstsol = NAN, secondsol = NAN;

    #ifdef DEBUG
        double true_firstsol = NAN, true_secondsol = NAN;
        FILE *unitest = nullptr, *answers = nullptr;
        int answer_target = -2;

        answers = fopen("test_answers.txt", "w");

        if((unitest = fopen("tests.txt", "r")) == NULL){
            printf("[DEBUG][%s, %s, line: %d]: Failed to open the test file!\n", __FILE__, __func__, __LINE__);
            exit(-1);
        }

        while(!feof(unitest)){
            test_reader(unitest, &aref, &bref, &cref, &answer_target, &true_firstsol, &true_secondsol);
            solve_general_equation(aref, bref, cref, &firstsol, &secondsol);
            check_test(&true_firstsol, &true_secondsol, &firstsol, &secondsol, answer_target, answers);
        }


        fclose(unitest);
        fclose(answers);
    #else
        user_input(&aref, &bref, &cref);
        solve_general_equation(aref, bref, cref, &firstsol, &secondsol);
    #endif

    return 0;
}


/*
* Test answers:
* 2 <=> 2 solutions
* 1 <=> 1 solution
* 0 <=> no solutions
* -1 <=> infinitely many solutions
*/
