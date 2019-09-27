
#include <stdlib.h>
#include "v.h"

cplex_t * cplex_add( cplex_t *op1, cplex_t *op2 )
{

    cplex_t *res = calloc( 1, sizeof(cplex_t));

    res->r = op1->r + op2->r;
    res->i = op1->i + op2->i;

    return res;

}

