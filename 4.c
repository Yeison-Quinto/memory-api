#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p = malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        *(p + i) = i + 1;
        printf("%d\n", *(p + i));
    }
}