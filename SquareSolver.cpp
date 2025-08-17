#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>       /*Для использования типов данных с точной шириной
                            (например, int32_t - для 32-битного целого числа)*/
#include <limits.h>       /*Для использования макросов, определяющих пределы типов данных
                            (например, INT32_MAX - максимальное значение для 32-битного целого числа)*/
#include <string.h>       /*Для использования функций работы со строками (например, strlen)*/
//#include <TXLib.h>

int Test_Type(double a, double b, double c);     // функция, проверяющая тип уравнения(норм если
                          // для функций у меня будет нотация Snake_Case???)


int main(void) {
    double a = 0,
           b = 0,
           c = 0,
           discr = 0,
           square_of_discr = 0,
           x1 = 0,
           x2 = 0;
    printf("Enter coefficients a, b, c: \n");
    scanf("%lf %lf %lf", &a, &b, &c);
    Test_Type(a, b, c);
    discr =  pow(b, 2) - 4 * a * c;
    square_of_discr = sqrt(discr);
    if (discr < 0)
        printf("решений нет!\n");
    else if (discr == 0)
    {
        x1 = x2 = (-b)/(2*a);
        printf("Решения этого уравнения: %.2lf и %.2lf\n", x1, x2);
    }
    else
    {
        x1 = (-b + square_of_discr) / (2 * a);
        x2 = (-b - square_of_discr)/ (2 * a);
        printf("Решения этого уравнения: %.2lf и %.2lf\n", x1, x2);
    }

    return 0;
}


int Test_Type(double a, double b, double c)
{
if (a == 0)
    {
        if (b != 0)
        {
            double x_line = 0;
            x_line = (-c) / b;
            printf("Ваше уравнение линейное, его решение: %.2lf \n", x_line);
            exit(0);
        }
        else
        {
            if (c == 0)
            {
                printf("Бесконечность не предел!!!\n");
                exit(0);
            }
            else
            {
                printf("эмм, решений нет\n");
                exit(0);
            }
        }
    }
    return 0;
}
