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
#include <string.h>
#include <stdio.h>

#include <squareball/sb-stdin.h>


int
__wrap_fgetc(FILE *stream)
{
    assert_int_equal(fileno(stream), fileno(stdin));
    return mock_type(int);
}


static void
test_stdin_get_contents(void **state)
{
    will_return(__wrap_fgetc, EOF);
    char *t = sb_stdin_get_contents();
    assert_non_null(t);
    assert_string_equal(t, "");
    free(t);
    will_return(__wrap_fgetc, 'b');
    will_return(__wrap_fgetc, 'o');
    will_return(__wrap_fgetc, 'l');
    will_return(__wrap_fgetc, 'a');
    will_return(__wrap_fgetc, EOF);
    t = sb_stdin_get_contents();
    assert_non_null(t);
    assert_string_equal(t, "bola");
    free(t);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_stdin_get_contents),
    };
    return run_tests(tests);
}
