
/*********************************************************************
 * The Open Group Base Specifications Issue 6
 * IEEE Std 1003.1, 2004 Edition
 *
 *    An XSI-conforming application should ensure that the feature 
 *    test macro _XOPEN_SOURCE is defined with the value 600 before 
 *    inclusion of any header. This is needed to enable the 
 *    functionality described in The _POSIX_C_SOURCE Feature Test 
 *    Macro and in addition to enable the XSI extension.
 *
 *********************************************************************/
#define _XOPEN_SOURCE 600

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main( int argc, char **argv)
{

    char buffer[255] = "";
    char time_buffer[32] = "";
    struct timespec time_tv;

    /* time now */
    setlocale ( LC_ALL, "POSIX" );
    clock_gettime( CLOCK_REALTIME, &time_tv );
    sprintf ( time_buffer, "%10lu.%-9lu", time_tv.tv_sec, time_tv.tv_nsec );
    sprintf ( buffer, "SIGSEGV : %s:%d", __FILE__, __LINE__ );
    printf( "%s at %s\n", buffer, time_buffer );
    return ( EXIT_FAILURE );

}

