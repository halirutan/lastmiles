
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

int X_error_handler(Display *dsp, XErrorEvent *errevt)
{
    char msg[80];
    XGetErrorText(dsp, errevt->error_code, msg, sizeof(msg));

    fprintf(stderr, "Error %d (%s): request %d.%d\n",
                     errevt->error_code, msg,
                     errevt->request_code,
                     errevt->minor_code);
    /* the returned value is ignored */
    return(EXIT_SUCCESS);
}

