
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

#define PI_L  3.141592653589793238462643383279502884L

/* for cube roots and deMoivre's Theorem we need 2pi / 3 */
#define PI3_L 2.0943951023931954923084289221863352533333L

typedef struct cplex {
    double r, i;
} cplex_type;

typedef struct vec {
    struct cplex x, y, z;
} vec_type;

