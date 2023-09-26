#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "quadro_heads.hpp"

/// @brief main file with high-level representation of programm script.

// Вопросы:
// Компилятор не знает старых флагов – что делать ? -Выпилить их
// Что делать, если в побочной функции выяснилось что аргумент infinite? Остановить программу? Как? – assert

// Дописать везде проверки, а затем assert`ы и 'isfinite'
// Запихнуть копипаст из проверок на aref, bref, cref в массив структур с функцией, как предлагалось для стека.


/*
 1) funcs_quadro stroki 230-251, 89-98, 95-103, 193-200-> сделать в define с решёткой (#) (+)
 2) сделать debug_echo через ifdef ifndef в объявлении самого define`a, чтобы не пришлось при каждом вызове
    макроса писать ifdef endif (+)
 3) все define`ы называют только капсом (+)
 4) сделать "эволюцию" обратных вызовов: если где-то произошла хуйня (прислали nullptr), вовзращаем retunr`ом код ошибки и
    в предыдущей функции ( в той, что вызвала ту, что нашла ошибку ) обрабатываем код ошибки конкретным заданным образом.
    И так со всеми функциями вплоть до main`a. (+)
 5) Нагуглить альтернативы флагам которые не нашёл мак и исправить соответствующие warning`и. (+)

*/

int main(){

    double aref = NAN, bref = NAN, cref = NAN, firstsol = NAN, secondsol = NAN;

    #ifdef DEBUG
        double true_firstsol = NAN, true_secondsol = NAN;
        FILE *unitest = nullptr, *answers = nullptr;
        int answer_target = -2;

        answers = fopen("test_answers.txt", "w");

        if((unitest = fopen("tests.txt", "r")) == NULL){
            printf("[DEBUG][%s, %s, line: %d]: Failed to open the test file!\n", __FILE__, __func__, __LINE__);
            return -1;
        }

        while(!feof(unitest)){
            test_reader(unitest, &aref, &bref, &cref, &answer_target, &true_firstsol, &true_secondsol);
            if(solve_general_equation(aref, bref, cref, &firstsol, &secondsol)){
                ERROR_MESSAGE();
                return -1;
            }
            if(check_test(&true_firstsol, &true_secondsol, &firstsol, &secondsol, answer_target, answers)){
                printf("[Error] Test is not passed!\n");
                return -1;
            }
        }


        fclose(unitest);
        fclose(answers);
    #else
        if(user_input(&aref, &bref, &cref) != 0){
            printf("[Error] %s got nullptr instead of address!\n", __func__);
            return -1;
        }
        if(solve_general_equation(aref, bref, cref, &firstsol, &secondsol)){
            ERROR_MESSAGE();
            return -1;
        }
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
