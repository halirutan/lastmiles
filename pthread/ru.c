

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
#include <stdio.h>
#include <stdint.h>
#include <sys/resource.h>
#include <unistd.h>

int ru(void)
{
    struct rusage r_usage;
    int inex, who = RUSAGE_SELF;

    inex = getrusage(who, &r_usage);

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
    return inex;

}

