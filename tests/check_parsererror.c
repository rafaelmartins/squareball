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

#include <string.h>
#include <squareball/sb-error.h>
#include <squareball/sb-parsererror.h>


static void
test_parser_error_new_null(void **state)
{
    sb_error_t *error = sb_parser_error_new(NULL, 0, 0, NULL);
    assert_non_null(error);
    const sb_parser_error_t *data = sb_error_get_data(error);
    assert_non_null(data);
    assert_null(data->msg);
    assert_null(data->linestr);
    assert_int_equal(data->lineno, 0);
    assert_int_equal(data->pos, 0);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error), "(unset)");
    sb_error_free(error);

    error = sb_parser_error_new(NULL, 0, 0, "asd");
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd");
    assert_null(data->linestr);
    assert_int_equal(data->lineno, 0);
    assert_int_equal(data->pos, 0);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error), "asd");
    sb_error_free(error);
}


static void
test_parser_error_new(void **state)
{
    const char *a = "bola\nguda\nchunda\n";
    sb_error_t *error = sb_parser_error_new(a, strlen(a), 11, "asd %d");
    assert_non_null(error);
    const sb_parser_error_t *data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd %d");
    assert_string_equal(data->linestr, "chunda");
    assert_int_equal(data->lineno, 3);
    assert_int_equal(data->pos, 2);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "asd %d\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);

    a = "bola\nguda\nchunda";
    error = sb_parser_error_new(a, strlen(a), 11, NULL);
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_null(data->msg);
    assert_string_equal(data->linestr, "chunda");
    assert_int_equal(data->lineno, 3);
    assert_int_equal(data->pos, 2);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "(unset)\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);

    a = "bola\nguda\nchunda";
    error = sb_parser_error_new(a, strlen(a), 0, "asd %d");
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd %d");
    assert_string_equal(data->linestr, "bola");
    assert_int_equal(data->lineno, 1);
    assert_int_equal(data->pos, 1);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "asd %d\nError occurred near line 1, position 1: bola");
    sb_error_free(error);

    a = "";
    error = sb_parser_error_new(a, strlen(a), 0, "asd %d");
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd %d");
    assert_string_equal(data->linestr, "");
    assert_int_equal(data->lineno, 1);
    assert_int_equal(data->pos, 1);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error), "asd %d");
    sb_error_free(error);
}


static void
test_parser_error_new_crlf(void **state)
{
    const char *a = "bola\r\nguda\r\nchunda\r\n";
    sb_error_t *error = sb_parser_error_new(a, strlen(a), 13, "asd %d");
    assert_non_null(error);
    const sb_parser_error_t *data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd %d");
    assert_string_equal(data->linestr, "chunda");
    assert_int_equal(data->lineno, 3);
    assert_int_equal(data->pos, 2);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "asd %d\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);

    a = "bola\r\nguda\r\nchunda";
    error = sb_parser_error_new(a, strlen(a), 13, NULL);
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_null(data->msg);
    assert_string_equal(data->linestr, "chunda");
    assert_int_equal(data->lineno, 3);
    assert_int_equal(data->pos, 2);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "(unset)\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);

    a = "bola\r\nguda\r\nchunda";
    error = sb_parser_error_new(a, strlen(a), 0, "asd %d");
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd %d");
    assert_string_equal(data->linestr, "bola");
    assert_int_equal(data->lineno, 1);
    assert_int_equal(data->pos, 1);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "asd %d\nError occurred near line 1, position 1: bola");
    sb_error_free(error);
}


static void
test_parser_error_new_printf(void **state)
{
    const char *a = "bola\nguda\nchunda\n";
    sb_error_t *error = sb_parser_error_new_printf(a, strlen(a), 11, "asd %d", 10);
    assert_non_null(error);
    const sb_parser_error_t *data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd 10");
    assert_string_equal(data->linestr, "chunda");
    assert_int_equal(data->lineno, 3);
    assert_int_equal(data->pos, 2);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "asd 10\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);

    a = "bola\nguda\nchunda";
    error = sb_parser_error_new_printf(a, strlen(a), 11, NULL);
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_null(data->msg);
    assert_string_equal(data->linestr, "chunda");
    assert_int_equal(data->lineno, 3);
    assert_int_equal(data->pos, 2);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "(unset)\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);

    a = "bola\nguda\nchunda";
    error = sb_parser_error_new_printf(a, strlen(a), 0, "asd %d", 10);
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd 10");
    assert_string_equal(data->linestr, "bola");
    assert_int_equal(data->lineno, 1);
    assert_int_equal(data->pos, 1);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "asd 10\nError occurred near line 1, position 1: bola");
    sb_error_free(error);

    a = "";
    error = sb_parser_error_new_printf(a, strlen(a), 0, "asd %d", 10);
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd 10");
    assert_string_equal(data->linestr, "");
    assert_int_equal(data->lineno, 1);
    assert_int_equal(data->pos, 1);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error), "asd 10");
    sb_error_free(error);
}


static void
test_parser_error_new_printf_crlf(void **state)
{
    const char *a = "bola\r\nguda\r\nchunda\r\n";
    sb_error_t *error = sb_parser_error_new_printf(a, strlen(a), 13, "asd %d", 10);
    assert_non_null(error);
    const sb_parser_error_t *data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd 10");
    assert_string_equal(data->linestr, "chunda");
    assert_int_equal(data->lineno, 3);
    assert_int_equal(data->pos, 2);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "asd 10\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);

    a = "bola\r\nguda\r\nchunda";
    error = sb_parser_error_new_printf(a, strlen(a), 13, NULL);
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_null(data->msg);
    assert_string_equal(data->linestr, "chunda");
    assert_int_equal(data->lineno, 3);
    assert_int_equal(data->pos, 2);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "(unset)\nError occurred near line 3, position 2: chunda");
    sb_error_free(error);

    a = "bola\r\nguda\r\nchunda";
    error = sb_parser_error_new_printf(a, strlen(a), 0, "asd %d", 10);
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_string_equal(data->msg, "asd 10");
    assert_string_equal(data->linestr, "bola");
    assert_int_equal(data->lineno, 1);
    assert_int_equal(data->pos, 1);
    assert_string_equal(sb_error_get_type_name(error), "parser");
    assert_string_equal(sb_error_to_string(error),
        "asd 10\nError occurred near line 1, position 1: bola");
    sb_error_free(error);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_parser_error_new_null),
        unit_test(test_parser_error_new),
        unit_test(test_parser_error_new_crlf),
        unit_test(test_parser_error_new_printf),
        unit_test(test_parser_error_new_printf_crlf),
    };
    return run_tests(tests);
}
