
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

#include "v.h"

void cplex_add( cplex_type *res, cplex_type *op1, cplex_type *op2 );
void cplex_sub( cplex_type *res, cplex_type *op1, cplex_type *op2 );
void cplex_mult( cplex_type *res, cplex_type *op1, cplex_type *op2 );
void cplex_div( cplex_type *res, cplex_type *op1, cplex_type *op2 );
void cplex_sq( cplex_type *res, cplex_type *op1 );
void cplex_sqrt( cplex_type *res, cplex_type *op1 );
void cplex_cbrt( cplex_type *res, cplex_type *op1 );
void cplex_v_dot( cplex_type *res, vec_type *op1, vec_type *op2 );
void cplex_v_cross( vec_type *res, vec_type *op1, vec_type *op2 );

double cplex_mag( cplex_type *op1 );
double cplex_theta( cplex_type *op1 );

int main ( int argc, char **argv)
{

    cplex_type op1, op2, opr, opr2[3];
    vec_type v[3];
    
/* not using the vectors yet 
    v1->x.r = 1.0;
    v2->y.r = 1.0;
*/

    op1.i = 1.0; op1.r = 0.0;
    op2.i = 1.0; op2.r = 0.0;
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     : op2 = ( %g, %g )\n", op2.r, op2.i);
    cplex_mult( &opr, &op1, &op2 );
    printf("     : opr = op1 * op2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be i^2 = -1\n\n");
    

    op1.r = 1.0;
    op1.i = 0.0;
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     : op2 = ( %g, %g )\n", op2.r, op2.i);
    cplex_mult( &opr, &op1, &op2 );

    printf("     : opr = op1 * op2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be 1i\n\n");
    
    op1.r = 4.0;
    op1.i = 3.0;
    op2.r = 2.0;
    op2.i = -1.0;
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     : op2 = ( %g, %g )\n", op2.r, op2.i);
    cplex_div( &opr, &op1, &op2 );
    printf("dbug : opr = op1 / op2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be 1 + 2i\n\n");
    
    op2.r = -4.0;
    op2.i = -12.0;
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     : op2 = ( %g, %g )\n", op2.r, op2.i);
    cplex_div( &opr, &op1, &op2 );
    printf("dbug : opr = op1 / op2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be -0.325 + 0.225i\n\n");
    
    op1.r = 2.0;
    op1.i = 1.0;
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     :     theta = %16.12e\n\n", cplex_theta( &op1 ) );

    op1.r = 4.0;
    op1.i = 3.0;
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     :     theta = %16.12e\n", cplex_theta( &op1 ) );

    cplex_sq( &opr, &op1 );
    printf("     : opr = op1^2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be 7 + 24i\n");
    printf("     :     magnitude is %g\n", cplex_mag(&opr));
    printf("     :     theta = %16.12e\n", cplex_theta( &opr));

    op1.r = opr.r;
    op1.i = opr.i;
    cplex_sqrt( opr2, &op1 );
    printf("root : 1 is ( %16.12e, %16.12e )\n", opr2[0].r, opr2[0].i);
    printf("root : 2 is ( %16.12e, %16.12e )\n\n", opr2[1].r, opr2[1].i);
    
    /* square root of ( 0, 1 ) */
    printf("dbug : square root test\n");
    op1.r = 0.0;
    op1.i = 1.0;
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     :     theta = %16.12e\n", cplex_theta(&op1) );
    printf("     :     magnitude is %g\n", cplex_mag(&op1));
    cplex_sqrt( opr2, &op1 );
    printf("root : 1 is ( %16.12e, %16.12e )\n", opr2[0].r, opr2[0].i);
    printf("root : 2 is ( %16.12e, %16.12e )\n\n", opr2[1].r, opr2[1].i);

    /* cube roots of ( -11 + 2i ) */
    printf("dbug : cube root test\n");
    op1.r = -11.0;
    op1.i = 2.0;
    printf("     : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     :     theta = %16.12e\n", cplex_theta(&op1) );
    printf("     :     magnitude is %g\n", cplex_mag(&op1));
    
    cplex_cbrt( opr2, &op1 );
    printf("root : 1 is ( %16.12e, %16.12e )\n", opr2[0].r, opr2[0].i);
    printf("root : 2 is ( %16.12e, %16.12e )\n", opr2[1].r, opr2[1].i);
    printf("root : 3 is ( %16.12e, %16.12e )\n\n", opr2[2].r, opr2[2].i);

    printf("Lets test vector dot product\n");
    /* < (1 + 1i), (2 + 2i), (3+3i) >
     *                    . <( -1 - 1i), ( -2 -2i), ( 3 - 3i ) >
     *
     *
     * should be ( 18, -10i ) */

    /* first vector is < (1 + 1i), (2 + 2i), (3+3i) > */
    v[0].x.r = 1.0; v[0].x.i = 1.0;
    v[0].y.r = 2.0; v[0].y.i = 2.0;
    v[0].z.r = 3.0; v[0].z.i = 3.0;
    printf("dbug : v1 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[0].x.r, v[0].x.i,
            v[0].y.r, v[0].y.i,
            v[0].z.r, v[0].z.i );

    /* second vector is <( -1 - 1i), ( -2 -2i), ( 3 - 3i ) > */
    v[1].x.r = -1.0; v[1].x.i = -1.0;
    v[1].y.r = -2.0; v[1].y.i = -2.0;
    v[1].z.r =  3.0; v[1].z.i = -3.0;
    printf("     : v2 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[1].x.r, v[1].x.i,
            v[1].y.r, v[1].y.i,
            v[1].z.r, v[1].z.i );

    cplex_v_dot( &opr, v, v+1);
    printf("     : dot product = ( %g, %g )\n\n", opr.r, opr.i);


    /* tw0st3p says < 12 + 12im, -6 - 6im, 0 + 0im > */
    cplex_v_cross( v+2, v, v+1 );
    printf("     : v1 cross v2 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[2].x.r, v[2].x.i,
            v[2].y.r, v[2].y.i,
            v[2].z.r, v[2].z.i );




    return ( EXIT_SUCCESS );

}

