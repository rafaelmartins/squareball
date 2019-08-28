/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include <squareball/sb-strfuncs.h>


static void
test_strdup(void **state)
{
    char *str = sb_strdup("bola");
    assert_string_equal(str, "bola");
    free(str);
    str = sb_strdup(NULL);
    assert_null(str);
}


static void
test_strndup(void **state)
{
    char *str = sb_strndup("bolaguda", 4);
    assert_string_equal(str, "bola");
    free(str);
    str = sb_strndup("bolaguda", 30);
    assert_string_equal(str, "bolaguda");
    free(str);
    str = sb_strndup("bolaguda", 8);
    assert_string_equal(str, "bolaguda");
    free(str);
    str = sb_strdup(NULL);
    assert_null(str);
}


static void
test_strdup_printf(void **state)
{
    assert_null(sb_strdup_printf(NULL));
    char *str = sb_strdup_printf("bola");
    assert_string_equal(str, "bola");
    free(str);
    str = sb_strdup_printf("bola, %s", "guda");
    assert_string_equal(str, "bola, guda");
    free(str);
}


static void
test_str_starts_with(void **state)
{
    assert_true(sb_str_starts_with("bolaguda", "bola"));
    assert_true(sb_str_starts_with("bola", "bola"));
    assert_false(sb_str_starts_with("gudabola", "bola"));
    assert_false(sb_str_starts_with("guda", "bola"));
    assert_false(sb_str_starts_with("bola", "bolaguda"));
}


static void
test_str_ends_with(void **state)
{
    assert_true(sb_str_ends_with("bolaguda", "guda"));
    assert_true(sb_str_ends_with("bola", "bola"));
    assert_false(sb_str_ends_with("gudabola", "guda"));
    assert_false(sb_str_ends_with("guda", "bola"));
    assert_false(sb_str_ends_with("bola", "gudabola"));
}


static void
test_str_lstrip(void **state)
{
    char *str = sb_strdup("  \tbola\n  \t");
    assert_string_equal(sb_str_lstrip(str), "bola\n  \t");
    free(str);
    str = sb_strdup("guda");
    assert_string_equal(sb_str_lstrip(str), "guda");
    free(str);
    str = sb_strdup("\n");
    assert_string_equal(sb_str_lstrip(str), "");
    free(str);
    str = sb_strdup("\t \n");
    assert_string_equal(sb_str_lstrip(str), "");
    free(str);
    str = sb_strdup("");
    assert_string_equal(sb_str_lstrip(str), "");
    free(str);
    assert_null(sb_str_lstrip(NULL));
}


static void
test_str_rstrip(void **state)
{
    char *str = sb_strdup("  \tbola\n  \t");
    assert_string_equal(sb_str_rstrip(str), "  \tbola");
    free(str);
    str = sb_strdup("guda");
    assert_string_equal(sb_str_rstrip(str), "guda");
    free(str);
    str = sb_strdup("\n");
    assert_string_equal(sb_str_rstrip(str), "");
    free(str);
    str = sb_strdup("\t \n");
    assert_string_equal(sb_str_rstrip(str), "");
    free(str);
    str = sb_strdup("");
    assert_string_equal(sb_str_rstrip(str), "");
    free(str);
    assert_null(sb_str_rstrip(NULL));
}


static void
test_str_strip(void **state)
{
    char *str = sb_strdup("  \tbola\n  \t");
    assert_string_equal(sb_str_strip(str), "bola");
    free(str);
    str = sb_strdup("guda");
    assert_string_equal(sb_str_strip(str), "guda");
    free(str);
    str = sb_strdup("\n");
    assert_string_equal(sb_str_strip(str), "");
    free(str);
    str = sb_strdup("\t \n");
    assert_string_equal(sb_str_strip(str), "");
    free(str);
    str = sb_strdup("");
    assert_string_equal(sb_str_strip(str), "");
    free(str);
    assert_null(sb_str_strip(NULL));
}


