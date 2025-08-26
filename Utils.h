#ifndef UTILS_H
#define UTILS_H

//TODO: константы в хедере не нужны тк здесь переменные не используются
// лучше переименовать на utils, а функции, обрабатывающие вещ. числа - в отдельный хедер/библиотеку

void skipString();
int isNull(const double num);
bool compareDoubleNumbers(const double num1, const double num2);
bool checkEqualityNumbers(const double num1, const double num2,
                          const double num1_ref, const double num2_ref);

#endif // UTILS_H
