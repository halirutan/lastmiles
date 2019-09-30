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
#include <string.h>
#include <ctype.h>

void dumpbuff ( unsigned n, const unsigned char *buf ) {
    int on_this_line = 0;
    int i;
    while (n-- > 0) {
        printf( "%02X ", *buf++);
        on_this_line += 1;
        if (on_this_line == 16 || n == 0) {
            fputs (" ", stdout );
            for (i = on_this_line; i < 16; i++)
                fputs (" ", stdout );
            for (i = on_this_line; i>0; i--)
                fputc(isprint(buf[-i]) ? buf[-i] : '.', stdout );
            fputs("\n", stdout );
            on_this_line = 0;
        }
    }
}

