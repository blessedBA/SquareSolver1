#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "SquareFuncs.h"

struct UnitTestSquareSolver
{
    double koef_a, koef_b, koef_c;
    int nRoots_ref;
    double x1_ref, x2_ref;
    int count_failed_tests;
};

int oneTest(UnitTestSquareSolver* ref_parametrs);
int runAllTests();
void getTestAnswer(const int nRoots, const double x1, const double x2);
void getDebugOutput(const int nRoots,const UnitTestSquareSolver* const ref_parametrs, const SquareParams parametrs);
NROOTS checkAnswerLineEquation(const UnitTestSquareSolver* const ref_parametrs);


#endif // UNIT_TEST_H
