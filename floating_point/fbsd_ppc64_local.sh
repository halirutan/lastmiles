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
unset EDITOR
unset GREP
unset JAVA_HOME
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
unset SED
unset SHELL
unset SRC
unset STD_CDEFINES
unset VISUAL

if [ -x /usr/local/bin/gcc8 ]; then
    CC=/usr/local/bin/gcc8
    export CC
else
    /usr/bin/printf "FAIL : /usr/local/bin/gcc8 not found\n"
    exit 1
fi

LD_RUN_PATH=/home/dclarke/local/lib
export LD_RUN_PATH

CPPFLAGS=\-D_POSIX_PTHREAD_SEMANTICS\ \-D_LARGEFILE64_SOURCE\ \-D_TS_ERRNO
export CPPFLAGS


CFLAGS=\-g\ \-m64\ \-std=iso9899:1999\ \-pedantic\ \-fno-builtin\ \-O0\ \
\-mcpu=970\ \-mcall-freebsd\ \-mno-altivec\ \-mno-isel\ \-mno-paired\ \
\-mno-vsx\ \-mno-crypto\ \-mno-htm\ \-mno-quad-memory-atomic\ \
\-mno-float128\ \-mno-float128-hardware\ \-mfull-toc\ \-mdouble-float\ \
\-mno-multiple\ \-mupdate\ \-mno-avoid-indexed-addresses\ \
\-ffp-contract=off\ \-mno-mulhw\ \-mno-dlmzb\ \-mno-bit-align\ \
\-mno-strict-align\ \-mno-toc\ \-mbig\ \-mregnames\ \-mno-recip\ \
\-fno-unsafe-math-optimizations
export CFLAGS 

PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/bin:/sbin:/usr/sbin:/opt/schily/bin
export PATH

unset LD_OPTIONS

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

ls -lapb test_fp128

