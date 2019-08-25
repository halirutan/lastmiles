
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

int main( int argc, char *argv[])
{

    Display *display;
    Window win;

    /* This GC is the graphics context and it will hold
     * all manner of characteristics and properties of
     * how stuff gets drawn ( or not ) on the screen.
     * This includes line style type stuff. */
    GC gc;

    Colormap screen_colormap;
    XColor red, green, blue, yellow, cyan, truecolor;

    int x1, y1, x2, y2;   /* some line perhaps */

    unsigned int sleep_time = 15;
    unsigned int slept_time = 0;

    char *disp_name = NULL;
    display = XOpenDisplay(disp_name);
    if ( display == NULL ){
        fprintf( stderr, "FAIL: we did not get a display.\n");
        exit ( EXIT_FAILURE );
    }
    printf ("INFO : we have a display from the env var DISPLAY\n");

    int conn_num = XConnectionNumber(display);
    printf ("INFO : we have a connection number %i\n", conn_num );

    int screen_num = DefaultScreen(display);
    printf ("INFO : we have a default screen number %i\n", screen_num);

    int depth = XDefaultDepth(display, screen_num);
    printf ("INFO : we have a default color depth of %i\n", depth);

    int disp_width = XDisplayWidth(display, screen_num);
    printf ("INFO : looks like display is %i pixels wide\n", disp_width);

    int disp_height = XDisplayHeight(display, screen_num);
    printf ("INFO : looks like display is %i pixels high\n", disp_height);

    /* does not seem to work for me ... maybe for you? 
     *int disp_width_mm = XDisplayWidthMM(display, screen_num);
     *printf ("INFO : looks like display is %i mm wide\n", disp_width);
     *
     *int disp_height_mm = XDisplayHeightMM(display, screen_num);
     *printf ("INFO : looks like display is %i mm high\n", disp_height);
     */

    screen_colormap = XDefaultColormap( display, screen_num);

    if (XAllocNamedColor( display, screen_colormap,
                         "red", &red, &red) == 0) {
        fprintf(stderr, "XAllocNamedColor - no red color?\n");
        exit(EXIT_FAILURE);
    }

    if (XAllocNamedColor( display, screen_colormap,
                         "green", &green, &green) == 0) {
        fprintf(stderr, "XAllocNamedColor - no green color?\n");
        exit(EXIT_FAILURE);
    }

    if (XAllocNamedColor( display, screen_colormap,
                         "blue", &blue, &blue) == 0) {
        fprintf(stderr, "XAllocNamedColor - red and green okay but blue??\n");
        exit(EXIT_FAILURE);
    }

    if (XAllocNamedColor( display, screen_colormap,
                         "yellow", &yellow, &yellow) == 0) {
        fprintf(stderr, "XAllocNamedColor - yellow bork bork bork!\n");
        exit(EXIT_FAILURE);
    }

    if (XAllocNamedColor( display, screen_colormap,
                         "cyan", &cyan, &cyan) == 0) {
        fprintf(stderr, "XAllocNamedColor - cyan bork bork bork!\n");
        exit(EXIT_FAILURE);
    }


    /*
     * Window XCreateSimpleWindow(Display *display,
     *                            Window parent,
     *                            int x, y,       <<--- offset from upper left
     *                            unsigned int width, height,
     *                            unsigned int border_width,
     *                            unsigned long border,
     *                            unsigned long background);
     *
     *
     * unsigned long XBlackPixel(Display *display, int screen_number);
     *     return the black pixel value for the specified screen.
     *
     *
     * unsigned long XWhitePixel(Display *display, int screen_number);
     *     return the white pixel value for the specified screen.
     *
     */

    Window wn = XCreateSimpleWindow( display,
                                     RootWindow(display, screen_num),
                                     500, 300, 
                                     200, 400,
                                     16,
                                     XWhitePixel( display, screen_num),
                                     XBlackPixel( display, screen_num) );


    /*  This is a complex function with many pages of docs.
     *
     * To create a new GC that is usable on a given screen with a depth
     * of drawable window wn, use XCreateGC.
     *
     *    GC XCreateGC(Display *display,
     *                 Drawable drawable,
     *                 unsignedlong valuemask,
     *                 XGCValues *values);
     *
     * drawable --> Specifies the drawable thing?  wtf ?
     *
     * valuemask specifies which components in the GC are to be
     *           this is a 32 bit mask of bits that turn on and off various
     *           graphics features.
     *
     * values specifies any values as specified by the valuemask.
     *
     * The XCreateGC function creates a graphics context and returns a
     * GC. The GC can be used with any destination drawable having the
     * same root and depth as the specified drawable.
     */

    unsigned long valuemask = 0;
    XGCValues values;
    unsigned int line_width = 2;
    int line_style = LineSolid;
    int cap_style = CapButt;
    int join_style = JoinBevel;

    gc = XCreateGC( display, wn, valuemask, &values);
    XSync( display, False);

    /* line style */
    XSetLineAttributes(display, gc, line_width, line_style, cap_style, join_style);

    /* fill style is solid */
    XSetFillStyle(display, gc, FillSolid);


    XClearWindow( display, wn );

    XSetForeground( display, gc, XWhitePixel(display, screen_num));
    XSetBackground( display, gc, XBlackPixel(display, screen_num));

    XDrawPoint( display, wn, gc, 20, 32);

    /* draw a blue box around the win */
    XDrawRectangle( display, win, gc, 10, 20, 180, 380);

    XMapWindow( display, wn );

    XFlushGC( display, gc );  /* send a pending messages to the Xserver */

                                     
    printf ("INFO : we shall sleep %d secs\n", sleep_time );
    slept_time = sleep( sleep_time );

    return ( EXIT_SUCCESS );

}

