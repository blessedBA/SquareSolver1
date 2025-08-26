#ifndef SQUARE_SOLVER_FUNCS_H
#define SQUARE_SOLVER_FUNCS_H

enum NROOTS // TODO:
{
    INF_ROOTS = -1,
    ZERO_ROOT =  0,
    ONE_ROOT  =  1,
    TWO_ROOTS =  2,
};

struct SquareParams
{
    double koef_a, koef_b, koef_c;
    double x1, x2;
    NROOTS nRoots; // TODO: enum type
};

NROOTS findRoots(SquareParams* parametrs);  // check type of equation
NROOTS findSquareRoots(SquareParams* parametrs); // TODO пометить static и перенести в cpp
NROOTS findLineRoots(SquareParams* parametrs);
bool getOneNumber(double* number);
bool checkAfterNumbers(bool* isEOF);

#endif // SQUARE_SOLVER_FUNCS_H
