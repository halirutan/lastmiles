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
unset LESSOPEN
unset LIBTOOL
unset LOADEDMODULES
unset M4
unset MACHTYPE
unset MAKE
unset MANPATH
unset MODULEPATH
unset MODULEPATH_modshare
unset MODULESHOME
unset MODULES_CMD
unset MODULES_RUN_QUARANTINE
unset NM
unset OPENSSL_SOURCE
unset OSTYPE
unset PAGER
unset PERL
unset PHP
unset PKG_CONFIG_PATH
unset POSIXLY_CORRECT
unset SED
unset SELINUX_LEVEL_REQUESTED
unset SELINUX_ROLE_REQUESTED
unset SELINUX_USE_CURRENT_RANGE
unset SHELL
unset SRC
unset STD_CDEFINES
unset VISUAL
unset XTERM_LOCALE

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

if [ -x /opt/bw/gcc9/bin/gcc ]; then
    CC=/opt/bw/gcc9/bin/gcc ; export CC
else
    /usr/bin/printf "WARN : can not locate gcc 9.2.x\n"
    if [ -x /usr/bin/gcc ]; then
        /usr/bin/printf "INFO : found system /usr/bin/gcc\n"
        CC=/usr/bin/gcc ; export CC
    else
        /usr/bin/printf "FAIL : no gcc compiler found.\n"
        exit 1
    fi
fi

CFLAGS=\-std=iso9899:1999\ \-m64\ \-g\ \
\-Wl,-rpath=/opt/bw/lib,--enable-new-dtags\ \-fno-builtin\ \
\-malign-double\ \-mpc80
export CFLAGS

CPPFLAGS=\-I/opt/bw/include\ \-D_POSIX_PTHREAD_SEMANTICS\ \
\-D_TS_ERRNO\ \-D_LARGEFILE64_SOURCE
export CPPFLAGS

LDFLAGS=\-Wl,-rpath=/opt/bw/lib,--enable-new-dtags
export LDFLAGS

LD_OPTIONS=\-L/opt/bw/lib
export LD_OPTIONS

LD_RUN_PATH=/opt/bw/lib
export LD_RUN_PATH

MANPATH=/opt/bw/share/man:/opt/bw/man:/usr/local/share/man:/usr/local/man:/usr/share/man:/opt/schily/share/man
export MANPATH

PATH=/opt/bw/bin:/opt/bw/sbin:/opt/bw/gcc9/bin:/usr/local/bin:/usr/local/sbin:/usr/sbin:/usr/bin:/opt/schily/bin
export PATH

PKG_CONFIG_PATH=/opt/bw/lib/pkgconfig
export PKG_CONFIG_PATH

RUNPATH=/opt/bw/lib
export RUNPATH


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

$CC $CFLAGS $CPPFLAGS -o test_fp128 test_fp128.c -lm

ls -lapb --full-time test_fp128

