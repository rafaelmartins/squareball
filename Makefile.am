## Autotools settings

ACLOCAL_AMFLAGS = -I m4

AM_DISTCHECK_CONFIGURE_FLAGS = \
	--enable-tests \
	--disable-valgrind \
	$(NULL)


## File listings

EXTRA_DIST = \
	autogen.sh \
	LICENSE \
	README.md \
	$(NULL)


include_HEADERS = \
	src/squareball.h \
	$(NULL)

lib_LTLIBRARIES = \
	libsquareball.la \
	$(NULL)

check_PROGRAMS = \
	$(NULL)


libsquareball_la_SOURCES = \
	src/mem.c \
	src/slist.c \
	src/strings.c \
	src/trie.c \
	$(NULL)

libsquareball_la_CFLAGS = \
	$(AM_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

libsquareball_la_LIBADD = \
	$(NULL)

libsquareball_la_LDFLAGS = \
	-version-info $(LIBSQUAREBALL_LT_VERSION_INFO) \
	$(NULL)


## Build rules: tests

if USE_CMOCKA

check_PROGRAMS += \
	tests/check_slist \
	tests/check_strings \
	tests/check_trie \
	$(NULL)

tests_check_slist_SOURCES = \
	tests/check_slist.c \
	$(NULL)

tests_check_slist_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	$(NULL)

tests_check_slist_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_slist_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

tests_check_strings_SOURCES = \
	tests/check_strings.c \
	$(NULL)

tests_check_strings_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	$(NULL)

tests_check_strings_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_strings_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

tests_check_trie_SOURCES = \
	tests/check_trie.c \
	$(NULL)

tests_check_trie_CFLAGS = \
	$(CMOCKA_CFLAGS) \
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
	$(DOXYGEN) Doxyfile
endif


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
