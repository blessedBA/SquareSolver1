#include "FuncsForRealNum.h"
#include "SquareFuncs.h"
#include "UnitTest.h"
#include "Utils.h"


#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


int oneTest(UnitTestSquareSolver* ref_parameters, size_t number_of_test)
{
    assert(ref_parameters != nullptr);
    SquareParams parameters = {
        .koef_a = ref_parameters->koef_a,
        .koef_b = ref_parameters->koef_b,
        .koef_c = ref_parameters->koef_c,
        .x1 = NAN, .x2 = NAN };

    int isFailedTest = 0;
    NROOTS nRoots = findRoots(&parameters); // передавать параметры MAIN THING FOR UNIT-TESTING
    if (nRoots == ref_parameters->nRoots_ref)
    {
        switch (nRoots)
        {
            case INF_ROOTS:
                break;
            case ZERO_ROOT:
                break;
            case ONE_ROOT:
                if (compareDoubleNumbers(parameters.x1, ref_parameters->x1_ref))
                {
                    break;
                }
                isFailedTest++;
                printf("FAILED: solution is incorrect:\n"
                       "%zu test:  %lg instead of %lg\n", number_of_test,
                                                         parameters.x1,
                                                         ref_parameters->x1_ref);
                break;
            case TWO_ROOTS:
                if (checkEqualityNumbers(parameters.x1, parameters.x2,
                    ref_parameters->x1_ref, ref_parameters->x2_ref))
                {
                    break;
                }
                isFailedTest++;
                getDebugOutput(nRoots, ref_parameters, &parameters);
                break;
            default:
                printf("error: invalid count of solutions\n");
        }
    }
    else if (nRoots != ref_parameters->nRoots_ref)
    {
        isFailedTest++;
        printf("FAILED: invalid count of solutions:\n"
        "%zu test:  %d  instead of  %d\n", number_of_test,
                                           nRoots, ref_parameters->nRoots_ref);
    }

    return isFailedTest;
}

void runAllTests(int* count_failed_tests, int* count_passed_tests)
{
    UnitTestSquareSolver tests[] =
  // koef_a, koef_b, koef_c, nRoots, x1_ref, x2_ref
    { {1,      2,      1,   ONE_ROOT,  -1,    NAN},
      {0,      0,      0,   INF_ROOTS, NAN,   NAN},
      {0,      0,      5,   ZERO_ROOT, NAN,   NAN},
      {4,      3,     -1,   TWO_ROOTS, 0.25,  -1 },
      {1,      0,     -1,   TWO_ROOTS, -1,     1 },
      {0.000001, 200000, 300000, TWO_ROOTS, -2e11, -1.5} };

    size_t nTests = sizeof(tests) / sizeof(tests[0]); //NOTE - аккуратно с sizeof, можно
                                                      // посчитать размер не того обьекта
    for (size_t i = 0; i < nTests; i++)
    {
        *count_failed_tests += oneTest(&tests[i], i);
    }
    *count_passed_tests = int(nTests) - *count_failed_tests;

}

void getDebugOutput(
    const int nRoots,
    const UnitTestSquareSolver* const ref_parameters,
    const SquareParams* const parameters)
{
    assert(ref_parameters != nullptr);
    assert(parameters != nullptr);

    printf("FAILED: your output: ");
    getTestAnswer(nRoots, parameters->x1, parameters->x2);
    printf("and expected: ");
    getTestAnswer(ref_parameters->nRoots_ref, ref_parameters->x1_ref, ref_parameters->x2_ref);
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


