
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

#include <stdio.h>
#include <stdlib.h>
#include "v.h"

int cplex_vec_print( vec_type *op )
{

    printf("< ( %16.12e, %16.12e ),\n", op->x.r, op->x.i );
    printf("  ( %16.12e, %16.12e ),\n", op->y.r, op->y.i );
    printf("  ( %16.12e, %16.12e ) >",  op->z.r, op->z.i);

    return ( 0 );

}

