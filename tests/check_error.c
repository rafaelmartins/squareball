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
    sb_error_t *error = sb_error_new(SB_ERROR_FOO, "bola %s");
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


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_error_new),
        unit_test(test_error_new_internal),
        unit_test(test_error_new_printf),
        unit_test(test_error_new_printf_internal),
    };
    return run_tests(tests);
}
