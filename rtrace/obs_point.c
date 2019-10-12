
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
#include <complex.h>

#include "v.h"

int main ( int argc, char **argv)
{

    /* We must first define where our observation plane is in R3
     * as a point and a normal direction. The obs_normal direction 
     * will be the direction of all rays that we trace. */
    cplex_vec obs_origin, obs_normal;

    /* The observation plane has its own coordinate system and 
     * thus we have x_prime_vec and y_prime_vec as ortogonal
     * and normalized vectors */
    cplex_vec x_prime_vec, y_prime_vec;

    /* To locate a given point on the observation plane we will
     * need scalar distances away from the observation plane
     * center along the directions x_prime_vec and y_prime_vec */
    double x_prime, y_prime;

    /* All of the above merely allows us to compute a starting
     * point for our ray to trace along the direction of the
     * vector obs_normal. */
    cplex_vec obs_point;


    /* Test case wwill be an observation plane at ( 12, 0, 0 ) */
    obs_origin.x.r = 12.0; obs_origin.x.i = 0.0;
    obs_origin.y.r = 0.0;  obs_origin.y.i = 0.0;
    obs_origin.z.r = 0.0;  obs_origin.z.i = 0.0;

    /* Observation direction is along negative i_hat basis vector */
    obs_normal.x.r = -1.0; obs_normal.x.i = 0.0;
    obs_normal.y.r =  0.0; obs_normal.y.i = 0.0;
    obs_normal.z.r =  0.0; obs_normal.z.i = 0.0;

    /* we arbitrarily choose the x_prime_vec and y_prime_vec */

    /* x_prime_vec is < 0, 1, 0 > */
    x_prime_vec.x.r = 0.0; x_prime_vec.x.i = 0.0;
    x_prime_vec.y.r = 1.0; x_prime_vec.y.i = 0.0;
    x_prime_vec.z.r = 0.0; x_prime_vec.z.i = 0.0;

    /* y_prime_vec is < 0, 0, 1 > */
    y_prime_vec.x.r = 0.0; y_prime_vec.x.i = 0.0;
    y_prime_vec.y.r = 0.0; y_prime_vec.y.i = 0.0;
    y_prime_vec.z.r = 1.0; y_prime_vec.z.i = 0.0;


    /* A test point to begin with on the observation plane */
    x_prime = 1.7;
    y_prime = -2.0;

    /* All of the above allows us to compute a starting point on
     * the observation plane in R3 and in the coordinate system
     * of the observation object.
     *
     * obs_point = x_prime * x_prime_vec 
     *           + y_prime * y_prime_vec
     *           + obs_origin
     *
     */







    /* Again thanks to cool data from Traviss we have some results
     * for a normalized vector v[0] thus :
     *
     * Thanks to Julia we see : 
     *
     * < ( 0.1889822365046136 + 0.1889822365046136im ),
     *   ( 0.3779644730092272 + 0.3779644730092272im ),
     *   ( 0.5669467095138407 + 0.5669467095138407im ) >
     *
    printf("Lets test vector normalization of v[0] as described.\n");
    printf("    : function call cplex_vec_normalize() returns %i\n",
            cplex_vec_normalize( (v+3), v ) );

    printf("    : |v[0]| = ");
    printf(" < ( %16.12e, %16.12e ),\n", v[3].x.r, v[3].x.i );
    printf("   ( %16.12e, %16.12e ),\n", v[3].y.r, v[3].y.i );
    printf("   ( %16.12e, %16.12e ) >\n", v[3].z.r, v[3].z.i );
    printf("Should be < ( 0.1889822365046 + 0.1889822365046 i ),\n");
    printf("            ( 0.3779644730092 + 0.3779644730092 i ),\n");
    printf("            ( 0.5669467095138 + 0.5669467095138 i )>\n\n");
    */


    return ( EXIT_SUCCESS );

}

