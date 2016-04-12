/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2016 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>
#include <string.h>

#include <squareball/sb-configparser.h>
#include <squareball/sb-configparser-private.h>
#include <squareball/sb-strfuncs.h>
#include <squareball/sb-trie.h>


static void
test_config_empty(void **state)
{
    const char *a = "";
    sb_error_t *err = NULL;
    sb_config_t *c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 0);
    sb_config_free(c);
}


static void
test_config_section_empty(void **state)
{
    const char *a = "[foo]";
    sb_error_t *err = NULL;
    sb_config_t *c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 1);
    char **s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 1);
    assert_string_equal(s[0], "foo");
    assert_null(s[1]);
    sb_strv_free(s);
    char **k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 0);
    assert_null(k[0]);
    sb_strv_free(k);
    sb_config_free(c);
}


static void
test_config_section(void **state)
{
    const char *a =
        "[foo]\n"
        "asd = zxc";
    sb_error_t *err = NULL;
    sb_config_t *c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 1);
    char **s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 1);
    assert_string_equal(s[0], "foo");
    assert_null(s[1]);
    sb_strv_free(s);
    assert_string_equal(sb_config_get(c, "foo", "asd"), "zxc");
    char **k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 1);
    assert_string_equal(k[0], "asd");
    assert_null(k[1]);
    sb_strv_free(k);
    sb_config_free(c);

    a =
        "[foo]\n"
        "asd = zxc\n";
    err = NULL;
    c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 1);
    s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 1);
    assert_string_equal(s[0], "foo");
    assert_null(s[1]);
    sb_strv_free(s);
    assert_string_equal(sb_config_get(c, "foo", "asd"), "zxc");
    k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 1);
    assert_string_equal(k[0], "asd");
    assert_null(k[1]);
    sb_strv_free(k);
    sb_config_free(c);

    a =
        "[foo]\r\n"
        "asd = zxc\r\n";
    err = NULL;
    c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 1);
    s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 1);
    assert_string_equal(s[0], "foo");
    assert_null(s[1]);
    sb_strv_free(s);
    assert_string_equal(sb_config_get(c, "foo", "asd"), "zxc");
    k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 1);
    assert_string_equal(k[0], "asd");
    assert_null(k[1]);
    sb_strv_free(k);
    sb_config_free(c);
}


static void
test_config_section_multiple_keys(void **state)
{
    const char *a =
        "[foo]\n"
        "asd = zxc\n"
        "qwe = rty\n"
        "zxc = vbn";
    sb_error_t *err = NULL;
    sb_config_t *c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 1);
    char **s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 1);
    assert_string_equal(s[0], "foo");
    assert_null(s[1]);
    sb_strv_free(s);
    assert_string_equal(sb_config_get(c, "foo", "asd"), "zxc");
    assert_string_equal(sb_config_get(c, "foo", "qwe"), "rty");
    assert_string_equal(sb_config_get(c, "foo", "zxc"), "vbn");
    char **k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 3);
    assert_string_equal(k[0], "asd");
    assert_string_equal(k[1], "qwe");
    assert_string_equal(k[2], "zxc");
    assert_null(k[3]);
    sb_strv_free(k);
    sb_config_free(c);

    a =
        "[foo]\n"
        "asd = zxc\n"
        "qwe = rty\n"
        "zxc = vbn\n";
    err = NULL;
    c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 1);
    s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 1);
    assert_string_equal(s[0], "foo");
    assert_null(s[1]);
    sb_strv_free(s);
    assert_string_equal(sb_config_get(c, "foo", "asd"), "zxc");
    assert_string_equal(sb_config_get(c, "foo", "qwe"), "rty");
    assert_string_equal(sb_config_get(c, "foo", "zxc"), "vbn");
    k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 3);
    assert_string_equal(k[0], "asd");
    assert_string_equal(k[1], "qwe");
    assert_string_equal(k[2], "zxc");
    assert_null(k[3]);
    sb_strv_free(k);
    sb_config_free(c);

    a =
        "[foo]\r\n"
        "asd = zxc\r\n"
        "qwe = rty\r\n"
        "zxc = vbn\r\n";
    err = NULL;
    c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 1);
    s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 1);
    assert_string_equal(s[0], "foo");
    assert_null(s[1]);
    sb_strv_free(s);
    assert_string_equal(sb_config_get(c, "foo", "asd"), "zxc");
    assert_string_equal(sb_config_get(c, "foo", "qwe"), "rty");
    assert_string_equal(sb_config_get(c, "foo", "zxc"), "vbn");
    k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 3);
    assert_string_equal(k[0], "asd");
    assert_string_equal(k[1], "qwe");
    assert_string_equal(k[2], "zxc");
    assert_null(k[3]);
    sb_strv_free(k);
    sb_config_free(c);
}


