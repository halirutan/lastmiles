#!/bin/sh
PATH=/usr/bin:/sbin:/bin:/usr/sbin:/opt/schily/bin
export PATH

CC=/usr/bin/cc
export CC

CFLAGS=\-m64\ \-std=c99\ \-Werror\ \-fno-builtin\ \-O0\ \-g\ \
\-no-integrated-as\ \-fno-fast-math\ \
\-fdiagnostics-format=vi\ \-fno-color-diagnostics
export CFLAGS

CPPFLAGS=\-D_TS_ERRNO\ \-D_POSIX_PTHREAD_SEMANTICS\ \
\-D_LARGEFILE64_SOURCE
export CPPFLAGS

LD_FLAGS=\-Wl,-rpath=/usr/local/lib
export LD_FLAGS

$CC $CFLAGS $CPPFLAGS -o tn tn.c -lrt

