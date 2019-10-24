
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
#include <stdlib.h>
#include "v.h"

int cplex_sqrt( cplex_type res[2], cplex_type *op1 )
{

    double epsilon = RT_EPSILON;
    int status = cplex_check(op1);
    if ( status != 0 ) return status;

    double theta = cplex_theta( op1 );
    double sqrt_mag = sqrt(cplex_mag( op1 ));

    /* Jefferson Carpenter says in cartesian coordinates,
     *
     *     (r, i)^2 = (r^2 - i^2, 2 * r * i)
     *              = ((-r)^2 - (-i)^2, 2 * (-r) * (-i))
     *              = (-r, -i)^2
     *
     * Another easy proof that there are two unique
     * square roots of complex numbers
     *
     */

    /* Thanks to Euler we go around the circle pi radians
     * however we need to check if theta is zero in which
     * case we are staying with a zero result exactly.
     */

    if ( fabs(theta) == 0.0 ) {
        res[0].r = sqrt_mag;
        res[0].i = 0.0;
        res[1].r = sqrt_mag;
        res[1].i = 0.0;
    } else {
        res[0].r = sqrt_mag * cos( theta / 2.0 );
        res[0].i = sqrt_mag * sin( theta / 2.0 );
        res[1].r = sqrt_mag * cos( PI_L + theta / 2.0 );
        res[1].i = sqrt_mag * sin( PI_L + theta / 2.0 );
    }

    return ( 0 );

}

