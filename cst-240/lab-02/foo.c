#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int value;
    int factor;

    if (argc < 2) return 1;

    value = atoi(argv[1]);
    if (value < 2) return 2;

    for (factor=2; factor < value; factor++)
    {
        if (value % factor == 0) return 3;
    }

    return 0;
}


    
