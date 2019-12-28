
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

    vec_type tmp[9];
    cplex_type c_tmp[3];
    vec_type grad, reflect;
    double vec_T_mag, theta_i;
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

    printf("\nINFO : viewport O obs_origin = ");
    printf("< %16.12e, %16.12e, %16.12e >\n",
                      obs_origin.x.r, obs_origin.y.r, obs_origin.z.r );

    /* Observation direction is along negative i_hat basis vector */
    cplex_vec_set( &obs_normal, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    printf("\nINFO : viewport direction obs_normal = ");
    printf("< %16.12e, %16.12e, %16.12e >\n",
                      obs_normal.x.r, obs_normal.y.r, obs_normal.z.r );

    /* we arbitrarily choose the x_prime_hat_vec and y_prime_hat_vec */
    /* x_prime_hat_vec is < 0, 1, 0 > */
    /* y_prime_hat_vec is < 0, 0, 1 > */
    cplex_vec_set( &x_prime_hat_vec, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
    cplex_vec_set( &y_prime_hat_vec, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    printf("     : viewport x_prime basis vector = ");
    printf("< %16.12e, %16.12e, %16.12e >\n",
       x_prime_hat_vec.x.r, x_prime_hat_vec.y.r, x_prime_hat_vec.z.r );

    printf("     : viewport y_prime basis vector = ");
    printf("< %16.12e, %16.12e, %16.12e >\n",
       y_prime_hat_vec.x.r, y_prime_hat_vec.y.r, y_prime_hat_vec.z.r );


    /* A test point to begin with on the observation plane.
     *
     *   x_prime = 1.7;
     *   y_prime = -2.0;
     *
     *
     * x_prime = pow( 2.0, -24.0);
     * double tiny_delta = pow( 2.0, -32.0);
     * printf("\nINFO : tiny_delta offset is %-36.32e\n\n",
     *                                            tiny_delta );
     */


    /* USE A TEST RAY */
    x_prime = ( 1.0 / sqrt(2.0) ) - pow( 2.0, -8.0);
    y_prime = ( 1.0 / sqrt(2.0) );
    printf("\nNOTE : **** inside \"1/sqrt(2) diagonal\" of test sphere\n\n");




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

    printf("\nINFO : L obs_point = ");
    printf("< %16.12e, %16.12e, %16.12e >\n",
                      obs_point.x.r, obs_point.y.r, obs_point.z.r );
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
    /* cplex_vec_set( &semi_major_axi, 5.0, 0.0, 2.0, 0.0, 6.0, 0.0); */





    /* USE A TEST SPHERE */
    cplex_vec_set( &semi_major_axi, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0);


    printf("DBUG : Note we are using a test sphere radius = 1\n\n");





    /* Note that the ray direction must be normalized */
    cplex_vec_normalize( &ray_direct, &obs_normal );

    printf("INFO : ray_direct = ");
    printf("< %16.12e, %16.12e, %16.12e >\n",
                      ray_direct.x.r, ray_direct.y.r, ray_direct.z.r );
    printf("\n\n");

    /* Now we call our intercept function to do most of the work */
    /* TODO fix up the intercept func to return 1 root count if in
     * fact there is only a single real root and not just two 
     * precisely identical real roots. */
    intercept_cnt = intercept ( k_val, &sign_data,
                                &object_location, &semi_major_axi,
                                &obs_point, &obs_normal );

    printf("intercept_cnt = %i\n", intercept_cnt );
    printf("\nINFO : k_val[0] = ( %16.12e, %16.12e )\n",
                           k_val[0].r, k_val[0].i );
    printf("     : k_val[1] = ( %16.12e, %16.12e )\n",
                           k_val[1].r, k_val[1].i );

    if ( intercept_cnt > 0 ) {

        intercept_point_flag = intercept_point( &hit_point,
                                                intercept_cnt,
                                                &k_val[0],
                                                &obs_point,
                                                &ray_direct);

        if ( intercept_point_flag == 0 ) {
             printf("\nDBUG : We have a good intercept point\n");
        }

        if ( intercept_point_flag == 0 ) {
            printf("INFO : H hit_point = ");
            printf("< %16.12e, %16.12e, %16.12e >\n",
                      hit_point.x.r, hit_point.y.r, hit_point.z.r );
            printf("\n");

            gradient( &grad,
                      &sign_data, &object_location,
                      &semi_major_axi, &hit_point );

            printf("\n------------------------------------------\n");
            printf("INFO : N gradient = ");
            printf("< %16.12e, %16.12e, %16.12e >\n",
                              grad.x.r, grad.y.r, grad.z.r );

            /* we should attempt to compute the T tangent vector in
             * the plane of incidence if and only if N is not parallel
             * to the incident ray_direct. We use -Ri for our vector
             * due to right-hand rule of the supposedly physical 
             * universe. So T == -Ri X N here. */
            cplex_vec_scale( tmp+3, &ray_direct, -1.0 );
            printf("\nINFO : -Ri = < %16.12e, %16.12e, %16.12e >\n",
                               tmp[3].x.r, tmp[3].y.r, tmp[3].z.r );

            /* what is the angle of incidence ? */
            cplex_vec_dot( c_tmp, &grad, tmp+3);
            if ( !(c_tmp->i == 0.0) ) {
                /* this should never happen */
                fprintf(stderr,"FAIL : bizarre complex dot product");
                fprintf(stderr," dot( N, -Ri )\n");
                fprintf(stderr,"     :  = ( %16.12e, %16.12e )\n",
                                                   c_tmp->r, c_tmp->i );
                fprintf(stderr,"BAIL : we are done.\n\n");
                return ( EXIT_FAILURE );
            } else {
                printf("     : dot( N, -Ri ) = %16.12e\n", c_tmp->r );
            }
            theta_i = acos(c_tmp->r);
            printf("     : theta_i = %16.12e\n", theta_i );
            printf("     :         = %16.12e degrees\n", theta_i * 180.0/M_PI );
            if ( fabs(theta_i) < RT_ANGLE_EPSILON ) {
                if ( theta_i == 0.0 ) {
                    fprintf(stderr,"WARN : theta_i is zero!\n");
                } else {
                    fprintf(stderr,"WARN : theta_i too small.\n");
                }
            }

            cplex_vec_cross( tmp+4, tmp+3, &grad );
            cplex_vec_normalize( &ray_direct, &obs_normal );
            printf("\n\nINFO : -Ri X N = ");
            printf("< %16.12e, %16.12e, %16.12e >\n",
                               tmp[4].x.r, tmp[4].y.r, tmp[4].z.r );

            vec_T_mag = cplex_vec_mag( tmp+4 );
            if ( ( vec_T_mag < RT_EPSILON )
                    ||
                 ( fabs(theta_i) < RT_ANGLE_EPSILON ) ) {

                if ( vec_T_mag == 0.0 ) {
                    printf("WARN : null vector result from -Ri x N\n");
                } else {
                    printf("WARN : tiny vector result from -Ri x N\n");
                }

                /* At this point there will be no solution using Cramer's
                 * method as the denominator matrix will be determinant
                 * of zero. However geometrically we may say that the
                 * reflected vector is the same as the normal N. */
                 cplex_vec_copy( &reflect, &grad );
                 printf("INFO : Rr = < %16.12e, %16.12e, %16.12e > ??\n",
                                 reflect.x.r, reflect.y.r, reflect.z.r);
                 printf("     : this is just the surface gradient N\n");

            } else {

                /* Cramer's Method and may as well embrace it */
                cplex_vec_normalize( tmp+5, tmp+4 );
                printf("     : this is the plane of incidence tangent\n");
                printf("     : T = ");
                printf("< %16.12e, %16.12e, %16.12e >\n",
                               tmp[5].x.r, tmp[5].y.r, tmp[5].z.r );
                printf("     : Cramer\'s Method needed from here\n");

/*

we did all this before ...

     *
     *  Solve for A,B,C where
     *  ( 0.5 - i ) * A  - 2 * B - 3 * C = ( 1 + 0.5i ),
     *  4 * A + 5 * B + 6 * C = ( 2 + 0.75i ),
     *  7 * A + ( -2 + 4i ) * B + 9 * C = ( 3 -0.25i ).

    printf("\n\nCramers rule test with existing matrix and\n");
    rh_col.x.r = 1.0; rh_col.x.i = 0.5;
    rh_col.y.r = 2.0; rh_col.y.i = 0.75;
    rh_col.z.r = 3.0; rh_col.z.i = -0.25;
    printf("rh_col = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
        rh_col.x.r, rh_col.x.i,
        rh_col.y.r, rh_col.y.i,
        rh_col.z.r, rh_col.z.i);

    status = cplex_cramer( &res_vec, &v[0], &v[1], &v[2], &rh_col );
    if ( status != 0 ) {
        printf("dbug : There is no valid solution.\n");
    } else {
        printf("     : result col = < ( %16.12e, %16.12e ),\n",
                    res_vec.x.r, res_vec.x.i );
        printf("                      ( %16.12e, %16.12e ),\n",
                    res_vec.y.r, res_vec.y.i );
        printf("                      ( %16.12e, %16.12e ) >\n\n",
                    res_vec.z.r, res_vec.z.i);
    }


    we need a left hand 3x3 matrix of rows T, N, -Ri

    T is in tmp[5]
    N is in grad
    -Ri is in  tmp[3]

    on right hand column we need 0,  Cos ( theta_i )  and cos ( 2 x theta_i )

    theta_i = acos ( dot( -Ri, N ) ) 

    so really we need rt hand column 0, dot( -Ri, N ), 2 * dot( -Ri, N )

*/



            }

        } else {
            printf("INFO : no intercept point\n");
        }

    } else {
        printf("INFO : no real solutions\n");
    }

    return ( EXIT_SUCCESS );

}

