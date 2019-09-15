#!/bin/bash
POSIXLY_CORRECT=1
export POSIXLY_CORRECT

unset ABI
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
unset EDITOR
unset GREP
unset JAVA_TOOL_OPTIONS
unset JRE_HOME
unset LANG
unset LC_ALL
unset LC_COLLATE
unset LC_CTYPE
unset LC_MESSAGES
unset LC_MONETARY
unset LC_NUMERIC
unset LC_TIME
unset LD
unset LD_FLAGS
unset LD_LIBRARY_PATH
unset LD_OPTIONS
unset LD_RUN_PATH
unset LIBTOOL
unset LS_COLORS
unset LS_COLORS
unset M4
unset MACHTYPE
unset MAKE
unset MANPATH
unset MONITOR_PORT
unset NM
unset OPENSSL_SOURCE
unset OSTYPE
unset PAGER
unset PERL
unset PHP
unset PKG_CONFIG_PATH
unset QT_GSTREAMER_WIDGET_VIDEOSINK
unset SED
unset SHELL
unset SRC
unset STD_CDEFINES
unset VISUAL
unset XDG_RUNTIME_DIR
unset XDG_SESSION_ID
unset XTERM_LOCALE

BUILD=/opt/bw/build
export BUILD

CC=/usr/bin/gcc-9
export CC

CFLAGS='-std=iso9899:1999 -pedantic -fno-builtin -O0 -g -m32 -march=i686 -mtune=i686 -Wl,-rpath=/opt/bw/lib,--enable-new-dtags -malign-double -mpc80'
export CFLAGS

CPPFLAGS='-I/opt/bw/include -D_POSIX_PTHREAD_SEMANTICS -D_TS_ERRNO -D_LARGEFILE64_SOURCE'
export CPPFLAGS 

CXX=/usr/bin/g++-9
export CXX

CXXFLAGS='-std=c++11 -m32 -g -O0 -march=i686 -mtune=i686 -Wl,-rpath=/opt/bw/lib,--enable-new-dtags -fno-builtin -malign-double -mpc80'
export CXXFLAGS

EDITOR=/usr/bin/vi
export EDITOR

LD_RUN_PATH=/opt/bw/lib
export LD_RUN_PATH

LDFLAGS='-Wl,-rpath=/opt/bw/lib,--enable-new-dtags'
export LDFLAGS

LD_OPTIONS='-L/opt/bw/lib'
export LD_OPTIONS

PATH=/opt/bw/bin:/opt/bw/sbin:/usr/local/bin:/usr/local/sbin:/sbin:/bin:/usr/sbin:/usr/bin:/opt/schily/bin
export PATH

PKG_CONFIG_PATH=/opt/bw/lib/pkgconfig
export PKG_CONFIG_PATH

RUNPATH=/opt/bw/lib
export RUNPATH

TERM=vt100
export TERM 

TZ=GMT0
export TZ

XTERM_LOCALE=C
export XTERM_LOCALE

LC_COLLATE=C;export LC_COLLATE
LC_CTYPE=C;export LC_CTYPE
LC_MESSAGES=C;export LC_MESSAGES
LC_MONETARY=C;export LC_MONETARY
LC_NUMERIC=C;export LC_NUMERIC
LC_TIME=C;export LC_TIME

AR=/usr/bin/ar ; export AR
AS=/usr/bin/as ; export AS
LD=/usr/bin/ld ; export LD
NM=/usr/bin/nm\ \-p ; export NM
M4=/usr/bin/m4 ; export M4
PERL=/usr/bin/perl ; export PERL
GREP=/bin/grep ; export GREP
SED=/bin/sed ; export SED
GAWK=/usr/bin/gawk ; export GAWK
MAKE=/usr/bin/make ; export MAKE

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

$CC $CFLAGS $CPPFLAGS -c -o timediff.o timediff.c
$CC $CFLAGS $CPPFLAGS -c -o sysmem.o sysmem.c
$CC $CFLAGS $CPPFLAGS -c -o maxalloc.o maxalloc.c
$CC $CFLAGS $CPPFLAGS -c -o mem_hack.o mem_hack.c


$CC $CFLAGS $CPPFLAGS -o maxalloc maxalloc.o timediff.o -lrt
$CC $CFLAGS $CPPFLAGS -o mem_hack mem_hack.o
$CC $CFLAGS $CPPFLAGS -o sysmem sysmem.o

ls -lapb --full-time maxalloc mem_hack sysmem

