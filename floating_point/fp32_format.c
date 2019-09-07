
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/* on a live stream we attempt to implement a tool 
 * that will convert an input fp value to a binary
 * 32 bit IEEE-754 2008 format.  Which has a sign
 * bit and 8-bits for an offset exponent and then
 * a remainder of 22 significand bits wherein there
 * is an implied leading 1 bit. */

int main ( int argc, char *argv[] )
{

    double num;
    double exponent_calc, running_total, test_subtract;
    int j, actual_exponent, fp32_exponent, sign_bit = 0;
    uint8_t bit_mask, shifter;

    /* some sort of a place to shove the bits */
    uint32_t fp32_bit_mask, fp32_register = 0;

    if ( argc < 2 ) {
        fprintf(stderr,"FAIL : give me a decimal number!\n");
        return ( EXIT_FAILURE );
    }

    num = strtod( argv[1], (char **)NULL );
    printf ("INFO : seems like a decimal number %20.16g\n", num);

    if ( num < 0.0 ){
        sign_bit = 1;
        fp32_bit_mask = 1<<31;
        /* we only have the sign of this thing */
        fp32_register = fp32_bit_mask;
        num = fabs(num);
        printf ("     : a negative number will have sign_bit = 1\n");
    }

    /*
     * An example would be pi = 3.14159265358979323846264..
     *                          3.14159265358979323846264338327950...
     * 
     * The IEEE-754 32-bit value would be 0x40490fdb
     *
     *       0100 0000 0100 1001 0000 1111 1101 1011
     *       ^ sign bit is zero for a positive number
     *
     *
     *
     *        100 0000 0100 1001 0000 1111 1101 1011
     *        ^^^ ^^^^ ^
     *        These are the offset 127 exponent bits
     *        and here we see 10000000 == 128 decimal
     *        so we subtract the 127 offset to get 1.
     *        Therefore the exponent is really just 1.
     *
     *                  100 1001 0000 1111 1101 1011
     *                  All that remains in the actual
     *                  floating point significand.
     *
     * Note that there is always an implied value of 1
     * in front of the significand on normal numbers.
     *
     * Thus the significand is really : 
     *
     *                1.100 1001 0000 1111 1101 1011
     *
     *
     */

    exponent_calc = floor( log(num)/log(2.0) );
    actual_exponent = (int) exponent_calc;
    printf ("     : actual exponent should be %i\n", actual_exponent );

    fp32_exponent = actual_exponent + 127;
    printf ("     : binary fp32 exponent will be ");
    for ( j=7; j>=0; j-- ){
        bit_mask = 1<<j;
        shifter = ( fp32_exponent & bit_mask ) ? 1 : 0;
        if (shifter){
            printf("1");
            fp32_bit_mask = 1<<(j+23);
            fp32_register = fp32_register | fp32_bit_mask;
        }else{
            printf("0");
        }
    }
    printf("\n");

    /* Manually using dc to attempt to compute the bits in
     * the significand : 
     *
     * titan$ echo '36k 36.584 32 /  1 - p 2 _3^ - p 2 _6^ - p
     *                                     2 _9^ - p 2 _11^ - p
     *                                     2 _13^ - p  2_14^-p
     *                                     2_21^-p 2_27^-p 
     *                                     q' | dc 
     * .143250000000000000000000000000000000
     * .018250000000000000000000000000000000
     * .002625000000000000000000000000000000
     * .000671875000000000000000000000000000
     * .000183593750000000000000000000000000
     * .000061523437500000000000000000000000
     * .000000488281250000000000000000000000
     * .000000011444091796875000000000000000
     * .000000003993511199951171875000000000
     * titan$  
     * hex data is  0x42 12 56 04
     *
     * Note that the 64-bit data is 0x4042 0x4ac0 0x8312 0x6e98
     */

    running_total = num / pow( 2.0, exponent_calc) - 1.0;
    printf("INFO : starting point running_total = %20.16g\n", running_total );
    for ( j=0; j<23; j++ ){
        test_subtract = pow( 2.0, ( 0.0 - (double)( j + 1 ) ) );
        printf("INFO : test bit %02i with value %20.16g\n", j+1, test_subtract);
        if ( ( running_total - test_subtract ) > 0.0 ) {
            running_total = running_total - test_subtract;
            printf("     : good bit %02i with new   %20.16g\n", j+1, running_total );
            fp32_register = fp32_register | ( 1<<(22-j) );
        }
    }

    printf("INFO : perhaps fp32_register = %8X\n", fp32_register );

    return ( EXIT_SUCCESS );

}

