#!/bin/sh
unset AR
unset AS
unset BUILD
unset CC
unset CFLAGS
unset CFLAGS_SOCKETS
unset CONFIG_SHELL
unset CPPFLAGS
unset CXX
unset CXXFLAGS
unset GREP
unset JAVA_HOME
unset JRE_HOME
unset LANG
unset LC_ALL
unset LD
unset LD_FLAGS
unset LD_LIBRARY_PATH
unset LD_OPTIONS
unset LD_RUN_PATH
unset LIBTOOL
unset M4
unset MACHTYPE
unset MAKE
unset MANPATH
unset NM
unset OPENSSL_SOURCE
unset OSTYPE
unset PERL
unset PHP
unset PKG_CONFIG_PATH
unset POSIXLY_CORRECT
unset SED
unset SRC
unset STD_CDEFINES

LC_COLLATE=C
export LC_COLLATE

LC_CTYPE=C
export LC_CTYPE

LC_MESSAGES=C
export LC_MESSAGES

LC_MONETARY=C
export LC_MONETARY

LC_NUMERIC=C
export LC_NUMERIC

LC_TIME=C
export LC_TIME

CC=/usr/bin/cc
export CC

CFLAGS=\-m64\ \-std=c99\ \-O0\ \-g\ \-Werror\ \
\-no-integrated-as\ \-fno-fast-math\ \-fno-builtin\ \
\-fdiagnostics-format=vi\ \-fno-color-diagnostics
export CFLAGS 

CPPFLAGS=\-D_TS_ERRNO\ \-D_POSIX_PTHREAD_SEMANTICS\ \
\-D_LARGEFILE64_SOURCE
export CPPFLAGS

LD_FLAGS=\-Wl,-rpath=/usr/local/lib\ \-L/usr/local/lib
export LD_FLAGS

LD_RUN_PATH=/usr/local/lib
export LD_RUN_PATH

RUNPATH=/usr/local/lib
export RUNPATH

PATH=/usr/local/bin:/usr/local/sbin:/sbin:/bin:/usr/sbin:/usr/bin:/opt/schily/bin
export PATH

PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
export PKG_CONFIG_PATH

TZ=GMT0
export TZ

XTERM_LOCALE=C
export XTERM_LOCALE

TMPDIR=/var/tmp/`( /usr/bin/id | /usr/bin/cut -f2 -d\( | /usr/bin/cut -f1 -d\) )`
export TMPDIR

if [ ! -d $TMPDIR ]; then
    /usr/bin/printf "INFO : no TMPDIR exists in /var/tmp/$USERNAME\n"
    mkdir -m 0750 $TMPDIR
    if [ ! -d $TMPDIR ]; then
        /usr/bin/printf "FAIL : could not create a TMPDIR\n"
        exit 1
    fi
    /usr/bin/printf "INFO : new TMPDIR created\n"
else
    chmod 0750 $TMPDIR
    touch $TMPDIR/foo_$$
    if [ ! -f $TMPDIR/foo_$$ ]; then
        /usr/bin/printf "FAIL : could not create a file in TMPDIR\n"
        exit 1
    fi
    rm $TMPDIR/foo_$$
fi

rm -f *.o

$CC $CFLAGS $CPPFLAGS -c -o cplex_add.o cplex_add.c
$CC $CFLAGS $CPPFLAGS -c -o cplex_sub.o cplex_sub.c
$CC $CFLAGS $CPPFLAGS -c -o cplex_mult.o cplex_mult.c
$CC $CFLAGS $CPPFLAGS -c -o dot_v.o dot_v.c

$CC $CFLAGS $CPPFLAGS -o dot_v dot_v.o cplex_mult.o cplex_add.o cplex_sub.o

ls -lap dot_v
