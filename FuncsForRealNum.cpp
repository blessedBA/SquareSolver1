#include "FuncsForRealNum.h"
#include "Utils.h"

#include <math.h>


const double EPSILON = 1e-6;


int isNull(const double num)
{
    return fabs(num) < EPSILON;
}

bool compareDoubleNumbers(const double num1, const double num2)
{
    return fabs(num1 - num2) < EPSILON;
}

bool checkEqualityNumbers(const double num1, const double num2,
                          const double num1_ref, const double num2_ref)
{
    return ((compareDoubleNumbers(num1, num1_ref) && compareDoubleNumbers(num2, num2_ref))
         || (compareDoubleNumbers(num1, num2_ref) && compareDoubleNumbers(num2, num1_ref)));
}

