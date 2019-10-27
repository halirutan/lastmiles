
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

int cplex_vec_copy( vec_type *dst, vec_type *src)
{

    dst->x.r = src->x.r + 0.0;
    dst->x.i = src->x.i + 0.0;

    dst->y.r = src->y.r + 0.0;
    dst->y.i = src->y.i + 0.0;

    dst->z.r = src->z.r + 0.0;
    dst->z.i = src->z.i + 0.0;

    return ( 0 );
}

