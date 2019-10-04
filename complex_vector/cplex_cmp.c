#define _XOPEN_SOURCE 600

// #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v.h"


int double_cmp( double *a, double *b, size_t n)
{
    // TODO: Dennis thought something was maybe not portable using sizeof(char) here
    // i didn't quite understand what needed to be changed. - Travis
    char* sa = calloc( (size_t)n+1, sizeof(char) );
    char* sb = calloc( (size_t)n+1, sizeof(char) );
    tohex(&sa, a, n);
    tohex(&sb, b, n);
    int result = strcmp(sa, sb);
    // printf("sa %s a %lf\n", sa, *a);
    // printf("sb %s b %lf\n", sb, *b);
    free(sa);
    free(sb);

    return result;

}

int cplex_cmp( cplex_type *a, cplex_type *b, size_t n)
{

    int rr = double_cmp( &a->r, &b->r, n );
    int ri = double_cmp( &a->i, &b->i, n );

    return rr | ri;

}

int vec_cmp( vec_type *a, vec_type *b, size_t n)
{

    int rx = cplex_cmp( &a->x, &b->x, n );
    int ry = cplex_cmp( &a->y, &b->y, n );
    int rz = cplex_cmp( &a->z, &b->z, n );

    return rx | ry | rz;

}
