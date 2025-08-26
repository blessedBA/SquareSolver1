
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>       /*Для использования типов данных с точной шириной
                            (например, int32_t - для 32-битного целого числа)*/
#include <limits.h>       /*Для использования макросов, определяющих пределы типов данных
                            (например, INT32_MAX - максимальное значение для 32-битного целого числа)*/
#include <string.h>       /*Для использования функций работы со строками (например, strlen)*/
#include <assert.h>
#include <ctype.h>

#include "UnitTest.h"
#include "SquareFuncs.h"
#include "Utils.h"

struct ConsoleFlag
{
    const char unit_test[7];
    const char release[10];
    const char help[7];
};
int getAnswer(const SquareParams parametrs);
void inputTest(SquareParams* parametrs, bool* isEOF);
void releaseMode();
// NOTE: посмотреть что такое NaN, как оно представляется (как представляется double/float),
// сколько существует NaN, как работают операции с NaN
// выражение (NaN == NaN) всегда возвращает false, поэтому для проверки числа на тип NaN
// используется функция isnan() из стандартной библиотеки math.h
// также любое выражение, содержащее в себе NaN, возвращает NaN.
// 2 типа NaN: qNaN(quiet NaN) и sNaN(signal NaN). Первый просто показывает где и что вернулось NaN
// а второй останавливает программу и показывает где он появился(был использован)
// лекции Северова ФРКТ

int main(const int argc, const char* argv[])// TODO: const
{
    ConsoleFlag flags = { .unit_test = "--test",
                          .release = "--release",
                          .help = "--help"       };
    if (argc == 1)
    {
        printf("Unknown command, please try again\n"
               "(enter ./a.out --help for help)\n");
        return 0;
    }
    else if (strcmp(argv[1], flags.unit_test) == false) // TODO: strncmp
    {
        int count_failed_tests = runAllTests();
        printf("failed %d tests\n", count_failed_tests); // TODO: useless parameter
    }
    else if (strcmp(argv[1], flags.release) == false)
    {
        releaseMode();
        return 0;
    }
    else if (strcmp(argv[1], flags.help) == false)
    {
        printf("Enter ./a.out --release for main version\n"
               "Enter ./a.out --test for Unit-testing");
    }
    else
    {
        printf("Unknown command, please try again\n"
               "(enter ./a.out --help for help)\n");
        return 0;
    }


    return 0;
}







int getAnswer(const SquareParams parametrs)
{
    switch (parametrs.nRoots)
    {
        case INF_ROOTS:
            printf("Infinity is not limit!!!\n");
            break;
        case ZERO_ROOT:
            printf("Your equation have no solutions\n");
            break;
        case ONE_ROOT:
            printf("Your equation have own solution: %.3lg\n", parametrs.x1);
            break;
        case TWO_ROOTS:
            printf("Your equation have solutions %.3lg and %.3lg\n", parametrs.x1, parametrs.x2);
            break;
        default:
            assert(0 && "ERROR: Count of solutions is invalid");
            break;
    }
    return 0;
}

void inputTest(SquareParams* parametrs, bool* isEOF)
{
    while (!(checkOneNumber(&(parametrs->koef_a))
          && checkOneNumber(&(parametrs->koef_b))
          && checkOneNumber(&(parametrs->koef_c))
          && !checkAfterNumbers(isEOF))) // обработка ввода на невалидность
    {
        printf("only numbers! Try again: \n");
        skipString();
    }
}

void releaseMode()
{
    SquareParams parametrs = {};
    bool isEOF = false;
    printf("This is very cool calculator for square equations!!!\n\n");
    printf("Enter coefficients a, b, c: \n");
    inputTest(&parametrs, &isEOF);
    parametrs.nRoots = findRoots(&parametrs);
    int ind = isEOF ? 1 : getAnswer(parametrs); // переделать логику isEOF
    if (ind == 1)
    {
        printf("Coefficients were not entered\n");
    }
}
