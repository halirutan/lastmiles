
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
#include <math.h>
#include "v.h"

double cplex_vec_mag( vec_type *op1 )
{

    double vec_magnitude, tmp_x, tmp_y, tmp_z;
    /* determine the complex vector magnitude thus :
     *
     * | < ( x.r, x.i ), ( y.r, y.i ), ( z.r, z.i ) > | 
     *
     * we need the square root of the sum of product 
     * components wherein each component is multiplied
     * by its complex conjugate :
     *
     * sqrt( ( x.r, x.i ) * ( x.r, -x.i )
     *     + ( y.r, y.i ) * ( y.r, -y.i )
     *     + ( z.r, z.i ) * ( z.r, -z.i ) )
     *
     *
     * Note on complex conjugate multiplication :
     *
     *   ( a + bi ) ( a - bi ) = a^2 - abi + abi - b^2 i^2
     *                         = a^2 + b^2 
     *
     */

    tmp_x = op1->x.r * op1->x.r + op1->x.i * op1->x.i + 0.0;
    tmp_y = op1->y.r * op1->y.r + op1->y.i * op1->y.i + 0.0;
    tmp_z = op1->z.r * op1->z.r + op1->z.i * op1->z.i + 0.0;

    vec_magnitude = sqrt( tmp_x + tmp_y + tmp_z );

    return ( vec_magnitude );

}