static void
test_str_split(void **state)
{
    char **strv = sb_str_split("bola:guda:chunda", ':', 0);
    assert_string_equal(strv[0], "bola");
    assert_string_equal(strv[1], "guda");
    assert_string_equal(strv[2], "chunda");
    assert_null(strv[3]);
    sb_strv_free(strv);
    strv = sb_str_split("bola:guda:chunda", ':', 2);
    assert_string_equal(strv[0], "bola");
    assert_string_equal(strv[1], "guda:chunda");
    assert_null(strv[2]);
    sb_strv_free(strv);
    strv = sb_str_split("bola:guda:chunda", ':', 1);
    assert_string_equal(strv[0], "bola:guda:chunda");
    assert_null(strv[1]);
    sb_strv_free(strv);
    strv = sb_str_split("", ':', 1);
    assert_null(strv[0]);
    sb_strv_free(strv);
    assert_null(sb_str_split(NULL, ':', 0));
}


static void
test_str_replace(void **state)
{
    char *str = sb_str_replace("bolao", 'o', "zaz");
    assert_string_equal(str, "bzazlazaz");
    free(str);
    str = sb_str_replace("bolao", 'b', "zaz");
    assert_string_equal(str, "zazolao");
    free(str);
    str = sb_str_replace("bolao", 'b', NULL);
    assert_string_equal(str, "bolao");
    free(str);
    assert_null(sb_str_replace(NULL, 'b', "zaz"));
}


static void
test_str_find(void **state)
{
    assert_null(sb_str_find(NULL, 'c'));
    assert_string_equal(sb_str_find("bola", 'l'), "la");
    assert_string_equal(sb_str_find("bo\\lalala", 'l'), "lala");
    assert_string_equal(sb_str_find("bola", '\0'), "");
    assert_null(sb_str_find("bola", 'g'));
    assert_null(sb_str_find("bo\\la", 'l'));
}


static void
test_str_to_bool(void **state)
{
    assert_false(sb_str_to_bool(NULL));
    assert_true(sb_str_to_bool("1"));
    assert_true(sb_str_to_bool("y"));
    assert_true(sb_str_to_bool("Y"));
    assert_true(sb_str_to_bool("yes"));
    assert_true(sb_str_to_bool("YES"));
    assert_true(sb_str_to_bool("true"));
    assert_true(sb_str_to_bool("TRUE"));
    assert_true(sb_str_to_bool("on"));
    assert_true(sb_str_to_bool("ON"));
    assert_false(sb_str_to_bool("0"));
    assert_false(sb_str_to_bool("n"));
    assert_false(sb_str_to_bool("N"));
    assert_false(sb_str_to_bool("no"));
    assert_false(sb_str_to_bool("NO"));
    assert_false(sb_str_to_bool("false"));
    assert_false(sb_str_to_bool("FALSE"));
    assert_false(sb_str_to_bool("off"));
    assert_false(sb_str_to_bool("OFF"));
}


static void
test_strv_join(void **state)
{
    char *pieces[] = {"guda","bola", "chunda", NULL};
    char *str = sb_strv_join(pieces, ":");
    assert_string_equal(str, "guda:bola:chunda");
    free(str);
    char *pieces2[] = {NULL};
    str = sb_strv_join(pieces2, ":");
    assert_string_equal(str, "");
    free(str);
    assert_null(sb_strv_join(pieces, NULL));
    assert_null(sb_strv_join(NULL, ":"));
    assert_null(sb_strv_join(NULL, NULL));
}


static void
test_strv_length(void **state)
{
    char *pieces[] = {"guda","bola", "chunda", NULL};
    assert_int_equal(sb_strv_length(pieces), 3);
    char *pieces2[] = {NULL};
    assert_int_equal(sb_strv_length(pieces2), 0);
    assert_int_equal(sb_strv_length(NULL), 0);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_strdup),
        unit_test(test_strndup),
        unit_test(test_strdup_printf),
        unit_test(test_str_starts_with),
        unit_test(test_str_ends_with),
        unit_test(test_str_lstrip),
        unit_test(test_str_rstrip),
        unit_test(test_str_strip),
        unit_test(test_str_split),
        unit_test(test_str_replace),
        unit_test(test_str_find),
        unit_test(test_str_to_bool),
        unit_test(test_strv_join),
        unit_test(test_strv_length),
    };
    return run_tests(tests);
}
