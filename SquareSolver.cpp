
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>       /*Для использования типов данных с точной шириной
                            (например, int32_t - для 32-битного целого числа)*/
#include <limits.h>       /*Для использования макросов, определяющих пределы типов данных
                            (например, INT32_MAX - максимальное значение для 32-битного целого числа)*/
#include <string.h>       /*Для использования функций работы со строками (например, strlen)*/
enum NROOTS
{
    zero_root,
   one_root,
   two_roots
};
const int INF = -1;
int findRoots(double *, double *, double, double, double);  // проверяет тип уравнения
// void korni(int, int, int); // выводит корни уравнения, в случае если оно
                                                // квадратное
int is_null(double);        // проверка, является ли вещественное число нулём
int formulas_sq_vers(double*, double*,
                     double, double, double); // формулы для "квадратного" случая

void skip_string(void);     // игнор символов до конца строки

void get_answer(int, double, double); // выводит ответ
int find_line_roots(double *, double, double);
// NOTE: посмотреть что такое NaN, как оно представляется (как представляется double/float),
// сколько существует NaN, как работают операции с NaN


int main(void) {


    double koef_a = 0,
           koef_b = 0,
           koef_c = 0,
           x1 = 0,
           x2 = 0;
    int nRoots = 0;
    printf("Это жесть какой крутой решатель квадратных уравнений!!!\n\n");

    printf("Enter coefficients a, b, c: \n");
    // TODO: обработка ввода на невалидность
    while (scanf("%lf %lf %lf", &koef_a, &koef_b, &koef_c) != 3) // обработка ввода на невалидность
    {
        printf("only numbers! Try again: \n");
        skip_string();
         // TODO вынести в отдельную функцию //
        // TODO обьяснить что означает getchar(с точки зрения типа и значения)
        /* гетчар считывает один символ с потока ввода и возвращает целочисленное
        значение - ASCII код считанного символа */
    }
    nRoots = findRoots(&x1, &x2, koef_a, koef_b, koef_c); // TODO: findRoots is better
    get_answer(nRoots, x1, x2);
    return 0;
}

int is_null(double num)
{
    const float EPSILON = 0.0001f;
    return fabs(num - EPSILON) < 0.0001;
}

// TODO: rename findRoots
int findRoots(double * x1, double * x2, double koef_a, double koef_b, double koef_c)
{  // assert (x1 && x2);
// TODO: assert ()
    // TODO: вынести в функцию сравнение с нулём
    int nRoots = 0;
    if (is_null(koef_a))
    {
        return find_line_roots(x1, koef_b, koef_c);
    }

    else
    {
        nRoots = formulas_sq_vers(x1, x2, koef_a, koef_b, koef_c);
        return nRoots;
         // TODO: лишнее

    }
    return 0;
}

/* void korni(int koef_a, int koef_b, int koef_c)
{
    double discr = 0,
           x1 = 0,
           x2 = 0;
    float square_of_discr = 0;
    discr =  pow(koef_b, 2) - 4 * koef_a * koef_c;
    square_of_discr = sqrt(discr);
    if (discr < 0)
        printf("Действительных решений нет!\n");
    else if (discr == 0)
    {
        x1 = x2 = (-koef_b) / (2 * koef_a);
        printf("Решения этого уравнения: %.2lf и %.2lf\n", x1, x2);
    }
    else
    {
        x1 = (-koef_b + square_of_discr) / (2 * koef_a);
        x2 = (-koef_b - square_of_discr)/ (2 * koef_a);
        printf("Решения этого уравнения: %.2lf и %.2lf\n", x1, x2);
    }
} */


int formulas_sq_vers(double * x1, double * x2,
                  double koef_a, double koef_b, double koef_c)
{
    double discr = (koef_b * koef_b)  - (4 * koef_a * koef_c);
    if (discr > 0)
    {
        double square_of_discr = sqrt(discr);
        *x1 = (-koef_b + square_of_discr) / (2 * koef_a);
        *x2 = (-koef_b - square_of_discr)/ (2 * koef_a);
        return two_roots;
    }
    else if (is_null(discr))
    {
        *x1 = (-koef_b) / (2 * koef_a);
        return one_root;
    }
    else
    {
        return zero_root;
    }
}
void skip_string(void)
{
    char ch = 0;
    while ((ch = char(getchar())) != '\n' && ch != EOF); // TODO: add check EOF
}

void get_answer(int nRoots, double x1, double x2)
{
    switch (nRoots)
    {
        case -1:
            printf("Бесконечность не предел!!!\n");
            break;
        case 0:
            printf("Решений нет");
            break;
        case 1:
            printf("Ваше уравнение имеет единственный корень: %.2lf\n", x1);
            break;
        case 2:
            printf("Ваше уравнение имеет корни %.2lf и %.2lf\n", x1, x2);
        default:
            printf("ошибка\n");
            exit(0);

    }
}

int find_line_roots(double *x1, double koef_b, double koef_c)
{
    {
            if (!is_null(koef_b))
            {
                *x1 = (-koef_c) / koef_b;
                return 1;
            }
            else
            {
                if (is_null(koef_c))
                {
                    return INF; // TODO: relocate to another func
                     // TODO: remove
                }
                else
                    return 0;

            }
        }
}

