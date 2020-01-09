

#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include <float.h>

int main()
{

    double u0, u1, un;
    double u3, denom, numer;
    int k, fp_round_mode, fpe_raised;

#ifdef FLT_EVAL_METHOD
    printf ( "INFO : FLT_EVAL_METHOD == %d\n", FLT_EVAL_METHOD);
#endif

    fp_round_mode = fegetround();
    printf("INFO : fp rounding mode is ");
    switch(fp_round_mode){
        case FE_TONEAREST:
            printf("FE_TONEAREST\n");
            break;
        case FE_TOWARDZERO:
            printf("FE_TOWARDZERO\n");
            break;
        case FE_UPWARD:
            printf("FE_UPWARD\n");
            break;
        case FE_DOWNWARD:
            printf("FE_DOWNWARD\n");
            break;
        default:
            printf("bloody unknown!\n");
            break;
        }

    u0 = 2.0;
    u1 = -4.0;

    /* we know from pen and paper and other mistakes that
     * u2 = 37/2 and u3 =  347/37 exactly. */

    printf("\n---------------------------------------\n");
    printf(" We know that u2 = 37/2 which is 18.5\n");
    printf(" We also know that u3 = 347/37 and that\n");
    printf(" can not be represented by any computer.\n");

    numer = 340.0 + 7.0;
    denom = 30.0 + 7.0;
    if ( feclearexcept(FE_ALL_EXCEPT) == 0 ) {
        printf("\n    feclearexcept(FE_ALL_EXCEPT) works!\n");
    } else {
        printf("\n    feclearexcept(FE_ALL_EXCEPT) fails!\n");
        return ( EXIT_FAILURE );
    }
    printf("\n");

    u3 = numer / denom;

    fpe_raised = fetestexcept(FE_ALL_EXCEPT);
    if (fpe_raised!=0){
        printf("INFO : FP Exception raised is");
        if(fpe_raised & FE_INEXACT) printf(" FE_INEXACT");
        if(fpe_raised & FE_DIVBYZERO) printf(" FE_DIVBYZERO");
        if(fpe_raised & FE_UNDERFLOW) printf(" FE_UNDERFLOW");
        if(fpe_raised & FE_OVERFLOW) printf(" FE_OVERFLOW");
        if(fpe_raised & FE_INVALID) printf(" FE_INVALID");
        printf("\n");
    } else {
        printf(" nothing!\n");
    }

    printf(" In fact u3 sort of is %-+32.28e\n", u3);
    printf("---------------------------------------\n");

    printf(" u[%2i] = %-+32.28e\n", 0 , u0 );
    printf(" u[%2i] = %-+32.28e\n", 1 , u1 );

    for ( k=2; k<32; k++ ) {

        feclearexcept(FE_ALL_EXCEPT);

        un = 111.0 - 1130.0/u1 + 3000.0 / ( u1 * u0 ) ;

        fpe_raised = fetestexcept(FE_ALL_EXCEPT);
        printf( " u[%2i] = %-+32.28e", k , un );
        if (fpe_raised!=0){
            printf("    FP Exception raised ==");
            if(fpe_raised & FE_INEXACT) printf(" FE_INEXACT");
            if(fpe_raised & FE_DIVBYZERO) printf(" FE_DIVBYZERO");
            if(fpe_raised & FE_UNDERFLOW) printf(" FE_UNDERFLOW");
            if(fpe_raised & FE_OVERFLOW) printf(" FE_OVERFLOW");
            if(fpe_raised & FE_INVALID) printf(" FE_INVALID");
            printf("\n");
        } else {
            printf(" nothing!\n");
        }

        u0 = u1;
        u1 = un;

    }

    return ( EXIT_SUCCESS );

}

