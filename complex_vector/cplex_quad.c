
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "v.h"

void check_status( int status );

int cplex_quadratic( cplex_type res[4],
                     cplex_type *op1,
                     cplex_type *op2,
                     cplex_type *op3 )
{

    /****************************************************************
     * Let's assume we have three operands provided such that
     * the quadratic equation represented is : 
     *
     *     op1 * k^2 + op2 * k + op3 = 0
     *
     * Therefore : 
     *
     *                -1 * op2 + sqrt( op2^2 - 4 * op1 * op3 )
     *     res[0]  = ------------------------------------------
     *                                 2 * op1
     *
     *
     *                -1 * op2 - sqrt( op2^2 - 4 * op1 * op3 )
     *     res[1]  = ------------------------------------------
     *                                 2 * op1
     *
     * Note that sqrt( op2^2 - 4 * op1 * op3 ) returns two complex
     * results roots[0] and roots[1] and therefore :
     *
     *     res[0] = ( -1 * op2 + roots[0] ) / 2 * op1
     *     res[1] = ( -1 * op2 + roots[1] ) / 2 * op1
     *
     * Also true is : 
     *
     *     res[2] = ( -1 * op2 - roots[0] ) / 2 * op1
     *     res[3] = ( -1 * op2 - roots[1] ) / 2 * op1
     *
     * Therefore four possible solutions to the quadratic and this
     * is due to the fact that we are in the complex plane and not
     * a trivial R3 space.
     ****************************************************************/

    int j, status;
    cplex_type neg_one, two, four, denom, radicand;
    cplex_type tmp0, tmp1, tmp2;
    cplex_type roots[2];
    two.r = 2.0; two.i = 0.0;
    four.r = 4.0; four.i = 0.0;
    neg_one.r = -1.0; neg_one.i = 0.0;

    status = cplex_check(op1);
    if ( status != 0 ) return status;

    status = cplex_check(op2);
    if ( status != 0 ) return status;

    status = cplex_check(op3);
    if ( status != 0 ) return status;

    printf("dbug : quad op1 = ( %g, %g )\n", op1->r, op1->i);
    printf("     : quad op2 = ( %g, %g )\n", op2->r, op2->i);
    printf("     : quad op3 = ( %g, %g )\n", op3->r, op3->i);

    check_status( cplex_mult( &denom, &two, op1 ) );
    printf("     : denom = 2 * op1 = ( %g, %g )\n", denom.r, denom.i);

    check_status( cplex_sq( &tmp0, op2 ) );
    printf("     : tmp0 = op2^2 = ( %g, %g )\n", tmp0.r, tmp0.i);

    check_status( cplex_mult( &tmp1, &four, op1 ) );
    printf("     : tmp1 = four * op1 = ( %g, %g )\n", tmp1.r, tmp1.i);

    check_status( cplex_mult( &tmp2, &tmp1, op3 ) );
    printf("     : tmp2 = four * op1 * op3 = ( %g, %g )\n", tmp2.r, tmp2.i);

    check_status( cplex_sub( &radicand, &tmp0, &tmp2 ) );
    printf("     : radicand = op2^2 - four * op1 * op3 = ( %g, %g )\n", radicand.r, radicand.i);

    check_status( cplex_sqrt( roots, &radicand ) );
    printf("     : radicand roots1 is ( %16.12e, %16.12e )\n", roots[0].r, roots[0].i);
    printf("     : radicand roots2 is ( %16.12e, %16.12e )\n\n", roots[1].r, roots[1].i);

    check_status( cplex_mult( &tmp1, &neg_one, op2 ) );
    printf("     : -1 * op2 = ( %g, %g )\n\n", tmp1.r, tmp1.i);

    /* 
     *     res[0] = ( -1 * op2 + roots[0] ) / 2 * op1
     *     res[1] = ( -1 * op2 + roots[1] ) / 2 * op1
     *     res[2] = ( -1 * op2 - roots[0] ) / 2 * op1
     *     res[3] = ( -1 * op2 - roots[1] ) / 2 * op1
    */

    check_status( cplex_add( &tmp0, &tmp1, roots ) );
    check_status( cplex_div( &res[0], &tmp0, &denom ) );

    check_status( cplex_add( &tmp0, &tmp1, (roots+1) ) );
    check_status( cplex_div( &res[1], &tmp0, &denom ) );

    check_status( cplex_sub( &tmp0, &tmp1, roots ) );
    check_status( cplex_div( &res[2], &tmp0, &denom ) );

    check_status( cplex_sub( &tmp0, &tmp1, (roots+1) ) );
    check_status( cplex_div( &res[3], &tmp0, &denom ) );

    for (j=0; j<4; j++ ) {
        printf("     : res[%i] = ( %16.12e, %16.12e )\n", j, res[j].r, res[j].i);
    }

    return ( 0 );

}

