
#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{

    long double *pi_fp128;
    double *pi_fp64;
    float *pi_fp32;

    int j = 1;  /* dummy test integer */
    int little_endian = (*(uint8_t*)&j == 1) ? 1 : 0;

    printf("the sizeof(long double pi) is %lld bytes\n",
                                        sizeof(long double) );

    printf("the sizeof(double pi) is      %lld bytes\n",
                                        sizeof(double) );

    printf("the sizeof(float pi) is       %lld bytes\n",
                                        sizeof(float) );

    pi_fp128 = calloc ( (size_t)1, sizeof(long double) );
    *pi_fp128 = 3.141592653589793238462643383279502884197L;

    pi_fp64 = calloc ( (size_t)1, sizeof(double) );
    *pi_fp64 = 3.141592653589793238462643;

    pi_fp32 = calloc ( (size_t)1, sizeof(float) );
    *pi_fp32 = 3.141592653589793;

    if (little_endian) {
        printf("\nThis is a little endian memory machine.\n");
        printf("Data in memory may be reversed.\n");
        printf("Here is the data in natural human order.\n");
        printf("--------- long double fp128 ---------\n");
        printf("0x%" PRIXPTR " : ", (uintptr_t)pi_fp128);
        for ( j=(sizeof(long double)-1); j>(-1); j-- )
            printf("%02x ", (uint8_t)((uint8_t*)pi_fp128)[j] );

        printf("\n--------- double fp64 ---------------\n");
        printf("0x%" PRIXPTR " : ", (uintptr_t)pi_fp64);
        for ( j=(sizeof(double)-1); j>(-1); j-- )
            printf("%02x ", (uint8_t)((uint8_t*)pi_fp64)[j] );

        printf("\n--------- float fp32 ----------------\n");
        printf("0x%" PRIXPTR " : ", (uintptr_t)pi_fp32);
        for ( j=(sizeof(float)-1); j>(-1); j-- )
            printf("%02x ", (uint8_t)((uint8_t*)pi_fp32)[j] );

    } else {
        printf("\nThis is a big endian memory machine.\n");
        printf("--------- long double fp128 ---------\n");
        printf("0x%" PRIXPTR " : ", (uintptr_t)pi_fp128);
        for ( j=0; j<sizeof(long double); j++ )
            printf("%02x ", (uint8_t)((uint8_t*)pi_fp128)[j] );

        printf("\n--------- double fp64 ---------------\n");
        printf("0x%" PRIXPTR " : ", (uintptr_t)pi_fp64);
        for ( j=0; j<sizeof(double); j++ )
            printf("%02x ", (uint8_t)((uint8_t*)pi_fp64)[j] );

        printf("\n--------- float fp32 ----------------\n");
        printf("0x%" PRIXPTR " : ", (uintptr_t)pi_fp32);
        for ( j=0; j<sizeof(float); j++ )
            printf("%02x ", (uint8_t)((uint8_t*)pi_fp32)[j] );

    }
    printf("\n\n" );

    printf("pi_fp128 could be decimal %-40.38Lg\n", *pi_fp128);
    printf("pi_fp64  could be decimal %-18.16g\n", *pi_fp64);
    printf("pi_fp32  could be decimal %-12.10g\n", *pi_fp32);

    return ( EXIT_SUCCESS );

}

