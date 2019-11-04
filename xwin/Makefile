
CC=/usr/bin/cc

CFLAGS= -I$(IDIR) -std=iso9899:1999 -m64 -g -O0 \
	-fno-fast-math -fno-builtin -malign-double

CPPFLAGS=-D_TS_ERRNO -D_POSIX_PTHREAD_SEMANTICS -D_LARGEFILE64_SOURCE \
	-D_X_OPEN_SOURCE=600 -D_POSIX_C_SOURCE=199309L

LIBS = -lX11 -lrt

SRCS = grid.c numpad.c x_error_handler.c create_gc.c \
	create_borderless_topwin.c ../time_and_date/timediff.c

OBJS = x_error_handler.o create_gc.o \
	create_borderless_topwin.o ../time_and_date/timediff.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

grid: grid.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LIBS)

numpad: numpad.o $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) grid numpad
