
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

#include <stdlib.h>
#include "v.h"

cplex_type * cplex_sub( cplex_type *op1, cplex_type *op2 );
cplex_type * cplex_mult( cplex_type *op1, cplex_type *op2 );

vec_type * cplex_v_cross( vec_type *op1, vec_type *op2 )
{

    cplex_type *op_left, *op_right, *op_sub;
    vec_type *res = calloc( (size_t)1, sizeof(vec_type));

    /* the determinant of a 3x3 matrix with the top row
     * being the basis vectors i, j, k and then row 2
     * would be operand op1 components and row 3 is op2
     * components : 
     *
     *
     *        ||    i       j       k     ||
     *        ||    a       b       c     ||
     *        ||    d       e       f     ||
     *
     *        ==>  bfi + cdj + aek - cei - afj - dbk
     *
     * However in our case a = op1.x
     *                     b = op1.y
     *                     c = op1.z
     *                     d = op2.x
     *                     e = op2.y
     *                     f = op2.z
     *
     * The resultant vector will be : 
     *
     *    < ( bf - ce ), ( cd - af ), ( ae - bd ) >
     *
     * So it may be expediant to use intermediate internal
     * product values. i.e. :
     *  
     *      cross[0] =  cplex_sub(
     *                      cplex_mult( &op1->y, &op2->z ),
     *                      cplex_mult( &op1->z, &op2->y ) )
     *
     * However the protect outselves from leaking memory we
     * may also need temporary operands opr0 and opr1.
     *
     */

    op_left = cplex_mult( &op1->y, &op2->z );
    op_right = cplex_mult( &op1->z, &op2->y );
    op_sub = cplex_sub( op_left, op_right );
    res->x.r = op_sub->r;
    res->x.i = op_sub->i;
    free(op_left); free(op_right); free(op_sub);

    op_left = cplex_mult( &op1->z, &op2->x );
    op_right = cplex_mult( &op1->x, &op2->z );
    op_sub = cplex_sub( op_left, op_right );
    res->y.r = op_sub->r;
    res->y.i = op_sub->i;
    free(op_left); free(op_right); free(op_sub);

    op_left = cplex_mult( &op1->x, &op2->y );
    op_right = cplex_mult( &op1->y, &op2->x );
    op_sub = cplex_sub( op_left, op_right );
    res->z.r = op_sub->r;
    res->z.i = op_sub->i;
    free(op_left); free(op_right); free(op_sub);

    return res;

}

