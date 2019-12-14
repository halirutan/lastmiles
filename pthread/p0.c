
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

void *sleeper(void *);    /* thread routine */

pthread_t tid[NUM_THREADS]; /* array of thread IDs */

int main(int argc, char **argv)
{

    int    i;
    struct timespec now_time;
    thread_parm_t *parm[NUM_THREADS];

    /*
     * Set en_US.UTF-8 locale which is what we use in the MySQL db tables.
     */
    setlocale( LC_ALL, "en_US.UTF-8" );

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
            /* really? possible ENOMEM? */
            if ( errno == ENOMEM ) {
                fprintf(stderr,"FAIL : calloc returns ENOMEM at %s:%d\n",
                        __FILE__, __LINE__ );
            } else {
                fprintf(stderr,"FAIL : calloc fails at %s:%d\n",
                        __FILE__, __LINE__ );
            }
            perror("FAIL ");
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

    return ( EXIT_SUCCESS );

}

void *sleeper(void *recv_parm)
{
    thread_parm_t *p = (thread_parm_t *)recv_parm;

    printf("TRD  : %d sleeping %d seconds\n", p->tnum, p->sleep_time);
    sleep(p->sleep_time);
    printf("TRD  : %d awake\n", p->tnum);

    /* return some random data */
    p->ret_val = drand48();

    return (NULL);
}

