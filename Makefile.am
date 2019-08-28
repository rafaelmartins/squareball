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
	examples/config.ini \
	autogen.sh \
	LICENSE \
	README.md \
	squareball.m4 \
	$(NULL)

BUILT_SOURCES = \
	$(top_srcdir)/.version \
	$(NULL)


if BUNDLE_ME

noinst_HEADERS = \
	src/squareball.h \
	src/squareball/sb-compat.h \
	src/squareball/sb-configparser.h \
	src/squareball/sb-configparser-private.h \
	src/squareball/sb-error.h \
	src/squareball/sb-file.h \
	src/squareball/sb-mem.h \
	src/squareball/sb-parsererror.h \
	src/squareball/sb-shell.h \
	src/squareball/sb-slist.h \
	src/squareball/sb-stdin.h \
	src/squareball/sb-strerror.h \
	src/squareball/sb-strfuncs.h \
	src/squareball/sb-string.h \
	src/squareball/sb-trie.h \
	src/squareball/sb-trie-private.h \
	src/squareball/sb-utf8.h \
	$(NULL)

noinst_LTLIBRARIES = \
	libsquareball.la \
	$(NULL)

else

include_HEADERS = \
	src/squareball.h \
	$(NULL)

pkginclude_HEADERS = \
	src/squareball/sb-compat.h \
	src/squareball/sb-configparser.h \
	src/squareball/sb-error.h \
	src/squareball/sb-file.h \
	src/squareball/sb-mem.h \
	src/squareball/sb-parsererror.h \
	src/squareball/sb-shell.h \
	src/squareball/sb-slist.h \
	src/squareball/sb-stdin.h \
	src/squareball/sb-strerror.h \
	src/squareball/sb-strfuncs.h \
	src/squareball/sb-string.h \
	src/squareball/sb-trie.h \
	src/squareball/sb-utf8.h \
	$(NULL)

noinst_HEADERS = \
	src/squareball/sb-configparser-private.h \
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
	src/sb-compat.c \
	src/sb-configparser.c \
	src/sb-error.c \
	src/sb-file.c \
	src/sb-mem.c \
	src/sb-parsererror.c \
	src/sb-shell.c \
	src/sb-slist.c \
	src/sb-stdin.c \
	src/sb-strerror.c \
	src/sb-strfuncs.c \
	src/sb-string.c \
	src/sb-trie.c \
	src/sb-utf8.c \
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
	examples/hello_configparser \
	examples/hello_custom_error_type \
	examples/hello_dir_create \
	examples/hello_file_read \
	examples/hello_file_write \
	examples/hello_shell \
	examples/hello_slist \
	examples/hello_string \
	examples/hello_trie \
	$(NULL)

examples_hello_configparser_SOURCES = \
	examples/hello_configparser.c \
	$(NULL)

examples_hello_configparser_CFLAGS = \
	-I$(top_srcdir)/src \
	$(NULL)

examples_hello_configparser_LDFLAGS = \
	-no-install \
	$(NULL)

examples_hello_configparser_LDADD= \
	libsquareball.la \
	$(NULL)

examples_hello_custom_error_type_SOURCES = \
	examples/hello_custom_error_type.c \
	$(NULL)

examples_hello_custom_error_type_CFLAGS = \
	-I$(top_srcdir)/src \
	$(NULL)

examples_hello_custom_error_type_LDFLAGS = \
	-no-install \
	$(NULL)

examples_hello_custom_error_type_LDADD= \
	libsquareball.la \
	$(NULL)

examples_hello_dir_create_SOURCES = \
	examples/hello_dir_create.c \
	$(NULL)

examples_hello_dir_create_CFLAGS = \
	-I$(top_srcdir)/src \
	$(NULL)

examples_hello_dir_create_LDFLAGS = \
	-no-install \
	$(NULL)

examples_hello_dir_create_LDADD= \
	libsquareball.la \
	$(NULL)

examples_hello_file_read_SOURCES = \
	examples/hello_file_read.c \
	$(NULL)

examples_hello_file_read_CFLAGS = \
	-I$(top_srcdir)/src \
	$(NULL)

examples_hello_file_read_LDFLAGS = \
	-no-install \
	$(NULL)

examples_hello_file_read_LDADD= \
	libsquareball.la \
	$(NULL)

examples_hello_file_write_SOURCES = \
	examples/hello_file_write.c \
	$(NULL)

examples_hello_file_write_CFLAGS = \
	-I$(top_srcdir)/src \
	$(NULL)

examples_hello_file_write_LDFLAGS = \
	-no-install \
	$(NULL)

examples_hello_file_write_LDADD= \
	libsquareball.la \
	$(NULL)

examples_hello_shell_SOURCES = \
	examples/hello_shell.c \
	$(NULL)

examples_hello_shell_CFLAGS = \
	-I$(top_srcdir)/src \
	$(NULL)

examples_hello_shell_LDFLAGS = \
	-no-install \
	$(NULL)

examples_hello_shell_LDADD= \
	libsquareball.la \
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
	tests/check_configparser \
	tests/check_error \
	tests/check_parsererror \
	tests/check_shell \
	tests/check_slist \
	tests/check_strerror \
	tests/check_strfuncs \
	tests/check_string \
	tests/check_trie \
	tests/check_utf8 \
	$(NULL)

tests_check_configparser_SOURCES = \
	tests/check_configparser.c \
	$(NULL)

tests_check_configparser_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_configparser_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_configparser_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

tests_check_error_SOURCES = \
	tests/check_error.c \
	$(NULL)

tests_check_error_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_error_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_error_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

tests_check_parsererror_SOURCES = \
	tests/check_parsererror.c \
	$(NULL)

tests_check_parsererror_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_parsererror_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_parsererror_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

tests_check_shell_SOURCES = \
	tests/check_shell.c \
	$(NULL)

tests_check_shell_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_shell_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_shell_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
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

tests_check_strerror_SOURCES = \
	tests/check_strerror.c \
	$(NULL)

tests_check_strerror_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_strerror_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_strerror_LDADD = \
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

tests_check_utf8_SOURCES = \
	tests/check_utf8.c \
	$(NULL)

tests_check_utf8_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_utf8_LDFLAGS = \
	-no-install \
	$(NULL)

tests_check_utf8_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)

if USE_LD_WRAP
check_PROGRAMS += \
	tests/check_stdin \
	$(NULL)

tests_check_stdin_SOURCES = \
	tests/check_stdin.c \
	$(NULL)

tests_check_stdin_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

tests_check_stdin_LDFLAGS = \
	-static \
	-no-install \
	-Wl,--wrap=fgetc \
	$(NULL)

tests_check_stdin_LDADD = \
	$(CMOCKA_LIBS) \
	libsquareball.la \
	$(NULL)
endif

endif

TESTS = \
	$(check_PROGRAMS)


clean-local:
	-rm -rf $(top_builddir)/doc/build/


## Helpers: Documentation

if BUILD_DOCS
docs: clean-local Doxyfile
	-$(MKDIR_P) $(top_builddir)/doc/build
	$(DOXYGEN) Doxyfile

dist-docs: docs
	cp -r $(top_builddir)/doc/build/html $(top_builddir)/docs
	tar \
		-cvJf "$(PACKAGE_TARNAME)-docs-$(PACKAGE_VERSION).tar.xz" \
		-C $(top_builddir) \
		docs
endif


## Helpers: dist-srpm

if USE_RPMBUILD
dist-srpm: squareball.spec dist-xz
	$(RPMBUILD) \
		--define "_srcrpmdir $(top_builddir)" \
		--define "_sourcedir $(top_builddir)" \
		-bs squareball.spec
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
