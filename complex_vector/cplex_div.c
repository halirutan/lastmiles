
#include <stdlib.h>
#include "v.h"

/* return op1 / op2 */
cplex_t * cplex_div( cplex_t *op1, cplex_t *op2 )
{

    cplex_t *res = calloc( (size_t)1, (size_t)sizeof(cplex_t));
    double denom;

    /* http://mathworld.wolfram.com/ComplexDivision.html
     *
     * We will use the complex conjugate here to simplify
     * the imaginary components in the denominator.
     *
     *     op1  = a + bi
     *     op2  = c + di
     *
     *     op2* = c - di
     *
     *                a + bi     a + bi     c - di
     *     op1/op2 = -------- = -------- x --------
     *                c + di     c + di     c - di
     *
     *
     *                (ac + bd) + (bc - ad)i
     *             = ------------------------
     *                      c^2 + d^2
     *
     */

    denom = op2->r * op2->r + op2->i * op2->i;
    res->r = (op1->r * op2->r + op1->i * op2->i) / denom;
    res->i = (op1->i * op2->r - op1->r * op2->i) / denom;

    return res;

}

