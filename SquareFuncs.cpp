#include "FuncsForRealNum.h"
#include "SquareFuncs.h"
#include "Utils.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static NROOTS findSquareRoots(SquareParams* parameters);
static NROOTS findLineRoot(SquareParams* parameters);

NROOTS findRoots(SquareParams* parameters)
{
    assert(parameters != nullptr);

    if (isNull(parameters->koef_a))
    {
        return findLineRoot(parameters);
    }

    return findSquareRoots(parameters);
}

NROOTS findSquareRoots(SquareParams* parameters)
{
    assert(parameters != nullptr);
    double discriminant = (parameters->koef_b * parameters->koef_b) -
                      (4 * parameters->koef_a * parameters->koef_c);
    if (isNull(discriminant))
    {
        parameters->x1 = (-parameters->koef_b) / (2 * parameters->koef_a);
        return ONE_ROOT;
    }

    if (discriminant < 0)
    {
        return ZERO_ROOT;
    }

    double square_of_discriminant = sqrt(discriminant);
    parameters->x1 = (-parameters->koef_b + square_of_discriminant) / (2 * parameters->koef_a);
    parameters->x2 = (-parameters->koef_b - square_of_discriminant) / (2 * parameters->koef_a);

    return TWO_ROOTS;
}

NROOTS findLineRoot(SquareParams* parameters)
{
    assert(parameters != nullptr);

    if (isNull(parameters->koef_b))
    {
        return isNull(parameters->koef_c) //
            ? INF_ROOTS                  //    Kaspersky edition
            : ZERO_ROOT;                 //
    }

    parameters->x1 = (-parameters->koef_c) / parameters->koef_b;

    return ONE_ROOT;
}

bool getOneNumber(double* number)
{
    return scanf("%lg", number);
}

bool checkAfterNumbers(bool* isEOF)
{
    int ch = 0;
    while ((ch = getchar()) == ' ') // skip useless spaces in input
        ;
    *isEOF = (ch == EOF);

    return ch != '\n' && !*isEOF;
}
