
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

void cplex_cubert( cplex_type *op1, cplex_type *res )
{

    double theta = cplex_theta( op1 );
    double cubert_mag = cbrt(cplex_mag( op1 ));

    /* Please see comment from Jefferson Carpenter 
     * regarding roots in the square root source.
     * However cube roots :
     *
     * (m, t)^3 = (m^3, 3 * t) = (m^3, 3t + 2 * N * pi)
     *                       = (m, t + 2 * N * pi/3)^3 
     *
     * for integer N.
     */
    
    /* primary root */
    res[0].r = cubert_mag * cos( theta / 3.0 );
    res[0].i = cubert_mag * sin( theta / 3.0 );
    /* Thanks to Euler we go around the circle 2pi/3 radians */
    res[1].r = cubert_mag * cos( PI3_L + theta / 3.0 ); 
    res[1].i = cubert_mag * sin( PI3_L + theta / 3.0 ); 

    res[2].r = cubert_mag * cos( 2.0L * PI3_L + theta / 3.0 ); 
    res[2].i = cubert_mag * sin( 2.0L * PI3_L + theta / 3.0 ); 

}

