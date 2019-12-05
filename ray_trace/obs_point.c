
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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include "v.h"

int main ( int argc, char **argv)
{

    vec_type tmp[5];
    int k, intercept_cnt = 0;

    /* per our diagrams we are just solving for k in the complex
     * cooeficient quadratic */
    cplex_type k_val[2];

    /* given that we only care about a real root that is forward
     * looking from the observation plane then we need a double
     * value for the root k */
    double k_root;

    /* if we actually do get an intercept then we need to determine
     * the closest forward looking point which is out actual H.
     * We can call that the hit_point just to be consistent with
     * the diagrams thus far */
    vec_type hit_point;

    /* We must first define where our observation plane is in R3
     * as a point and a normal direction. The obs_normal direction
     * will be the direction of all rays that we trace. */
    vec_type obs_origin, obs_normal;

    /* The observation plane has its own coordinate system and
     * thus we have x_prime_hat_vec and y_prime_hat_vec as ortogonal
     * and normalized vectors */
    vec_type x_prime_hat_vec, y_prime_hat_vec;

    /* To locate a given point on the observation plane we will
     * need scalar distances away from the observation plane
     * center along the directions x_prime_hat_vec and 
     * y_prime_hat_vec */
    double x_prime, y_prime;

    /* All of the above merely allows us to compute a starting
     * point for our ray to trace along the direction of the
     * vector obs_normal. */
    vec_type obs_point;

    /* Test case will be an observation plane at ( 12, 0, 0 ) */
    /* cplex_vec_set( &obs_origin, 12.0, 0.0, 0.0, 0.0, 0.0, 0.0); */
    cplex_vec_set( &obs_origin, -2.039539708420069, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* Observation direction is along negative i_hat basis vector */
    cplex_vec_set( &obs_normal, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* we arbitrarily choose the x_prime_hat_vec and y_prime_hat_vec */
    /* x_prime_hat_vec is < 0, 1, 0 > */
    cplex_vec_set( &x_prime_hat_vec, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);

    /* y_prime_hat_vec is < 0, 0, 1 > */
    cplex_vec_set( &y_prime_hat_vec, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    /* A test point to begin with on the observation plane.
     * However we have tested with slight offset values such as
     * ( 2 ^ -32 ) == 0.00000000023283064365386962890625 */
    x_prime = 1.7;
    y_prime = -2.0;

    printf("INFO : initial x' and y' : ( %-18.14e, %-18.14e )\n",
                                                    x_prime, y_prime );

    /* All of the above allows us to compute a starting point on
     * the observation plane in R3 and in the coordinate system
     * of the observation object.
     *
     * obs_point = x_prime * x_prime_hat_vec
     *           + y_prime * y_prime_hat_vec
     *           + obs_origin
     *
     */
    cplex_vec_scale( tmp,   &x_prime_hat_vec, x_prime );
    cplex_vec_scale( tmp+1, &y_prime_hat_vec, y_prime );

    cplex_vec_add( tmp+2, tmp, tmp+1);
    cplex_vec_add( tmp, tmp+2, &obs_origin );

    cplex_vec_copy( &obs_point, tmp );

    printf("INFO : obs_point = ");
    cplex_vec_print( &obs_point );
    printf("\n");

    /* At this moment we have the observation point and the direction
     * of the plane within obs_normal. What we need is to pass all
     * this to an intercept function that will determine a
     * k index value on the ray trace line.
     *
     * See page 6 of the note on github at :
     *     https://github.com/blastwave/lastmiles/ray_trace/math_notes
     *
     * So clearly we need :
     *
     *     Our L point is obs_point along with a ray_direction.
     *     We shall need the sign_data, object_location and the
     *     semi_major_axi of that ellipsoid.
     *
     *     At the moment for this test we shall use :
     *
     *         sign_data = < 1, 1, 1 >
     *
     *         object_location = < 0, 0, 0 >
     *
     *         semi_major_axi = < 5, 2, 6 >
     *
     *         ray_direct = obs_normal where this must be a
     *                           normalized vector
     *
     * */
    vec_type sign_data, object_location, semi_major_axi, ray_direct;

    /* Within the set of signs Sx, Sy, and Sz we do not care about
     * the complex component and merely want the real. The same
     * may be said for object_location, semi_major_axi and the
     * direction of our ray ray_direct */
    cplex_vec_set( &sign_data, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0);

    /* by default we were using an object at the origin but we can
     * shift around for testing purposes. */
    cplex_vec_set( &object_location, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* Again the diagrams we used had a=5, b=2 and c=6 */
    cplex_vec_set( &semi_major_axi, 5.0, 0.0, 2.0, 0.0, 6.0, 0.0);


    /*****************************************************
     *   WARNING : the ray direction must be normalized  *
     *****************************************************/
    cplex_vec_copy( &ray_direct, &obs_normal );


    intercept_cnt = intercept ( k_val, &sign_data,
                                &object_location, &semi_major_axi,
                                &obs_point, &obs_normal );

    printf ("INFO : we have %i real k values.\n", intercept_cnt);

    printf ("   0 : k_val[0] = ( %-18.14e, %-18.14e )\n",
                                   k_val[0].r, k_val[0].i);

    printf ("   1 : k_val[1] = ( %-18.14e, %-18.14e )\n",
                                   k_val[1].r, k_val[1].i);

    if ( ( intercept_cnt == 2 ) 
         &&
         ( k_val[0].r == k_val[1].r )
         &&
         ( k_val[0].i == k_val[1].i ) ) {

        intercept_cnt = 1;
        printf ("     : only one unique root.\n");

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
         *     hit_point = obs_point + k_root * ray_direct
         */

        if ( intercept_cnt > 0 ) {
            cplex_vec_scale( tmp+3, &ray_direct, k_root );
            cplex_vec_add( &hit_point, &obs_point, tmp+3);

            printf("INFO : hit_point = ");
            cplex_vec_print( &hit_point );
            printf("\n");
        }

    }

    return ( EXIT_SUCCESS );

}

