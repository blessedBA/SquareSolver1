#include "FuncsForRealNum.h"
#include "UnitTest.h"
#include "Utils.h"
#include "SquareFuncs.h"

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>       /*Для использования типов данных с точной шириной
                            (например, int32_t - для 32-битного целого числа)*/
#include <limits.h>       /*Для использования макросов, определяющих пределы типов данных
                            (например, INT32_MAX - максимальное значение для 32-битного целого числа)*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>       /*Для использования функций работы со строками (например, strlen)*/


struct ConsoleFlag
{
    int status;
    char name[20];
};

struct ConsoleFlag2
{
    const char unit_test[7];
    const char  release[10];
    const char      help[7];
};


int getAnswer(const SquareParams parametrs);
void getInput(SquareParams* parametrs, bool* isEOF);
void releaseMode();
int getFlags(int argc, const char* argv[],
             ConsoleFlag list_flags[], size_t nElements);
// NOTE: посмотреть что такое NaN, как оно представляется (как представляется double/float),
// сколько существует NaN, как работают операции с NaN
// выражение (NaN == NaN) всегда возвращает false, поэтому для проверки числа на тип NaN
// используется функция isnan() из стандартной библиотеки math.h
// также любое выражение, содержащее в себе NaN, возвращает NaN.
// 2 типа NaN: qNaN(quiet NaN) и sNaN(signal NaN). Первый просто показывает где и что вернулось NaN
// а второй останавливает программу и показывает где он появился(был использован)
// лекции Северова ФРКТ



// TODO сделать арк парсер - глобал функцию, в которую принимается
// массив структур(каждая структура - флаг), argc и argv[] и аргумент флага и еще че то(путь какой то в хранилище)
// в этой функции поступившие флаги сверяются с флагами из структуры и при соответсвии выполняются
int main(const int argc, const char* argv[])// TODO: const
{
    // TODO сделать массив указателей на функции запуска версий программы
    // (переделать runAllTests чтоб стала без параметров)
    //
    ConsoleFlag list_flags[2] = { {0, "--release"},
                                 {0,    "--test"} };
    size_t nElements = sizeof(list_flags) / sizeof(list_flags[0]);
    //int i = getFlags(argc, argv, list_flags, nElements);
    ConsoleFlag2 flags = { .unit_test = "--test",
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
        int count_failed_tests = 0,
            count_passed_tests = 0,
            count_all_tests = 0;
        runAllTests(&count_failed_tests, &count_passed_tests);

        count_all_tests = count_failed_tests + count_passed_tests;
        printf("failed %d tests.\n"
               "passed %d/%d tests.\n",
                count_failed_tests,
                count_passed_tests,
                count_all_tests);
    }
    else if (strcmp(argv[1], flags.release) == false)
    {
        releaseMode();
        return 0;
    }
    else if (strcmp(argv[1], flags.help) == 0)
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

int getFlags(int argc, const char* argv[],
             ConsoleFlag list_flags[], size_t nElements)
{
    char do_flag[] = "";
    int remember_flag = 0;
    for (int i = 3; i <= argc; i++)
    {
        for (size_t j = 0; j < nElements; j++)
        {
            if (strcmp(argv[i], list_flags[j].name) == 0)
            {
                list_flags[j].status++;
                remember_flag = j;
            }
        }

    }
    switch (remember_flag)
    {
        case 0:
            releaseMode();
        // case 1:
        //     unitTestMode();
        default:
            assert ("FATAL ERROR: invalid flag\n");
    }

    return 0;
}


void releaseMode()
{
    SquareParams parametrs = {.x1 = NAN, .x2 = NAN};
    bool isEOF = false;

    printf("This is very cool calculator for square equations!!!\n\n");
    printf("Enter coefficients a, b, c: \n");

    getInput(&parametrs, &isEOF);
    parametrs.nRoots = findRoots(&parametrs);
    int ind = isEOF ? 1 : getAnswer(parametrs); // переделать логику isEOF
    if (ind == 1)
    {
        printf("Coefficients were not entered\n");
    }
}

void getInput(SquareParams* parametrs, bool* isEOF)
{
    while (!(getOneNumber(&(parametrs->koef_a))
          && getOneNumber(&(parametrs->koef_b))
          && getOneNumber(&(parametrs->koef_c))
          && !checkAfterNumbers(isEOF))) // обработка ввода на невалидность
    {
        printf("only numbers! Try again: \n");
        skipString();
    }
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
