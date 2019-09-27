
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

/* return op1 / op2 */
cplex_type * cplex_div( cplex_type *op1, cplex_type *op2 )
{

    cplex_type *res = calloc( (size_t)1, (size_t)sizeof(cplex_type));
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

