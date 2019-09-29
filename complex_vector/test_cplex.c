
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

cplex_type * cplex_add( cplex_type *op1, cplex_type *op2 );
cplex_type * cplex_sub( cplex_type *op1, cplex_type *op2 );
cplex_type * cplex_mult( cplex_type *op1, cplex_type *op2 );
cplex_type * cplex_div( cplex_type *op1, cplex_type *op2 );
cplex_type * cplex_sq( cplex_type *op1 );
cplex_type * cplex_sqrt( cplex_type *op1 );
cplex_type * cplex_cubert( cplex_type *op1 );
cplex_type * cplex_v_dot( vec_type *op1, vec_type *op2 );
vec_type * cplex_v_cross( vec_type *op1, vec_type *op2 );

double cplex_mag( cplex_type *op1 );
double cplex_theta( cplex_type *op1 );

int main ( int argc, char **argv)
{

    cplex_type *op1, *op2, *opr;
    vec_type *v = calloc ( (size_t)3, sizeof(vec_type) );
    op1 = calloc ( (size_t)1, sizeof(cplex_type) );
    op2 = calloc ( (size_t)1, sizeof(cplex_type) );

/* not using the vectors yet 
    v1->x.r = 1.0;
    v2->y.r = 1.0;
*/

    op1->i = 1.0;
    op2->i = 1.0;
    printf("dbug : op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     : op2 = ( %g, %g )\n", op2->r, op2->i);
    opr = cplex_mult( op1, op2 );
    printf("     : opr = op1 * op2 = ( %g, %g )\n", opr->r, opr->i);
    printf("     :     should be i^2 = -1\n\n");
    free(opr);

    op1->r = 1.0;
    op1->i = 0.0;
    printf("dbug : op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     : op2 = ( %g, %g )\n", op2->r, op2->i);
    opr = cplex_mult( op1, op2 );

    printf("     : opr = op1 * op2 = ( %g, %g )\n", opr->r, opr->i);
    printf("     :     should be 1i\n\n");
    free(opr);

    op1->r = 4.0;
    op1->i = 3.0;
    op2->r = 2.0;
    op2->i = -1.0;
    printf("dbug : op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     : op2 = ( %g, %g )\n", op2->r, op2->i);
    opr = cplex_div( op1, op2 );
    printf("dbug : opr = op1 / op2 = ( %g, %g )\n", opr->r, opr->i);
    printf("     :     should be 1 + 2i\n\n");
    free(opr);

    op2->r = -4.0;
    op2->i = -12.0;
    printf("dbug : op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     : op2 = ( %g, %g )\n", op2->r, op2->i);
    opr = cplex_div( op1, op2 );
    printf("dbug : opr = op1 / op2 = ( %g, %g )\n", opr->r, opr->i);
    printf("     :     should be -0.325 + 0.225i\n\n");
    free(opr);

    op1->r = 2.0;
    op1->i = 1.0;
    printf("dbug : op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     :     theta = %16.12e\n\n", cplex_theta( op1 ) );

    op1->r = 4.0;
    op1->i = 3.0;
    printf("dbug : op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     :     theta = %16.12e\n", cplex_theta( op1 ) );

    opr = cplex_sq( op1 );
    printf("     : opr = op1^2 = ( %g, %g )\n", opr->r, opr->i);
    printf("     :     should be 7 + 24i\n");
    printf("     :     magnitude is %g\n", cplex_mag(opr));
    printf("     :     theta = %16.12e\n", cplex_theta( opr));

    op1->r = opr->r;
    op1->i = opr->i;
    free(opr);
    opr = cplex_sqrt( op1 );
    printf("root : 1 is ( %16.12e, %16.12e )\n", opr->r, opr->i);
    printf("root : 2 is ( %16.12e, %16.12e )\n\n", (opr+1)->r, (opr+1)->i);
    free(opr);

    /* square root of ( 0, 1 ) */
    printf("dbug : square root test\n");
    op1->r = 0.0;
    op1->i = 1.0;
    printf("dbug : op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     :     theta = %16.12e\n", cplex_theta(op1) );
    printf("     :     magnitude is %g\n", cplex_mag(op1));
    opr = cplex_sqrt( op1 );
    printf("root : 1 is ( %16.12e, %16.12e )\n", opr->r, opr->i);
    printf("root : 2 is ( %16.12e, %16.12e )\n\n", (opr+1)->r, (opr+1)->i);
    free(opr);

    /* cube roots of ( -11 + 2i ) */
    printf("dbug : cube root test\n");
    op1->r = -11.0;
    op1->i = 2.0;
    printf("     : op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     :     theta = %16.12e\n", cplex_theta(op1) );
    printf("     :     magnitude is %g\n", cplex_mag(op1));
    opr = cplex_cubert( op1 );
    printf("root : 1 is ( %16.12e, %16.12e )\n", opr->r, opr->i);
    printf("root : 2 is ( %16.12e, %16.12e )\n", (opr+1)->r, (opr+1)->i);
    printf("root : 3 is ( %16.12e, %16.12e )\n\n", (opr+2)->r, (opr+2)->i);
    free(opr);

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

    opr = cplex_v_dot( v, v+1 );
    printf("     : dot product = ( %g, %g )\n\n", opr->r, opr->i);


    /* tw0st3p says < 3 + 14i, 6 - 15i, -1 + 1i > */
    v[2] = *cplex_v_cross(  v, v+1 );
    printf("     : v1 cross v2 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[2].x.r, v[2].x.i,
            v[2].y.r, v[2].y.i,
            v[2].z.r, v[2].z.i );




    free(opr);
    free(v);
    free(op1);
    free(op2);
    return ( EXIT_SUCCESS );

}

