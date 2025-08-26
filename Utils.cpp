#include <stdio.h>
#include <string.h>


void skipString()
{
    int ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
