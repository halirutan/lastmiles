#!/bin/bash

unset LD_FLAGS

unset AR
unset AS
unset BUILD
unset CC
unset CFLAGS
unset CONFIG_SHELL
unset CPPFLAGS
unset CXX
unset CXXFLAGS
unset EDITOR
unset GREP
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
unset PKG_CONFIG_PATH
unset SED
unset SHELL
unset SRC
unset STD_CDEFINES
unset VISUAL
unset XTERM_LOCALE

LANG=C
export LANG

unset LC_ALL

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

CFLAGS=\-std=iso9899:1999\ \-m32\ \-g\ \
\-Wl,-rpath=/opt/bw/lib,--enable-new-dtags\ \-fno-builtin\ \
\-malign-double\ \-mpc80\ \-D_LARGEFILE64_SOURCE
export CFLAGS

CPPFLAGS=\-I/opt/bw/include\ \-D_POSIX_PTHREAD_SEMANTICS\ \-D_TS_ERRNO
export CPPFLAGS

unset CXXFLAGS

LDFLAGS=\-Wl,-rpath=/opt/bw/lib,--enable-new-dtags
export LDFLAGS

LD_OPTIONS=\-L/opt/bw/lib
export LD_OPTIONS

LD_RUN_PATH=/opt/bw/lib
export LD_RUN_PATH

# M4=/opt/bw/bin/m4
unset M4

MAKE=/usr/local/bin/gmake
export MAKE

MANPATH=/opt/bw/share/man:/opt/bw/man:/usr/local/share/man:/usr/local/man:/usr/share/man:/opt/schily/share/man
export MANPATH

PATH=/opt/bw/bin:/opt/bw/sbin:/usr/local/bin:/usr/local/sbin:/sbin:/bin:/usr/sbin:/usr/bin:/opt/schily/bin
export PATH

PKG_CONFIG_PATH=/opt/bw/lib/pkgconfig
export PKG_CONFIG_PATH

RUNPATH=/opt/bw/lib
export RUNPATH

SHELL=/bin/bash
export SHELL

SRC=/opt/bw/src
export SRC

TZ=GMT0
export TZ

XTERM_LOCALE=C; export XTERM_LOCALE

unset LD_LIBRARY_PATH
unset CFLAGS_SOCKETS
unset POSIXLY_CORRECT
unset PHP

# AR=/usr/bin/ar ; export AR
# AS=/usr/bin/as ; export AS
# GREP=/bin/grep ; export GREP
# LD=/usr/bin/ld ; export LD
# NM=/usr/bin/nm\ \-p; export NM
# MAKE=/usr/bin/make ; export MAKE
# PERL=/usr/bin/perl ; export PERL
# SED=/bin/sed ; export SED

CPPFLAGS=\-I/opt/bw/include\ \-D_POSIX_PTHREAD_SEMANTICS\ \-D_TS_ERRNO
export CPPFLAGS

unset CXXFLAGS
unset LD_LIBRARY_PATH
unset LIBTOOL
unset CFLAGS_SOCKETS
unset POSIXLY_CORRECT
unset PHP

CC=/usr/bin/gcc ; export CC

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

rm *.s *.o *.i *.bc mpfr_set_str pr_mpfr_quiet pr_mpfr pr_quiet pr > /dev/null 2>&1

$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o mpfr_set_str.o mpfr_set_str.c
$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o pr_mpfr_quiet.o pr_mpfr_quiet.c
$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o pr_mpfr.o pr_mpfr.c
$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o pr_quiet.o pr_quiet.c
$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o pr.o pr.c

# $CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o mpfr_check_flags.o ../mpfr/mpfr_check_flags.c

$CC $CFLAGS $CPPFLAGS $LDFLAGS -o mpfr_set_str mpfr_set_str.o -lgmp -lm -lmpfr
$CC $CFLAGS $CPPFLAGS $LDFLAGS -o pr_mpfr_quiet pr_mpfr_quiet.o -lgmp -lm -lmpfr
$CC $CFLAGS $CPPFLAGS $LDFLAGS -o pr_mpfr pr_mpfr.o -lgmp -lm -lmpfr
$CC $CFLAGS $CPPFLAGS $LDFLAGS -o pr_quiet pr_quiet.o -lm
$CC $CFLAGS $CPPFLAGS $LDFLAGS -o pr pr.c

ls -lapb --full-time *.o 
/usr/bin/printf "\n"
ls -lapb --full-time mpfr_set_str pr_mpfr_quiet pr_mpfr pr_quiet pr

