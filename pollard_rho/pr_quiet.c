
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <math.h>

int gcd(uint64_t a, uint64_t b) 
{
    uint64_t remainder;
    uint64_t save_a, save_b;
    uint64_t loop = 0;
    save_a = a;
    save_b = b;
    while (b != 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int main (int argc, char *argv[]) 
{
    uint64_t count, number = 10403, loop = 1;
    uint64_t x_fixed = 2, size = 2, x = 2, factor = 1;
    long double foo;
    if (argc>1) number = (uint64_t)strtoll(argv[1], (char **)NULL, 10);
    foo = rintl(log10l((long double) number));
    printf("log_10 of number is at least %4.4Lg\n", foo);
    while (factor == 1) {
        printf("loop %4"PRIu64"    ", loop);
        for (count = 1; (count <= size) && (factor <= 1); count++) {
            x = (x * x + 1) % number;
            factor = gcd(abs(x - x_fixed), number);
            /* printf("count = %"PRIu64"  x = %"PRIu64"  factor = %"PRIu64"\n", count, x, factor); */
        }
        printf("count = %9"PRIu64"    x = %22"PRIu64"    factor = %10"PRIu64"\n", count, x, factor);
        size = 2 * size;
        x_fixed = x;
        loop = loop + 1;
    }
    printf("A factor of %"PRIu64" is %"PRIu64"\n", number, factor);
    return EXIT_SUCCESS;
}

