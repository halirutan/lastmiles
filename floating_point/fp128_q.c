
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <quadmath.h>
#include <float.h>
#include <fenv.h>

#define BUFFERSIZE 128

int main(int argc, char *argv[]){

    /* long double fp0, fp1, fp2; */
    __float128 fp0, fp1, fp2;
    const size_t buffer_size = BUFFERSIZE;
    char *buffer = calloc(buffer_size,sizeof(unsigned char));
    int num_chars;

#ifdef FLT_EVAL_METHOD
    printf ( "INFO : FLT_EVAL_METHOD == %d\n", FLT_EVAL_METHOD);
#endif

#ifdef DECIMAL_DIG
    printf ( "INFO : DECIMAL_DIG == %d\n", DECIMAL_DIG);
#endif

/* LDBL_DIG, FLT_DECIMAL_DIG, DBL_DECIMAL_DIG, LDBL_DECIMAL_DIG */
#ifdef FLT_DECIMAL_DIG
    printf ( "INFO : FLT_DECIMAL_DIG == %d\n", FLT_DECIMAL_DIG);
#endif

#ifdef DBL_DECIMAL_DIG
    printf ( "INFO : DBL_DECIMAL_DIG == %d\n", DBL_DECIMAL_DIG);
#endif

#ifdef LDBL_DECIMAL_DIG
    printf ( "INFO : LDBL_DECIMAL_DIG == %d\n", LDBL_DECIMAL_DIG);
#endif

#ifdef LDBL_DIG
    printf ( "INFO : LDBL_DIG == %d\n", LDBL_DIG);
#endif


    fp0 = 36.584Q;

    printf ( "the sizeof(fp0) is %i\n", sizeof(fp0) );

    num_chars = quadmath_snprintf( buffer, buffer_size, "%40.36Qg", fp0 );
    if ( num_chars > 0 ) {
        printf ("INFO : quadmath_snprintf formatted %i chars.\n", num_chars);
    } else {
        fprintf(stderr,"FAIL : quadmath_snprintf failed. No idea why.\n");
        return ( EXIT_FAILURE );
    }

    printf ( "the value of fp0 is %s\n", buffer );


    fp1 =  7.812;

    printf ( "the sizeof(fp1) is %i\n", sizeof(fp1) );
    num_chars = quadmath_snprintf( buffer, buffer_size, "%40.36Qg", fp1 );
    if ( num_chars > 0 ) {
        printf ("INFO : quadmath_snprintf formatted %i chars.\n", num_chars);
    } else {
        fprintf(stderr,"FAIL : wtf quadmath_snprintf failed. No idea why.\n");
        return ( EXIT_FAILURE );
    }

    printf ( "the value of fp1 is %s\n", buffer );

    fp2 = fp0 + fp1;

    printf ( "the sizeof(fp2) is %i bytes\n", sizeof(fp2) );
    num_chars = quadmath_snprintf( buffer, buffer_size, "%40.36Qg", fp2 );
    if ( num_chars > 0 ) {
        printf ("INFO : quadmath_snprintf formatted %i chars.\n", num_chars);
    } else {
        fprintf(stderr,"FAIL : wtf quadmath_snprintf failed. No idea why.\n");
        return ( EXIT_FAILURE );
    }

    printf ( "fp2 = fp0 + fp1 = %s\n", buffer );

    free(buffer);
    return ( EXIT_SUCCESS );

}

