#include <stdio.h>
#include <math.h>
#include <inttypes.h>       /*Для использования типов данных с точной шириной
                            (например, int32_t - для 32-битного целого числа)*/
#include <limits.h>       /*Для использования макросов, определяющих пределы типов данных
                            (например, INT32_MAX - максимальное значение для 32-битного целого числа)*/
#include <string.h>       /*Для использования функций работы со строками (например, strlen)*/
//#include <TXLib.h>




int main() {
    double a, b, c, Discriminant, x1, x2;
    int degree_indication; //старший показатель степени
    printf("Введите квадратное уравнение, корни которого вы хотите получить,\n"
            "в виде ax^2+bx+c = 0, где а,b,c - действительные числа!\n");
    scanf("%lfx^%d%lfx%lf", &a, &degree_indication, &b, &c);
    printf("%lf", a);
    if (degree_indication != 2) {
        printf("Это не квадратное уравнение!!!\n");
        return 0;
    }
    Discriminant =  pow(b, 2) - 4*a*c;
    if (Discriminant < 0)
        printf("решений нет!\n");
    else if (Discriminant == 0) {
        x1 = x2 = (-b)/(2*a);
        printf("Решения этого уравнения: %.2lf и %.2lf\n", x1, x2);
    }
    else {
        x1 = (-b + sqrt(Discriminant))/(2*a);
        x2 = (-b - sqrt(Discriminant))/(2*a);
        printf("Решения этого уравнения: %.2lf и %.2lf\n", x1, x2);
    }







    return 0;
}
