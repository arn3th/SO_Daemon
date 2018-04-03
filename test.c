#include <stdio.h>

void f2(int * zmienna)
{
    (*zmienna)++;
    printf("f2: %d\n", *zmienna);
    
}
void f1(int *zmienna)
{
    (*zmienna)++;
    printf("f1: %d\n", *zmienna);
    f2(&(*zmienna));
}
int main(int argc, char *argv[])
{

    int zmienna = 1;
    /*
    for(int i=0; i<argc; i++)
    {
        printf("%d. argv[%d] = %s\n", i, i, argv[i]);
    }
    printf("%c", argv[2][2]); */

    f1(&zmienna);
    return 0;
}