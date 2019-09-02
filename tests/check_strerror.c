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
#include <squareball/sb-strerror.h>


static void
test_strerror_new(void **state)
{
    sb_error_t *error = sb_strerror_new("bola %s");
    assert_non_null(error);
    assert_string_equal(sb_error_to_string(error), "bola %s");
    assert_string_equal(sb_error_get_data(error), "bola %s");
    assert_string_equal(sb_error_get_type_name(error), "string");
    sb_error_free(error);
}


static void
test_strerror_new_no_string(void **state)
{
    sb_error_t *error = sb_strerror_new("bola %s");
    assert_non_null(error);
    assert_string_equal(sb_error_get_data(error), "bola %s");
    assert_string_equal(sb_error_get_type_name(error), "string");
    sb_error_free(error);
}


static void
test_strerror_new_null(void **state)
{
    sb_error_t *error = sb_strerror_new(NULL);
    assert_non_null(error);
    assert_null(sb_error_to_string(error));
    assert_null(sb_error_get_data(error));
    assert_string_equal(sb_error_get_type_name(error), "string");
    sb_error_free(error);
}


static void
test_strerror_new_printf(void **state)
{
    sb_error_t *error = sb_strerror_new_printf("bola %s", "guda");
    assert_non_null(error);
    assert_string_equal(sb_error_to_string(error), "bola guda");
    assert_string_equal(sb_error_get_data(error), "bola guda");
    assert_string_equal(sb_error_get_type_name(error), "string");
    sb_error_free(error);
}


static void
test_strerror_new_printf_null(void **state)
{
    sb_error_t *error = sb_strerror_new_printf(NULL);
    assert_non_null(error);
    assert_null(sb_error_to_string(error));
    assert_null(sb_error_get_data(error));
    assert_string_equal(sb_error_get_type_name(error), "string");
    sb_error_free(error);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_strerror_new),
        unit_test(test_strerror_new_no_string),
        unit_test(test_strerror_new_null),
        unit_test(test_strerror_new_printf),
        unit_test(test_strerror_new_printf_null),
    };
    return run_tests(tests);
}
