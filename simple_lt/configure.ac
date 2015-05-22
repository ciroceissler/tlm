## ****************************************************************************
##
##  Copyright (c) 2015 by Ceissler. All rights reserved.
##
## ****************************************************************************
##
##  configure.ac --
##                                                -*- Autoconf -*-
##  Process this file with autoconf to produce a configure script.
##
##  Original Author: Ciro Ceissler, Ceissler, 22-05-2015
##
## ****************************************************************************
##
##  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
##  changes you are making here.
##
##      Name, Affiliation, Date:
##  Description of Modification:
##
## ****************************************************************************

AC_PREREQ([2.63])
AC_INIT([simple_lt],
        [1.0.0],
        [ciro@ceissler.com.br],
        [simple_lt],
        [http://www.ceissler.com.br/])
AC_LANG([C++])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

# Figure out architecture dependent variables

case "$target" in
    *-apple-*)
        case "$target_cpu" in
            x86_64)
                TARGET_ARCH="macosx64"
                CPU_ARCH="x86_64"
                ;;
            x386 | i386)
                TARGET_ARCH="macosx"
                CPU_ARCH="i386"
                ;;
            powerpc)
                TARGET_ARCH="macosxppc"
                CPU_ARCH="ppc"
                ;;
            powerpc64)
                TARGET_ARCH="macosxppc64"
                CPU_ARCH="ppc64"
                ;;
            *)
                AC_MSG_ERROR("sorry... architecture not supported.")
                ;;
        esac
        if test "$GXX" = "yes"; then
                EXTRA_CXXFLAGS="${EXTRA_CXXFLAGS} -arch ${CPU_ARCH}"
                LDFLAG_RPATH="-Wl,-rpath -Wl,"
        else
                AC_MSG_ERROR("sorry... compiler not supported.")
        fi
        ;;
    sparc-sun-solaris*)
        if test "$GXX" = "yes"; then
                TARGET_ARCH="gccsparcOS5"
                LDFLAG_RPATH="-Wl,-R"
        else
            if test "$CXX_COMP" = "CC"; then
                EXTRA_CXXFLAGS=""
                OPT_CXXFLAGS="-fast -xO4 -xnolibmil -mc"
                TARGET_ARCH="sparcOS5"
                LDFLAG_RPATH="-Wl,-R"
            else
                AC_MSG_ERROR("sorry... compiler not supported.")
            fi
        fi
        ;;
    *linux*)
        case "$target_cpu" in
            x86_64 | amd64)
                TARGET_ARCH="linux64"
                CPU_ARCH=64
                ;;
            i*86)
                TARGET_ARCH="linux"
                CPU_ARCH=32
                ;;
            *)
                AC_MSG_ERROR("sorry... architecture not supported.")
            ;;
        esac
        if test "$GXX" = "yes"; then
                EXTRA_CXXFLAGS="${EXTRA_CXXFLAGS} -m${CPU_ARCH}"
        else
                AC_MSG_ERROR("sorry... compiler not supported.")
        fi
        ;;
    *freebsd* | dragonfly* | *netbsd* | openbsd*)
        case "$target_cpu" in
            x86_64 | amd64)
                TARGET_ARCH="bsd64"
                CPU_ARCH=64
                ;;
            i*86)
                TARGET_ARCH="bsd"
                CPU_ARCH=32
                ;;
            *)
                AC_MSG_ERROR("sorry... architecture not supported.")
            ;;
        esac
        if test "$GXX" = "yes"; then
                EXTRA_CXXFLAGS="${EXTRA_CXXFLAGS} -m${CPU_ARCH}"
        else
                AC_MSG_ERROR("sorry... compiler not supported.")
        fi
        ;;
    *cygwin*)
        case "$target_cpu" in
            x86_64 | amd64)
                TARGET_ARCH="cygwin64"
                CPU_ARCH=64
                ;;
            i*86)
                TARGET_ARCH="cygwin"
                CPU_ARCH=32
                ;;
            *)
                AC_MSG_ERROR("sorry... architecture not supported.")
            ;;
        esac
        if test "$GXX" = "yes"; then
                EXTRA_CXXFLAGS="${EXTRA_CXXFLAGS} -m${CPU_ARCH}"
        else
                AC_MSG_ERROR("sorry... compiler not supported.")
        fi
        ;;
    *mingw*)
        case "$target_cpu" in
            x86_64 | amd64)
                TARGET_ARCH="mingw64"
                CPU_ARCH=64
                ;;
            i*86)
                TARGET_ARCH="mingw"
                CPU_ARCH=32
                ;;
            *)
                AC_MSG_ERROR("sorry... architecture not supported.")
            ;;
        esac
        if test "$GXX" = "yes"; then
                EXTRA_CXXFLAGS="${EXTRA_CXXFLAGS} -m${CPU_ARCH}"
        else
                AC_MSG_ERROR("sorry... compiler not supported.")
        fi
        ;;
