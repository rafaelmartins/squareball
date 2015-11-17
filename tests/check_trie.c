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

#include "../src/squareball.h"


static void
test_trie_new(void **state)
{
    sb_trie_t *trie = sb_trie_new(free);
    assert_non_null(trie);
    assert_null(trie->root);
    assert_true(trie->free_func == free);
    sb_trie_free(trie);
}


static void
test_trie_insert(void **state)
{
    sb_trie_t *trie = sb_trie_new(free);

    sb_trie_insert(trie, "bola", sb_strdup("guda"));
    assert_true(trie->root->key == 'b');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'o');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'l');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == 'a');
    assert_null(trie->root->child->child->child->data);
    assert_true(trie->root->child->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->child->data, "guda");


    sb_trie_insert(trie, "chu", sb_strdup("nda"));
    assert_true(trie->root->key == 'b');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'o');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'l');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == 'a');
    assert_null(trie->root->child->child->child->data);
    assert_true(trie->root->child->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->child->data, "guda");

    assert_true(trie->root->next->key == 'c');
    assert_null(trie->root->next->data);
    assert_true(trie->root->next->child->key == 'h');
    assert_null(trie->root->next->child->data);
    assert_true(trie->root->next->child->child->key == 'u');
    assert_null(trie->root->next->child->child->data);
    assert_true(trie->root->next->child->child->child->key == '\0');
    assert_string_equal(trie->root->next->child->child->child->data, "nda");


    sb_trie_insert(trie, "bote", sb_strdup("aba"));
    assert_true(trie->root->key == 'b');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'o');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'l');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == 'a');
    assert_null(trie->root->child->child->child->data);
    assert_true(trie->root->child->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->child->data, "guda");

    assert_true(trie->root->next->key == 'c');
    assert_null(trie->root->next->data);
    assert_true(trie->root->next->child->key == 'h');
    assert_null(trie->root->next->child->data);
    assert_true(trie->root->next->child->child->key == 'u');
    assert_null(trie->root->next->child->child->data);
    assert_true(trie->root->next->child->child->child->key == '\0');
    assert_string_equal(trie->root->next->child->child->child->data, "nda");

    assert_true(trie->root->child->child->next->key == 't');
    assert_null(trie->root->child->child->next->data);
    assert_true(trie->root->child->child->next->child->key == 'e');
    assert_null(trie->root->child->child->next->child->data);
    assert_true(trie->root->child->child->next->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->next->child->child->data, "aba");


    sb_trie_insert(trie, "bo", sb_strdup("haha"));
    assert_true(trie->root->key == 'b');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'o');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'l');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == 'a');
    assert_null(trie->root->child->child->child->data);
    assert_true(trie->root->child->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->child->data, "guda");

    assert_true(trie->root->next->key == 'c');
    assert_null(trie->root->next->data);
    assert_true(trie->root->next->child->key == 'h');
    assert_null(trie->root->next->child->data);
    assert_true(trie->root->next->child->child->key == 'u');
    assert_null(trie->root->next->child->child->data);
    assert_true(trie->root->next->child->child->child->key == '\0');
    assert_string_equal(trie->root->next->child->child->child->data, "nda");

    assert_true(trie->root->child->child->next->key == 't');
    assert_null(trie->root->child->child->next->data);
    assert_true(trie->root->child->child->next->child->key == 'e');
    assert_null(trie->root->child->child->next->child->data);
    assert_true(trie->root->child->child->next->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->next->child->child->data, "aba");

    assert_true(trie->root->child->child->next->next->key == '\0');
    assert_string_equal(trie->root->child->child->next->next->data, "haha");

    sb_trie_free(trie);


    trie = sb_trie_new(free);

    sb_trie_insert(trie, "chu", sb_strdup("nda"));
    assert_true(trie->root->key == 'c');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'h');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'u');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->data, "nda");


    sb_trie_insert(trie, "bola", sb_strdup("guda"));
    assert_true(trie->root->key == 'c');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'h');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'u');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->data, "nda");

    assert_true(trie->root->next->key == 'b');
    assert_null(trie->root->next->data);
    assert_true(trie->root->next->child->key == 'o');
    assert_null(trie->root->next->child->data);
    assert_true(trie->root->next->child->child->key == 'l');
    assert_null(trie->root->next->child->child->data);
    assert_true(trie->root->next->child->child->child->key == 'a');
    assert_null(trie->root->next->child->child->child->data);
    assert_true(trie->root->next->child->child->child->child->key == '\0');
    assert_string_equal(trie->root->next->child->child->child->child->data, "guda");


    sb_trie_insert(trie, "bote", sb_strdup("aba"));
    assert_true(trie->root->key == 'c');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'h');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'u');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->data, "nda");

    assert_true(trie->root->next->key == 'b');
    assert_null(trie->root->next->data);
    assert_true(trie->root->next->child->key == 'o');
    assert_null(trie->root->next->child->data);
    assert_true(trie->root->next->child->child->key == 'l');
    assert_null(trie->root->next->child->child->data);
    assert_true(trie->root->next->child->child->child->key == 'a');
    assert_null(trie->root->next->child->child->child->data);
    assert_true(trie->root->next->child->child->child->child->key == '\0');
    assert_string_equal(trie->root->next->child->child->child->child->data, "guda");

    assert_true(trie->root->next->child->child->next->key == 't');
    assert_null(trie->root->next->child->child->next->data);
    assert_true(trie->root->next->child->child->next->child->key == 'e');
    assert_null(trie->root->next->child->child->next->child->data);
    assert_true(trie->root->next->child->child->next->child->child->key == '\0');
    assert_string_equal(trie->root->next->child->child->next->child->child->data, "aba");


    sb_trie_insert(trie, "bo", sb_strdup("haha"));
    assert_true(trie->root->key == 'c');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'h');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'u');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->data, "nda");

    assert_true(trie->root->next->key == 'b');
    assert_null(trie->root->next->data);
    assert_true(trie->root->next->child->key == 'o');
    assert_null(trie->root->next->child->data);
    assert_true(trie->root->next->child->child->key == 'l');
    assert_null(trie->root->next->child->child->data);
    assert_true(trie->root->next->child->child->child->key == 'a');
    assert_null(trie->root->next->child->child->child->data);
    assert_true(trie->root->next->child->child->child->child->key == '\0');
    assert_string_equal(trie->root->next->child->child->child->child->data, "guda");

    assert_true(trie->root->next->child->child->next->key == 't');
    assert_null(trie->root->next->child->child->next->data);
    assert_true(trie->root->next->child->child->next->child->key == 'e');
    assert_null(trie->root->next->child->child->next->child->data);
    assert_true(trie->root->next->child->child->next->child->child->key == '\0');
    assert_string_equal(trie->root->next->child->child->next->child->child->data, "aba");

    assert_true(trie->root->next->child->child->next->next->key == '\0');
    assert_string_equal(trie->root->next->child->child->next->next->data, "haha");

    sb_trie_free(trie);
}


