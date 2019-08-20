#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *data = malloc(100 * sizeof(int));
    int *funny = (data + 50);
    free(funny); 
    printf("%d", *(data + 50));
    free(data);
}