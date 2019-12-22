
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
#include <stdlib.h>

#define PI_L  3.141592653589793238462643383279502884L

/* for cube roots and deMoivre's Theorem we need 2pi / 3 */
#define PI3_L 2.0943951023931954923084289221863352533333L

/* Given that this is a Ray Trace prototype we may limit
 * ourselves to an epsilon for zero testing wherein anything
 * smaller than 10^-12 is essentially zero. */
#define RT_EPSILON 1.0e-12

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

int cplex_vec_set( vec_type *op, double r0, double i0,
                                 double r1, double i1,
                                 double r2, double i2 );

int cplex_vec_print( vec_type *op );
int cplex_vec_copy( vec_type *dst, vec_type *src);
int cplex_vec_add( vec_type *res, vec_type *op1, vec_type *op2 );
int cplex_vec_scale( vec_type *res, vec_type *op1, double factor );
int cplex_vec_dot( cplex_type *res, vec_type *op1, vec_type *op2 );
int cplex_vec_cross( vec_type *res, vec_type *op1, vec_type *op2 );
int cplex_vec_normalize( vec_type *res, vec_type *op1 );

int cplex_quadratic( cplex_type res[4],
                     cplex_type *op1,
                     cplex_type *op2,
                     cplex_type *op3 );

int cplex_det( cplex_type *res,
               vec_type *r1,
               vec_type *r2,
               vec_type *r3 );


int cplex_cramer( vec_type *res,
                  vec_type *r1,
                  vec_type *r2,
                  vec_type *r3,
                  vec_type *d );

double cplex_mag( cplex_type *op1 );
double cplex_theta( cplex_type *op1 );
double cplex_vec_mag( vec_type *op1 );

/* return the solutions to the complex coefficient quadratic */
int intercept( cplex_type res[2],
                vec_type *sign,
                vec_type *loc,
                vec_type *axi,
                vec_type *obs_p,
                vec_type *obs_v );

/* compute an actual intercept point if possible */
int intercept_point( vec_type *pt,
                     int intercept_cnt,
                     cplex_type *k_val,
                     vec_type *obs_point,
                     vec_type *ray_direction);

/* compute the surface gradient normal vector */
int gradient( vec_type *res,
              vec_type *sign,
              vec_type *loc,
              vec_type *axi,
              vec_type *intercept );

int cplex_check( cplex_type *op );
size_t tohex( char **ret, const void *addr, const size_t n );
int double_cmp( double *a, double *b, size_t n);
int vec_cmp( vec_type *a, vec_type *b, size_t n);
