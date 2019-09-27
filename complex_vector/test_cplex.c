
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "v.h"

cplex_t * cplex_add( cplex_t *op1, cplex_t *op2 );
cplex_t * cplex_sub( cplex_t *op1, cplex_t *op2 );
cplex_t * cplex_mult( cplex_t *op1, cplex_t *op2 );
cplex_t * cplex_div( cplex_t *op1, cplex_t *op2 );

int main ( int argc, char **argv)
{

    cplex_t *op1, *op2, *opr;

/* these are noop test vectors
    vec_t *v1, *v2;
    v1 = calloc ( 1, sizeof(vec_t) );
    v2 = calloc ( 1, sizeof(vec_t) );
*/

    op1 = calloc ( 1, sizeof(cplex_t) );
    op2 = calloc ( 1, sizeof(cplex_t) );

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



    /*
    free(v1);
    free(v2);
    */
    free(op1);
    free(op2);
    return ( EXIT_SUCCESS );

}

