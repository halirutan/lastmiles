
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

int cplex_vec_add( vec_type *res, vec_type *op1, vec_type *op2 )
{

    res->x.r = op1->x.r + op2->x.r + 0.0;
    res->x.i = op1->x.i + op2->x.i + 0.0;

    res->y.r = op1->y.r + op2->y.r + 0.0;
    res->y.i = op1->y.i + op2->y.i + 0.0;

    res->z.r = op1->z.r + op2->z.r + 0.0;
    res->z.i = op1->z.i + op2->z.i + 0.0;

    return ( 0 );

}

