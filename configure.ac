AC_PREREQ([2.69])

AC_INIT([squareball], [0], [https://github.com/rafaelmartins/squareball],
  [squareball], [https://squareball.rgm.io])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# code changed: REVISION++.
# interface changed: CURRENT++, REVISION=0.
# interface changed (backwards compatible): AGE++, else AGE=0.
LIBSQUAREBALL_CURRENT=0
LIBSQUAREBALL_AGE=0
LIBSQUAREBALL_REVISION=0

LIBSQUAREBALL_LT_VERSION_INFO="$LIBSQUAREBALL_CURRENT:$LIBSQUAREBALL_REVISION:$LIBSQUAREBALL_AGE"
AC_SUBST(LIBSQUAREBALL_LT_VERSION_INFO)

AM_INIT_AUTOMAKE([1.13 foreign no-dist-gzip dist-xz subdir-objects serial-tests])
AC_CONFIG_HEADERS([config.h])
AM_SILENT_RULES([yes])
AM_MAINTAINER_MODE([enable])

AC_USE_SYSTEM_EXTENSIONS

LT_INIT

AC_PROG_CC_C99
AS_IF([test "x$ac_cv_prog_cc_c99" = "xno"], [
  AC_MSG_ERROR([no C99 compiler found, squareball requires a C99 compiler.])
])

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE([bundleme], AS_HELP_STRING([--enable-bundleme],
              [do not build shared library and do not install anything]))
AS_IF([test "x$enable_bundleme" = "xyes"], [
  enable_static=yes
  enable_shared=no
])
AM_CONDITIONAL([BUNDLE_ME], [test "x$enable_bundleme" = "xyes"])

AC_ARG_ENABLE([doc], AS_HELP_STRING([--disable-doc],
              [ignore presence of doxygen and disable documentation build]))
AS_IF([test "x$enable_doc" != "xno"], [
  AC_PATH_PROG([doxygen], [doxygen])
  AS_IF([test "x$ac_cv_path_doxygen" = "x"], [
    have_doxygen=no
  ], [
    have_doxygen=yes
  ])
])
AS_IF([test "x$have_doxygen" = "xyes"], , [
  AS_IF([test "x$enable_doc" = "xyes"], [
    AC_MSG_ERROR([doxygen requested but not found])
  ])
])

AM_CONDITIONAL([BUILD_DOCS], [test "x$have_doxygen" = "xyes"])
DOXYGEN="$ac_cv_path_doxygen"
AC_SUBST(DOXYGEN)

AC_ARG_ENABLE([valgrind], AS_HELP_STRING([--disable-valgrind],
              [ignore presence of valgrind]))
AS_IF([test "x$enable_valgrind" != "xno"], [
  AC_PATH_PROG([valgrind], [valgrind])
  AS_IF([test "x$ac_cv_path_valgrind" = "x"], [
    have_valgrind=no
  ], [
    have_valgrind=yes
  ])
])
AS_IF([test "x$have_valgrind" = "xyes"], , [
  AS_IF([test "x$enable_valgrind" = "xyes"], [
    AC_MSG_ERROR([valgrind requested but not found])
  ])
])
AM_CONDITIONAL([USE_VALGRIND], [test "x$have_valgrind" = "xyes"])
VALGRIND="$ac_cv_path_valgrind"
AC_SUBST(VALGRIND)

AC_ARG_ENABLE([tests], AS_HELP_STRING([--disable-tests],
              [disable unit tests, ignoring presence of cmocka]))
AS_IF([test "x$enable_tests" != "xno"], [
  PKG_CHECK_MODULES([CMOCKA], [cmocka], [
    TESTS="enabled"
    have_cmocka=yes
  ], [
    TESTS="disabled"
    have_cmocka=no
  ])
])
AS_IF([test "x$have_cmocka" = "xyes"], , [
  AS_IF([test "x$enable_tests" = "xyes"], [
    AC_MSG_ERROR([unit tests requested but cmocka not found])
  ])
])
AM_CONDITIONAL([USE_CMOCKA], [test "x$have_cmocka" = "xyes"])

AC_ARG_ENABLE([examples], AS_HELP_STRING([--enable-examples], [build examples]))
AS_IF([test "x$enable_examples" = "xyes"], [
  EXAMPLES="enabled"
], [
  EXAMPLES="disabled"
])
AM_CONDITIONAL([BUILD_EXAMPLES], [test "x$enable_examples" = "xyes"])

AC_CONFIG_FILES([
  Makefile
  Doxyfile
  squareball.pc
])
AC_OUTPUT

AS_IF([test "x$enable_bundleme" != "xyes"], [AS_ECHO("
        ==== ${PACKAGE_STRING} ====

        prefix:       ${prefix}
        exec_prefix:  ${exec_prefix}
        bindir:       ${bindir}

        compiler:     ${CC}
        cflags:       ${CFLAGS}
        ldflags:      ${LDFLAGS}

        tests:        ${TESTS}
        examples:     ${EXAMPLES}

        doxygen:      ${DOXYGEN}
        valgrind:     ${VALGRIND}
")])
