
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

#define PI_L  3.141592653589793238462643383279502884L

/* for cube roots and deMoivre's Theorem we need 2pi / 3 */
#define PI3_L 2.0943951023931954923084289221863352533333L

typedef struct cplex {
    double r, i;
} cplex_type;

typedef struct vec {
    struct cplex x, y, z;
} vec_type;

int cplex_add( cplex_type *res, cplex_type *op1, cplex_type *op2 );
int cplex_sub( cplex_type *res, cplex_type *op1, cplex_type *op2 );
int cplex_mult( cplex_type *res, cplex_type *op1, cplex_type *op2 );
int cplex_div( cplex_type *res, cplex_type *op1, cplex_type *op2 );
int cplex_sq( cplex_type *res, cplex_type *op1 );
int cplex_sqrt( cplex_type *res, cplex_type *op1 );
int cplex_cbrt( cplex_type *res, cplex_type *op1 );
int cplex_vec_dot( cplex_type *res, vec_type *op1, vec_type *op2 );
int cplex_vec_cross( vec_type *res, vec_type *op1, vec_type *op2 );

int cplex_quadratic( cplex_type res[4],
                     cplex_type *op1,
                     cplex_type *op2,
                     cplex_type *op3 );

int cplex_det( cplex_type *res,
               vec_type *r1,
               vec_type *r2,
               vec_type *r3 );


double cplex_mag( cplex_type *op1 );
double cplex_theta( cplex_type *op1 );

int cplex_check( cplex_type *op );
