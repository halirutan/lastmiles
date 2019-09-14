
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <assert.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <iso646.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <unistd.h>

uint64_t system_memory()
{
    /* should return the amount of memory available in bytes */
    long en;
    uint64_t pages, page_size;

    en = sysconf(_SC_PHYS_PAGES);
    if ( en < 0 ){
        perror("sysconf(_SC_PHYS_PAGES) : ");
        exit(EXIT_FAILURE);
    }
    pages = (uint64_t) en;

    page_size = (uint64_t)sysconf(_SC_PAGE_SIZE);
    return ( pages * page_size );
}

int main (int argc, char *argv[])
{

    int inex = 0; /* ret val for some system calls */
    struct utsname uname_data;
    int who = RUSAGE_SELF;
    struct rusage r_usage;

    uint64_t sysmem = system_memory();
    uint64_t pagesize = (uint64_t)sysconf(_SC_PAGESIZE);

    /* from the man page for getrusage()
           struct rusage {
               struct timeval ru_utime;  * user CPU time used *
               struct timeval ru_stime;  * system CPU time used *
               long   ru_maxrss;         * maximum resident set size *
               long   ru_ixrss;          * integral shared memory size *
               long   ru_idrss;          * integral unshared data size *
               long   ru_isrss;          * integral unshared stack size *
               long   ru_minflt;         * page reclaims (soft page faults) *
               long   ru_majflt;         * page faults (hard page faults) *
               long   ru_nswap;          * swaps *
               long   ru_inblock;        * block input operations *
               long   ru_oublock;        * block output operations *
               long   ru_msgsnd;         * IPC messages sent *
               long   ru_msgrcv;         * IPC messages received *
               long   ru_nsignals;       * signals received *
               long   ru_nvcsw;          * voluntary context switches *
               long   ru_nivcsw;         * involuntary context switches *
           };
    */

    setlocale( LC_MESSAGES, "C" );
    if ( uname( &uname_data ) < 0 ) {
        fprintf ( stderr,
                 "WARNING : Could not attain system uname data.\n" );
        perror ( "uname" );
    } else {
        printf ( "-------------------------------" );
        printf ( "------------------------------\n" );
        printf ( "        system name = %s\n", uname_data.sysname );
        printf ( "          node name = %s\n", uname_data.nodename );
        printf ( "            release = %s\n", uname_data.release );
        printf ( "            version = %s\n", uname_data.version );
        printf ( "            machine = %s\n", uname_data.machine );
        printf ( "          page size = %" PRIu64 "\n", pagesize );
        printf ( "       avail memory = %" PRIu64 "\n", sysmem );
        printf ( "                    = %" PRIu64 " kB\n", sysmem/1024 );
        printf ( "                    = %" PRIu64 " MB\n", sysmem/1048576 );
        if ( sysmem > ( 1024 * 1048576 ) ) {
            printf ( "                    = %" PRIu64 " GB\n",
                    sysmem/( 1024 * 1048576 ) );
        }
        printf ( "-------------------------------" );
        printf ( "------------------------------" );
    }
    printf ("\n");

    inex = getrusage(who, &r_usage);
    printf("inf : start maximum resident set size pages     maxrss = %ld\n",r_usage.ru_maxrss);
    printf("inf : start integral shared memory size          ixrss = %ld\n",r_usage.ru_ixrss);
    printf("inf : start integral unshared data size          idrss = %ld\n",r_usage.ru_idrss);
    printf("inf : start integral unshared stack size         isrss = %ld\n",r_usage.ru_isrss);
    printf("inf : start page reclaims (soft page faults) ru_minflt = %ld\n",r_usage.ru_isrss);
    printf("inf : start page faults (hard page faults)   ru_majflt = %ld\n",r_usage.ru_majflt);
    printf("inf : start swaps (may be pages swapped)      ru_nswap = %ld\n",r_usage.ru_nswap);
    printf("inf : start block input operations          ru_inblock = %ld\n",r_usage.ru_inblock);
    printf("inf : start block output operations         ru_oublock = %ld\n",r_usage.ru_oublock);
    printf("inf : start IPC messages sent                ru_msgsnd = %ld\n",r_usage.ru_msgsnd);
    printf("inf : start IPC messages received            ru_msgrcv = %ld\n",r_usage.ru_msgrcv);
    printf("inf : start signals received               ru_nsignals = %ld\n",r_usage.ru_nsignals);
    printf("inf : start voluntary context switches        ru_nvcsw = %ld\n",r_usage.ru_nvcsw);
    printf("inf : start involuntary context switches     ru_nivcsw = %ld\n",r_usage.ru_nivcsw);
    printf("\n");


    return ( EXIT_SUCCESS );

}

