
#include <X11/Xlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

Window create_simple_win(Display *dsp,
                         int width, int height, int border_width,
                         int x, int y);

Window create_borderless_topwin(Display *dsp,
                         int width, int height,
                         int x, int y, int bg_color);

GC create_gc(Display *dsp, Window win);

int X_error_handler(Display *dsp, XErrorEvent *errevt);

int check_ascii_input ( char *inp );

#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

/* local defs for a gc plot area */
#define WIN_WIDTH 640 
#define WIN_HEIGHT 640
#define OFFSET 10

#define CELL_COUNT 16
#define ELEMENT_COUNT 16

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

    /* some primordial vars */
    int disp_width, disp_height, width, height;
    int conn_num, screen_num, depth;
    int j, k, p, q, offset_x, offset_y, lx, ly, ux, uy, px, py;
    int eff_width, eff_height;
    float radian_angle, s;
    char *buf;

    if ( argc > 2 ) {
        /* do we have reasonable width and height ? */
        width = check_ascii_input(argv[1]);
        if ( width > 0 ) {
            fprintf(stdout,"INFO : width  %i accepted.\n", width);
        } else {
            fprintf(stderr,"FAIL : width  \"%s\" garbled.", argv[1]);
            return EXIT_FAILURE;
        }

        height = check_ascii_input(argv[2]);
        if ( height > 0 ) {
            fprintf(stdout,"INFO : height %i accepted.\n", height);
        } else {
            fprintf(stderr,"FAIL : height \"%s\" garbled.", argv[2]);
            return EXIT_FAILURE;
        }

    } else {
        width = WIN_WIDTH;
        height = WIN_HEIGHT;
        fprintf(stdout,"INFO : ");
        fprintf(stdout,"default width=%4i height=%4i\n", width, height);
    }

    char *disp_name = NULL;
    XSetErrorHandler(X_error_handler);
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
    type_font = XLoadFont(dsp, "*-lucidatypewriter-medium-r-normal-sans-14-100-100-100-*-iso8859-1");

    disp_width = DisplayWidth(dsp, screen_num);
    disp_height = DisplayHeight(dsp, screen_num);

    printf("display seems to be %i wide and %i high.\n",
                                   disp_width, disp_height);

    if ((disp_width<width)||(disp_height<height)){
        fprintf(stderr, "ERROR: screen is too small\n\n");
        exit(EXIT_FAILURE);
    }

    /* check for a dual head over wide display */
    if (((float)disp_width/(float)disp_height)>3.0F) {
        /* we shall use the left hand half of the screen
         * width and try to center on it */
        offset_x = (disp_width/2 - width)/2;
    } else {
        /* just try to center on the display */
        offset_x = (disp_width - width)/2;
    }
    offset_y = (disp_height - height)/2;

    /* temporary hack offset */
    offset_x = 40;
    offset_y = 40;

    printf("try offset x=%i y=%i\n", offset_x, offset_y);

    /* center a really pale grey window on the screen */
    win = create_borderless_topwin(dsp, width, height,
                                        offset_x, offset_y,
                                        0x0f0f0f);
    gc = create_gc(dsp, win);

    /* create a smaller darker window to the right */
    win2 = create_borderless_topwin(dsp, 400, 200, 696, 100, 0x080808);
    gc2 = create_gc(dsp, win2);

    /* create another small window below that */
    win3 = create_borderless_topwin(dsp, 400, 200, 696, 440, 0x080808);
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

    /* red pixel at each corner 5 pixels indented */
    XSetForeground(dsp, gc, red.pixel);
    XDrawPoint(dsp, win, gc, 5, 5);
    XDrawPoint(dsp, win, gc, 5, height - 5);
    XDrawPoint(dsp, win, gc, width - 5, 5);
    XDrawPoint(dsp, win, gc, width - 5, height - 5);

    /* draw a blue box inside the second window */
    XSetForeground(dsp, gc2, blue.pixel);
    retcode1 = XSetLineAttributes(dsp, gc2, 1, LineSolid, CapButt, JoinMiter);
    fprintf(stdout,"gc2 XSetLineAttributes returns %i\n", retcode1 );
    XDrawRectangle(dsp, win2, gc2, 5, 5, 390, 190);

    /* draw a yellow box inside the third window */
    XSetForeground(dsp, gc3, yellow.pixel);
    retcode1 = XSetLineAttributes(dsp, gc3, 1, LineSolid, CapButt, JoinMiter);
    fprintf(stdout,"gc3 XSetLineAttributes returns %i\n", retcode1 );
    XDrawRectangle(dsp, win3, gc3, 5, 5, 390, 190);

    /* try to set line characteristics on the gc
     * https://www.x.org/archive/X11R7.7/doc/man/man3/XSetLineAttributes.3.xhtml
     * int XSetLineAttributes(Display *display, GC gc,
     *                        unsigned int line_width,
     *                        int line_style,
     *                        int cap_style,
     *                        int join_style);
     *
     *  line-style : LineSolid, LineOnOffDash, or LineDoubleDash
     *  join-style : JoinMiter, JoinRound, or JoinBevel.
     *  cap-style  : CapNotLast, CapButt, CapRound, or CapProjecting
     *
     *  the most normal seems to be CapButt and JoinMiter
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
    p = 0;
    for ( j=(offset_x + (eff_width/16)); j<lx; j+=(eff_width/16) ){
        XDrawLine(dsp, win, gc, j, 8, j, 12);
        XDrawLine(dsp, win, gc, j, height - 8, j, height - 12);
        sprintf(buf,"[%02i] j = %4i   minus offset = %4i", p, j, j - offset_x);
        fprintf(stdout,"horizontal minor tic mark %s\n",buf);
        k = 60 + 20 * p;
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
        fprintf(stdout,"vertical minor tic mark %s\n",buf);
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
    for(j=30;j>0;j--){
        if(j%5==0) fprintf(stdout,"%2i",j);
        fprintf(stdout,".");
        fflush(stdout);
        sleep(1);
    }
    fprintf(stdout,"\n");

    /* setup a single cell worth of data */
/*
    node0303 = calloc((size_t) 1, sizeof(cell_t));
    fprintf(stdout,"\nsizeof(node0303) = %llx\n", sizeof(node0303));

*/

    /* XFreeGC(dsp,gc);  should never do? */
    XCloseDisplay(dsp);

    /* free(node0303); */

    return EXIT_SUCCESS;
}

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

int check_ascii_input(char *inp)
{
    /* ensure that the width and height are at least 512 pixels */
    char *buf = calloc((size_t)32, sizeof(unsigned char));
    int char_cnt, retval;

    retval = (int)strtol( inp, (char **)NULL, 10);
    char_cnt = snprintf(buf, (size_t)32, "%i", retval);
    /* did we get at least a single valid digit ? */
    if ( char_cnt < 1 ) {
        retval = -1;
    } else {
        /* compare the input string to the integer conversion */
        if ( strncmp( inp, buf, char_cnt) != 0 ){
            retval = -1;
        } else {
            /* ensure that we have at least 512 pixels */
            if ( retval < 512 ) retval = 512;
        }
    }
    free(buf);
    return retval;
}

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

