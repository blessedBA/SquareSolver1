
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>       /*Для использования типов данных с точной шириной
                            (например, int32_t - для 32-битного целого числа)*/
#include <limits.h>       /*Для использования макросов, определяющих пределы типов данных
                            (например, INT32_MAX - максимальное значение для 32-битного целого числа)*/
#include <string.h>       /*Для использования функций работы со строками (например, strlen)*/
#include <assert.h>

enum NROOTS
{
    INF_ROOTS = -1,
    ZERO_ROOT =  0,
    ONE_ROOT  =  1,
    TWO_ROOTS =  2,
};

void skipString();     // игнор символов до конца строки
int isNull(double num);    // проверка, является ли вещественное число нулём
int findRoots(double koef_a, double koef_b, double koef_c, double* x1, double* x2);  // return count of solutions and
int formulasSquareVersion(double koef_a, double koef_b, double koef_c, double* x1, double* x2); // formulas for square case
int findLineRoots(double koef_b, double koef_c, double *x1); // return count of solutions and find them(lineal case)
void getAnswer(int nRoots, double x1, double x2); // выводит ответ
void inputTest(double* koef_a, double* koef_b, double* koef_c);



// NOTE: посмотреть что такое NaN, как оно представляется (как представляется double/float),
// сколько существует NaN, как работают операции с NaN


int main() {

    double koef_a = 0,
           koef_b = 0,
           koef_c = 0;
    double x1 = 0,
           x2 = 0;
    int nRoots = 0;
    printf("This is very cool calculator for square equations!!!\n\n");

    printf("Enter coefficients a, b, c: \n");
    inputTest(&koef_a, &koef_b, &koef_c);

    nRoots = findRoots(koef_a, koef_b, koef_c, &x1, &x2);
    getAnswer(nRoots, x1, x2);

    return 0;
}

void skipString()
{
    int ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int isNull(double num)
{
    const double EPSILON = 0.0000001;
    return fabs(num) < EPSILON;
}

int findRoots(double koef_a, double koef_b, double koef_c, double * x1, double * x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (isNull(koef_a))
    {
        return findLineRoots(koef_b, koef_c, x1);
    }

    return formulasSquareVersion(koef_a, koef_b, koef_c, x1, x2);
}

int formulasSquareVersion(double koef_a, double koef_b, double koef_c, double* x1, double* x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    double discr = (koef_b * koef_b)  - (4 * koef_a * koef_c);
    if (isNull(discr))
    {
        *x1 = (-koef_b) / (2 * koef_a);
        return ONE_ROOT;
    }

    if (discr < 0)
    {
        return ZERO_ROOT;
    }

    double square_of_discr = sqrt(discr);
    *x1 = (-koef_b + square_of_discr) / (2 * koef_a);
    *x2 = (-koef_b - square_of_discr)/ (2 * koef_a);

    return TWO_ROOTS;
}

int findLineRoots(double koef_b, double koef_c, double *x1)
{
    assert(x1 != NULL);

    if (isNull(koef_b))
    {
        return isNull(koef_c)
            ? INF_ROOTS
            : ZERO_ROOT;
    }

    *x1 = (-koef_c) / koef_b;

    return ONE_ROOT;
}

void getAnswer(int nRoots, double x1, double x2)
{
    switch (nRoots)
    {
        case INF_ROOTS:
            printf("Infinity is not limit!!!\n");
            break;
        case ZERO_ROOT:
            printf("Your equation have no solutions\n");
            break;
        case ONE_ROOT:
            printf("Your equation have own solution: %.3lg\n", x1);
            break;
        case TWO_ROOTS:
            printf("Your equation have solutions %.3lg and %.3lg\n", x1, x2);
            break;
        default:
            assert(0 && "ERROR: Count of solutions is invalid");
            break;
    }
}

void inputTest(double* koef_a, double* koef_b, double* koef_c)
{
    while (scanf("%lg %lg %lg", koef_a, koef_b, koef_c) != 3) // обработка ввода на невалидность
    {
        printf("only numbers! Try again: \n");
        skipString();
    }
}

