#include <stdio.h>
#include <math.h>
#include <inttypes.h>       /*Для использования типов данных с точной шириной
                            (например, int32_t - для 32-битного целого числа)*/
#include <limits.h>       /*Для использования макросов, определяющих пределы типов данных
                            (например, INT32_MAX - максимальное значение для 32-битного целого числа)*/
#include <string.h>       /*Для использования функций работы со строками (например, strlen)*/
//#include <TXLib.h>




int main() {
    char lets[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char main_symbol;
    int index_of_main_symbol = 0;
    printf("Enter a symbol: \n");
    scanf("%c", &main_symbol);
    for (char ch = 'A'; ch != main_symbol; ch++)
        index_of_main_symbol++;
    int index_of_main_symbol_2 = ++index_of_main_symbol;
    for (int i = 0; i < index_of_main_symbol_2; i++)
    {
        int m = i;
        for (int j = i; j < index_of_main_symbol; j++)
            printf(" ");
        for (int k = 0; k < i; k++)
            printf("%c", lets[k]);
        printf("%c", lets[i]);
        for (int l = --m; l >= 0; l--)
            printf("%c", lets[l]);
        for (int n = i; n < index_of_main_symbol; n++)
            printf(" ");
        printf("\n");
    }
    for (int i = index_of_main_symbol; i >= 0; i--)
    {
        int m = i;
        for (int j = i; j < index_of_main_symbol; j++)
            printf(" ");
        for (int k = 0; k < i; k++)
            printf("%c", lets[k]);
        printf("%c", lets[i]);
        for (int l = --m; l >= 0; l--)
            printf("%c", lets[l]);
        for (int n = i; n < index_of_main_symbol; n++)
            printf(" ");
        printf("\n");
    }
    return 0;
}


