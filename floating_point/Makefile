
IDIR = .

CC=/usr/bin/cc
CFLAGS= -I$(IDIR) -std=iso9899:1999 -m64 -O0 -g -fno-fast-math -fno-builtin
CPPFLAGS=-D_TS_ERRNO -D_POSIX_PTHREAD_SEMANTICS -D_LARGEFILE64_SOURCE -D_X_OPEN_SOURCE=600
LIBS = -lrt

OBJSIGSEGV = sigsegv.o
OBJ = fptohex.o test_fptohex.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

sigsegv: $(OBJSIGSEGV)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LIBS)

test_fptohex: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f *.o sigsegv test_fptohex
