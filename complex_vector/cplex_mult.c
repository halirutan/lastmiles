
#include <stdlib.h>
#include "v.h"

cplex_t * cplex_mult( cplex_t *op1, cplex_t *op2 )
{

    cplex_t *res = calloc( 1, sizeof(cplex_t));

    /*  ( r1, i1 ) ( r2, i2 ) =  r1xr2 + r1xi2 + i1xr2 + i1xi2
     *
     * theddmage (x+i*y)*(a+i*b) == ax + i*bx + i*ya -1(by)
     */

    res->r = op1->r * op2->r - ( op1->i * op2->i );
    res->i = op1->r * op2->i + ( op2->r * op1->i );

    return res;

}

