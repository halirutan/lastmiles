
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

double cplex_theta( cplex_type *op1 );
double cplex_mag( cplex_type *op1 );

cplex_type * cplex_sqrt( cplex_type *op1 )
{

    double theta = cplex_theta( op1 );
    double sqrt_mag = sqrt(cplex_mag( op1 ));

    /* negatratoron: in cartesian coordinates,
     *     (r, i)^2 = (r^2 - i^2, 2 r i) 
     *              = ((-r)^2 - (-i)^2, 2 (-r) (-i))
     *              = (-r, -i)^2
     *
     * Another easy proof that there are two unique
     * square roots of complex numbers
     *
     */
    cplex_type *res = calloc( (size_t)2, (size_t)sizeof(cplex_type));

    res->r = sqrt_mag * cos( theta / 2.0 );
    res->i = sqrt_mag * sin( theta / 2.0 );

    (res+1)->r = sqrt_mag * cos( PI_L + theta / 2.0 ); 
    (res+1)->i = sqrt_mag * sin( PI_L + theta / 2.0 ); 

    return res;

}

