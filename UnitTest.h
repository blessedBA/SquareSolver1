#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "SquareFuncs.h"

#include <stdlib.h>

struct UnitTestSquareSolver
{
    double koef_a, koef_b, koef_c;
    int nRoots_ref;
    double x1_ref, x2_ref;
};

int oneTest(UnitTestSquareSolver* ref_parametrs, size_t number_of_test);
void runAllTests(int* count_failed_tests, int* count_passed_tests);
void getTestAnswer(int nRoots, double x1, double x2);
void getDebugOutput( int nRoots,const UnitTestSquareSolver*  ref_parametrs,
                                const SquareParams*          parametrs     );


#endif // UNIT_TEST_H



// архив функций
/*
NROOTS checkAnswerLineEquation(const UnitTestSquareSolver*   ref_parametrs );

NROOTS checkAnswerLineEquation(const UnitTestSquareSolver* const ref_parametrs)
{ // TODO убрать функцию, если она не нужна
    if (isNull(ref_parametrs->koef_b))
    {
        return isNull(ref_parametrs->koef_c)
            ? INF_ROOTS
            : ZERO_ROOT;
    }
    return ONE_ROOT;
}*/
