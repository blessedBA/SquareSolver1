#include "SquareFuncs.h"
#include "UnitTest.h"
#include "Utils.h"


#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int oneTest(UnitTestSquareSolver* ref_parametrs)
{
    SquareParams parametrs = {
        .koef_a = ref_parametrs->koef_a,
        .koef_b = ref_parametrs->koef_b,
        .koef_c = ref_parametrs->koef_c};

    int flag = 0;
    NROOTS nRoots = findRoots(&parametrs); // передавать параметры MAIN THING FOR UNIT-TESTING
    if (isnan(ref_parametrs->x2_ref)) // TODO вывернутая логика, стоит сначала проверять
                                      // количество корней(nRoots), и улучшить вывод
                                      // например, сделать табличкой.
    {
        switch (checkAnswerLineEquation(ref_parametrs)) // TODO функция не нужна, подумать почему
        { // тут стоит свич потому что нам нужно проверить одно конкретное условие, а не все сразу
          // при использовании ветвлений мы в случае беск. решений и отсутствия решений "провалим"
          // тест два раза(тк для этих случаев проверка одинаковая: nRoots == nRoots_ref)
            case ONE_ROOT:
                if (nRoots == ref_parametrs->nRoots_ref
                    && compareDoubleNumbers(parametrs.x1, ref_parametrs->x1_ref))
                {
                    break;
                }
                ++flag;
                getDebugOutput(nRoots, ref_parametrs, parametrs);
                break;
            case ZERO_ROOT:
                if (nRoots == ref_parametrs->nRoots_ref)
                {
                    break;
                }
                ++flag;
                getDebugOutput(nRoots, ref_parametrs, parametrs);
                break;
            case INF_ROOTS:
                if (nRoots == ref_parametrs->nRoots_ref)
                {
                    break;
                }
                ++flag;
                getDebugOutput(nRoots, ref_parametrs, parametrs);
                break;
            default:
                ;

        }
    }
    if (!isnan(ref_parametrs->x2_ref) && (nRoots != ref_parametrs->nRoots_ref
     || !checkEqualityNumbers(parametrs.x1, parametrs.x2,
                              ref_parametrs->x1_ref, ref_parametrs->x2_ref)))
    {
        ++flag;
        getDebugOutput(nRoots, ref_parametrs, parametrs);
    }

    return flag;
}

int runAllTests()
{                                // koef_a, koef_b, koef_c, nRoots, x1_ref, x2_ref
    UnitTestSquareSolver tests[] = { {1,      2,      1,   ONE_ROOT,  -1,    NAN},
                                     {0,      0,      0,   INF_ROOTS, NAN,   NAN},
                                     {0,      0,      5,   ZERO_ROOT, NAN,   NAN}, };
    int count_failed_tests = 0;
    size_t nTests = sizeof(tests) / sizeof(tests[0]); //NOTE - аккуратно с sizeof, можно
    // TODO: rename                                 // посчитать размер не того обьекта
    for (size_t i = 0; i < nTests; i++)
    {
        count_failed_tests += oneTest(&tests[i]);
    }

    return count_failed_tests;
}

NROOTS checkAnswerLineEquation(const UnitTestSquareSolver* const ref_parametrs)
{
    if (isNull(ref_parametrs->koef_b))
    {
        return isNull(ref_parametrs->koef_c)
            ? INF_ROOTS
            : ZERO_ROOT;
    }
    return ONE_ROOT;
}

void getDebugOutput(
    const int nRoots,
    const UnitTestSquareSolver* const ref_parametrs,
    const SquareParams parametrs)
{
    assert(ref_parametrs != nullptr);
    assert(&parametrs != nullptr);

    printf("FAILED: your output: ");
    getTestAnswer(nRoots, parametrs.x1, parametrs.x2);
    printf("and expected: ");
    getTestAnswer(ref_parametrs->nRoots_ref, ref_parametrs->x1_ref, ref_parametrs->x2_ref);
    printf("\n");
}

void getTestAnswer(const int nRoots, const double x1, const double x2)
{
    switch (nRoots)
    {
        case INF_ROOTS:
            printf("Infinity solutions ");
            break;
        case ZERO_ROOT:
            printf("No solutions ");
            break;
        case ONE_ROOT:
            printf("%d solution: %.3lg ", nRoots,  x1);
            break;
        case TWO_ROOTS:
            printf("%d solutions: %.3lg and %.3lg ", nRoots, x1, x2);
            break;
        default:
            assert (0 && "ERROR: invalid count of solutions!!!");
    }
}

