
IDIR = .

CC=/usr/bin/cc
CFLAGS= -I$(IDIR) -std=iso9899:1999 -m64 -O0 -g -fno-fast-math -fno-builtin
CPPFLAGS=-D_TS_ERRNO -D_POSIX_PTHREAD_SEMANTICS -D_LARGEFILE64_SOURCE -D_X_OPEN_SOURCE=600
LIBS = -lm

DEPS = v.h
OBJ = test_cplex.o cplex_add.o cplex_mult.o cplex_sub.o cplex_div.o cplex_sq.o cplex_mag.o cplex_theta.o cplex_sqrt.o cplex_cubert.o cplex_v_dot.o cplex_v_cross.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

test_cplex: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LIBS)

clean:
	rm -f *.o test_cplex
