
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>       /*Для использования типов данных с точной шириной
                            (например, int32_t - для 32-битного целого числа)*/
#include <limits.h>       /*Для использования макросов, определяющих пределы типов данных
                            (например, INT32_MAX - максимальное значение для 32-битного целого числа)*/
#include <string.h>       /*Для использования функций работы со строками (например, strlen)*/

int test_type(double koef_a, double koef_b, double koef_c);
void korni(int koef_a, int koef_b, int koef_c);

int main(void) {
    double koef_a = 0,
           koef_b = 0,
           koef_c = 0;
    printf("Это жесть какой крутой решатель квадратных уравнений!!!\n\n");

    printf("Enter coefficients a, b, c: \n");
    scanf("%lf %lf %lf", &koef_a, &koef_b, &koef_c);

    test_type(koef_a, koef_b, koef_c);
    korni(koef_a, koef_b, koef_c);
    return 0;
}


int test_type(double koef_a, double koef_b, double koef_c)
{
    double pogresh = 0.0001;
    if (fabs(koef_a) < pogresh)
        {
            if (koef_b != 0)
            {
                double x_line = 0;
                x_line = (-koef_c) / koef_b;
                printf("Ваше уравнение линейное, его решение: %.2lf \n", x_line);
                exit(0);
            }
            else
            {
                if (koef_c == 0)
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

void korni(int koef_a, int koef_b, int koef_c)
{
    double discr = 0,
           x1 = 0,
           x2 = 0;
    float square_of_discr = 0;
    discr =  pow(koef_b, 2) - 4 * koef_a * koef_c;
    square_of_discr = sqrt(discr);
    if (discr < 0)
        printf("решений нет!\n");
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
}
