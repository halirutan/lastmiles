
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <gmp.h>
#include <mpfr.h>

int main(int argc, char *argv[])
{

    int inex = 0;
    mpfr_t pi256;

    printf("GMP  library version : %d.%d.%d\n",
            __GNU_MP_VERSION,
            __GNU_MP_VERSION_MINOR,
            __GNU_MP_VERSION_PATCHLEVEL );

    printf("MPFR library: %-12s\n", mpfr_get_version ());
    printf("MPFR header : %s (based on %d.%d.%d)\n",
            MPFR_VERSION_STRING,
            MPFR_VERSION_MAJOR,
            MPFR_VERSION_MINOR,
            MPFR_VERSION_PATCHLEVEL);


    if (mpfr_buildopt_tls_p()!=0)
        printf("            : compiled as thread safe using TLS\n");

    if (mpfr_buildopt_float128_p()!=0) 
        printf("            : __float128 support enabled\n");

    if (mpfr_buildopt_decimal_p()!=0)
        printf("            : decimal float support enabled\n");

    if (mpfr_buildopt_gmpinternals_p()!=0)
        printf("            : compiled with GMP internals\n");

    if (mpfr_buildopt_sharedcache_p()!=0)
        printf("            : threads share cache per MPFR const\n");

    printf("MPFR thresholds file used at compile time : %s\n",
                                      mpfr_buildopt_tune_case ());


    mpfr_init2 ( pi256, 256);  /* 256 bit precision data */
    inex = mpfr_const_pi ( pi256, MPFR_RNDN);

    mpfr_printf ("72 digits of pi = %.72Rg\n\n", pi256 );

    mpfr_clear  ( pi256 );


    return ( EXIT_SUCCESS );

}

