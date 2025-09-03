#include "ArgParser.h"
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
#include <stdlib.h> /*Для использования функций работы со строками (например, strlen)*/

int startProgramm(const FlagStorage* storage);
void releaseMode();
void unitTestMode();
void getInput(SquareParams* parametrs, bool* isEOF);
int getAnswer(const SquareParams parametrs);
//{
// NOTE: посмотреть что такое NaN, как оно представляется (как представляется double/float),
// сколько существует NaN, как работают операции с NaN
// выражение (NaN == NaN) всегда возвращает false, поэтому для проверки числа на тип NaN
// используется функция isnan() из стандартной библиотеки math.h
// также любое выражение, содержащее в себе NaN, возвращает NaN.
// 2 типа NaN: qNaN(quiet NaN) и sNaN(signal NaN). Первый просто показывает где и что вернулось NaN
// а второй останавливает программу и показывает где он появился(был использован)
// TODO посмотреть лекции Северова ФРКТ про NaN-ы
// TODO поделить проект на папки - в одних хедера, в других сппшники
// TODO разобраться с мейкфайлом
// TODO исправить 6ой тест - неправильное сравнение двух чисел
//}
int main(const int argc, const char* argv[])
{
    printf("МЯУ\n\n");
    FlagStorage storage = { .inputFileName = nullptr,
                            .outputFileName = nullptr };

    const ConsoleFlag list_flags[4] =
        { {"--release", "-r", setRelease      , false},
          {  "--test",  "-t", setUnitTests    , false},
          {"--input",   "-i", inputFileEnable , true },
          {"--output",  "-o", outputFileEnable, true } };

    size_t count_flags  = sizeof(list_flags) / sizeof(list_flags[0]);
    getFlags(argc, argv, list_flags, count_flags, &storage);
    startProgramm(&storage);

    return 0;
}

int startProgramm(const FlagStorage* storage)
{
    assert(storage != nullptr);
    bool test_valid = testValid(storage);
    if (!test_valid)
    {
        printf("invalid command!!!\n");
        return 0;
    }
    if (storage->inputFileName != nullptr)
    {
        FILE* ptr_to_input_file = fopen(storage->inputFileName, "r");
        printf("%s\n", storage->inputFileName);
        fclose(ptr_to_input_file);
        //releaseModeInFile();
    }

    if (storage->outputFileName != nullptr)
    {
        FILE* ptr_to_output_file = fopen(storage->outputFileName, "w");
        printf("%s\n", storage->outputFileName);
        fclose(ptr_to_output_file);
        //releaseModeOutFile();
    }

    if (storage->releaseEnabled)
    {
        releaseMode();
        return 0;
    }

    if (storage->testsEnabled)
    {
        unitTestMode();
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
    int ind = isEOF ? 1 : getAnswer(parametrs);
    if (ind == 1)
    {
        printf("Coefficients were not entered\n");
    }
}

void unitTestMode()
{
    int count_failed_tests = 0,
        count_passed_tests = 0,
        count_all_tests    = 0;
    runAllTests(&count_failed_tests, &count_passed_tests);
    count_all_tests = count_failed_tests + count_passed_tests;
    printf("failed %d tests.\n", count_failed_tests);
    printf("passed %d/%d tests.\n", count_passed_tests, count_all_tests);
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
            printf("\n\nGITHUB COMMIT");
            break;
        case ZERO_ROOT:
            printf("Your equation have no solutions\n");
            printf("\n\nGITHUB COMMIT");
            break;
        case ONE_ROOT:
            printf("Your equation have own solution: %.3lg\n", parametrs.x1);
            printf("\n\nGITHUB COMMIT");
            break;
        case TWO_ROOTS:
            printf("Your equation have solutions %.3lg and %.3lg\n", parametrs.x1, parametrs.x2);
            printf("\n\nGITHUB COMMIT");
            break;
        default:
            assert(0 && "ERROR: Count of solutions is invalid");
            break;
    }
    return 0;
}
