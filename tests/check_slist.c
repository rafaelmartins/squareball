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

#include <squareball/sb-slist.h>
#include <squareball/sb-strfuncs.h>
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
test_slist_prepend(void **state)
{
    sb_slist_t *l = NULL;
    l = sb_slist_prepend(l, (void*) sb_strdup("bola"));
    assert_non_null(l);
    assert_string_equal(l->data, "bola");
    assert_null(l->next);
    l = sb_slist_prepend(l, (void*) sb_strdup("guda"));
    assert_non_null(l);
    assert_string_equal(l->data, "guda");
    assert_non_null(l->next);
    assert_string_equal(l->next->data, "bola");
    assert_null(l->next->next);
    sb_slist_free_full(l, free);
}


static int
sort_func(const void *a, const void *b)
{
    return strcmp((const char*) a, (const char*) b);
}


static void
test_slist_sort_empty(void **state)
{
    sb_slist_t *l = NULL;
    assert_null(sb_slist_sort(l, sort_func));
}


static void
test_slist_sort_single(void **state)
{
    sb_slist_t *l = NULL;
    l = sb_slist_append(l, sb_strdup("a"));

    l = sb_slist_sort(l, sort_func);

    assert_non_null(l);
    assert_string_equal(l->data, "a");
    assert_null(l->next);

    sb_slist_free_full(l, free);
}


static void
test_slist_sort_sorted(void **state)
{
    sb_slist_t *l = NULL;
    l = sb_slist_append(l, sb_strdup("a"));
    l = sb_slist_append(l, sb_strdup("b"));
    l = sb_slist_append(l, sb_strdup("c"));

    l = sb_slist_sort(l, sort_func);

    assert_non_null(l);
    assert_string_equal(l->data, "a");
    assert_string_equal(l->next->data, "b");
    assert_string_equal(l->next->next->data, "c");
    assert_null(l->next->next->next);

    sb_slist_free_full(l, free);
}


static void
test_slist_sort_reverse(void **state)
{
    sb_slist_t *l = NULL;
    l = sb_slist_append(l, sb_strdup("d"));
    l = sb_slist_append(l, sb_strdup("c"));
    l = sb_slist_append(l, sb_strdup("b"));
    l = sb_slist_append(l, sb_strdup("a"));

    l = sb_slist_sort(l, sort_func);

    assert_non_null(l);
    assert_string_equal(l->data, "a");
    assert_string_equal(l->next->data, "b");
    assert_string_equal(l->next->next->data, "c");
    assert_string_equal(l->next->next->next->data, "d");
    assert_null(l->next->next->next->next);

    sb_slist_free_full(l, free);
}


static void
test_slist_sort_mixed1(void **state)
{
    sb_slist_t *l = NULL;
    l = sb_slist_append(l, sb_strdup("a"));
    l = sb_slist_append(l, sb_strdup("d"));
    l = sb_slist_append(l, sb_strdup("c"));
    l = sb_slist_append(l, sb_strdup("b"));

    l = sb_slist_sort(l, sort_func);

    assert_non_null(l);
    assert_string_equal(l->data, "a");
    assert_string_equal(l->next->data, "b");
    assert_string_equal(l->next->next->data, "c");
    assert_string_equal(l->next->next->next->data, "d");
    assert_null(l->next->next->next->next);

    sb_slist_free_full(l, free);
}


static void
test_slist_sort_mixed2(void **state)
{
    sb_slist_t *l = NULL;
    l = sb_slist_append(l, sb_strdup("c"));
    l = sb_slist_append(l, sb_strdup("b"));
    l = sb_slist_append(l, sb_strdup("a"));
    l = sb_slist_append(l, sb_strdup("d"));

    l = sb_slist_sort(l, sort_func);

    assert_non_null(l);
    assert_string_equal(l->data, "a");
    assert_string_equal(l->next->data, "b");
    assert_string_equal(l->next->next->data, "c");
    assert_string_equal(l->next->next->next->data, "d");
    assert_null(l->next->next->next->next);

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
    assert_int_equal(sb_slist_length(NULL), 0);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_slist_append),
        unit_test(test_slist_prepend),
        unit_test(test_slist_sort_empty),
        unit_test(test_slist_sort_single),
        unit_test(test_slist_sort_sorted),
        unit_test(test_slist_sort_reverse),
        unit_test(test_slist_sort_mixed1),
        unit_test(test_slist_sort_mixed2),
        unit_test(test_slist_free),
        unit_test(test_slist_length),
    };
    return run_tests(tests);
}
