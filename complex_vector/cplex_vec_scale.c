
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

int cplex_vec_scale( vec_type *res, vec_type *op1, double factor )
{

    res->x.r = op1->x.r * factor; res->x.i = op1->x.i * factor;
    res->y.r = op1->y.r * factor; res->y.i = op1->y.i * factor;
    res->z.r = op1->z.r * factor; res->z.i = op1->z.i * factor;

    return ( 0 );

}

