#include "SquareFuncs.h"

#include "Utils.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NROOTS findRoots(SquareParams* parametrs)
{
    assert(parametrs != nullptr);

    if (isNull(parametrs->koef_a))
    {
        return findLineRoots(parametrs);
    }

    return findSquareRoots(parametrs);
}

NROOTS findSquareRoots(SquareParams* parametrs)
{
    assert(&parametrs->x1 != NULL);
    assert(&parametrs->x2 != NULL);
    assert(&parametrs->x1 != &parametrs->x2);

    double discriminant = (parametrs->koef_b * parametrs->koef_b) -
                      (4 * parametrs->koef_a * parametrs->koef_c);
    if (isNull(discriminant))
    {
        parametrs->x1 = (-parametrs->koef_b) / (2 * parametrs->koef_a);
        return ONE_ROOT;
    }

    if (discriminant < 0)
    {
        return ZERO_ROOT;
    }

    double square_of_discriminant = sqrt(discriminant);
    parametrs->x1 = (-parametrs->koef_b + square_of_discriminant) / (2 * parametrs->koef_a);
    parametrs->x2 = (-parametrs->koef_b - square_of_discriminant) / (2 * parametrs->koef_a);

    return TWO_ROOTS;
}

NROOTS findLineRoots(SquareParams* parametrs)
{
    assert(&parametrs->x1 != NULL);

    if (isNull(parametrs->koef_b))
    {
        return isNull(parametrs->koef_c) //
            ? INF_ROOTS                  //    Kaspersky edition
            : ZERO_ROOT;                 //
    }

    parametrs->x1 = (-parametrs->koef_c) / parametrs->koef_b;

    return ONE_ROOT;
}

bool checkOneNumber(double* number)
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
