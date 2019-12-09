
CC=/usr/bin/cc

CFLAGS= -I$(IDIR) -std=iso9899:1999 -m64 -g -O0 \
	-fno-fast-math -fno-builtin

CPPFLAGS=-D_TS_ERRNO -D_POSIX_PTHREAD_SEMANTICS -D_LARGEFILE64_SOURCE \
	-D_X_OPEN_SOURCE=600

LIBS = -lm

SRCS = basel_double.c

OBJS = basel_double.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

basel_double: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) basel_double
