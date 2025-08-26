#include "FuncsForRealNum.h"
#include "SquareFuncs.h"
#include "UnitTest.h"
#include "Utils.h"


#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int oneTest(UnitTestSquareSolver* ref_parametrs, size_t number_of_test)
{
    SquareParams parametrs = {
        .koef_a = ref_parametrs->koef_a,
        .koef_b = ref_parametrs->koef_b,
        .koef_c = ref_parametrs->koef_c,
        .x1 = NAN, .x2 = NAN};
    
    int flag = 0;
    NROOTS nRoots = findRoots(&parametrs); // передавать параметры MAIN THING FOR UNIT-TESTING
    if (nRoots == ref_parametrs->nRoots_ref)
    {
        switch (nRoots)
        {
            case INF_ROOTS:
                break;
            case ZERO_ROOT:
                break;
            case ONE_ROOT:
                if (compareDoubleNumbers(parametrs.x1, ref_parametrs->x1_ref))
                {
                    break;
                }
                flag++;
                printf("FAILED: solution is incorrect:\n"
                       "%zu test:  %lg instead of %lg\n", number_of_test,
                                                         parametrs.x1,
                                                         ref_parametrs->x1_ref);
                break;
            case TWO_ROOTS:
                if (checkEqualityNumbers(parametrs.x1, parametrs.x2,
                    ref_parametrs->x1_ref, ref_parametrs->x2_ref))
                {
                    break;
                }
                flag++;
                getDebugOutput(nRoots, ref_parametrs, parametrs);
                break;
            default:
                printf("error: invalid count of solutions\n");
        }
        // if (isnan(ref_parametrs->x2_ref) &&
        //     !compareDoubleNumbers(parametrs.x1, ref_parametrs->x1_ref))
        // {
        //     flag++;
        //     getDebugOutput(nRoots, ref_parametrs, parametrs);
        // }
        // else if (!checkEqualityNumbers(parametrs.x1, parametrs.x2,
        //           ref_parametrs->x1_ref, ref_parametrs->x2_ref))
        // {
        //     flag++;
        //     getDebugOutput(nRoots, ref_parametrs, parametrs);
        // }
    }
    else if (nRoots != ref_parametrs->nRoots_ref)
    {
        flag++;
        printf("FAILED: invalid count of solutions:\n"
        "%zu test:  %d  instead of  %d\n", number_of_test,
                                           nRoots, ref_parametrs->nRoots_ref);
    }

    return flag;
}

void runAllTests(int* count_failed_tests, int* count_passed_tests)
{                                // koef_a, koef_b, koef_c, nRoots, x1_ref, x2_ref
    UnitTestSquareSolver tests[] =
  // koef_a, koef_b, koef_c, nRoots, x1_ref, x2_ref
    { {1,      2,      1,   ONE_ROOT,  -1,    NAN},
      {0,      0,      0,   INF_ROOTS, NAN,   NAN},
      {0,      0,      5,   ZERO_ROOT, NAN,   NAN},
      {4,      3,     -1,   TWO_ROOTS, 0.25,  -1 },
      {1,      0,     -1,   TWO_ROOTS, -1,     1 } };

    size_t nTests = sizeof(tests) / sizeof(tests[0]); //NOTE - аккуратно с sizeof, можно
                                                      // посчитать размер не того обьекта
    for (size_t i = 0; i < nTests; i++)
    {
        *count_failed_tests += oneTest(&tests[i], i);
    }
    *count_passed_tests = int(nTests) - *count_failed_tests;

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
    const SquareParams parametrs) //TODO передавай структуру через указатель(везде в коде)
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


