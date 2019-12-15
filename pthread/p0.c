
#define _XOPEN_SOURCE 600

#include <ctype.h>
#include <errno.h>
#include <locale.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <limits.h>
#include <pthread.h>
#include <stdarg.h>
#include <unistd.h>

#include "p0.h"

int sysinfo(void);
int ru(void);
void *sleeper(void *);    /* thread routine */

pthread_t tid[NUM_THREADS]; /* array of thread IDs */

int main(int argc, char **argv)
{

    int    i, j, k;
    struct timespec now_time;
    thread_parm_t *parm[NUM_THREADS];

    /*
     * Set en_US.UTF-8 locale which is what we use in the MySQL db tables.
     */
    setlocale( LC_ALL, "C" );
    sysinfo();

    /* Get the REALTIME_CLOCK time in a timespec struct */
    if ( clock_gettime( CLOCK_REALTIME, &now_time ) == -1 ) {
        /* We could not get the clock. Bail out. */
        fprintf(stderr,"ERROR : could not attain CLOCK_REALTIME\n");
        return(EXIT_FAILURE);
    } else {
        /* call srand48() with the sub-second time data */
        srand48( (long) now_time.tv_nsec );
    }

    printf("\n-------------- begin dispatch -----------------------\n");
    for ( i = 0; i < NUM_THREADS; i++) {
        parm[i] = calloc( (size_t) 1 , (size_t) sizeof(thread_parm_t) );

        if ( parm[i] == NULL ) {
            if ( errno == ENOMEM ) {
                fprintf(stderr,"FAIL : calloc returns ENOMEM at %s:%d\n",
                        __FILE__, __LINE__ );
            } else {
                fprintf(stderr,"FAIL : calloc fails at %s:%d\n",
                        __FILE__, __LINE__ );
            }
            perror("FAIL ");
            /* gee .. before we bail out did we allocate any of the
             * previous thread parameter memory regions? If so then
             * clean up before bailing out. In fact we may have 
             * already dispatched out threads. */

            if (i == 0 ) return ( EXIT_FAILURE );

            for ( j = 0; j < i; j++ ) {
                /* lets ask those threads to just be nice and 
                 * we call them in with a join */
                pthread_join(tid[j], NULL);
                fprintf(stderr,"BAIL : pthread_join(%i) done.\n", j);
                free(parm[j]);
                parm[j] = NULL;
            }
            fprintf(stderr,"BAIL : cleanup done.\n", j);
            ru();

            return ( EXIT_FAILURE );

        }

        parm[i]->tnum = i;
        parm[i]->sleep_time = 1 + (int)( drand48() * 10.0 );

        pthread_create( &tid[i], NULL, sleeper, (void *)parm[i] );

        printf("INFO : pthread_create %2i called for %2i secs.\n",
                                               i, parm[i]->sleep_time );
    }
    printf("\n-------------- end dispatch -------------------------\n");

    for ( i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);

        printf("main() pthread_join %2i returned %-14.12g data.\n",
                                                  i, parm[i]->ret_val );

    }
    printf("\n-------------- end join -----------------------------\n");
    printf("All %i threads have terminated\n", i);

    for ( i = 0; i < NUM_THREADS; i++) {
        free(parm[i]);
        parm[i] = NULL;
    }

    ru();

    return ( EXIT_SUCCESS );

}

void *sleeper(void *recv_parm)
{
    thread_parm_t *p = (thread_parm_t *)recv_parm;

    /*
    printf("TRD  : %d sleeping %d seconds\n", p->tnum, p->sleep_time);
    sleep(p->sleep_time);
    printf("TRD  : %d awake\n", p->tnum);
    */

    printf("TRD  : %d filling the big_array.\n", p->tnum);
    for ( p->loop0 = 0; p->loop0 < BIG_ARRAY_DIM0; p->loop0++ ) {
        for ( p->loop1 = 0; p->loop1 < BIG_ARRAY_DIM1; p->loop1++ ) {
            p->big_array[p->loop0][p->loop1] = (uint64_t)(p->loop0 * p->loop1);
        }
    }
    printf("TRD  : %d big_array full.\n", p->tnum);

    /* return some random data */
    p->ret_val = drand48();

    return (NULL);
}

