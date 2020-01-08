

#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>

int main()
{

    double u0, u1, un;

    int k;

    u0 = 2.0;
    u1 = -4.0;

    for ( k=2; k<32; k++ ) {

        un = 111.0 - 1130.0/u1 + 3000.0 / ( u1 * u0 ) ;

        printf( " u[%2i] = %-+32.28e\n", k , un );

        u0 = u1;
        u1 = un;

    }

    return ( EXIT_SUCCESS );

}