esac

AC_SUBST([TARGET_ARCH])

# arch suffix
AC_MSG_CHECKING([for SystemC library arch suffix])


LIB_ARCH_SUFFIX="-${TARGET_ARCH}"

AC_ARG_WITH([arch-suffix],
  [AS_HELP_STRING([--with-arch-suffix@<:@=SUFFIX@:>@],
                  [append SUFFIX to library installation directory
                   @<:@default=-$TARGET_ARCH@:>@])],
  [case "$withval" in
     "no" | "")  have_arch_suffix="no";  LIB_ARCH_SUFFIX="";;
     "yes")      have_arch_suffix="yes"; LIB_ARCH_SUFFIX="-${TARGET_ARCH}";;
     *)          have_arch_suffix="yes"; LIB_ARCH_SUFFIX="$withval";;
  esac],
  [ac_dummy=""])

AC_MSG_RESULT($have_arch_suffix (TARGET_ARCH=${TARGET_ARCH}))
AC_SUBST(LIB_ARCH_SUFFIX)

CPPFLAGS=${CPPFLAGS}" -fPIC -std=c++0x "

# Check if SystemC path has been overloaded
AC_ARG_WITH(systemc,
  AS_HELP_STRING([--with-systemc=<path>], [systemc library to use (will be completed with /include and /lib), otherwise use $SYSTEMC_HOME]),
  [],
  [with_systemc=$SYSTEMC_HOME])

if test "x$with_systemc" = "x"; then
  AC_MSG_FAILURE(with-systemc not specified and \$SYSTEMC_HOME not defined)
else
  AC_MSG_NOTICE([using SystemC at $with_systemc])
  # TODO(ciroceissler): check systemc version, line below doesn't work
  # PKG_CHECK_MODULES(SYSTEMC, [systemc <= 2.3.1])
  LDFLAGS=${LDFLAGS}" -L$with_systemc/lib${LIB_ARCH_SUFFIX}"
  CPPFLAGS=${CPPFLAGS}" -I$with_systemc/include -DSC_INCLUDE_DYNAMIC_PROCESSES"
fi

# Check if TLM path has been overloaded, use SYSTEMC_HOME because since SystemC version 2.3 is included
AC_ARG_WITH(tlm,
  AS_HELP_STRING([--with-tlm=<path>], [tlm path to use (will be completed with /include), otherwise use $SYSTEMC_HOME]),
  [],
  [with_tlm=$SYSTEMC_HOME])

if test "x$with_tlm" = "x"; then
  AC_MSG_FAILURE(with-tlm not specified and \$SYSTEMC_HOME not defined)
else
  AC_MSG_NOTICE([using TLM at $with_tlm])
  CPPFLAGS=${CPPFLAGS}" -I$with_tlm/include"
fi

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADER(systemc.h,, AC_MSG_ERROR([systemc.h not found. Please install the SystemC library (version >= 2.3.1). Use --with-systemc=<path> to overload default includes search path.]))
AC_CHECK_HEADER(tlm.h,, AC_MSG_ERROR([tlm.h not found. Please install the TLM (version >= 2.0.1). Use --with-tlm=<path> to overload default includes search path.]))

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_MSG_NOTICE([checking systemc library function])

LIBS=${LIBS}" -lsystemc"

AC_RUN_IFELSE(
  [AC_LANG_SOURCE(
    #include <systemc.h>
    int sc_main(int argc, char **argv) { return 0; })
  ],,
  [AC_MSG_ERROR([installed SystemC is broken. Please install the SystemC library (version > 2.3). Use --with-systemc=<path> to overload default includes search path.])])

# Explicitly substitute the variables we have changed
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(LIBS)

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

# Taf!
