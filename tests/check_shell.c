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

#include <squareball/sb-shell.h>


static void
test_shell_quote(void **state)
{
    char *t;
    t = sb_shell_quote(NULL);
    assert_string_equal(t, "''");
    free(t);
    t = sb_shell_quote("!bola");
    assert_string_equal(t, "''\\!'bola'");
    free(t);
    t = sb_shell_quote("'bola");
    assert_string_equal(t, "''\\''bola'");
    free(t);
    t = sb_shell_quote("bo!bola");
    assert_string_equal(t, "'bo'\\!'bola'");
    free(t);
    t = sb_shell_quote("bo'bola");
    assert_string_equal(t, "'bo'\\''bola'");
    free(t);
    t = sb_shell_quote("bola!");
    assert_string_equal(t, "'bola'\\!''");
    free(t);
    t = sb_shell_quote("bola'");
    assert_string_equal(t, "'bola'\\'''");
    free(t);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_shell_quote),
    };
    return run_tests(tests);
}
