
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
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include "v.h"

/* If we have non-zero intercept_cnt number of real roots to the
 * complex coefficient quadratic then we may now compute the
 * actual hit point H and return it in pt. If there is no valid
 * forward looking points from the perspective of the observation
 * plane and ray_direction then return a null vector and integer
 * value -1.  Otherwise we return a zero integer value along with
 * the point of interception in pt */
int intercept_point( vec_type *pt, int intercept_cnt, cplex_type *k_val,
                     vec_type *obs_point, vec_type *ray_direction)
{
    vec_type tmp;
    int return_value; 

    /* given that we only care about a real root that is forward
     * looking from the observation plane then we need a double
     * value for the root k */
    double k_root;

    /* If we actually do get an intercept then we need to determine
     * the closest forward looking point which is our actual point
     * of intercept H.
     * We can call that the hit_point just to be consistent with
     * the diagrams thus far where we use H and hit_point to mean
     * the actual intercept. */
    vec_type hit_point;

    printf ("-------- intercept_point begins -------------\n");

    printf ("   0 : k_val[0] = ( %-18.14e, %-18.14e )\n",
                                   k_val[0].r, k_val[0].i);

    printf ("   1 : k_val[1] = ( %-18.14e, %-18.14e )\n\n",
                                   k_val[1].r, k_val[1].i);

    printf ("INFO : we have %i real k values.\n", intercept_cnt);

    /* if the two real roots are equal then we really only have a single
     * real solution. Note that we only really care about real roots at
     * this time. */
    if ( ( intercept_cnt == 2 ) 
         &&
         ( k_val[0].r == k_val[1].r )
         &&
         ( k_val[0].i == k_val[1].i ) ) {

        intercept_cnt = 1;
        printf ("     : only one unique root.\n\n");

    }

    /* So did we get a real root ? */
    if ( intercept_cnt > 0 ) {
        /* Did we get two of them ? */
        if ( intercept_cnt == 2 ) {
            /* Is one of them non-negative? */
            if ( ( k_val[0].r >= 0.0 )
                 ||
                 ( k_val[1].r >= 0.0 ) ) {

                /* pick the closest value in front
                 * of the viewport */
                if ( (
                       ( k_val[0].r >= 0.0 )
                       && 
                       ( k_val[0].r <= k_val[1].r ) )
                    ||
                     (
                       ( k_val[0].r >= 0.0 )
                       &&
                       ( k_val[1].r < 0.0 ) ) ) {

                    k_root = k_val[0].r;

                } else {
                    k_root = k_val[1].r;
                }
            } else {
                /* no root to the front of the viewport 
                 * thus we set the intercept count down
                 * to zero. */
                printf("WARN : no intercept to the front.\n");
                intercept_cnt = 0;
            }
        } else {
            /* we have only a single real root */
            if ( k_val[0].i == 0.0 ) {
                k_root = k_val[0].r;
            } else {
                k_root = k_val[1].r;
            }
            /* is that real value to the front of the
             * viewport ?  If not then set the intercept
             * down to zero. */
            if ( k_root < 0.0 ) {
               printf("WARN : no intercept to the front.\n");
               intercept_cnt = 0;
            }
        }

        /* If we still have an intercept after all that
         * choosey logic above then we can compute the
         * point in 3-space for the actual intercept :
         *
         *     hit_point = obs_point + k_root * ray_direction
         */

        if ( intercept_cnt > 0 ) {
            /* We can finally say that we did get an intercept
             * point and thus the integer value for this whole
             * task is a nice silent zero to indicate all is well */
            return_value = 0;

            cplex_vec_scale( &tmp, ray_direction, k_root );
            cplex_vec_add( &hit_point, obs_point, &tmp);

            /*
            printf("INFO : hit_point = ");
            cplex_vec_print( &hit_point );
            printf("\n");
            */

            cplex_vec_copy( pt, &hit_point);

        } else {

            /* we have nothing to return */
            return_value = -1;

        }

    }

    return ( return_value );

}

