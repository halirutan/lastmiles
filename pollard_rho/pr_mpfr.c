
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <math.h>
#include <gmp.h>
#include <mpfr.h>

#define PREC 113 /* lowest reasonable precision */

int gcd_m(mpfr_t *a_in, mpfr_t *b_in, mpfr_t *g_in)
{
    int inex, loop = 0;
    mpfr_t rem_m, a, b, g; /* remainder */
    mpfr_inits(rem_m, a, b, g, (mpfr_ptr) NULL);
    inex = mpfr_set(a, *a_in, MPFR_RNDN);
    inex = mpfr_set(b, *b_in, MPFR_RNDN);
    inex = mpfr_set(g, *g_in, MPFR_RNDN);
    printf("\nentered in gcd_m(a,b,g)\n");
    mpfr_printf("    a = %.Rf\n", a);
    mpfr_printf("    b = %.Rf\n", b);
    mpfr_printf("    g = %.Rf\n", g);

    while ( mpfr_zero_p(b) == 0 ) {
        printf("\nin gcd while loop = %i\n", loop++);
        printf("\nbefore call to mpfr_fmod(rem_m, a, b, MPFR_RNDN)\n");
        mpfr_printf("    rem_m = %.Rf\n", rem_m);
        mpfr_printf("    a = %.Rf\n", a);
        mpfr_printf("    b = %.Rf\n", b);
        inex = mpfr_fmod(rem_m, a, b, MPFR_RNDN);
        printf("\nafter call to mpfr_fmod(rem_m, a, b, MPFR_RNDN)\n");
        mpfr_printf("    rem_m = %.Rf\n", rem_m);
        mpfr_printf("    a = %.Rf\n", a);
        mpfr_printf("    b = %.Rf\n", b);
        printf("\nbefore call to mpfr_set(a, b, MPFR_RNDN)\n");
        mpfr_printf("    a = %.Rf\n", a);
        mpfr_printf("    b = %.Rf\n", b);
        inex = mpfr_set(a, b, MPFR_RNDN);
        printf("\nafter call to mpfr_set()\n");
        mpfr_printf("    a = %.Rf\n", a);
        mpfr_printf("    b = %.Rf\n", b);
        printf("\nbefore call to mpfr_set(b, rem_m, MPFR_RNDN)\n");
        mpfr_printf("    b = %.Rf\n", b);
        mpfr_printf("    rem_m = %.Rf\n", rem_m);
        inex = mpfr_set(b, rem_m, MPFR_RNDN);
        printf("\nafter call to mpfr_set()\n");
        mpfr_printf("    b = %.Rf\n", b);
        mpfr_printf("    rem_m = %.Rf\n", rem_m);
    }
    printf("\nbefore call to mpfr_set(*g_in, a, MPFR_RNDN)\n");
    mpfr_printf("    g_in = %.Rf\n", *g_in);
    mpfr_printf("       a = %.Rf\n", a);
    inex = mpfr_set(*g_in, a, MPFR_RNDN);
    printf("\nafter call to mpfr_set()\n");
    mpfr_printf("    g_in = %.Rf\n", *g_in);
    mpfr_printf("       a = %.Rf\n", a);
    return EXIT_SUCCESS;
}

