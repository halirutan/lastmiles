
#include <X11/Xlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

Window create_borderless_topwin(Display *dsp,
                         int width, int height,
                         int x, int y, int bg_color);

GC create_gc(Display *dsp, Window win);

int X_error_handler(Display *dsp, XErrorEvent *errevt);

uint64_t timediff( struct timespec st, struct timespec en );

/* local defs */
#define WIN_WIDTH 660
#define WIN_HEIGHT 660
#define OFFSET 10

int main(int argc, char*argv[])
{
    /* our display and window and graphics context */
    Display *dsp;
    Window win, win2, win3;
    GC gc, gc2, gc3;
    Colormap screen_colormap;
    XEvent event;
    Font fixed_font, type_font;

    /* a very few colours */
    XColor red, green, blue, yellow, color_cell, truecolor;

    Status retcode0;  /* not really needed for trivial stuff */
    int retcode1;     /* curious what some funcs return */

    /* setup mouse x and y */
    int mouse_x = -1, mouse_y = -1;

    /* these next five are just mouse button counters where the
     * roll_up and roll_dn are mouse wheel events */
    int button, left_count, mid_count, right_count, roll_up, roll_dn;
    left_count = 0;
    mid_count = 0;
    right_count = 0;
    roll_up = 0;
    roll_dn = 0;

    uint64_t t_delta; /* left mouse button click timing */
    struct timespec t0, t1;

    /* some primordial vars */
    int disp_width, disp_height, width, height;
    int conn_num, screen_num, depth;
    int j, k, p, q, offset_x, offset_y, lx, ly, ux, uy, px, py;
    int eff_width, eff_height;
    float radian_angle, s;
    char *buf;


    /* The whole objective here is to map a point on the display
     * to the observation plane for ray tracing.
     *
     * Therefore we need some very basic data about the actual
     * observation plane such as the location and the plane
     * normal vector. We need the dimensions of the observation
     * viewport which is really just a part of the plane.
     *
     *     obs_loc = < 12, 0, 0 >
     *     obs_vec = < -1, 0, 0 >
     *     obs_x_width = 6.0
     *     obs_y_height = 6.0
     *
     * We will also require the coordinate basis vectors within
     * the observation plane.
     *
     *     obs_x_hat_prime = < 0, 1, 0 >
     *     obs_y_hat_prime = < 0, 0, 1 >
     *
     * It should be reasonably clear that a click of the mouse
     * within the active display region of our primary window
     * will result in an x_prime and y_prime pair. The Xll xlib
     * return mouse click coordinates referenced to the graphics
     * context and the window therein. This means we get possibly
     * negative coordinates from a mouse click that is left and
     * above the upper left corner of our grey window win.
     *
     * This will only make sense if mouse_x > offset and also
     * mouse_x < eff_width + offset.
     *
     *     win_x = ( mouse_x - offset ) / eff_width
     *     win_y = ( mouse_y - offset ) / eff_height
     *
     *
     *
     *
     *
     * no idea what this crud is .. cant recall ...
     *    x_prime = ( eff_width / 2 ) + ( obs_x_width / eff_width )
     *
     *
     *
     *
     */
    double win_x, win_y;

    width = WIN_WIDTH;
    height = WIN_HEIGHT;
    fprintf(stdout,"INFO : ");
    fprintf(stdout,"default width=%4i height=%4i\n", width, height);

    char *disp_name = NULL;
    XSetErrorHandler(X_error_handler);

    /* should work with a null display name */
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

    fixed_font = XLoadFont(dsp, "fixed");

    /* really we need to get a list of the available fonts and then
     * use one that should work in the correct size
     */
    type_font = XLoadFont(dsp, "lucidasanstypewriter-10");

    disp_width = DisplayWidth(dsp, screen_num);
    disp_height = DisplayHeight(dsp, screen_num);

    printf("display seems to be %i wide and %i high.\n",
                                   disp_width, disp_height);

    if ((disp_width<width)||(disp_height<height)){
        fprintf(stderr, "ERROR: screen is too small\n\n");
        exit(EXIT_FAILURE);
    }

    /* hard coded screen offset */
    offset_x = 40;
    offset_y = 40;

    printf("INFO : offset x=%i y=%i\n", offset_x, offset_y);

    /* Our primary plotting windows is pale grey on the screen */
    win = create_borderless_topwin(dsp, width, height,
                                        offset_x, offset_y,
                                        0x0f0f0f);
    gc = create_gc(dsp, win);

    /* create a smaller darker window to the right */
    win2 = create_borderless_topwin(dsp, 400, 300, 720, 60, 0x000020);
    gc2 = create_gc(dsp, win2);

    /* create another small window below that */
    win3 = create_borderless_topwin(dsp, 400, 300, 720, 380, 0x080808 );
    gc3 = create_gc(dsp, win2);

    XSync(dsp, False);

    screen_colormap = XDefaultColormap(dsp, DefaultScreen(dsp));
    if (XAllocNamedColor(dsp,
                         screen_colormap,
                         "red", &red, &red) == 0) {
        fprintf(stderr, "XAllocNamedColor - no red color?\n");
        exit(EXIT_FAILURE);
    }
    if (XAllocNamedColor(dsp,
                         screen_colormap,
                         "green", &green, &green) == 0) {
        fprintf(stderr, "XAllocNamedColor - red works but green no??\n");
        exit(EXIT_FAILURE);
    }
    if (XAllocNamedColor(dsp,
                         screen_colormap,
                         "blue", &blue, &blue) == 0) {
        fprintf(stderr, "XAllocNamedColor - red and green okay but blue??\n");
        exit(EXIT_FAILURE);
    }
    if (XAllocNamedColor(dsp,
                         screen_colormap,
                         "yellow", &yellow, &yellow) == 0) {
        fprintf(stderr, "XAllocNamedColor - yellow bork bork bork!\n");
        exit(EXIT_FAILURE);
    }

    /* yellow pixel at each corner 5 pixels indented */
    XSetForeground(dsp, gc, yellow.pixel);
    XDrawPoint(dsp, win, gc, 5, 5);
    XDrawPoint(dsp, win, gc, 5, height - 5);
    XDrawPoint(dsp, win, gc, width - 5, 5);
    XDrawPoint(dsp, win, gc, width - 5, height - 5);

    /* draw a red box inside the second window */
    XSetForeground(dsp, gc2, red.pixel);
    retcode1 = XSetLineAttributes(dsp, gc2, 1, LineSolid, CapButt, JoinMiter);
    fprintf(stdout,"gc2 XSetLineAttributes returns %i\n", retcode1 );
    XDrawRectangle(dsp, win2, gc2, 5, 5, 390, 290);

    /* draw a yellow box inside the third window */
    XSetForeground(dsp, gc3, yellow.pixel);
    retcode1 = XSetLineAttributes(dsp, gc3, 1, LineSolid, CapButt, JoinMiter);
    fprintf(stdout,"gc3 XSetLineAttributes returns %i\n", retcode1 );
    XDrawRectangle(dsp, win3, gc3, 5, 5, 390, 290);

    /* initial line characteristics on the gc are set in the XCreateGC
     * calls that we do.
     *
     * https://www.x.org/archive/X11R7.7/doc/man/man3/XSetLineAttributes.3.xhtml
     */

    /* set our graph box inside by OFFSET pixels
     *
     * reuse the offset_foo vars from above as we do not
     * need them for window location anymore. So we can
     * use them as interior offset distances for our plot.
     */
    offset_x = 10;
    offset_y = 10;
    fprintf(stdout,"INFO : offset_x = %i  offset_y = %i\n", offset_x, offset_y );

    /* upper left point */
    ux = offset_x;
    uy = offset_y;

    /* lower right point */
    lx = width - offset_x;
    ly = height - offset_y;
    fprintf(stdout,"     : ( %5i , %5i ) to ( %5i , %5i )\n", ux, uy, lx, ly);

    /* therefore we have effective box width and height */
    eff_width = lx - ux;
    eff_height = ly - uy;
    fprintf(stdout,"     : eff_width = %5i    eff_height = %5i\n", eff_width, eff_height);

    retcode1 = XSetLineAttributes(dsp, gc, 1, LineSolid, CapButt, JoinMiter);
    fprintf(stdout,"XSetLineAttributes returns %i\n", retcode1 );

    /* make up a small char buffer */
    buf = calloc((size_t)128,sizeof(unsigned char));

    XSetForeground(dsp, gc, WhitePixel(dsp, screen_num));
    /* XSetForeground(dsp, gc2, yellow.pixel); */
    XSetFont(dsp, gc2, type_font);

    /* horizontal minor tic marks at every 16th */
    printf("\n-------------------------------------------------\n");
    printf("\n\nINFO : horizontal minor tic marks at every 16th\n");
    p = 0;
    for ( j=(offset_x + (eff_width/16)); j<lx; j+=(eff_width/16) ){
        XDrawLine(dsp, win, gc, j, 8, j, 12);
        XDrawLine(dsp, win, gc, j, height - 8, j, height - 12);
        sprintf(buf,"[%02i] j = %4i   minus offset = %4i", p, j, j - offset_x);
        /* fprintf(stdout,"horizontal minor tic mark %s\n",buf); */
        /* k = 61 + 20 * p; */
        /* note that the gc2 default color was commented out above */
        /* XDrawImageString(dsp,win2,gc2,10,k,buf,strlen(buf)); */
        p += 1;
    }
    XFlush(dsp);

    XSetForeground(dsp, gc2, green.pixel);
    /* vertical minor tic marks at every 16th */
    p = 0;
    for ( j = offset_y + (eff_height/16); j < ly; j = j + (eff_height/16) ){
        XDrawLine(dsp, win, gc, 8, j, 12, j);
        XDrawLine(dsp, win, gc, width - 8, j, width - 12, j);
        sprintf(buf,"[%02i] j = %4i   minus offset = %4i", p, j, j - offset_y);
        /* fprintf(stdout,"vertical minor tic mark %s\n",buf); */
        k = 60 + 20 * p;
        /* XDrawImageString(dsp,win2,gc2,40,k,buf,strlen(buf)); */
        p += 1;
    }
    XFlush(dsp);

    /* now we need an inner grid which is a very very dark grey.
     * Here we manually define the rgb components using 16bit
     * values and then create the new color */
    color_cell.flags= DoRed | DoGreen | DoBlue;
    color_cell.red = 0x1f00;
    color_cell.green = 0x1f00;
    color_cell.blue = 0x1f00;
    XAllocColor(dsp, screen_colormap, &color_cell);

    /* now we use the color we created */
    XSetForeground(dsp,gc,color_cell.pixel);
    for ( j=(offset_x + (eff_width/16)); j<lx; j+=(eff_width/16) ){
        XDrawLine(dsp, win, gc, j, 13, j, height-13);
    }
    for ( j = offset_y + (eff_height/16); j < ly; j = j + (eff_height/16) ){
        XDrawLine(dsp, win, gc, 13, j, width-13, j);
    }
    /* a dead center white pixel */
    XSetForeground(dsp, gc, XWhitePixel(dsp, screen_num));
    XDrawPoint(dsp, win, gc,
            offset_x + (eff_width/2), offset_y + (eff_height/2) );

    XFlush(dsp);


    /* outer edge green lines */
    XSetForeground(dsp, gc, green.pixel);
    XDrawLine(dsp, win, gc, 10, 10, width - 10, 10);
    XDrawLine(dsp, win, gc, width - 10, 10, width - 10, height - 10);
    XDrawLine(dsp, win, gc, width - 10, height - 10, 10, height - 10);
    XDrawLine(dsp, win, gc, 10, height - 10, 10, 10);

    /* RGB values for a dark green */
    color_cell.flags= DoRed | DoGreen | DoBlue;
    color_cell.red = 0;
    color_cell.green = 0x5f00;
    color_cell.blue = 0;

    /* output text to win2 */
    if ( XAllocColor(dsp, screen_colormap, &color_cell) == 0 ){
        fprintf(stderr,"WARN : XAllocColor failed\n");
    } else {
        /* watch for gc2 and win2 here */
        XSetForeground(dsp,gc2,color_cell.pixel);
        XDrawImageString(dsp,win2,gc2,20,20,"RGB color 0 0x5f00 0",20);
        XFlush(dsp);

        /* now by name */
        if (XAllocNamedColor(dsp,screen_colormap,
                             "red", &color_cell, &truecolor) == 0) {
            fprintf(stderr,"WARN : Color '%s' unknown\n", "red");
        } else {
            if (truecolor.red != color_cell.red ||
                truecolor.green != color_cell.green ||
                truecolor.blue != color_cell.blue)
                    fprintf(stderr,"WARN : %s color may be wrong\n", "red");
        }

        XSetForeground(dsp,gc2,color_cell.pixel);
        XDrawImageString(dsp,win2,gc2,20,40, "named color",11);
    }

    XFlush(dsp); /* flush all pending */

    /* TODO : at the moment the only events we are trapping are
     * the mouse buttons but in the future we will want to redraw
     * and re-expose the window if there other event types */
    XGrabPointer(dsp, win, False, ButtonPressMask, GrabModeAsync,
                           GrabModeAsync, None, None, CurrentTime);

    XSelectInput(dsp, win, ButtonPressMask);

    /* we need to display timing data or whatever in the lower
     * right window */
    XSetForeground(dsp, gc3, green.pixel);
    XSetForeground(dsp, gc2, green.pixel);
    XSetFont(dsp, gc3, type_font);

    /* some initial time data before anyone clicks anything */
    clock_gettime( CLOCK_MONOTONIC, &t0 );
    clock_gettime( CLOCK_MONOTONIC, &t1 );
    t_delta = timediff( t0, t1 );
    sprintf(buf,"[0000] tdelta = %16lld nsec", t_delta);
    XDrawImageString( dsp, win3, gc3, 20, 20, buf, strlen(buf));

    /* draw a red box inside the third window for ray trace data */
    XSetForeground(dsp, gc3, red.pixel);
    retcode1 = XSetLineAttributes(dsp, gc3, 1, LineSolid, CapButt, JoinMiter);
    XDrawRectangle(dsp, win3, gc3, 10, 30, 380, 260);
    XSetForeground(dsp, gc3, green.pixel);

    /* TODO at some point check for why we are fetching the x and y
     * values over and over and over inside the switch-case */
    while(1){

        XNextEvent(dsp,&event);

        switch(event.type){
            case ButtonPress:
                switch(event.xbutton.button){
                    case Button1: /* left mouse button */
                        mouse_x=event.xbutton.x;
                        mouse_y=event.xbutton.y;
                        button=Button1;
                        left_count += 1;
                        break;

                    case Button2: /* middle mouse button or scroll wheel click */
                        mouse_x=event.xbutton.x;
                        mouse_y=event.xbutton.y;
                        button=Button2;
                        mid_count += 1;
                        break;

                    case Button3: /* right mouse button */
                        mouse_x=event.xbutton.x;
                        mouse_y=event.xbutton.y;
                        button=Button3;
                        right_count += 1;
                        break;

                    case Button4: /* mouse scroll wheel up */
                        mouse_x=event.xbutton.x;
                        mouse_y=event.xbutton.y;
                        button=Button4;
                        roll_up += 1;
                        break;

                    case Button5: /* mouse scroll wheel down */
                        mouse_x=event.xbutton.x;
                        mouse_y=event.xbutton.y;
                        button=Button5;
                        roll_dn += 1;
                        break;

                    default:
                        break;
                }
            break;
        default:
            break;
        }

        sprintf(buf,"raw  [ %4i , %4i ]  ", mouse_x, mouse_y);
        XSetForeground(dsp, gc2, red.pixel);
        XDrawImageString( dsp, win2, gc2, 20, 180, buf, strlen(buf));

        /* adjustment of one or two pixels */
        mouse_x = mouse_x - 1;
        mouse_y = mouse_y - 2;

        if ( button == Button1 ){

            printf("leftclick");

            if (    ( mouse_x >=  offset_x )  && ( mouse_y >= offset_y )
                 && ( mouse_x < ( eff_width + offset_x ) )
                 && ( mouse_y < ( eff_height + offset_y ) ) ) {

                /* we are inside the primary window plotting region */
                win_x = ( 1.0 * ( mouse_x - offset_x ) ) / eff_width;

                /* lets try to invert the y axis */
                sprintf(buf,"adj [ %4i , %4i ]  ",
                              mouse_x - offset_x,
                              eff_height - mouse_y + offset_y );

                XSetForeground(dsp, gc2, green.pixel);
                XDrawImageString( dsp, win2, gc2, 20, 200,
                                                       buf, strlen(buf));

                win_y = ( 1.0 * ( eff_height - mouse_y + offset_y ) )
                                                            / eff_height;

                sprintf(buf,"fp64( %8.6g , %8.6g )", win_x, win_y );
                XDrawImageString( dsp, win2, gc2, 20, 220,
                                                       buf, strlen(buf));

                sprintf(buf,"[ %4i , %4i ]", mouse_x, mouse_y );
                XDrawImageString( dsp, win2, gc2, 20, 240,
                                                       buf, strlen(buf));

                /* center point shall be ( 0.0, 0.0 ) */
                win_x = win_x * 2.0 - 1.0;
                win_y = win_y * 2.0 - 1.0;

                XSetForeground(dsp, gc2, red.pixel);
                sprintf(buf,"fp64( %8.6g , %8.6g )", win_x, win_y );
                XDrawImageString( dsp, win2, gc2, 20, 260,
                                                       buf, strlen(buf));

            }

        } else if ( button == Button2 ) {

            printf("midclick");

        } else if ( button == Button3 ) {

            printf("rightclick");
            clock_gettime( CLOCK_MONOTONIC, &t1 );
            t_delta = timediff( t0, t1 );

            sprintf(buf,"[%04i] tdelta = %16lld nsec",
                                            right_count, t_delta);

            /* k = 20 + ( right_count%5 ) * 20; */
            XDrawImageString( dsp, win3, gc3, 20, 20,
                               buf, strlen(buf));

            t0.tv_sec = t1.tv_sec;
            t0.tv_nsec = t1.tv_nsec;
            /* If a 200ms right double click anywhere then quit */
            if ( t_delta < 200000000 ) break;


        } else if ( button == Button4 ) {
            /* TODO note that a mouse wheel event being used here to
             * track observation plane position will result in all
             * data being redrawn. */
            printf("roll up");

        } else if ( button == Button5 ) {

            printf("roll down");

        } else {

            printf("unknown button");

        }

        printf(" at %d %d \n", mouse_x, mouse_y);

    }

    XCloseDisplay(dsp);

    return EXIT_SUCCESS;
}

