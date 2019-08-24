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
#include <squareball/sb-mem.h>
#include <squareball/sb-strfuncs.h>
#include <squareball/sb-error.h>

typedef struct {
    int a;
    char *b;
} my_error_data_t;


static char*
my_error_to_string(void *data)
{
    if (data == NULL)
        return sb_strdup("");

    my_error_data_t *d = data;
    return sb_strdup_printf("my error: %s (%d)", d->b == NULL ? "NULL" : d->b,
        d->a);
}


static void
my_error_free(void *data)
{
    if (data == NULL)
        return;

    my_error_data_t *d = data;
    free(d->b);
    free(d);
}


static sb_error_type_t my_error = {
    .name = "my_error",
    .to_string_func = my_error_to_string,
    .free_func = my_error_free,
};


static sb_error_t*
my_error_new(int a, const char *b)
{
    my_error_data_t *d = sb_malloc(sizeof(my_error_data_t));
    d->a = a;
    d->b = sb_strdup(b);
    return sb_error_new_from_type(&my_error, d);
}


static void
test_error_new(void **state)
{
    sb_error_t *error = my_error_new(0, NULL);
    assert_non_null(error);
    const my_error_data_t *data = sb_error_get_data(error);
    assert_non_null(data);
    assert_int_equal(data->a, 0);
    assert_null(data->b);
    assert_string_equal(sb_error_get_type_name(error), "my_error");
    assert_string_equal(sb_error_to_string(error), "my error: NULL (0)");
    sb_error_free(error);

    error = my_error_new(2, "asd");
    assert_non_null(error);
    data = sb_error_get_data(error);
    assert_non_null(data);
    assert_int_equal(data->a, 2);
    assert_string_equal(data->b, "asd");
    assert_string_equal(sb_error_get_type_name(error), "my_error");
    assert_string_equal(sb_error_to_string(error), "my error: asd (2)");
    sb_error_free(error);
}


static void
test_error_new_null(void **state)
{
    sb_error_t *error = sb_error_new_from_type(NULL, NULL);
    assert_non_null(error);
    assert_null(sb_error_get_data(error));
    assert_null(sb_error_get_type_name(error));
    assert_null(sb_error_to_string(error));
    sb_error_free(error);

    error = sb_error_new_from_type(&my_error, NULL);
    assert_non_null(error);
    assert_null(sb_error_get_data(error));
    assert_string_equal(sb_error_get_type_name(error), "my_error");
    assert_string_equal(sb_error_to_string(error), "");
    sb_error_free(error);

    error = sb_error_new_from_type(NULL, "asd");
    assert_non_null(error);
    assert_string_equal(sb_error_get_data(error), "asd");
    assert_null(sb_error_get_type_name(error));
    assert_null(sb_error_to_string(error));
    sb_error_free(error);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_error_new),
        unit_test(test_error_new_null),
    };
    return run_tests(tests);
}
