
/*************************************************
 * The Open Group Base Specifications Issue 6
 * IEEE Std 1003.1, 2004 Edition
 *************************************************/
#define _XOPEN_SOURCE 600

#include <X11/Xlib.h>

Window
create_borderless_topwin(Display *dsp,
                         int width, int height,
                         int offset_x, int offset_y, int bg_color)
{
    Window wn;
    XSetWindowAttributes attribs;
    attribs.override_redirect = 1;
    /* note parameter 7 for border width is zero */
    wn = XCreateWindow(dsp,
                       RootWindow(dsp, DefaultScreen(dsp)),
                       offset_x, offset_y, width, height, 0,
                       CopyFromParent, CopyFromParent,
                       CopyFromParent, CWOverrideRedirect,
                       &attribs);
    XSetWindowBackground( dsp, wn, bg_color);
    XClearWindow(dsp, wn);
    XMapWindow(dsp, wn);
    XFlush(dsp);
    return wn;
}

