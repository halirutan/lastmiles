
/*************************************************
 * The Open Group Base Specifications Issue 6
 * IEEE Std 1003.1, 2004 Edition
 *************************************************/
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

GC
create_gc(Display *display, Window win)
{
    GC gc;
    unsigned long valuemask = 0;
    XGCValues values;

    /* Assume a default line width of 2 pixels and then the
     * user can make their own changes to the Graphics Context
     * later if they want. */
    unsigned int line_width = 2;

    /* a few line style assumptions */
    int line_style = LineSolid;
    int cap_style = CapButt;
    int join_style = JoinBevel;

    int screen_num = DefaultScreen(display);

    gc = XCreateGC(display, win, valuemask, &values);
    /* note that a 32-bit system will throw a warning about
     * cast from pointer to integer of different size with
     * (int64_t) type used on a pointer comparison. 
     *
     * this is clumsy and there is even improper pointer comparison
     * being done.  LLVM/Clang barfs on this.
     *
     *    if ((int64_t)gc < 0) {
     *        fprintf(stderr, "XCreateGC failed\n");
     *        exit(EXIT_FAILURE);
     *    }
     */

    /* Assume basic White foreground on Black background */
    XSetForeground(display, gc, XWhitePixel(display, screen_num));
    XSetBackground(display, gc, XBlackPixel(display, screen_num));

    /* line style */
    XSetLineAttributes(display, gc,
        line_width, line_style,
        cap_style, join_style);

    /* fill style is solid */
    XSetFillStyle(display, gc, FillSolid);

    return ( gc );

}

