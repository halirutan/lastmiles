#!/bin/ksh

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
unset LC_ALL
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

AR=/usr/ccs/bin/ar
export AR

AS=/usr/ccs/bin/as
export AS

AWK=/usr/xpg4/bin/gawk
export AWK

CC=/opt/developerstudio12.6/bin/cc
export CC

CFLAGS=\-std=iso9899:1999\ \-g\ \-errfmt=error\ \-erroff=%none\ \-xmemalign=8s\ \
\-errshort=full\ \-xstrconst\ \-xildoff\ \-m64\ \-xnolibmil\ \
\-xcode=pic32\ \-xregs=no%appl\ \-xlibmieee\ \-ftrap=%none\ \
\-xarch=sparc\ \-mc\ \-xs\ \-xbuiltin=%none\ \-xdebugformat=dwarf\ \
\-xunroll=1
export CFLAGS

CXX=/opt/developerstudio12.6/bin/CC
export CXX

GREP=/usr/xpg4/bin/grep
export GREP

HOME=/export/home/dclarke
export HOME

LD=/usr/ccs/bin/sparcv9/ld
export LD

NM=/usr/ccs/bin/sparcv9/nm\ \-p
export NM

SED=/usr/xpg4/bin/sed
export SED

SHELL=/bin/ksh
export SHELL

VISUAL=/usr/xpg6/bin/vi
export VISUAL

CPPFLAGS=\-D_POSIX_PTHREAD_SEMANTICS\ \-D_LARGEFILE64_SOURCE\ \-D_TS_ERRNO
export CPPFLAGS

PATH=/usr/xpg6/bin:/usr/xpg4/bin:/usr/ccs/bin:/usr/bin:/opt/developerstudio12.6/bin:/sbin:/bin:/usr/sbin:/opt/schily/bin
export PATH

unset CXXFLAGS
unset LD_LIBRARY_PATH
unset LIBTOOL
unset CFLAGS_SOCKETS

JAVA_HOME=/usr/jdk/latest
export JAVA_HOME

unset POSIXLY_CORRECT
unset PHP

EDITOR=/usr/xpg6/bin/vi
export EDITOR

LD_OPTIONS=\-64\ \-R/usr/local/lib\ \-L/usr/local/lib
export LD_OPTIONS

PAGER=/usr/xpg4/bin/more
export PAGER

TMPDIR=/var/tmp/`( /usr/xpg4/bin/id | /usr/bin/cut -f2 -d\( | /usr/bin/cut -f1 -d\) )`
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
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o check_status.o check_status.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_add.o cplex_add.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_cbrt.o cplex_cbrt.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_check.o cplex_check.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_cmp.o cplex_cmp.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_cramer.o cplex_cramer.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_det.o cplex_det.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_div.o cplex_div.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_mag.o cplex_mag.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_mult.o cplex_mult.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_quad.o cplex_quad.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_sq.o cplex_sq.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_sqrt.o cplex_sqrt.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_sub.o cplex_sub.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_theta.o cplex_theta.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_vec_cross.o cplex_vec_cross.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_vec_dot.o cplex_vec_dot.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_vec_mag.o cplex_vec_mag.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o cplex_vec_normalize.o cplex_vec_normalize.c
$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o tohex.o tohex.c

$CC $CFLAGS $CPPFLAGS -I/usr/local/include -c -o test_cplex.o test_cplex.c

ls -lapb *.o
/usr/bin/printf "\n"

$CC $CFLAGS $CPPFLAGS -Wl,-rpath=/usr/local/lib -L/usr/local/lib -o test_cplex \
test_cplex.o check_status.o cplex_add.o cplex_cbrt.o cplex_check.o cplex_div.o \
cplex_mag.o cplex_mult.o cplex_quad.o cplex_sq.o cplex_sqrt.o cplex_sub.o \
cplex_theta.o cplex_vec_cross.o cplex_vec_dot.o cplex_det.o cplex_cmp.o \
cplex_vec_normalize.o cplex_vec_mag.o cplex_cramer.o tohex.o -lm

ls -lapb test_cplex

