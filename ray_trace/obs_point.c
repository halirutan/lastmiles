
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
    cplex_type c_tmp[2];
    vec_type grad;
    int k, intercept_cnt = -1;
    int intercept_point_flag = -1;

    /* https://github.com/blastwave/lastmiles/blob/master/ray_trace/
     *                                  math_notes/notes_rt_math_006.png
     *
     * per our diagrams we are just solving for k in the complex
     * coefficient quadratic */
    cplex_type k_val[2];

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

    /* We must first define where our observation plane is in R3
     * as a point and a normal direction. The obs_normal direction
     * will be the direction of all rays that we trace. */
    vec_type obs_origin, obs_normal;

    /* The observation plane has its own coordinate system and
     * thus we have x_prime_hat_vec and y_prime_hat_vec as ortogonal
     * and normalized vectors. See notes_rt_math_004_m.png */
    vec_type x_prime_hat_vec, y_prime_hat_vec;

    /* To locate a given point L_0 on the observation plane we will
     * need scalar distances away from the observation plane
     * center along the directions x_prime_hat_vec and 
     * y_prime_hat_vec */
    double x_prime, y_prime;

    /* All of the above merely allows us to compute a starting
     * point for our ray to trace along the direction of the
     * vector obs_normal. In the diagrams this may be called L_0
     * on the observation plane. */
    vec_type obs_point;

    /* Test case will be an observation plane at ( 12, 0, 0 ) */
    cplex_vec_set( &obs_origin, 12.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* Observation direction is along negative i_hat basis vector */
    cplex_vec_set( &obs_normal, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* we arbitrarily choose the x_prime_hat_vec and y_prime_hat_vec */
    /* x_prime_hat_vec is < 0, 1, 0 > */
    /* y_prime_hat_vec is < 0, 0, 1 > */
    cplex_vec_set( &x_prime_hat_vec, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
    cplex_vec_set( &y_prime_hat_vec, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    /* A test point to begin with on the observation plane.
     */
    x_prime = 1.7;
    y_prime = -2.0;

    x_prime = 2.0;
    y_prime = 0.0;

    /* try an offset of 2^(-48)
     *    double tiny_delta = pow( 2.0, -48.0);
     * 3.5527136788005009293556213378906250e-15 */

    printf("INFO : initial x' and y' : ( %-18.14e, %-18.14e )\n\n",
                                                    x_prime, y_prime );

    /* All of the above allows us to compute a starting point on
     * the observation plane in R3 and in the coordinate system
     * of the observation object.  This is also called L_0 in the
     * various diagrams.
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

    printf("INFO : L obs_point = ");
    cplex_vec_print( &obs_point );
    printf("\n\n");

    /* At this moment we have the observation point and the direction
     * of the plane within obs_normal. What we need is to pass all
     * this to an intercept function that will determine a
     * k index value on the ray trace line.
     *
     * See page 6 of the notes on github at :
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
     */
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

    /* Note that the ray direction must be normalized */
    cplex_vec_normalize( &ray_direct, &obs_normal );

    printf("INFO : ray_direct = ");
    cplex_vec_print( &ray_direct );
    printf("\n\n");

    /* Now we call our intercept function to do most of the work */
    /* TODO fix up the intercept func to return 1 root count if in
     * fact there is only a single real root and not just two 
     * precisely identical real roots. */
    intercept_cnt = intercept ( k_val, &sign_data,
                                &object_location, &semi_major_axi,
                                &obs_point, &obs_normal );

    if ( intercept_cnt > 0 ) {

        intercept_point_flag = intercept_point( &hit_point,
                                                intercept_cnt,
                                                &k_val[0],
                                                &obs_point,
                                                &ray_direct);

        if ( intercept_point_flag == 0 ) {
            printf("INFO : H hit_point = ");
            cplex_vec_print( &hit_point );
            printf("\n");

            gradient( &grad,
                      &sign_data, &object_location,
                      &semi_major_axi, &hit_point );

            printf("\n------------------------------------------\n");
            printf("INFO : N gradient = ");
            cplex_vec_print( &grad );
            printf("\n\n");

            /* we should attempt to compute the T tangent vector in
             * the plane of incidence if and only if N is not parallel
             * to the incident ray_direct */

            /* just for shits and sniggles lets do both the dot and
             * the cross products and see what we get. */

            cplex_vec_dot( c_tmp, &ray_direct, &grad );
            printf("INFO : ray_direct dot grad = ( %16.12e, %16.12e )",
                                                  c_tmp->r, c_tmp->i );

            cplex_vec_cross( tmp+3, &ray_direct, &grad );
            printf("\n\nINFO : ray_direct X grad = ");
            cplex_vec_print( tmp+3 );
            printf("\n\n");

        } else {
            printf("INFO : no intercept point\n");
        }

    } else {
        printf("INFO : no real solutions\n");
    }

    return ( EXIT_SUCCESS );

}