int main (int argc, char *argv[]) 
{
    uint64_t count, number, bit_prec, loop = 1;
    uint64_t x_fixed = 2, size = 2, x = 2, factor = 1;
    mpfr_t number_m, x_m, x_fixed_m, size_m;
    mpfr_t factor_m, gcd_test_m, one_m, four_m, input_m;
    mpfr_prec_t actual_prec; /* see _MPFR_PREC_FORMAT */
    int inex; /* mpfr retval */

    /* check if a test integer was on the command line */
    if (argc<3){
        fprintf(stderr,"FAIL : test number and bit precision missing.\n");
        fprintf(stderr,"FAIL : %s <integer> <bit precision>\n", argv[0]);
        return (EXIT_FAILURE);
    }

    /* check if a bit precision parameter was on the command line */
    if (argc>2){
        bit_prec = (int)strtol(argv[2], (char **)NULL, 10);
        if (bit_prec>1023){
            bit_prec = 1024;
            printf("\nWARNING : limit precision to 1024 bits.\n");
        }
    } else {
        bit_prec = PREC;
    }
    printf("\nWe shall use %i bits of precision.\n", bit_prec);
    mpfr_set_default_prec((mpfr_prec_t)bit_prec);
    mpfr_init2 (input_m, (mpfr_prec_t) bit_prec);
    mpfr_init2 (four_m, (mpfr_prec_t) bit_prec);

    if (argc>1){
        inex = mpfr_set_str(input_m, argv[1], 10, MPFR_RNDN);
        if ( inex < 0 ) {
            printf("\nFAIL : some mysterious problem happened!\n");
            printf("     : we tried to interpret %s\n", argv[1]);
            printf("     : however we seemed to get ");
            mpfr_printf("%.Rf\n", input_m);
            return (EXIT_FAILURE);
        }

        if (mpfr_number_p(input_m)==0){
            printf("\nFAIL : provide a reasonable decimal number.\n");
            return (EXIT_FAILURE);
        }

        mpfr_set_si(four_m, (long)4, MPFR_RNDN);
        if (mpfr_cmp (input_m, four_m) < 0 ) {
            printf("\nFAIL : provide a reasonable composite integer.\n");
            return (EXIT_FAILURE);
        }

    }
    printf("\nWe shall find a factor of ");
    mpfr_printf("%.Rf\n", input_m);

    mpfr_set_default_prec((mpfr_prec_t)bit_prec);

    mpfr_inits(number_m, x_m, x_fixed_m,
               size_m, gcd_test_m, factor_m,
               one_m, (mpfr_ptr) NULL);

    mpfr_set(number_m, input_m, MPFR_RNDN);
    mpfr_set_si(x_fixed_m, (long)x_fixed, MPFR_RNDN);
    mpfr_set_si(x_m, (long)x, MPFR_RNDN);
    mpfr_set_si(size_m, (long)size, MPFR_RNDN);
    mpfr_set_si(factor_m, (long)factor, MPFR_RNDN);

    /* we need a dummy value for the gdc call */
    mpfr_set_si(gcd_test_m, (long)0, MPFR_RNDN);

    /* we need a value of one to compare to factor_m */
    mpfr_set_si(one_m, (long)1, MPFR_RNDN);

    actual_prec=mpfr_get_default_prec();
    printf("All variables are initialized with %i bits of precision.\n",
                                                       (int)actual_prec);
    printf("\n------------------------------------------------------\n");

    /*
     * int mpfr_number_p (mpfr_t op)
     *    Return non-zero if op is an ordinary number i.e., neither NaN nor an infinity)
     *    Return zero otherwise. 
     *
     * int mpfr_cmp (mpfr_t op1, mpfr_t op2)
     *    Compare op1 and op2.
     *        Return a positive value if op1 > op2
     *        Return zero if op1 = op2
     *        Return a negative value if op1 < op2 */

    /* entering the loop should look like 

          About to enter while loop.
          factor_m = 1e+00
             one_m = 1e+00
          mpfr_number_p(factor_m) = 1
          mpfr_cmp( factor_m, one_m) = 0

    */
    printf("\nAbout to enter while loop.\n");
    mpfr_printf("factor_m = %.Rf\n", factor_m);
    mpfr_printf("   one_m = %.Rf\n", one_m);
    printf("mpfr_number_p(factor_m) = %i\n", mpfr_number_p(factor_m) );
    printf("mpfr_cmp( factor_m, one_m) = %i\n", mpfr_cmp( factor_m, one_m) );
    printf("\n");

    /* do while factor_m is equal to one */
    while ( mpfr_cmp( factor_m, one_m) == 0 ) {

        printf("----   loop %"PRIu64"   ----\n", loop);

        /* operate a for loop so long as size >= count
         * and also factor <= 1 */

        /* About to enter for loop.
               size_m = 2e+00
               factor_m = 1e+00
               mpfr_cmp_si(size_m,(long)count) = 1
               mpfr_cmp_si(factor_m,(long)1) = 0
         */
        printf("\nAbout to enter for loop.\n");
        mpfr_printf("size_m = %.Rf\n", size_m);
        mpfr_printf("factor_m = %.Rf\n", factor_m);
        mpfr_printf("mpfr_cmp_si(size_m,(long)count) = %i\n", mpfr_cmp_si(size_m,(long)count) );
        mpfr_printf("mpfr_cmp_si(factor_m,(long)1) = %i\n", mpfr_cmp_si(factor_m,(long)1) );

        for ( count = 1;
                 (mpfr_cmp_si(size_m,(long)count)>=0)
                 &&
                 (mpfr_cmp_si(factor_m,(long)1)<=0); count++) {

            /* mpfr_fmod(mpfr_t r, mpfr_t x, mpfr_t y, mpfr_rnd_t rnd)
             *     Set r to the value of x - ny, 
             *     where n is the integer quotient of x divided by y
             *     n is rounded toward zero */

            /* x = (x * x + 1) % number */

            mpfr_printf("before we square x_m = %.Rf\n", x_m);
            inex = mpfr_mul(x_m, x_m, x_m, MPFR_RNDN);
            mpfr_printf("after the square x_m = %.Rf\n", x_m);
            
            inex = mpfr_add_si(x_m, x_m, (long) 1, MPFR_RNDN);
            mpfr_printf("after we add one x_m = %.Rf\n", x_m);

            inex = mpfr_fmod(x_m, x_m, number_m, MPFR_RNDN);
            mpfr_printf("modulo number_m = %.Rf\n", number_m);

            printf("\nbefore call to mpfr_sub(gcd_test_m, x_m, x_fixed_m)\n");
            mpfr_printf("    gcd_test_m = %.Rf\n", gcd_test_m);
            mpfr_printf("           x_m = %.Rf\n", x_m);
            mpfr_printf("     x_fixed_m = %.Rf\n", x_fixed_m);
            inex = mpfr_sub(gcd_test_m, x_m, x_fixed_m, MPFR_RNDN);
            printf("\nafter call to mpfr_sub(gcd_test_m, x_m, x_fixed_m)\n");
            mpfr_printf("    gcd_test_m = %.Rf\n", gcd_test_m);
            mpfr_printf("           x_m = %.Rf\n", x_m);
            mpfr_printf("     x_fixed_m = %.Rf\n", x_fixed_m);

            inex = mpfr_abs(gcd_test_m, gcd_test_m, MPFR_RNDN);
            printf("\nafter call to mpfr_abs(gcd_test_m, gcd_test_m, MPFR_RNDN)\n");
            mpfr_printf("    gcd_test_m = %.Rf\n", gcd_test_m);
            mpfr_printf("           x_m = %.Rf\n", x_m);
            mpfr_printf("     x_fixed_m = %.Rf\n", x_fixed_m);

            /* factor = gcd(abs(x - x_fixed), number); */

            printf("\nbefore call to gcd_m(&number_m, &gcd_test_m, &factor_m)\n");
            mpfr_printf("    gcd_test_m = %.Rf\n", gcd_test_m);
            mpfr_printf("      number_m = %.Rf\n", number_m);
            mpfr_printf("      factor_m = %.Rf\n", factor_m);
            inex = gcd_m(&number_m, &gcd_test_m, &factor_m);
            printf("\nafter call to gcd_m()\n");
            mpfr_printf("    gcd_test_m = %.Rf\n", gcd_test_m);
            mpfr_printf("      number_m = %.Rf\n", number_m);
            mpfr_printf("      factor_m = %.Rf\n", factor_m);

            /* printf("count = %4i  x = %6i  factor = %i\n",
                                                   count, x, factor); */

            printf("\ncount = %4i  ", count);
            mpfr_printf("x_m = %.Rf  ", x_m);
            mpfr_printf("factor_m = %.Rf\n\n", factor_m);

            mpfr_printf("size_m = %.Rf\n", size_m);
            mpfr_printf("mpfr_cmp_si(size_m,(long)count) = %i\n", mpfr_cmp_si(size_m,(long)count) );
            mpfr_printf("mpfr_cmp_si(factor_m,(long)1) = %i\n", mpfr_cmp_si(factor_m,(long)1) );
            printf("\nboolean (mpfr_cmp_si(size_m,(long)count)>=0) = %i\n",
                         (int)(mpfr_cmp_si(size_m,(long)count)>=0) );
            printf("\nboolean (mpfr_cmp_si(factor_m,(long)1)<=0) = %i\n",
                         (int)(mpfr_cmp_si(factor_m,(long)1)<=0) );

        }
        inex = mpfr_mul_si(size_m,size_m,(long)2,MPFR_RNDN);
        inex = mpfr_set(x_fixed_m, x_m, MPFR_RNDN);
        loop = loop + 1;

        printf("\nboolean (mpfr_number_p(factor_m) !=0 ) = %i\n",
                       (int)(mpfr_number_p(factor_m) !=0 ));

        printf("\nboolean (mpfr_cmp( factor_m, one_m) == 0) = %i\n",
                       (int)(mpfr_cmp(factor_m, one_m) == 0));

    }
    mpfr_printf("A factor of %.Rf is %.Rf\n", number_m, factor_m);
    return EXIT_SUCCESS;
}

