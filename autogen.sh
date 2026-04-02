#!/bin/sh
# Run this to generate all the initial makefiles, etc.

DIE=0

(autoconf --version) < /dev/null > /dev/null 2>&1 || {
        echo
        echo "You must have autoconf installed to compile this package."
        echo "Download the appropriate package for your distribution,"
        echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/autoconf"
        DIE=1
}

(automake --version) < /dev/null > /dev/null 2>&1 || {
        echo
        echo "You must have automake installed to compile this package."
        echo "Get it at ftp://ftp.gnu.org/pub/gnu/automake"
        DIE=1
}

if test "$DIE" -eq 1; then
        exit 1
fi

if test -z "$*"; then
        echo "I am going to run ./configure with no arguments - if you wish "
        echo "to pass any to it, please specify them on the $0 command line."
fi

echo "Generating configuration files for IRCSP 5.1, please wait...."

echo "  aclocal $ACLOCAL_FLAGS"
aclocal $ACLOCAL_FLAGS
echo "  autoheader"
autoheader
echo "  automake --add-missing"
automake --add-missing 
echo "  autoconf"
autoconf

configure "$@" && echo && echo "Now type 'make' to compile IRCSP 5.1"
