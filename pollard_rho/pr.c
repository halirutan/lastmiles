
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

/*
 note that a mpfr code returns 123451 thus : 

count =    1  x_m = 5.000000  factor_m = 1.000000
count =    2  x_m = 26.000000  factor_m = 1.000000
count =    1  x_m = 677.000000  factor_m = 1.000000
count =    2  x_m = 87977.000000  factor_m = 1.000000
count =    3  x_m = 68634.000000  factor_m = 1.000000
count =    4  x_m = 106150.000000  factor_m = 1.000000
count =    1  x_m = 79378.000000  factor_m = 1.000000
count =    2  x_m = 51296.000000  factor_m = 1.000000
count =    3  x_m = 45003.000000  factor_m = -1.000000
count =    4  x_m = 56355.000000  factor_m = -1.000000
count =    5  x_m = 109051.000000  factor_m = 1.000000
count =    6  x_m = 85772.000000  factor_m = -1.000000
count =    7  x_m = 20542.000000  factor_m = 41.000000
*/
int gcd(uint64_t a, uint64_t b) 
{
    uint64_t remainder;
    uint64_t save_a, save_b;
    uint64_t loop = 0;
    save_a = a;
    save_b = b;
        printf("----   loop %"PRIu64"   ----\n", loop);
    printf("\n------\nEntered into gcd( a = %"PRIu64", b = %"PRIu64")\n", a, b);
    while (b != 0) {
        printf("gcd loop %"PRIu64" :  a = %"PRIu64"  b = %"PRIu64"  and a %% b", loop++);
        remainder = a % b;
        printf(" remainder = %"PRIu64"\n", remainder);
        a = b;
        b = remainder;
    }
    printf ("gcd( %"PRIu64", %"PRIu64" ) returns %"PRIu64"\n\n------\n", save_a, save_b, a);

    return a;
}

int main (int argc, char *argv[]) 
{
    uint64_t count, number = 10403, loop = 1;
    uint64_t x_fixed = 2, size = 2, x = 2, factor = 1;
    if (argc>1) number = (uint64_t)strtoll(argv[1], (char **)NULL, 10);
    while (factor == 1) {
        printf("----   loop %"PRIu64"   ----\n", loop);
        printf("\nentering for loop with size = %"PRIu64"\n", size);
        for (count = 1; (count <= size) && (factor <= 1); count++) {
            printf("x = %"PRIu64"\n", x);
            x = (x * x + 1) % number;
            printf("x = (x * x + 1) %% number is now x = %"PRIu64"\n", x);
            printf("x_fixed = %"PRIu64"\n", x_fixed);
            printf("abs(x - x_fixed) = %"PRIu64"\n", abs(x - x_fixed));
            factor = gcd(abs(x - x_fixed), number);
            printf("count = %"PRIu64"  x = %"PRIu64"  factor = %"PRIu64"\n", count, x, factor);
        }
        size = 2 * size;
        x_fixed = x;
        loop = loop + 1;
    }
    printf("A factor of %"PRIu64" is %"PRIu64"\n", number, factor);
    return EXIT_SUCCESS;
}