static void
test_config_section_multiple_sections(void **state)
{
    const char *a =
        "[foo]\n"
        "asd = zxc\n"
        "qwe = rty\n"
        "zxc = vbn\n"
        "\n"
        "[bar]\n"
        "lol = hehe";
    sb_error_t *err = NULL;
    sb_config_t *c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 2);
    char **s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 2);
    assert_string_equal(s[0], "foo");
    assert_string_equal(s[1], "bar");
    assert_null(s[2]);
    sb_strv_free(s);
    assert_string_equal(sb_config_get(c, "foo", "asd"), "zxc");
    assert_string_equal(sb_config_get(c, "foo", "qwe"), "rty");
    assert_string_equal(sb_config_get(c, "foo", "zxc"), "vbn");
    assert_string_equal(sb_config_get(c, "bar", "lol"), "hehe");
    char **k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 3);
    assert_string_equal(k[0], "asd");
    assert_string_equal(k[1], "qwe");
    assert_string_equal(k[2], "zxc");
    assert_null(k[3]);
    sb_strv_free(k);
    k = sb_config_list_keys(c, "bar");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 1);
    assert_string_equal(k[0], "lol");
    assert_null(k[1]);
    sb_strv_free(k);
    sb_config_free(c);

    a =
        "[foo]\n"
        "asd = zxc\n"
        "qwe = rty\n"
        "zxc = vbn\n"
        "\n"
        "[bar]\n"
        "lol = hehe\n";
    err = NULL;
    c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 2);
    s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 2);
    assert_string_equal(s[0], "foo");
    assert_string_equal(s[1], "bar");
    assert_null(s[2]);
    sb_strv_free(s);
    assert_string_equal(sb_config_get(c, "foo", "asd"), "zxc");
    assert_string_equal(sb_config_get(c, "foo", "qwe"), "rty");
    assert_string_equal(sb_config_get(c, "foo", "zxc"), "vbn");
    assert_string_equal(sb_config_get(c, "bar", "lol"), "hehe");
    k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 3);
    assert_string_equal(k[0], "asd");
    assert_string_equal(k[1], "qwe");
    assert_string_equal(k[2], "zxc");
    assert_null(k[3]);
    sb_strv_free(k);
    k = sb_config_list_keys(c, "bar");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 1);
    assert_string_equal(k[0], "lol");
    assert_null(k[1]);
    sb_strv_free(k);
    sb_config_free(c);

    a =
        "[foo]\r\n"
        "asd = zxc\r\n"
        "qwe = rty\r\n"
        "zxc = vbn\r\n"
        "\r\n"
        "[bar]\r\n"
        "lol = hehe\r\n";
    err = NULL;
    c = sb_config_parse(a, strlen(a), &err);
    assert_null(err);
    assert_non_null(c);
    assert_non_null(c->root);
    assert_int_equal(sb_trie_size(c->root), 2);
    s = sb_config_list_sections(c);
    assert_non_null(s);
    assert_int_equal(sb_strv_length(s), 2);
    assert_string_equal(s[0], "foo");
    assert_string_equal(s[1], "bar");
    assert_null(s[2]);
    sb_strv_free(s);
    assert_string_equal(sb_config_get(c, "foo", "asd"), "zxc");
    assert_string_equal(sb_config_get(c, "foo", "qwe"), "rty");
    assert_string_equal(sb_config_get(c, "foo", "zxc"), "vbn");
    assert_string_equal(sb_config_get(c, "bar", "lol"), "hehe");
    k = sb_config_list_keys(c, "foo");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 3);
    assert_string_equal(k[0], "asd");
    assert_string_equal(k[1], "qwe");
    assert_string_equal(k[2], "zxc");
    assert_null(k[3]);
    sb_strv_free(k);
    k = sb_config_list_keys(c, "bar");
    assert_non_null(k);
    assert_int_equal(sb_strv_length(k), 1);
    assert_string_equal(k[0], "lol");
    assert_null(k[1]);
    sb_strv_free(k);
    sb_config_free(c);
}


static void
test_config_error_start(void **state)
{
    const char *a =
        "asd\n"
        "[foo]";
    sb_error_t *err = NULL;
    sb_config_t *c = sb_config_parse(a, strlen(a), &err);
    assert_non_null(err);
    assert_null(c);
    assert_int_equal(err->code, -10);
    assert_string_equal(err->msg, "File must start with section");
    sb_error_free(err);
}


static void
test_config_error_section_with_newline(void **state)
{
    const char *a =
        "[foo\nbar]";
    sb_error_t *err = NULL;
    sb_config_t *c = sb_config_parse(a, strlen(a), &err);
    assert_non_null(err);
    assert_null(c);
    assert_int_equal(err->code, -10);
    assert_string_equal(err->msg, "Section names can't have new lines");
    sb_error_free(err);
}


static void
test_config_error_key_without_value(void **state)
{
    const char *a =
        "[foobar]\n"
        "asd = 12\n"
        "foo";
    sb_error_t *err = NULL;
    sb_config_t *c = sb_config_parse(a, strlen(a), &err);
    assert_non_null(err);
    assert_null(c);
    assert_int_equal(err->code, -10);
    assert_string_equal(err->msg, "Key without value: foo");
    sb_error_free(err);
    a =
        "[foobar]\n"
        "asd = 12\n"
        "foo\n";
    err = NULL;
    c = sb_config_parse(a, strlen(a), &err);
    assert_non_null(err);
    assert_null(c);
    assert_int_equal(err->code, -10);
    assert_string_equal(err->msg, "Key without value: foo");
    sb_error_free(err);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_config_empty),
        unit_test(test_config_section_empty),
        unit_test(test_config_section),
        unit_test(test_config_section_multiple_keys),
        unit_test(test_config_section_multiple_sections),
        unit_test(test_config_error_start),
        unit_test(test_config_error_section_with_newline),
        unit_test(test_config_error_key_without_value),
    };
    return run_tests(tests);
}
