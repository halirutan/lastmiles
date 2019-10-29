
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

/* we shall need some sort of function to do the heavy lifting and it
 * should really return the actual points of intersection. However for
 * a quick and dirty prototype of the basic ideas we shall just return
 * the solutions to the complex cooefficient quadratic */
int intersect( cplex_type res[2],
                vec_type *sign,
                vec_type *loc,
                vec_type *axi,
                vec_type *obs_p,
                vec_type *obs_v );

int main ( int argc, char **argv)
{

    int intersect_cnt = 0;
    cplex_type intersections[2];

    vec_type tmp[3];

    /* We must first define where our observation plane is in R3
     * as a point and a normal direction. The obs_normal direction
     * will be the direction of all rays that we trace. */
    vec_type obs_origin, obs_normal;

    /* The observation plane has its own coordinate system and
     * thus we have x_prime_vec and y_prime_vec as ortogonal
     * and normalized vectors */
    vec_type x_prime_vec, y_prime_vec;

    /* To locate a given point on the observation plane we will
     * need scalar distances away from the observation plane
     * center along the directions x_prime_vec and y_prime_vec */
    double x_prime, y_prime;

    /* All of the above merely allows us to compute a starting
     * point for our ray to trace along the direction of the
     * vector obs_normal. */
    vec_type obs_point;

    /* Test case will be an observation plane at ( 12, 0, 0 ) */
    cplex_vec_set( &obs_origin, 12.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* Observation direction is along negative i_hat basis vector */
    cplex_vec_set( &obs_normal, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* we arbitrarily choose the x_prime_vec and y_prime_vec */
    /* x_prime_vec is < 0, 1, 0 > */
    cplex_vec_set( &x_prime_vec, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);

    /* y_prime_vec is < 0, 0, 1 > */
    cplex_vec_set( &y_prime_vec, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    /* A test point to begin with on the observation plane */
    x_prime = 1.7;
    y_prime = -2.0;

    /* try for a single result with a glance intercept */
    x_prime = 2.0 + 0.003906250;
    x_prime = 2.0;
    y_prime = 0.0;

    /* All of the above allows us to compute a starting point on
     * the observation plane in R3 and in the coordinate system
     * of the observation object.
     *
     * obs_point = x_prime * x_prime_vec
     *           + y_prime * y_prime_vec
     *           + obs_origin
     *
     */
    cplex_vec_scale( tmp,   &x_prime_vec, x_prime );
    cplex_vec_scale( tmp+1, &y_prime_vec, y_prime );

    cplex_vec_add( tmp+2, tmp, tmp+1);
    cplex_vec_add( tmp, tmp+2, &obs_origin );

    cplex_vec_copy( &obs_point, tmp );

    printf("INFO : obs_point = ");
    cplex_vec_print( &obs_point );
    printf("\n");


    /* At this moment we have the observation point and the direction
     * of the plane within obs_normal. What we need is to pass all
     * this to an object_intercept function that will determine a
     * k index value on the ray trace line.
     *
     * See page 6 of the note on github at :
     *     https://github.com/blastwave/lastmiles/
     *            rtrace/math_notes/notes_006.png
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
    cplex_vec_set( &sign_data, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    cplex_vec_set( &object_location, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    cplex_vec_set( &semi_major_axi, 5.0, 0.0, 2.0, 0.0, 6.0, 0.0);
    cplex_vec_copy( &ray_direct, &obs_normal );


    intersect_cnt = intersect ( intersections, &sign_data,
                                &object_location, &semi_major_axi,
                                &obs_point, &obs_normal );

    printf ("INFO : we have %i intersection points.\n", intersect_cnt);


    return ( EXIT_SUCCESS );

}

int intersect( cplex_type res[2],
                vec_type *sign,
                vec_type *loc,
                vec_type *axi,
                vec_type *obs_p,
                vec_type *obs_v )
{

    /* computer the intersection points between our line and the
     * analytic surface described and return an integer count
     * of the real intersections. */

    vec_type tmp[9];
    cplex_type c_tmp[18];
    cplex_type quad_res[2];

    /* we shall form the complex cooefficients of a quadratic */
    cplex_type A, B, C;

    printf("\n---------+---------+---------+---------+---------+");
    printf("---------+---------+--\n");


    /* create a tmp vector of the semi_major_axi data to be used
     * in dot product calcs wherein we will have
     *
     *     < b^2 * c^2, a^2 * c^2, a^2 * b^2 >
     *
     * */
    tmp[0].x.i = 0.0;
    tmp[0].y.i = 0.0;
    tmp[0].z.i = 0.0;

    tmp[0].x.r = axi->y.r * axi->y.r * axi->z.r * axi->z.r;
    tmp[0].y.r = axi->x.r * axi->x.r * axi->z.r * axi->z.r;
    tmp[0].z.r = axi->x.r * axi->x.r * axi->y.r * axi->y.r;

    printf("\n\nINFO : intermediate axi vector = ");
    cplex_vec_print( tmp );
    printf("\n\n");

    /* product of the sign data with the intermediate axi vector
     * in tmp[0] to form a factor of our complex cooefficient A */

    tmp[1].x.i = 0.0;
    tmp[1].y.i = 0.0;
    tmp[1].z.i = 0.0;
    tmp[1].x.r = sign->x.r * tmp[0].x.r;
    tmp[1].y.r = sign->y.r * tmp[0].y.r;
    tmp[1].z.r = sign->z.r * tmp[0].z.r;

    /* another factor of A is the complex components of the ray
     * direction squared. */
    cplex_mult( &((tmp+2)->x), &(obs_v->x), &(obs_v->x) );
    cplex_mult( &((tmp+2)->y), &(obs_v->y), &(obs_v->y) );
    cplex_mult( &((tmp+2)->z), &(obs_v->z), &(obs_v->z) );
    printf("dbug : Rx^2 = ( %g, %g )\n", tmp[2].x.r, tmp[2].x.i);
    printf("dbug : Ry^2 = ( %g, %g )\n", tmp[2].y.r, tmp[2].y.i);
    printf("dbug : Rz^2 = ( %g, %g )\n", tmp[2].z.r, tmp[2].z.i);

    /* now we form the first complex cooefficient from the dot
     * product of tmp[0] and tmp[2] to form A */
    cplex_vec_dot( &A, tmp, tmp+2 );
    printf("\n\nINFO : A = ( %g, %g )\n\n", A.r, A.i );


    /* moving onwards to complex cooefficient B wherein we need
     * multiple intermediate calculations */
    cplex_sub( c_tmp, &(obs_p->x), &(loc->x) );
    cplex_sub( c_tmp+1, &(obs_p->y), &(loc->y) );
    cplex_sub( c_tmp+2, &(obs_p->z), &(loc->z) );

    printf("dbug : Lx - Px = ( %g, %g )\n", c_tmp[0].r, c_tmp[0].i);
    printf("dbug : Ly - Py = ( %g, %g )\n", c_tmp[1].r, c_tmp[1].i);
    printf("dbug : Lz - Pz = ( %g, %g )\n", c_tmp[2].r, c_tmp[2].i);

    cplex_vec_set( tmp+3, c_tmp[0].r, c_tmp[0].i,
                          c_tmp[1].r, c_tmp[1].i,
                          c_tmp[2].r, c_tmp[2].i);

    printf("INFO : L - P = ");
    cplex_vec_print( tmp+3 );
    printf("\n\n");

    /* now multiply each component of tmp[3] by the obs_v
     * components */
    cplex_mult( c_tmp+3, &(obs_v->x), &(tmp[3]).x );
    cplex_mult( c_tmp+4, &(obs_v->y), &(tmp[3]).y );
    cplex_mult( c_tmp+5, &(obs_v->z), &(tmp[3]).z );

    cplex_vec_set( tmp+4, c_tmp[3].r, c_tmp[3].i,
                          c_tmp[4].r, c_tmp[4].i,
                          c_tmp[5].r, c_tmp[5].i);

    printf("INFO : R * ( L - P ) = ");
    cplex_vec_print( tmp+4 );
    printf("\n\n");

    /* dot product of the intermediate sign vec now */

    cplex_vec_dot( c_tmp+6, tmp, tmp+4 );
    c_tmp[7].r = 2.0; c_tmp[7].i = 0.0;
    cplex_mult( &B, c_tmp+6, c_tmp+7 );

    printf("\n\nINFO : B = ( %g, %g )\n\n", B.r, B.i );

    /* we first need to create (L-P) component squares */
    cplex_mult( c_tmp+8,  c_tmp,   c_tmp );
    cplex_mult( c_tmp+9,  c_tmp+1, c_tmp+1 );
    cplex_mult( c_tmp+10, c_tmp+2, c_tmp+2 );

    cplex_vec_set( tmp+5, c_tmp[8].r,  c_tmp[8].i,
                          c_tmp[9].r,  c_tmp[9].i,
                          c_tmp[10].r, c_tmp[10].i);

    printf("INFO : ( L - P )^2 = ");
    cplex_vec_print( tmp+5 );
    printf("\n\n");

    /* now the dot product again with the intermediate signs */
    cplex_vec_dot( c_tmp+11, tmp, tmp+5 );
    printf("\n\nINFO : <sign bits> dot < L-P bits > = ( %g, %g )\n",
                                             c_tmp[11].r, c_tmp[11].i );


    /* now create a^2 * b^2 * c^2 */
    cplex_mult( c_tmp+12, &(axi->x), &(axi->x));
    cplex_mult( c_tmp+13, &(axi->y), &(axi->y));
    cplex_mult( c_tmp+14, &(axi->z), &(axi->z));
    cplex_mult( c_tmp+15, c_tmp+12, c_tmp+13);
    cplex_mult( c_tmp+16, c_tmp+15, c_tmp+14);

    printf("\n\nINFO : a^2 * b^2 * c^2 = ( %g, %g )\n",
                                              c_tmp[16].r, c_tmp[16].i );

    cplex_sub( &C, c_tmp+11, c_tmp+16);

    printf("\n\nINFO : C = ( %g, %g )\n\n", C.r, C.i );

    /* We shall get the solutions to a complex quadratic polynomial.
     * see https://en.wikipedia.org/wiki/Complex_quadratic_polynomial */
    cplex_quadratic( quad_res, &A, &B, &C );

    printf("Quadratic result 1 = ( %16.12e, %16.12e )\n",
                                          quad_res[0].r, quad_res[0].i);

    printf("          result 2 = ( %16.12e, %16.12e )\n\n",
                                          quad_res[1].r, quad_res[1].i);

    printf("\n---------+---------+---------+---------+---------+");
    printf("---------+---------+--\n");

    /* Did we get only complex results? */
    if (    ( fabs(quad_res[0].i) > 0.0 )
         || ( fabs(quad_res[1].i) > 0.0 ) ) {

        printf("DBUG : no real results.\n");
        return ( 0 );

    }

    /* We should check if these two results that were returned are
     * near equal to within the bounds of our RT_EPSILON value */
    if ( ( fabs( quad_res[0].r - quad_res[1].r ) < RT_EPSILON ) &&
         ( fabs( quad_res[0].i - quad_res[1].i ) < RT_EPSILON ) ) {

        printf("DBUG : both results are equal within RT_EPSILON.\n");

        res[0].r = quad_res[0].r;

        /* why bother to return anything here other than zero for
         * the imaginary component? */
        res[0].i = quad_res[0].i;
        return (1);

    } else {

        res[0].r = quad_res[0].r;
        res[0].i = quad_res[0].i;
        res[1].r = quad_res[1].r;
        res[1].i = quad_res[1].i;
        return (2);

    }

}

