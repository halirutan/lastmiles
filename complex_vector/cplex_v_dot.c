
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

void cplex_mult( cplex_type *res, cplex_type *op1, cplex_type *op2 );

void cplex_v_dot( cplex_type *res, vec_type *op1, vec_type *op2 )
{

    cplex_type tmp[3];

    cplex_mult( &tmp[0], &op1->x, &op2->x );
    cplex_mult( &tmp[1], &op1->y, &op2->y );
    cplex_mult( &tmp[2], &op1->z, &op2->z );

    res->r = tmp[0].r + tmp[1].r + tmp[2].r;
    res->i = tmp[0].i + tmp[1].i + tmp[2].i;

}

