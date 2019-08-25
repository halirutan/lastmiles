
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv<::>)
{
    int j;

    printf ( "\nthis is a line of text.\n" );

    if ( argc > 2 ){
        printf ( "\n    there are %i things on the cli\n", argc );
        for ( j=0; j<argc; j++ ){
            printf ( "    arg[ %2i ] is \'%s\'\n", j, argv[j] );
        }
    }

    return ( EXIT_SUCCESS );
}

