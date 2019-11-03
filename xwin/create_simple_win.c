
/*************************************************
 * The Open Group Base Specifications Issue 6
 * IEEE Std 1003.1, 2004 Edition
 *************************************************/
#define _XOPEN_SOURCE 600

#include <X11/Xlib.h>

Window
create_simple_win(Display *dsp,
                  int width, int height,
                  int border_width,
                  int offset_x, int offset_y)
{
    /* we need to create a thing called an unmapped InputOutput
     * subwindow of some given parent window. In this case the
     * parent is the root level window.  See page 38 */
    Window wn;
    int scr = DefaultScreen(dsp);
    wn = XCreateSimpleWindow(dsp, RootWindow(dsp, scr),
                             offset_x, offset_y, width, height, border_width,
                             XBlackPixel(dsp, scr),
                             XBlackPixel(dsp, scr));
    XSetWindowBackground( dsp, wn, 0x000000);
    XClearWindow(dsp, wn);
    XMapWindow(dsp, wn);
    XFlush(dsp);
    return wn;
}

