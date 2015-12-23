/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include <squareball/sb-slist.h>
#include <squareball/sb-string.h>


static void
test_slist_append(void **state)
{
    sb_slist_t *l = NULL;
    l = sb_slist_append(l, (void*) sb_strdup("bola"));
    assert_non_null(l);
    assert_string_equal(l->data, "bola");
    assert_null(l->next);
    l = sb_slist_append(l, (void*) sb_strdup("guda"));
    assert_non_null(l);
    assert_string_equal(l->data, "bola");
    assert_non_null(l->next);
    assert_string_equal(l->next->data, "guda");
    assert_null(l->next->next);
    sb_slist_free_full(l, free);
}


static void
test_slist_free(void **state)
{
    sb_slist_t *l = NULL;
    char *t1 = sb_strdup("bola");
    char *t2 = sb_strdup("guda");
    char *t3 = sb_strdup("chunda");
    l = sb_slist_append(l, (void*) t1);
    l = sb_slist_append(l, (void*) t2);
    l = sb_slist_append(l, (void*) t3);
    sb_slist_free(l);
    assert_string_equal(t1, "bola");
    assert_string_equal(t2, "guda");
    assert_string_equal(t3, "chunda");
    free(t1);
    free(t2);
    free(t3);
}


static void
test_slist_length(void **state)
{
    sb_slist_t *l = NULL;
    l = sb_slist_append(l, (void*) sb_strdup("bola"));
    l = sb_slist_append(l, (void*) sb_strdup("guda"));
    l = sb_slist_append(l, (void*) sb_strdup("chunda"));
    assert_int_equal(sb_slist_length(l), 3);
    sb_slist_free_full(l, free);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_slist_append),
        unit_test(test_slist_free),
        unit_test(test_slist_length),
    };
    return run_tests(tests);
}
