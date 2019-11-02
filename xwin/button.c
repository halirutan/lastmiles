
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

Window
create_borderless_topwin(Display *dsp,
                         int width, int height,
                         int offset_x, int offset_y,
                         int bg_color);

GC create_gc(Display *dsp, Window win);

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

int main (int argc, char *argv[])
{

    /* our display and window and graphics context */
    Display *dsp;
    Window win;
    GC gc;
    Colormap screen_colormap;
    XEvent event;

    /* a very few colours */
    XColor red, green, blue, yellow;

    Status retcode0;  /* not really needed for trivial stuff */
    int retcode1;     /* curious what some funcs return */
    int conn_num, screen_num, depth;
    int disp_width, disp_height;

    /* setup x and y as impossible negative values */
    int x = -1, y = -1;
    int button;

    /* get a display name but it is not really needed.
     * we can just assume null and Xwindows will go with
     * the DISPLAY env var anyways
     *    char *disp_name = getenv("DISPLAY");
     */
    char *disp_name = NULL;
    dsp = XOpenDisplay(disp_name);
    if (dsp == NULL) {
        fprintf(stderr, "%s: no X server?? '%s'\n",
            argv[0], disp_name);
        exit(EXIT_FAILURE);
    }
    conn_num = XConnectionNumber(dsp);
    printf("connection number %i\n", conn_num);

    screen_num = DefaultScreen(dsp);
    printf("screen number %i\n", screen_num);

    depth = XDefaultDepth(dsp,screen_num);
    printf("default depth is %i\n", depth);

    disp_width = DisplayWidth(dsp, screen_num);
    disp_height = DisplayHeight(dsp, screen_num);

    printf("display seems to be %i wide and %i high.\n",
                                   disp_width, disp_height);


    /* 640x480 window at x=20 y=20 coords with grey background */
    win = create_borderless_topwin(dsp, 800, 240, 20, 20, 0xfffaf0);
    gc = create_gc(dsp, win);

    XGrabPointer(dsp, win, False, ButtonPressMask, GrabModeAsync,
                           GrabModeAsync, None, None, CurrentTime);

    XSelectInput(dsp, win, ButtonPressMask);

    /* capture button press and release events
     * XSelectInput(display, root, ButtonPressMask|ButtonReleaseMask);
     */

    while(1){

        XNextEvent(dsp,&event);

        switch(event.type){
            case ButtonPress:
                switch(event.xbutton.button){
                    case Button1:
                        x=event.xbutton.x;
                        y=event.xbutton.y;
                        button=Button1;
                        break;

                    case Button3:
                        x=event.xbutton.x;
                        y=event.xbutton.y;
                        button=Button3;
                        break;
                    default:
                        break;
                }
            break;
        default:
            break;
        }

        if ( (x >= 0) && (y >= 0) ) break;

    } /* while */

    if ( button == Button1 ){
        printf("leftclick at %d %d \n", x, y);
    } else {
        printf("rightclick at %d %d \n", x, y);
    }

    XCloseDisplay(dsp);
    return EXIT_SUCCESS;
}

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

GC
create_gc(Display *dsp, Window win)
{
    GC gc;
    unsigned long valuemask = 0;
    XGCValues values;
    unsigned int line_width = 2;
    int line_style = LineSolid;
    int cap_style = CapButt;
    int join_style = JoinBevel;
    int screen_num = DefaultScreen(dsp);

    gc = XCreateGC(dsp, win, valuemask, &values);
    if ((int64_t)gc < 0) { /* just taser me improper pointer comparison */
        fprintf(stderr, "XCreateGC failed\n");
        exit(EXIT_FAILURE); /* clumsy */
    }

    XSetForeground(dsp, gc, XWhitePixel(dsp, screen_num));
    XSetBackground(dsp, gc, XBlackPixel(dsp, screen_num));

    /* line style */
    XSetLineAttributes(dsp, gc,
        line_width, line_style,
        cap_style, join_style);

    /* fill style is solid */
    XSetFillStyle(dsp, gc, FillSolid);

    return gc;
}

