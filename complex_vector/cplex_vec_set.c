
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

#include <math.h>
#include "v.h"

/* initialize the values inside a complex vector */
int cplex_vec_set( vec_type *op,
                       double r0, double i0,
                       double r1, double i1,
                       double r2, double i2 )
{

    op->x.r = r0; op->x.i = i0;
    op->y.r = r1; op->y.i = i1;
    op->z.r = r2; op->z.i = i2;
    return ( 0 );
}

