## Autotools settings

ACLOCAL_AMFLAGS = -I m4

AM_DISTCHECK_CONFIGURE_FLAGS = \
	--enable-examples \
	--enable-tests \
	--disable-valgrind \
	--disable-bundleme \
	$(NULL)


## File listings

EXTRA_DIST = \
	build-aux/git-version-gen \
	$(top_srcdir)/.version \
	doc/00_index.md \
	autogen.sh \
	LICENSE \
	README.md \
	$(NULL)

BUILT_SOURCES = \
	$(top_srcdir)/.version \
	$(NULL)


if BUNDLE_ME

noinst_HEADERS = \
	src/squareball.h \
	src/squareball/sb-mem.h \
	src/squareball/sb-slist.h \
	src/squareball/sb-strfuncs.h \
	src/squareball/sb-string.h \
	src/squareball/sb-trie.h \
	src/squareball/sb-trie-private.h \
	$(NULL)

noinst_LTLIBRARIES = \
	libsquareball.la \
	$(NULL)

else

include_HEADERS = \
	src/squareball.h \
	$(NULL)

pkginclude_HEADERS = \
	src/squareball/sb-mem.h \
	src/squareball/sb-slist.h \
	src/squareball/sb-strfuncs.h \
	src/squareball/sb-string.h \
	src/squareball/sb-trie.h \
	$(NULL)

noinst_HEADERS = \
	src/squareball/sb-trie-private.h \
	$(NULL)

lib_LTLIBRARIES = \
	libsquareball.la \
	$(NULL)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = squareball.pc

endif

noinst_PROGRAMS = \
	$(NULL)

check_PROGRAMS = \
	$(NULL)


libsquareball_la_SOURCES = \
	src/sb-mem.c \
	src/sb-slist.c \
	src/sb-strfuncs.c \
	src/sb-string.c \
	src/sb-trie.c \
	$(NULL)

libsquareball_la_CFLAGS = \
	$(AM_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

libsquareball_la_LIBADD = \
	$(NULL)

if !BUNDLE_ME
libsquareball_la_LDFLAGS = \
	-version-info $(LIBSQUAREBALL_LT_VERSION_INFO) \
	$(NULL)
endif


## Build rules: examples

if BUILD_EXAMPLES

noinst_PROGRAMS += \
	examples/hello_slist \
	examples/hello_string \
	examples/hello_trie \
	$(NULL)

examples_hello_slist_SOURCES = \
	examples/hello_slist.c \
	$(NULL)

examples_hello_slist_CFLAGS = \
	-I$(top_srcdir)/src \
	$(NULL)

examples_hello_slist_LDFLAGS = \
	-no-install \
	$(NULL)

examples_hello_slist_LDADD= \
	libsquareball.la \
	$(NULL)

examples_hello_string_SOURCES = \
	examples/hello_string.c \
	$(NULL)

examples_hello_string_CFLAGS = \
	-I$(top_srcdir)/src \
	$(NULL)

examples_hello_string_LDFLAGS = \
	-no-install \
	$(NULL)

examples_hello_string_LDADD= \
	libsquareball.la \
	$(NULL)

examples_hello_trie_SOURCES = \
	examples/hello_trie.c \
	$(NULL)

examples_hello_trie_CFLAGS = \
	-I$(top_srcdir)/src \
	$(NULL)

examples_hello_trie_LDFLAGS = \
	-no-install \
	$(NULL)

examples_hello_trie_LDADD= \
	libsquareball.la \
	$(NULL)

endif


## Build rules: tests

if USE_CMOCKA

check_PROGRAMS += \
	tests/check_slist \
	tests/check_strfuncs \
	tests/check_string \
	tests/check_trie \
	$(NULL)

tests_check_slist_SOURCES = \
	tests/check_slist.c \
	$(NULL)

tests_check_slist_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_slist_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_slist_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

tests_check_strfuncs_SOURCES = \
	tests/check_strfuncs.c \
	$(NULL)

tests_check_strfuncs_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_strfuncs_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_strfuncs_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

tests_check_string_SOURCES = \
	tests/check_string.c \
	$(NULL)

tests_check_string_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_string_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_string_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

tests_check_trie_SOURCES = \
	tests/check_trie.c \
	$(NULL)

tests_check_trie_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_trie_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_trie_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

endif

TESTS = \
	$(check_PROGRAMS)


clean-local:
	-rm -rf $(top_builddir)/doc/build/


## Helpers: Documentation

if BUILD_DOCS
docs: clean-local Doxyfile
	-mkdir -p $(top_builddir)/doc/build
	$(DOXYGEN) Doxyfile
endif


## Helpers: git-version-gen

$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@

dist-hook:
	echo $(VERSION) > $(distdir)/.tarball-version


## Helpers: Valgrind runner

if USE_VALGRIND
valgrind: all
	$(MAKE) check TESTS_ENVIRONMENT=" \
		$(VALGRIND) \
			--tool=memcheck \
			--leak-check=full \
			--leak-resolution=high \
			--num-callers=20 \
			--error-exitcode=1 \
			--show-possibly-lost=no"

endif
