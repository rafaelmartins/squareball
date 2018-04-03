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

#include <squareball/sb-error.h>


static void
test_error_new(void **state)
{
    sb_error_t *error = sb_error_new(1, "bola %s");
    assert_non_null(error);
    assert_int_equal(error->code, 1);
    assert_string_equal(error->msg, "bola %s");
    sb_error_free(error);
}


static void
test_error_new_internal(void **state)
{
    sb_error_t *error = sb_error_new(SB_ERROR_FILE_OPEN, "bola %s");
    assert_non_null(error);
    assert_int_equal(error->code, -1);
    assert_string_equal(error->msg, "bola %s");
    sb_error_free(error);
}


static void
test_error_new_printf(void **state)
{
    sb_error_t *error = sb_error_new_printf(2, "bola %s", "guda");
    assert_non_null(error);
    assert_int_equal(error->code, 2);
    assert_string_equal(error->msg, "bola guda");
    sb_error_free(error);
}


static void
test_error_new_printf_internal(void **state)
{
    sb_error_t *error = sb_error_new_printf(-2, "bola %s", "guda");
    assert_non_null(error);
    assert_int_equal(error->code, -2);
    assert_string_equal(error->msg, "bola guda");
    sb_error_free(error);
}


static void
test_error_new_printf_parser(void **state)
{
    const char *a = "bola\nguda\nchunda\n";
    sb_error_t *error = sb_error_new_printf_parser(1, a, strlen(a), 11, "asd %d", 10);
    assert_non_null(error);
    assert_int_equal(error->code, 1);
    assert_string_equal(error->msg,
        "asd 10\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);
    a = "bola\nguda\nchunda";
    error = sb_error_new_printf_parser(1, a, strlen(a), 11, "asd %d", 10);
    assert_non_null(error);
    assert_int_equal(error->code, 1);
    assert_string_equal(error->msg,
        "asd 10\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);
    a = "bola\nguda\nchunda";
    error = sb_error_new_printf_parser(1, a, strlen(a), 0, "asd %d", 10);
    assert_non_null(error);
    assert_int_equal(error->code, 1);
    assert_string_equal(error->msg,
        "asd 10\nError occurred near line 1, position 1: bola");
    sb_error_free(error);
    a = "";
    error = sb_error_new_printf_parser(1, a, strlen(a), 0, "asd %d", 10);
    assert_non_null(error);
    assert_int_equal(error->code, 1);
    assert_string_equal(error->msg, "asd 10");
    sb_error_free(error);
}


static void
test_error_new_printf_parser_crlf(void **state)
{
    const char *a = "bola\r\nguda\r\nchunda\r\n";
    sb_error_t *error = sb_error_new_printf_parser(1, a, strlen(a), 13, "asd %d", 10);
    assert_non_null(error);
    assert_int_equal(error->code, 1);
    assert_string_equal(error->msg,
        "asd 10\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);
    a = "bola\r\nguda\r\nchunda";
    error = sb_error_new_printf_parser(1, a, strlen(a), 13, "asd %d", 10);
    assert_non_null(error);
    assert_int_equal(error->code, 1);
    assert_string_equal(error->msg,
        "asd 10\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);
    a = "bola\r\nguda\r\nchunda";
    error = sb_error_new_printf_parser(1, a, strlen(a), 0, "asd %d", 10);
    assert_non_null(error);
    assert_int_equal(error->code, 1);
    assert_string_equal(error->msg,
        "asd 10\nError occurred near line 1, position 1: bola");
    sb_error_free(error);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_error_new),
        unit_test(test_error_new_internal),
        unit_test(test_error_new_printf),
        unit_test(test_error_new_printf_internal),
        unit_test(test_error_new_printf_parser),
        unit_test(test_error_new_printf_parser_crlf),
    };
    return run_tests(tests);
}
