
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

/* we shall need the complex math functions */
#include "v.h"

Window create_borderless_topwin(Display *dsp,
                         int width, int height,
                         int x, int y, int bg_color);

GC create_gc(Display *dsp, Window win);

int X_error_handler(Display *dsp, XErrorEvent *errevt);

uint64_t timediff( struct timespec st, struct timespec en );

/* A quick and dirty prototype of the basic ideas where we shall just
 * return the solutions to the complex cooefficient quadratic */
int intercept( cplex_type res[2],
                vec_type *sign,
                vec_type *loc,
                vec_type *axi,
                vec_type *obs_p,
                vec_type *obs_v );

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
    struct timespec soln_t0, soln_t1;

    /* some primordial vars */
    int disp_width, disp_height, width, height;
    int conn_num, screen_num, depth;
    int j, k, p, q, offset_x, offset_y, lx, ly, ux, uy, px, py;
    int eff_width, eff_height, vbox_w, vbox_h;

    /* The vbox idea on the table is to create an array of
     * pointers to some sort of a magic struct wherein we
     * can gather up the data for a view box region. 
     *
     * At this time we have no idea what that struct looks
     * like or how we are going to dispatch out to POSIX
     * thread type workers.
     *
     * However, having said all that, it is clear that we
     * need to take advantage of parallel processing in some
     * manner. My preference is to look at NVidia CUDA style
     * workers. Eventually.
     */

    /* small general purpose char buffer */
    char *buf = calloc((size_t)128,sizeof(unsigned char));


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
     *
     *     This is merely example data for the display viewport :
     *     obs_x_width  = 8.0
     *     obs_y_height = 8.0
     */

    int intercept_cnt = 0;
    /* per our diagrams we are just solving for k in the complex
     * cooeficient quadratic */
    cplex_type k_val[2];

    vec_type obs_origin, obs_normal, obs_point;

    double obs_x_width, obs_y_height;

    vec_type x_prime_vec, y_prime_vec;
    vec_type tmp[3];

    /* Test case will be an observation plane at ( 12, 0, 0 ) */
    /* cplex_vec_set( &obs_origin, 12.0, 0.0, 0.0, 0.0, 0.0, 0.0); */


    /* 5 Nov 2019 let us now test for negative values due to an
     * intercept behind the observation viewport */
    cplex_vec_set( &obs_origin, 4.0, 0.0, 1.2, 0.0, 0.0, 0.0);

    /* Observation direction is along negative i_hat basis vector */
    cplex_vec_set( &obs_normal, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* viewport is 8 x 8 */
    obs_x_width = 8.0;
    obs_y_height = 8.0;

    /* TODO compute the reasonable plank constant of this
     * observation viewport. Strictly a lowest level epsilon
     * to be used for resolution. */

    double x_prime, y_prime;

    /*
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
     */

    /* x_prime_vec is < 0, 1, 0 > */
    cplex_vec_set( &x_prime_vec, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);

    /* y_prime_vec is < 0, 0, 1 > */
    cplex_vec_set( &y_prime_vec, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    /*
     *         sign_data = < 1, 1, 1 >
     *
     *         object_location = < 0, 0, 0 >
     *
     *         semi_major_axi = < 5, 2, 6 >
     *
     *         ray_direct = obs_normal where this must be a
     *                           normalized vector
     *
     */
    vec_type sign_data, object_location, semi_major_axi, ray_direct;

    /* Within the set of signs Sx, Sy, and Sz we do not care about
     * the complex component and merely want the real. The same
     * may be said for object_location, semi_major_axi and the
     * direction of our ray ray_direct */
    cplex_vec_set( &sign_data, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* by default we were using an object at the origin but we can
     * shift around for testing purposes. */
    cplex_vec_set( &object_location, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    /* Again the diagrams we used had a=5, b=2 and c=6 */
    cplex_vec_set( &semi_major_axi, 5.0, 0.0, 2.0, 0.0, 6.0, 0.0);

    /* we may need to change the sight line direction in the future
     * thus we will make a copy of the viewport plane normal vector */
    cplex_vec_copy( &ray_direct, &obs_normal );


    /* These are the initial and normalized mouse fp64 values
     * from within the observation viewport. */
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

    fprintf(stdout,"     : eff_width = %5i    eff_height = %5i\n",
                           eff_width, eff_height);

    retcode1 = XSetLineAttributes(dsp, gc, 1,
                                  LineSolid, CapButt, JoinMiter);

    fprintf(stdout,"XSetLineAttributes returns %i\n", retcode1 );

    XSetForeground(dsp, gc, WhitePixel(dsp, screen_num));
    XSetForeground(dsp, gc2, WhitePixel(dsp, screen_num));
    XSetFont(dsp, gc2, type_font);

    /* horizontal minor tic marks at every 16th of the viewport 
     * drawing area
     * printf("\n-------------------------------------------------\n");
     * printf("\n\nINFO : horizontal minor tic marks at every 16th\n");
     * p = 0;
     */

    /****************************************************************
     *
     * The viewport is made up of a neat grid of 16 x 16 little box
     * areas and we can lay down a lightly colored dashed lines to
     * indicate where they are. We may as well refer to these little
     * boxes as view box regions. Starting from the lower left at
     * vbox [0] [0] upwards to the upper most right corner which
     * we can call vbox [15] [15].
     *
     * Each of these vbox elements has a height and width in the
     * on screen pixels of :
     *
     *     vbox_w = eff_width/16
     *
     *     vbox_h = eff_height/16
     *
     * These may come in handy later to identify where the user has
     * clicked and to perhaps identify a small region that can be
     * rendered without the burder of computing the entire viewport.
     *
     ****************************************************************/
    vbox_w = eff_width/16;
    vbox_h = eff_height/16;

    for ( j=offset_x + vbox_w; j<lx; j+=vbox_w ){
        XDrawLine(dsp, win, gc, j, 8, j, 12);
        XDrawLine(dsp, win, gc, j, height - 8, j, height - 12);

        /*********** at one point we needed to see where we were ****
         * sprintf(buf,"[%02i] j = %4i   minus offset = %4i",
         *                                    p, j, j - offset_x);
         *
         * fprintf(stdout,"horizontal minor tic mark %s\n",buf);
         * k = 61 + 20 * p;
         * 
         * note the gc2 default color above 
         *
         * XDrawImageString(dsp,win2,gc2,10,k,buf,strlen(buf));
         * p += 1;
         */

    }
    XFlush(dsp);

    XSetForeground(dsp, gc2, green.pixel);
    /* vertical minor tic marks at every 16th of the interior viewport
     * drawing area 
     *
     * p = 0;
     * */
    for ( j = offset_y + vbox_h; j < ly; j += vbox_h ){
        XDrawLine(dsp, win, gc, 8, j, 12, j);
        XDrawLine(dsp, win, gc, width - 8, j, width - 12, j);
        /*
         *  sprintf(buf,"[%02i] j = %4i   minus offset = %4i",
         *                                          p, j, j - offset_y);
         *
         * fprintf(stdout,"vertical minor tic mark %s\n",buf);
         * k = 60 + 20 * p;
         * XDrawImageString(dsp,win2,gc2,40,k,buf,strlen(buf));
         * p += 1;
         */

    }
    XFlush(dsp);

    /* We need an inner grid which is a very very dark grey.
     * Here we manually define the rgb components using 16bit
     * values and then create the new color */
    color_cell.flags= DoRed | DoGreen | DoBlue;
    color_cell.red = 0x1f00;
    color_cell.green = 0x1f00;
    color_cell.blue = 0x1f00;
    XAllocColor(dsp, screen_colormap, &color_cell);

    /* now we use the color we created */
    XSetForeground(dsp,gc,color_cell.pixel);

    /* draw the vertical lines */
    for ( j= offset_x + vbox_w; j<lx; j+=vbox_w ){
        XDrawLine(dsp, win, gc, j, 13, j, height-13);
    }

    /* draw the horizontal lines */
    for ( j = offset_y + vbox_h; j<ly; j+=vbox_h ){
        XDrawLine(dsp, win, gc, 13, j, width-13, j);
    }

    /* a center white pixel */
    XSetForeground(dsp, gc, XWhitePixel(dsp, screen_num));
    XDrawPoint(dsp, win, gc,
               offset_x + (eff_width/2), offset_y + (eff_height/2) );

    /* outer edge green lines and green text as default */
    XSetForeground(dsp, gc, green.pixel);
    XSetForeground(dsp, gc2, green.pixel);
    XSetForeground(dsp, gc3, green.pixel);
    XDrawLine(dsp, win, gc, 10, 10, width - 10, 10);
    XDrawLine(dsp, win, gc, width - 10, 10, width - 10, height - 10);
    XDrawLine(dsp, win, gc, width - 10, height - 10, 10, height - 10);
    XDrawLine(dsp, win, gc, 10, height - 10, 10, 10);

    XFlush(dsp);

    /* TODO : at the moment the only events we are trapping are
     * the mouse buttons but in the future we will want to redraw
     * and re-expose the window if there other event types */
    XGrabPointer(dsp, win, False, ButtonPressMask, GrabModeAsync,
                           GrabModeAsync, None, None, CurrentTime);

    XSelectInput(dsp, win, ButtonPressMask);

    /* Display timing data in the lower right window */
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

    /* plot some points on the grid that we created */
    XSetForeground(dsp, gc, yellow.pixel);
    XDrawPoint(dsp, win, gc, 5, 5);
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

                    case Button2: /* middle mouse button */
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

                /* we are inside the primary window plotting region
                 * so lets try to create floating point values for
                 * the coordinates selected. We start with just a
                 * normalized value from zero to one. */

                win_x = ( 1.0 * ( mouse_x - offset_x ) ) / eff_width;

                win_y = ( 1.0 * ( eff_height - mouse_y + offset_y ) )
                                                            / eff_height;

                /* lets try to invert the y axis */
                sprintf(buf,"adj [ %4i , %4i ]  ",
                             mouse_x - offset_x,
                             eff_height - mouse_y + offset_y );

                XSetForeground(dsp, gc2, green.pixel);
                XDrawImageString( dsp, win2, gc2, 20, 200,
                                                       buf, strlen(buf));

                sprintf(buf,"fp64( %8.6g , %8.6g )", win_x, win_y );
                XDrawImageString( dsp, win2, gc2, 20, 220,
                                                       buf, strlen(buf));

                sprintf(buf,"int [ %4i , %4i ]", mouse_x, mouse_y );
                XDrawImageString( dsp, win2, gc2, 20, 240,
                                                       buf, strlen(buf));

                /* Off set the floating point values such that the
                 * center point shall be ( 0.0, 0.0 ) */
                win_x = win_x * 2.0 - 1.0;
                win_y = win_y * 2.0 - 1.0;

                XSetForeground(dsp, gc2, red.pixel);
                sprintf(buf,"fp64( %8.6g , %8.6g )", win_x, win_y );
                XDrawImageString( dsp, win2, gc2, 20, 260,
                                                       buf, strlen(buf));

                /* At this moment we have normalized values for a
                 * location within the observation viewport. We can
                 * scale those values by half of the viewport width
                 * and height to get actual x_prime and y_prime
                 * values.
                 *
                 * All of the above allows us to compute a starting
                 * L_0 point on the observation plane in R3 and in
                 * the coordinate system of the observation object.
                 *
                 * Note the x_prime = obs_x_width * win_x / 2.0
                 *          y_prime = obs_y_height * win_y / 2.0
                 *
                 * obs_point = x_prime * x_prime_vec
                 *           + y_prime * y_prime_vec
                 *           + obs_origin
                 *
                 */

                x_prime = obs_x_width * win_x / 2.0;
                y_prime = obs_y_height * win_y / 2.0;

                XSetForeground(dsp, gc3, yellow.pixel);

                sprintf(buf," x' ,  y' = ( %8.6g , %8.6g )",
                              x_prime, y_prime );

                XDrawImageString( dsp, win3, gc3, 30, 50,
                                  buf, strlen(buf));

                /* computer the observation point */
                cplex_vec_scale( tmp, &x_prime_vec, x_prime );
                cplex_vec_scale( tmp+1, &y_prime_vec, y_prime );
                cplex_vec_add( tmp+2, tmp, tmp+1);
                cplex_vec_add( tmp, tmp+2, &obs_origin );
                cplex_vec_copy( &obs_point, tmp );

                sprintf(buf,"L = < %8.6g , %8.6g, %8.6g >",
                        obs_point.x.r, obs_point.y.r, obs_point.z.r );

                XDrawImageString( dsp, win3, gc3, 30, 70,
                                  buf, strlen(buf));

                /* time the computation of the intercepts */
                clock_gettime( CLOCK_MONOTONIC, &soln_t0 );

                intercept_cnt = intercept ( k_val, &sign_data,
                                &object_location, &semi_major_axi,
                                &obs_point, &obs_normal );

                clock_gettime( CLOCK_MONOTONIC, &soln_t1 );

                /* figure out if we have a real root. */
                if ( ( k_val[0].i == 0.0 ) || ( k_val[1].i == 0.0 ) ) {
                    if ( ( k_val[0].i == 0.0 ) && ( k_val[1].i == 0.0 ) ) {
                        /* two real roots.  pick the value that is not
                         * negative and also closest to the viewport */
                        if ( ( k_val[0].r < 0.0 ) && ( k_val[1].r >= 0.0 ) ) {
                            /* we have a root in k_val[1].r */
                            XDrawPoint(dsp, win, gc, mouse_x, mouse_y);
                            sprintf(buf,"icept1 = %8.6g     ", k_val[1].r );
                        } else if ( 
                                    ( k_val[0].r >= 0.0 )
                                    &&
                                    ( k_val[1].r < 0.0 ) ) {

                            /* we have a root in k_val[0].r */
                            XDrawPoint(dsp, win, gc, mouse_x, mouse_y);
                            sprintf(buf,"icept0 = %8.6g     ", k_val[0].r );

                        } else if ( 
                                    ( fabs( k_val[0].r ) < 0.001 )
                                    &&
                                    ( k_val[1].r > 0.0 ) ) {

                            /* viewport intersects the object */
                            XSetForeground(dsp, gc, red.pixel);
                            XDrawPoint(dsp, win, gc, mouse_x, mouse_y);
                            XSetForeground(dsp, gc, yellow.pixel);
                            sprintf(buf,"icept1v= %8.6g     ", k_val[1].r );

                        } else if (
                                    ( fabs( k_val[1].r ) < 0.001 )
                                    &&
                                    ( k_val[0].r > 0.0 ) ) {

                            /* this is also the viewport intersects the
                             * object */
                            XSetForeground(dsp, gc, red.pixel);
                            XDrawPoint(dsp, win, gc, mouse_x, mouse_y);
                            XSetForeground(dsp, gc, yellow.pixel);
                            sprintf(buf,"icept0^= %8.6g     ", k_val[0].r );

                        } else if ( k_val[0].r < k_val[1].r ) {

                            /* so root 0 is real and closer */
                            XDrawPoint(dsp, win, gc, mouse_x, mouse_y);
                            sprintf(buf,"icept0c= %8.6g     ", k_val[0].r );

                        } else if ( k_val[1].r < k_val[0].r ) {

                            /* root 1 is real and closer */
                            XDrawPoint(dsp, win, gc, mouse_x, mouse_y);
                            sprintf(buf,"icept1c= %8.6g     ", k_val[1].r );

                        } else if (
                                    ( ( k_val[1].r - k_val[0].r ) < 0.001 )
                                    && ( k_val[0].r > 0.0 )
                                    && ( k_val[1].r > 0.0 ) ) {
                            /* we hit close enough to the edge of something */
                            /* TODO calculate a reasonable epsilon value */
                            XSetForeground(dsp, gc, green.pixel);
                            XDrawPoint(dsp, win, gc, mouse_x, mouse_y);
                            XSetForeground(dsp, gc, yellow.pixel);
                            sprintf(buf,"icept0== %8.6g     ", k_val[0].r );

                        }
                    } else {

                        /* bizarre condition wherein we have only a
                         * single real root */

                        if ( k_val[0].r >= 0.0 ) {

                            /* root 0 is the only real value */
                            XDrawPoint(dsp, win, gc, mouse_x, mouse_y);
                            sprintf(buf,"ICEPT0 = %8.6g     ", k_val[0].r );

                        } else if ( k_val[1].r >= 0.0 ) {

                            /* root 1 is all that is left to us */
                            XDrawPoint(dsp, win, gc, mouse_x, mouse_y);
                            sprintf(buf,"ICEPT1 = %8.6g     ", k_val[1].r );

                        }
                    }

                    XDrawImageString( dsp, win3, gc3, 30, 150,
                                      buf, strlen(buf));

                }

                t_delta = timediff( soln_t0, soln_t1 );
                sprintf(buf,"[soln] = %16lld nsec", t_delta);

                XDrawImageString( dsp, win3, gc3, 30, 180,
                                  buf, strlen(buf));


                sprintf(buf,"root 0 = ( %8.6g + %8.6g i )       ",
                        k_val[0].r, k_val[0].i );

                XDrawImageString( dsp, win3, gc3, 30, 90,
                                  buf, strlen(buf));

                sprintf(buf,"root 1 = ( %8.6g + %8.6g i )       ",
                        k_val[1].r, k_val[1].i );

                XDrawImageString( dsp, win3, gc3, 30, 110,
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

