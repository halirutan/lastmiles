
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    long double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280L;

    printf("the sizeof(pi) is %i bytes\n", sizeof(long double) );
    printf("pi could be %42.38Le\n", pi);


    long double tenth = 0.1L;


    long double sum = 0.0L;

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum + tenth;
    printf("sum = %42.38Le\n", sum);

    sum = sum - 1.0L;

    printf("final sum is %42.38Le\n", sum);

    return ( EXIT_SUCCESS );

}

