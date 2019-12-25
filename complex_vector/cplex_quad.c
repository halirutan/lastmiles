
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

int cplex_quadratic( cplex_type res[2],
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
     * a trivial R3 space. This function should return the number of
     * real roots.
     ****************************************************************/

    int j, status, real_root_count;
    cplex_type neg_one, two, four, denom, radicand;
    cplex_type tmp0, tmp1, tmp2;
    cplex_type full_res[4], roots[2];
    two.r = 2.0; two.i = 0.0;
    four.r = 4.0; four.i = 0.0;
    neg_one.r = -1.0; neg_one.i = 0.0;

    status = cplex_check(op1);
    if ( status != 0 ) return status;

    status = cplex_check(op2);
    if ( status != 0 ) return status;

    status = cplex_check(op3);
    if ( status != 0 ) return status;

    check_status( cplex_mult( &denom, &two, op1 ) );
    check_status( cplex_sq( &tmp0, op2 ) );
    check_status( cplex_mult( &tmp1, &four, op1 ) );
    check_status( cplex_mult( &tmp2, &tmp1, op3 ) );
    check_status( cplex_sub( &radicand, &tmp0, &tmp2 ) );

    check_status( cplex_sqrt( roots, &radicand ) );
    check_status( cplex_mult( &tmp1, &neg_one, op2 ) );

    /* we are collecting all four possible results internally :
     *     full_res[0] = ( -1 * op2 + roots[0] ) / 2 * op1
     *     full_res[1] = ( -1 * op2 + roots[1] ) / 2 * op1
     *     full_res[2] = ( -1 * op2 - roots[0] ) / 2 * op1
     *     full_res[3] = ( -1 * op2 - roots[1] ) / 2 * op1
     *
     * However we only need full_res[0] and full_res[2].
     */

    check_status( cplex_add( &tmp0, &tmp1, roots ) );
    check_status( cplex_div( &full_res[0], &tmp0, &denom ) );

    check_status( cplex_add( &tmp0, &tmp1, (roots+1) ) );
    check_status( cplex_div( &full_res[1], &tmp0, &denom ) );

    check_status( cplex_sub( &tmp0, &tmp1, roots ) );
    check_status( cplex_div( &full_res[2], &tmp0, &denom ) );

    check_status( cplex_sub( &tmp0, &tmp1, (roots+1) ) );
    check_status( cplex_div( &full_res[3], &tmp0, &denom ) );

    /* we have already checked all this with deMoivre's theorem 
     *     for (j=0; j<4; j++ ) {
     *         printf("     : full_res[%i] = ( %16.12e, %16.12e )\n",
     *                               j, full_res[j].r, full_res[j].i);
     *     }
     */

    res[0].r = full_res[0].r;
    res[0].i = full_res[0].i;

    res[1].r = full_res[2].r;
    res[1].i = full_res[2].i;


    /* check how many unique real roots we have */
    if ( ( fabs( res[0].i ) > 0.0 ) && ( fabs( res[1].i ) > 0.0 ) ) {
        real_root_count = 0;
    } else if ( ( fabs( res[0].i ) == 0.0 ) && ( fabs( res[1].i ) == 0.0 ) ) {
        real_root_count = 2;
        /* well we had better check these are unique
         * TODO consider an epsilon delta here */
        if ( ( res[0].r == res[1].r ) && ( res[0].i == res[1].i ) ) {
            real_root_count = 1;
            /* throw away the second root ? */
        }
    } else {
        real_root_count = 1;
    }

    /* As seen in chat on 20191111014002 we saw 
     * potapeno: assert is a debugging tool for me, and imo one
     *           of the least well utilized
     *
     *    assert ( real_root_count != 1 );
     */

    return ( real_root_count );

}

