
#include <X11/Xlib.h>

Window
create_borderless_topwin(Display *display,
                         int offset_x, int offset_y,
                         int width, int height,
                         int bg_color)
{
    Window window_handle_to_return;
    XSetWindowAttributes attribs;
    attribs.override_redirect = 1;

    /* See the X.org website to get an explanation of these
     * various parameters for the call to XCreateWindow :
     *
     * https://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.html#XCreateWindow
     *
     */

    /* parameter 7 of the call to XCreateWindow for border width is 0 */
    window_handle_to_return = XCreateWindow(display,
                                  RootWindow(display, DefaultScreen(display) ),
                                  offset_x, offset_y,
                                  width, height,
                                  0,
                                  CopyFromParent, CopyFromParent,
                                  CopyFromParent, CWOverrideRedirect,
                                  &attribs);

    /* we received a background color so use it */
    XSetWindowBackground( display, window_handle_to_return, bg_color);

    /* clear it, map it to display and flush the Xwindows messages */
    XClearWindow(display, window_handle_to_return );
    XMapWindow(display, window_handle_to_return );
    XFlush(display);

    return ( window_handle_to_return );

}

