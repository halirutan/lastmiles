
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

#include <stdlib.h>
#include "v.h"

int cplex_mult( cplex_type *res, cplex_type *op1, cplex_type *op2 )
{

    /*  ( r1, i1 ) ( r2, i2 ) =  r1xr2 + r1xi2 + i1xr2 + i1xi2
     *
     * theddmage (x+i*y)*(a+i*b) == ax + i*bx + i*ya -1(by)
     */

    int status = cplex_check(op1);
    if ( status != 0 ) return status;
    status = cplex_check(op2);
    if ( status != 0 ) return status;

    res->r = op1->r * op2->r - ( op1->i * op2->i );
    res->i = op1->r * op2->i + ( op2->r * op1->i );

    return ( 0 );

}

