
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <gmp.h>
#include <mpfr.h>

int main(int argc, char *argv[])
{

    int inex = 0;
    mpfr_t pi_mpfr, atan_pi_mpfr, atan_pi4_mpfr, theta_mpfr, delta_mpfr;

    mpfr_prec_t prec = 113;

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

    if ( argc > 1 ) {
        prec = atoi( argv[1] );
        if ( prec < 23 ) {
            fprintf(stderr,"FAIL : IEEE754 minimum is 23 bits.\n");
            return ( EXIT_FAILURE );
        }
        if ( prec > 327679 ){
            fprintf(stderr,"DBUG : madness!! You want 100,000 digits!\n");
            prec = 327680;
        } else {
            printf("INFO : you asked for %i bits.\n", prec );
            if ( prec > 4096 ){
                fprintf(stderr,"WARN : we shall limit to 384 bits.\n");
                prec = 4096;
            }
        }
    }

    mpfr_inits2 ( prec, pi_mpfr, theta_mpfr, atan_pi4_mpfr, atan_pi_mpfr, delta_mpfr, (mpfr_ptr*) 0 );

    inex = mpfr_const_pi ( pi_mpfr, MPFR_RNDN);

    printf("\nINFO : we are using %i bits of precision.\n", prec );
    mpfr_printf ("pi may be %.Re\n\n", pi_mpfr );
    printf("100 digits of pi is     3.141592653589793238462643383");
    printf("27950288419716939937510582097494459230781640628620899");
    printf("86280348253421170679\n\n\n");

    inex = mpfr_set_flt ( theta_mpfr, 1.0, MPFR_RNDN);
    mpfr_printf ("theta = %.Re\n\n", theta_mpfr );

    inex = mpfr_atan ( atan_pi4_mpfr, theta_mpfr, MPFR_RNDN);
    mpfr_printf ("pi/4 may be %.Re\n\n", atan_pi4_mpfr );

    inex = mpfr_mul_si ( atan_pi_mpfr, atan_pi4_mpfr, 4, MPFR_RNDN);
    mpfr_printf ("pi may be %.Re\n\n", atan_pi_mpfr );

    inex = mpfr_sub (delta_mpfr, pi_mpfr, atan_pi_mpfr, MPFR_RNDN);
    inex = mpfr_abs (delta_mpfr, delta_mpfr, MPFR_RNDN);
    mpfr_printf ("delta( 4 * atan(1) ) - pi = %.Re\n\n", delta_mpfr);

    mpfr_clears  ( theta_mpfr, atan_pi4_mpfr, atan_pi_mpfr, pi_mpfr, delta_mpfr, (mpfr_ptr*) 0 );
    return ( EXIT_SUCCESS );

}

