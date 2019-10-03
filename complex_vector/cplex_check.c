#define _XOPEN_SOURCE 600

#include <math.h>
#include <assert.h>

#include "v.h"


int cplex_check( cplex_type *op )
{

    /* check for invalid data: null, nan, inf
     * not sure about using asserts here
     * should return error codes but not sure how to best proceed.
     *
     * Fair enough and we can sort this out later as we are in
     * dirty prototype mode anyways.  Dennis 
     *
     */

    assert( op );

    assert( !isnan(op->i) );
    assert( !isnan(op->r) );

    assert( !isinf(op->i) );
    assert( !isinf(op->r) );

    return ( 0 );

}
