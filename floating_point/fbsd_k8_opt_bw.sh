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
unset PAGER
unset PERL
unset PHP
unset PKG_CONFIG_PATH
unset POSIXLY_CORRECT
unset SED
unset SHELL
unset SRC
unset STD_CDEFINES

LANG=C
export LANG

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

CFLAGS=\-std=iso9899:1999\ \-m64\ \-g\ \-march=opteron\ \
\-fno-builtin\ \-malign-double\ \-mpc80
export CFLAGS

LDFLAGS=\-Wl,-rpath=/usr/local/lib/gcc9,--enable-new-dtags\ \-Wl,-rpath=/opt/bw/lib,--enable-new-dtags\ \-L/opt/bw/lib
export LDFLAGS

LD_RUN_PATH=/opt/bw/lib
export LD_RUN_PATH

PATH=/opt/bw/bin:/opt/bw/sbin:/usr/local/bin:/usr/local/sbin:/sbin:/bin:/usr/sbin:/usr/bin:/opt/schily/bin
export PATH

PKG_CONFIG_PATH=/opt/bw/lib/pkgconfig
export PKG_CONFIG_PATH

RUNPATH=/opt/bw/lib
export RUNPATH

TZ=GMT0
export TZ

XTERM_LOCALE=C
export XTERM_LOCALE

CPPFLAGS=\-D_POSIX_PTHREAD_SEMANTICS\ \-D_TS_ERRNO\ \-D_LARGEFILE64_SOURCE
export CPPFLAGS

CC=/usr/local/bin/gcc9
export CC

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
$CC $CFLAGS $CPPFLAGS -c -o fp128_q.o fp128_q.c
$CC $CFLAGS $CPPFLAGS -c -o fp32_format.o fp32_format.c
$CC $CFLAGS $CPPFLAGS -c -o fp32_test.o fp32_test.c
$CC $CFLAGS $CPPFLAGS -c -o test_fp128.o test_fp128.c

ls -lap *.o

$CC $CFLAGS $CPPFLAGS -o fp128_q fp128_q.o -lm -lquadmath
$CC $CFLAGS $CPPFLAGS -o fp32_format fp32_format.o -lm
$CC $CFLAGS $CPPFLAGS -o fp32_test fp32_test.o -lm
$CC $CFLAGS $CPPFLAGS -o test_fp128 test_fp128.o -lm

ls -lap fp128_q fp32_format fp32_test test_fp128

