#!/bin/bash
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
unset RUNPATH
unset SED
unset SHELL
unset SRC
unset STD_CDEFINES
unset VISUAL
unset XTERM_LOCALE

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

PATH=/usr/bin:/sbin:/bin:/usr/sbin:/opt/schily/bin
export PATH

CC=/usr/bin/gcc
export CC

CFLAGS=\-g\ \-m64\ \-std=c99\ \-fno-builtin\ \-O0\ \-mcpu=970\ \
\-mno-altivec\ \-mfull-toc\ \-ffp-contract=off\ \-mregnames\ \-fno-unsafe-math-optimizations
export CFLAGS 

CPPFLAGS=\-D_TS_ERRNO\ \-D_POSIX_PTHREAD_SEMANTICS\ \
\-D_LARGEFILE64_SOURCE
export CPPFLAGS

MANPATH=/usr/local/share/man:/usr/local/man:/usr/local/share/man:/usr/local/man:/usr/share/man:/opt/schily/share/man
export MANPATH

PATH=/usr/local/bin:/usr/local/sbin:/sbin:/bin:/usr/sbin:/usr/bin:/opt/schily/bin
export PATH

SHELL=/bin/bash
export SHELL

TZ=GMT0
export TZ

XTERM_LOCALE=C; export XTERM_LOCALE

# AR=/usr/bin/ar ; export AR
# AS=/usr/bin/as ; export AS
# GREP=/bin/grep ; export GREP
# LD=/usr/bin/ld ; export LD
# NM=/usr/bin/nm\ \-p; export NM
# MAKE=/usr/bin/make ; export MAKE
# PERL=/usr/bin/perl ; export PERL
# SED=/bin/sed ; export SED

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

$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o mpfr_set_str.o mpfr_set_str.c
$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o pr.o pr.c
$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o pr_mpfr.o pr_mpfr.c
$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o pr_mpfr_quiet.o pr_mpfr_quiet.c
$CC $CFLAGS $CPPFLAGS -I/opt/bw/include -c -o pr_quiet.o pr_quiet.c

$CC $CFLAGS $CPPFLAGS -L/opt/bw/lib -o mpfr_set_str mpfr_set_str.o -lgmp -lm -lmpfr
$CC $CFLAGS $CPPFLAGS -L/opt/bw/lib -o pr pr.o
$CC $CFLAGS $CPPFLAGS -L/opt/bw/lib -o pr_mpfr pr_mpfr.o -lgmp -lm -lmpfr
$CC $CFLAGS $CPPFLAGS -L/opt/bw/lib -o pr_mpfr_quiet pr_mpfr_quiet.o -lgmp -lm -lmpfr
$CC $CFLAGS $CPPFLAGS -L/opt/bw/lib -o pr_quiet pr_quiet.o -lm

ls -lapb --full-time *.o
ls -lapb --full-time mpfr_set_str pr pr_mpfr pr_mpfr_quiet pr_quiet

