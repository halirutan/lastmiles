
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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/resource.h>

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