static void
test_trie_insert_duplicated(void **state)
{
    sb_trie_t *trie = sb_trie_new(free);

    sb_trie_insert(trie, "bola", sb_strdup("guda"));
    assert_true(trie->root->key == 'b');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'o');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'l');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == 'a');
    assert_null(trie->root->child->child->child->data);
    assert_true(trie->root->child->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->child->data, "guda");

    sb_trie_insert(trie, "bola", sb_strdup("asdf"));
    assert_true(trie->root->key == 'b');
    assert_null(trie->root->data);
    assert_true(trie->root->child->key == 'o');
    assert_null(trie->root->child->data);
    assert_true(trie->root->child->child->key == 'l');
    assert_null(trie->root->child->child->data);
    assert_true(trie->root->child->child->child->key == 'a');
    assert_null(trie->root->child->child->child->data);
    assert_true(trie->root->child->child->child->child->key == '\0');
    assert_string_equal(trie->root->child->child->child->child->data, "asdf");

    sb_trie_free(trie);
}


static void
test_trie_keep_data(void **state)
{
    sb_trie_t *trie = sb_trie_new(NULL);

    char *t1 = "guda";
    char *t2 = "nda";
    char *t3 = "aba";
    char *t4 = "haha";

    sb_trie_insert(trie, "bola", t1);
    sb_trie_insert(trie, "chu", t2);
    sb_trie_insert(trie, "bote", t3);
    sb_trie_insert(trie, "bo", t4);

    sb_trie_free(trie);

    assert_string_equal(t1, "guda");
    assert_string_equal(t2, "nda");
    assert_string_equal(t3, "aba");
    assert_string_equal(t4, "haha");
}


