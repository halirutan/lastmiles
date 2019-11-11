
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

/* A quick and dirty prototype of the basic ideas where we shall just
 * return the solutions to the complex cooefficient quadratic */
int intercept( cplex_type res[2],
                vec_type *sign,
                vec_type *loc,
                vec_type *axi,
                vec_type *obs_p,
                vec_type *obs_v );

int main ( int argc, char **argv)
{

    int k, intercept_cnt = 0;

    /* per our diagrams we are just solving for k in the complex
     * cooeficient quadratic */
    cplex_type k_val[2];

    vec_type tmp[3];

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

    /* sanity check with the observation plane intersecting the 
     * object */
    cplex_vec_set( &obs_origin, 3.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* Observation direction is along negative i_hat basis vector */
    cplex_vec_set( &obs_normal, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* we arbitrarily choose the x_prime_hat_vec and y_prime_hat_vec */
    /* x_prime_hat_vec is < 0, 1, 0 > */
    cplex_vec_set( &x_prime_hat_vec, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);

    /* y_prime_hat_vec is < 0, 0, 1 > */
    cplex_vec_set( &y_prime_hat_vec, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    /* A test point to begin with on the observation plane.
     * However we have tested with slight offset values such as
     * ( 2 ^ -32 ) */
    x_prime = 1.7;
    y_prime = -2.0;


    /* sanity check */
    x_prime = 0.0;
    y_prime = 0.0;

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
    cplex_vec_copy( &ray_direct, &obs_normal );


    intercept_cnt = intercept ( k_val, &sign_data,
                                &object_location, &semi_major_axi,
                                &obs_point, &obs_normal );

    printf ("INFO : we have %i real k values.\n", intercept_cnt);

    printf ("   0 : k_val[0] = ( %16.12e, %16.12e )\n",
                                   k_val[0].r, k_val[0].i);

    printf ("   1 : k_val[1] = ( %16.12e, %16.12e )\n",
                                   k_val[1].r, k_val[1].i);

    return ( EXIT_SUCCESS );

}

