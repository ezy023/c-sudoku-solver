AC_PREREQ(2.61)
AC_INIT([sudoku], [0.0.1], [erik])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])
AC_CONFIG_MACRO_DIR([m4])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

AC_CONFIG_FILES([
               Makefile
               src/Makefile
               test/Makefile
               ])

AC_OUTPUT