static void
test_trie_lookup(void **state)
{
    sb_trie_t *trie = sb_trie_new(free);

    sb_trie_insert(trie, "bola", sb_strdup("guda"));
    sb_trie_insert(trie, "chu", sb_strdup("nda"));
    sb_trie_insert(trie, "bote", sb_strdup("aba"));
    sb_trie_insert(trie, "bo", sb_strdup("haha"));

    assert_string_equal(sb_trie_lookup(trie, "bola"), "guda");
    assert_string_equal(sb_trie_lookup(trie, "chu"), "nda");
    assert_string_equal(sb_trie_lookup(trie, "bote"), "aba");
    assert_string_equal(sb_trie_lookup(trie, "bo"), "haha");

    assert_null(sb_trie_lookup(trie, "arcoiro"));

    sb_trie_free(trie);

    trie = sb_trie_new(free);

    sb_trie_insert(trie, "chu", sb_strdup("nda"));
    sb_trie_insert(trie, "bola", sb_strdup("guda"));
    sb_trie_insert(trie, "bote", sb_strdup("aba"));
    sb_trie_insert(trie, "bo", sb_strdup("haha"));
    sb_trie_insert(trie, "copa", sb_strdup("bu"));
    sb_trie_insert(trie, "b", sb_strdup("c"));
    sb_trie_insert(trie, "test", sb_strdup("asd"));

    assert_string_equal(sb_trie_lookup(trie, "bola"), "guda");
    assert_string_equal(sb_trie_lookup(trie, "chu"), "nda");
    assert_string_equal(sb_trie_lookup(trie, "bote"), "aba");
    assert_string_equal(sb_trie_lookup(trie, "bo"), "haha");

    assert_null(sb_trie_lookup(trie, "arcoiro"));

    sb_trie_free(trie);
}


static void
test_trie_size(void **state)
{
    sb_trie_t *trie = sb_trie_new(free);

    sb_trie_insert(trie, "bola", sb_strdup("guda"));
    sb_trie_insert(trie, "chu", sb_strdup("nda"));
    sb_trie_insert(trie, "bote", sb_strdup("aba"));
    sb_trie_insert(trie, "bo", sb_strdup("haha"));

    assert_int_equal(sb_trie_size(trie), 4);
    assert_int_equal(sb_trie_size(NULL), 0);

    sb_trie_free(trie);

    trie = sb_trie_new(free);

    sb_trie_insert(trie, "chu", sb_strdup("nda"));
    sb_trie_insert(trie, "bola", sb_strdup("guda"));
    sb_trie_insert(trie, "bote", sb_strdup("aba"));
    sb_trie_insert(trie, "bo", sb_strdup("haha"));
    sb_trie_insert(trie, "copa", sb_strdup("bu"));
    sb_trie_insert(trie, "b", sb_strdup("c"));
    sb_trie_insert(trie, "test", sb_strdup("asd"));

    assert_int_equal(sb_trie_size(trie), 7);
    assert_int_equal(sb_trie_size(NULL), 0);

    sb_trie_free(trie);
}


static unsigned int counter;
static char *expected_keys[] = {"chu", "copa", "bola", "bote", "bo", "b", "test"};
static char *expected_datas[] = {"nda", "bu", "guda", "aba", "haha", "c", "asd"};

static void
mock_foreach(const char *key, void *data)
{
    assert_string_equal(key, expected_keys[counter]);
    assert_string_equal((char*) data, expected_datas[counter++]);
}


static void
test_trie_foreach(void **state)
{
    sb_trie_t *trie = sb_trie_new(free);

    sb_trie_insert(trie, "chu", sb_strdup("nda"));
    sb_trie_insert(trie, "bola", sb_strdup("guda"));
    sb_trie_insert(trie, "bote", sb_strdup("aba"));
    sb_trie_insert(trie, "bo", sb_strdup("haha"));
    sb_trie_insert(trie, "copa", sb_strdup("bu"));
    sb_trie_insert(trie, "b", sb_strdup("c"));
    sb_trie_insert(trie, "test", sb_strdup("asd"));

    counter = 0;
    sb_trie_foreach(trie, mock_foreach);

    sb_trie_free(trie);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_trie_new),
        unit_test(test_trie_insert),
        unit_test(test_trie_insert_duplicated),
        unit_test(test_trie_keep_data),
        unit_test(test_trie_lookup),
        unit_test(test_trie_size),
        unit_test(test_trie_foreach),
    };
    return run_tests(tests);
}