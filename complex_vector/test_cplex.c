
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
double cplex_mag( cplex_type *op1 );
double cplex_theta( cplex_type *op1 );

int main ( int argc, char **argv)
{

    cplex_type *op1, *op2, *opr;

/* these are noop test vectors
    vec_t *v1, *v2;
    v1 = calloc ( 1, sizeof(vec_t) );
    v2 = calloc ( 1, sizeof(vec_t) );
*/

    op1 = calloc ( 1, sizeof(cplex_type) );
    op2 = calloc ( 1, sizeof(cplex_type) );

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
    op1->r = 0.0;
    op1->i = 1.0;
    printf("dbug : op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     :     theta = %16.12e\n", cplex_theta(op1) );
    printf("     :     magnitude is %g\n", cplex_mag(op1));
    opr = cplex_sqrt( op1 );
    printf("root : 1 is ( %16.12e, %16.12e )\n", opr->r, opr->i);
    printf("root : 2 is ( %16.12e, %16.12e )\n\n", (opr+1)->r, (opr+1)->i);
    free(opr);

    /*
    free(v1);
    free(v2);
    */
    free(op1);
    free(op2);
    return ( EXIT_SUCCESS );

}

