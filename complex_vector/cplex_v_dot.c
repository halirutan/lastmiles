
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

void cplex_mult( cplex_type *op1, cplex_type *op2, cplex_type *res );

void cplex_v_dot( vec_type *op1, vec_type *op2, cplex_type *res )
{

    cplex_type tmp[3];

    cplex_mult( &op1->x, &op2->x, &tmp[0] );
    cplex_mult( &op1->y, &op2->y, &tmp[1] );
    cplex_mult( &op1->z, &op2->z, &tmp[2] );

    res->r = tmp[0].r + tmp[1].r + tmp[2].r;
    res->i = tmp[0].i + tmp[1].i + tmp[2].i;

}

