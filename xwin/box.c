
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

Window
create_borderless_topwin(Display *dsp,
                         int offset_x, int offset_y,
                         int width, int height,
                         int bg_color);

GC
create_gc(Display *display, Window win);

int main( int argc, char *argv[])
{

    Display *display;
    char *disp_name = NULL;
    int conn_num, screen_num, depth, disp_width, disp_height;
    int offset_x, offset_y, width, height;

    Colormap screen_colormap;
    XColor red, green, blue, yellow, cyan, orange, truecolor;

    /* some coordinates to be use later */
    int x1, y1, x2, y2;

    unsigned int sleep_time = 15;
    unsigned int slept_time = 0;

    display = XOpenDisplay(disp_name);
    if ( display == NULL ){
        fprintf( stderr, "FAIL: we did not get a display.\n");
        exit ( EXIT_FAILURE );
    }
    printf ("INFO : we have a display from the env var DISPLAY\n");

    conn_num = XConnectionNumber(display);
    printf ("INFO : we have a connection number %i\n", conn_num );

    screen_num = DefaultScreen(display);
    printf ("INFO : we have a default screen number %i\n", screen_num);

    depth = XDefaultDepth(display, screen_num);
    printf ("INFO : we have a default color depth of %i\n", depth);

    disp_width = XDisplayWidth(display, screen_num);
    printf ("INFO : looks like display is %i pixels wide\n", disp_width);

    disp_height = XDisplayHeight(display, screen_num);
    printf ("INFO : looks like display is %i pixels high\n", disp_height);

    /*
     * For reasons unknown I do not get actual measurements from these
     * calls. Perhaps because I am using a dual head display.
     *
     * int disp_width_mm = XDisplayWidthMM(display, screen_num);
     * printf ("INFO : looks like display is %i mm wide\n", disp_width);
     *
     * int disp_height_mm = XDisplayHeightMM(display, screen_num);
     * printf ("INFO : looks like display is %i mm high\n", disp_height);
     */

    /* a few default values that seem to work with Twitch OBS stream */

    offset_x = 10;  /* across to the right from the left border */
    offset_y = 10;  /* down from the top border */
    width = 1240;
    height = 700;

    /* however we should allow for options */
    if ( argc > 4 ) {
        /* lets assume that the order is offset x and y and 
         * then width and height on the command line. */
        offset_x = atoi( argv[1] );
        offset_y = atoi( argv[2] );
        width = atoi( argv[3] );
        height = atoi( argv[4] );

        /* Check for common sense */
        if (  ( offset_x < 0 ) || ( offset_y < 0 )
              || ( width < 0 ) || ( height < 0 ) ){

            fprintf (stderr, "FAIL : Please do not ask for negative coordinates.\n");
            return ( EXIT_FAILURE );

        }

        /* check we are in reasonable location on the screen */
        if ( 
                ( ( offset_x + width ) > disp_width )
                ||
                ( ( offset_y + height ) > disp_height ) ) {

            fprintf (stderr, "FAIL : Coordinates falls off the screen.\n");
            return ( EXIT_FAILURE );

        }

    }

    /* the background color is a RGB value of 0x202020h hexadecimal
     * and that is a perfect mixture of red and green and blue to give
     * up a grey window. */

    Window win = create_borderless_topwin(display,
                                         offset_x, offset_y,
                                         width, height,
                                         0x102010 );


    /* Create a Graphics Context object handle for
     * this window we just created.
     *
     * This GC is the graphics context and it will hold
     * all manner of characteristics and properties of
     * how stuff gets drawn ( or not ) on the screen.
     * This includes line style type stuff. */
    GC gc = create_gc(display, win);


    /* Lets now define a few basic trivial colors to be used on the
     * window we just created.
     *
     * Also useful is the manner in which we can fetch the current
     * display settings for trivial Black and White colors :
     *
     * unsigned long XBlackPixel(Display *display, int screen_number);
     *     return the black pixel value for the specified screen.
     *
     * unsigned long XWhitePixel(Display *display, int screen_number);
     *     return the white pixel value for the specified screen.
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

    if (XAllocNamedColor( display, screen_colormap,
                         "orange", &orange, &orange) == 0) {
        fprintf(stderr, "XAllocNamedColor - orange bork bork bork!\n");
        exit(EXIT_FAILURE);
    }

    XSync( display, False);

    XDrawPoint( display, win, gc, 20, 32);

    /* draw a blue box around the win */
    XSetForeground( display, gc, blue.pixel);
    XDrawRectangle( display, win, gc, 10, 20, 160, 360);

    XFlush( display );  /* send a pending messages to the Xserver */

    printf ("INFO : we shall sleep %d secs\n", sleep_time );
    slept_time = sleep( sleep_time );

    return ( EXIT_SUCCESS );

}

