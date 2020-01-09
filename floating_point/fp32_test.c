
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include <float.h>

int main(int argc, char *argv[]){

    float fp0, fp1, fp2, tenth, dragon;
    int j, fp_round_mode, fpe_raised;

#ifdef FLT_EVAL_METHOD
    printf ( "INFO : FLT_EVAL_METHOD == %d\n", FLT_EVAL_METHOD);
#endif

    fp0 = 36.584;
    fp1 =  7.812;
    tenth = 0.1;
    dragon = 0.099;

    printf ( "the sizeof(fp0) is %i\n", sizeof(fp0) );

    printf ( "the value of fp0 is %g\n", fp0 );
    printf ( "the value of fp1 is %g\n", fp1 );
    printf ( "the value of dragon is %g\n", dragon );

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

    feclearexcept(FE_ALL_EXCEPT);

    fp2 = fp0 + fp1;

    fpe_raised = fetestexcept(FE_ALL_EXCEPT);
    if (fpe_raised!=0){
        printf("INFO : FP Exception raised is");
        if(fpe_raised & FE_INEXACT) printf(" FE_INEXACT");
        if(fpe_raised & FE_DIVBYZERO) printf(" FE_DIVBYZERO");
        if(fpe_raised & FE_UNDERFLOW) printf(" FE_UNDERFLOW");
        if(fpe_raised & FE_OVERFLOW) printf(" FE_OVERFLOW");
        if(fpe_raised & FE_INVALID) printf(" FE_INVALID");
        printf("\n");
    }

    printf ( "fp2 = fp0 + fp1 = %g\n", fp2 );

    feclearexcept(FE_ALL_EXCEPT);
    fp2 = fp2 + tenth;
    if (fpe_raised!=0){
        printf("INFO : FP Exception raised is");
        if(fpe_raised & FE_INEXACT) printf(" FE_INEXACT");
        if(fpe_raised & FE_DIVBYZERO) printf(" FE_DIVBYZERO");
        if(fpe_raised & FE_UNDERFLOW) printf(" FE_UNDERFLOW");
        if(fpe_raised & FE_OVERFLOW) printf(" FE_OVERFLOW");
        if(fpe_raised & FE_INVALID) printf(" FE_INVALID");
        printf("\n");
    }
    printf ( "fp2 = fp0 + fp1 + tenth = %g\n", fp2 );

    feclearexcept(FE_ALL_EXCEPT);
    fp2 = fp2 + dragon;
    if (fpe_raised!=0){
        printf("INFO : FP Exception raised is");
        if(fpe_raised & FE_INEXACT) printf(" FE_INEXACT");
        if(fpe_raised & FE_DIVBYZERO) printf(" FE_DIVBYZERO");
        if(fpe_raised & FE_UNDERFLOW) printf(" FE_UNDERFLOW");
        if(fpe_raised & FE_OVERFLOW) printf(" FE_OVERFLOW");
        if(fpe_raised & FE_INVALID) printf(" FE_INVALID");
        printf("\n");
    }
    printf ( "fp2 = fp0 + fp1 + tenth + dragon = %g\n", fp2 );

    return ( EXIT_SUCCESS );

}

