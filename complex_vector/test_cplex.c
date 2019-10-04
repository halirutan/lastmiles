
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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <complex.h>

#include "v.h"

void check_status( int status );

int main ( int argc, char **argv)
{

    cplex_type op1, op2, op3, opr, opr2[3], quad_res[4];
    vec_type v[3];
    double dres;
    int status;

    op1 = (cplex_type){1.0, 0.0};
    op2 = (cplex_type){1.0, 0.0};
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     : op2 = ( %g, %g )\n", op2.r, op2.i);
    check_status( cplex_mult( &opr, &op1, &op2 ) );
    printf("     : opr = op1 * op2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be i^2 = -1\n\n");
    assert( cplex_cmp( &(cplex_type){1.0, 0.0}, &opr, 8) == 0 );

    op1 = (cplex_type){1.0,0.0};
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     : op2 = ( %g, %g )\n", op2.r, op2.i);
    check_status( cplex_mult( &opr, &op1, &op2 ) );
    printf("     : opr = op1 * op2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be 1\n\n");
    assert( cplex_cmp( &(cplex_type){1.0,0.0}, &opr, 8) == 0 );

    op1 = (cplex_type){-1.0, 0.0};
    op2 = (cplex_type){0.0, 0.0};
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     : op2 = ( %g, %g )\n", op2.r, op2.i);
    check_status( cplex_mult( &opr, &op1, &op2 ) );
    printf("     : opr = op1 * op2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be just zero.\n\n");
    assert( cplex_cmp( &(cplex_type){0.0, 0.0}, &opr, 8) == 0 );

    op1 = (cplex_type){4.0, 3.0};
    op2 = (cplex_type){2.0,-1.0};
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     : op2 = ( %g, %g )\n", op2.r, op2.i);
    check_status( cplex_div( &opr, &op1, &op2 ) );
    printf("dbug : opr = op1 / op2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be 1 + 2i\n\n");
    assert( cplex_cmp( &(cplex_type){1.0, 2.0}, &opr, 8) == 0 );

    op2 = (cplex_type){-4.0, -12.0};
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     : op2 = ( %g, %g )\n", op2.r, op2.i);
    check_status( cplex_div( &opr, &op1, &op2 ) );
    printf("dbug : opr = op1 / op2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be -0.325 + 0.225i\n\n");
    assert( cplex_cmp( &(cplex_type){-0.325, 0.225}, &opr, 8) == 0 );

    op1 = (cplex_type){2.0,1.0};
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    dres = cplex_theta( &op1 );
    printf("     :     theta = %16.12e\n\n", dres );
    assert( double_cmp( &(double){ 4.636476090008060935154787784995278343558311462402e-01 }, &dres, 8) == 0 );

    op1 = (cplex_type){4.0,3.0};
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    dres = cplex_theta( &op1 );
    printf("     :     theta = %16.12e\n", dres );
    assert( double_cmp( &(double){ 6.435011087932843709680241772730369120836257934570e-01 }, &dres, 8) == 0 );

    check_status( cplex_sq( &opr, &op1 ) );
    printf("     : opr = op1^2 = ( %g, %g )\n", opr.r, opr.i);
    printf("     :     should be 7 + 24i\n");
    printf("     :     magnitude is %g\n", cplex_mag(&opr));
    printf("     :     theta = %16.12e\n", cplex_theta( &opr));
    assert( cplex_cmp( &(cplex_type){7.0, 24.0}, &opr, 8) == 0 );

    printf("     : now we take the square root(s) of opr\n");
    op1 = (cplex_type){opr.r,opr.i};
    double complex z = op1.r + op1.i * I;
    check_status( cplex_sqrt( opr2, &op1 ) );
    printf("root : 1 is ( %16.12e, %16.12e )\n", opr2[0].r, opr2[0].i);
    printf("root : 2 is ( %16.12e, %16.12e )\n", opr2[1].r, opr2[1].i);
    double complex zr = csqrt(z);
    printf("     : csqrt returns ( %16.12e, %16.12e )\n",
                                                creal(zr), cimag(zr) );
    printf("     : we should get back ( 4, 3i ) and ( -4, -3i ).\n\n");
    assert( cplex_cmp( &(cplex_type){4.0, 3.0}, &opr2[0], 8) == 0 );
    // TODO: negative numbers producing slightly different hex strings
    // assert( cplex_cmp( &(cplex_type){-4.0, -3.0}, &opr2[1], 8) == 0 );

    /* square root of ( 0, 1 ) */
    printf("dbug : square root test\n");
    op1.r = 0.0;
    op1.i = 1.0;
    printf("dbug : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     :     theta = %16.12e\n", cplex_theta(&op1) );
    printf("     :     magnitude is %g\n", cplex_mag(&op1));
    check_status( cplex_sqrt( opr2, &op1 ) );
    printf("root : 1 = ( %16.48e, %16.48e )\n", opr2[0].r, opr2[0].i);
    printf("root : 2 = ( %16.48e, %16.48e )\n\n", opr2[1].r, opr2[1].i);
    // TODO: not sure how to test this number.
    // double r707 = 7.071067811865475727373109293694142252206802368164e-01;
    // assert( cplex_cmp( &(cplex_type){r707, r707}, &opr2[0], 8) == 0 );
    // TODO: negative numbers producing slightly different hex strings
    // assert( cplex_cmp( &(cplex_type){-r707, -r707}, &opr2[1], 8) == 0 );

    /* cube roots of ( -11 + 2i ) */
    printf("dbug : cube root test\n");
    op1.r = -11.0;
    op1.i = 2.0;
    printf("     : op1 = ( %g, %g )\n", op1.r, op1.i);
    printf("     :     theta = %16.12e\n", cplex_theta(&op1) );
    printf("     :     magnitude is %g\n", cplex_mag(&op1));

    check_status( cplex_cbrt( opr2, &op1 ) );
    printf("root : 1 = ( %16.12e, %16.12e )\n", opr2[0].r, opr2[0].i);
    printf("root : 2 = ( %16.12e, %16.12e )\n", opr2[1].r, opr2[1].i);
    printf("root : 3 = ( %16.12e, %16.12e )\n\n", opr2[2].r, opr2[2].i);
    assert( cplex_cmp( &(cplex_type){1.232050807568877415221209048468153923749923706055e+00, 1.866025403784438596588302061718422919511795043945e+00}, &opr2[0], 8) == 0 );
    assert( cplex_cmp( &(cplex_type){-2.232050807568877193176604123436845839023590087891e+00, 1.339745962155611813670930132502689957618713378906e-01}, &opr2[1], 8) == 0 );
    assert( cplex_cmp( &(cplex_type){9.999999999999997779553950749686919152736663818359e-01, -2.000000000000000444089209850062616169452667236328e+00}, &opr2[2], 8) == 0 );

    printf("Lets test vector dot product\n");
    /* < (1 + 1i), (2 + 2i), (3+3i) >
     *                    . <( -1 - 1i), ( -2 -2i), ( 3 - 3i ) >
     *
     *
     * should be ( 18, -10i ) */

    /* first vector is < (1 + 1i), (2 + 2i), (3+3i) > */
    v[0].x = (cplex_type){1.0,1.0};
    v[0].y = (cplex_type){2.0,2.0};
    v[0].z = (cplex_type){3.0,3.0};
    printf("dbug : v1 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[0].x.r, v[0].x.i,
            v[0].y.r, v[0].y.i,
            v[0].z.r, v[0].z.i );

    /* second vector is <( -1 - 1i), ( -2 -2i), ( 3 - 3i ) > */
    v[1].x = (cplex_type){-1.0, -1.0};
    v[1].y = (cplex_type){-2.0, -2.0};
    v[1].z = (cplex_type){ 3.0, -3.0};
    printf("     : v2 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[1].x.r, v[1].x.i,
            v[1].y.r, v[1].y.i,
            v[1].z.r, v[1].z.i );

    check_status( cplex_vec_dot( &opr, v, v+1) );
    printf("     : dot product = ( %g, %g )\n\n", opr.r, opr.i);
    assert( cplex_cmp( &(cplex_type){18.0, -10.0}, &opr, 8) == 0 );


    check_status( cplex_vec_cross( v+2, v, v+1 ) );
    printf("     : v1 X v2 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[2].x.r, v[2].x.i,
            v[2].y.r, v[2].y.i,
            v[2].z.r, v[2].z.i );
    assert( vec_cmp( &(vec_type){(cplex_type){12.0, 12.0},(cplex_type){-6.0, -6.0},(cplex_type){0.0, 0.0}}, &v[2], 8) == 0 );


    op1 = (cplex_type){1.0, 0.0};
    op2 = (cplex_type){-9.0, 0.0};
    op3 = (cplex_type){14.0, 0.0};
    check_status( cplex_quadratic( quad_res, &op1, &op2, &op3 ) );
    printf("Quadratic result 1 = ( %16.12e, %16.12e )\n",
                                          quad_res[0].r, quad_res[0].i);
    printf("          result 2 = ( %16.12e, %16.12e )\n\n",
                                          quad_res[1].r, quad_res[1].i);
    assert( cplex_cmp( &(cplex_type){7.0, 0.0}, &quad_res[0], 8) == 0 );
    assert( cplex_cmp( &(cplex_type){2.0, 0.0}, &quad_res[1], 8) == 0 );

    op1 = (cplex_type){1.0, 0.0};
    op2 = (cplex_type){5.0, 0.0};
    op3 = (cplex_type){-14.0, 0.0};
    check_status( cplex_quadratic( quad_res, &op1, &op2, &op3 ) );
    printf("Quadratic result 1 = ( %16.12e, %16.12e )\n",
                                          quad_res[0].r, quad_res[0].i);
    printf("          result 2 = ( %16.12e, %16.12e )\n\n",
                                          quad_res[1].r, quad_res[1].i);
    assert( cplex_cmp( &(cplex_type){2.0, 0.0}, &quad_res[0], 8) == 0 );
    assert( cplex_cmp( &(cplex_type){-7.0, 0.0}, &quad_res[1], 8) == 0 );


    op1 = (cplex_type){1.0, 0.0};
    op2 = (cplex_type){-5.0, 0.0};
    op3 = (cplex_type){14.0, 0.0};
    check_status( cplex_quadratic( quad_res, &op1, &op2, &op3 ) );
    printf("Quadratic result 1 = ( %16.12e, %16.12e )\n",
                                          quad_res[0].r, quad_res[0].i);
    printf("          result 2 = ( %16.12e, %16.12e )\n\n",
                                          quad_res[1].r, quad_res[1].i);
    assert( cplex_cmp( &(cplex_type){5.283882181415011203284848306793719530105590820312, 0.0}, &quad_res[0], 8) == 0 );
    // TODO: negative float cmp fail
    // assert( cplex_cmp( &(cplex_type){-2.838821814150107591956384567311033606529235839844, 0.0}, &quad_res[1], 8) == 0 );


    op1 = (cplex_type){2.0, 3.0};
    op2 = (cplex_type){-5.0, 2.0};
    op3 = (cplex_type){-1.0, -7.0};
    check_status( cplex_quadratic( quad_res, &op1, &op2, &op3 ) );
    printf("Quadratic result 1 = ( %16.12e, %16.12e )\n",
                                          quad_res[0].r, quad_res[0].i);
    printf("          result 2 = ( %16.12e, %16.12e )\n\n",
                                          quad_res[1].r, quad_res[1].i);
    assert( cplex_cmp( &(cplex_type){1.307692307692307709388046532694716006517410278320e+00, -4.615384615384616195932210302999010309576988220215e-01},
                                          &quad_res[0], 8) == 0 );
    assert( cplex_cmp( &(cplex_type){-1.0, -1.0}, &quad_res[1], 8) == 0 );

    /* Determinant of three row matrix */
    v[0].x = (cplex_type){1.0, 0.0};
    v[0].y = (cplex_type){2.0, 0.0};
    v[0].z = (cplex_type){3.0, 0.0};
    printf("dbug : row 1 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[0].x.r, v[0].x.i,
            v[0].y.r, v[0].y.i,
            v[0].z.r, v[0].z.i );

    /* second row */
    v[1].x = (cplex_type){4.0, 0.0};
    v[1].y = (cplex_type){5.0, 0.0};
    v[1].z = (cplex_type){6.0, 0.0};
    printf("     : row 2 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[1].x.r, v[1].x.i,
            v[1].y.r, v[1].y.i,
            v[1].z.r, v[1].z.i );

    /* third row */
    v[2].x = (cplex_type){7.0, 0.0};
    v[2].y = (cplex_type){8.0, 0.0};
    v[2].z = (cplex_type){9.0, 0.0};
    printf("     : row 3 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[2].x.r, v[2].x.i,
            v[2].y.r, v[2].y.i,
            v[2].z.r, v[2].z.i );

    check_status( cplex_det( &opr, &v[0], &v[1], &v[2] ) );
    printf("     : det = ( %g, %g )\n", opr.r, opr.i);
    assert( cplex_cmp( &(cplex_type){0, 0}, &opr, 8 ) == 0);

    printf("\n\nNew Row data on row1 \n");
    v[0].x = (cplex_type) {10.0, 0.0};
    v[0].y = (cplex_type) {-2.0, 0.0};
    v[0].z = (cplex_type) {-3.0, 0.0};
    printf("dbug : row 1 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[0].x.r, v[0].x.i,
            v[0].y.r, v[0].y.i,
            v[0].z.r, v[0].z.i );
    check_status( cplex_det( &opr, &v[0], &v[1], &v[2] ) );
    printf("     : det = ( %g, %g )\n", opr.r, opr.i);
    assert( cplex_cmp( &(cplex_type){-33, 0}, &opr, 8 ) == 0);

    printf("\n\nComplex row data in row1 and row 3\n");
    v[0].x = (cplex_type) {0.5, -1.0};
    printf("dbug : row 1 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[0].x.r, v[0].x.i,
            v[0].y.r, v[0].y.i,
            v[0].z.r, v[0].z.i );
    v[2].y = (cplex_type){-2.0, 4.0};
    printf("     : row 3 = < ( %g, %g ), ( %g, %g ), ( %g, %g ) >\n",
            v[2].x.r, v[2].x.i,
            v[2].y.r, v[2].y.i,
            v[2].z.r, v[2].z.i );

    check_status( cplex_det( &opr, &v[0], &v[1], &v[2] ) );
    printf("     : det = ( %g, %g )\n", opr.r, opr.i);
    assert( cplex_cmp( &(cplex_type){121.5, -117}, &opr, 8 ) == 0);


    return ( EXIT_SUCCESS );

}

