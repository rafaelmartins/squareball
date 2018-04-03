/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdlib.h>
#include <squareball/sb-mem.h>
#include <squareball/sb-string.h>
#include <squareball/sb-trie.h>
#include <squareball/sb-trie-private.h>


sb_trie_t*
sb_trie_new(sb_free_func_t free_func)
{
    sb_trie_t *trie = sb_malloc(sizeof(sb_trie_t));
    trie->root = NULL;
    trie->free_func = free_func;
    return trie;
}


static void
sb_trie_free_node(sb_trie_t *trie, sb_trie_node_t *node)
{
    if (trie == NULL || node == NULL)
        return;
    if (node->data != NULL && trie->free_func != NULL)
        trie->free_func(node->data);
    sb_trie_free_node(trie, node->next);
    sb_trie_free_node(trie, node->child);
    free(node);
}


void
sb_trie_free(sb_trie_t *trie)
{
    if (trie == NULL)
        return;
    sb_trie_free_node(trie, trie->root);
    free(trie);
}


void
sb_trie_insert(sb_trie_t *trie, const char *key, void *data)
{
    if (trie == NULL || key == NULL || data == NULL)
        return;

    sb_trie_node_t *parent = NULL;
    sb_trie_node_t *previous;
    sb_trie_node_t *current;
    sb_trie_node_t *tmp;

    while (1) {

        if (trie->root == NULL || (parent != NULL && parent->child == NULL)) {
            current = sb_malloc(sizeof(sb_trie_node_t));
            current->key = *key;
            current->data = NULL;
            current->next = NULL;
            current->child = NULL;
            if (trie->root == NULL)
                trie->root = current;
            else
                parent->child = current;
            parent = current;
            goto clean;
        }

        tmp = parent == NULL ? trie->root : parent->child;
        previous = NULL;

        while (tmp != NULL && tmp->key != *key) {
            previous = tmp;
            tmp = tmp->next;
        }

        parent = tmp;

        if (previous == NULL || parent != NULL)
            goto clean;

        current = sb_malloc(sizeof(sb_trie_node_t));
        current->key = *key;
        current->data = NULL;
        current->next = NULL;
        current->child = NULL;
        previous->next = current;
        parent = current;

clean:
        if (*key == '\0') {
            if (parent->data != NULL && trie->free_func != NULL)
                trie->free_func(parent->data);
            parent->data = data;
            break;
        }
        key++;
    }
}


void*
sb_trie_lookup(sb_trie_t *trie, const char *key)
{
    if (trie == NULL || trie->root == NULL || key == NULL)
        return NULL;

    sb_trie_node_t *parent = trie->root;
    sb_trie_node_t *tmp;
    while (1) {
        for (tmp = parent; tmp != NULL; tmp = tmp->next) {

            if (tmp->key == *key) {
                if (tmp->key == '\0')
                    return tmp->data;
                parent = tmp->child;
                break;
            }
        }
        if (tmp == NULL)
            return NULL;

        if (*key == '\0')
            break;
        key++;
    }
    return NULL;
}


static void
sb_trie_size_node(sb_trie_node_t *node, size_t *count)
{
    if (node == NULL || count == NULL)
        return;

    if (node->key == '\0')
        (*count)++;

    sb_trie_size_node(node->next, count);
    sb_trie_size_node(node->child, count);
}


size_t
sb_trie_size(sb_trie_t *trie)
{
    if (trie == NULL)
        return 0;

    size_t count = 0;
    sb_trie_size_node(trie->root, &count);
    return count;
}


static void
sb_trie_foreach_node(sb_trie_node_t *node, sb_string_t *str,
    sb_trie_foreach_func_t func, void *user_data)
{
    if (node == NULL || str == NULL || func == NULL)
        return;

    if (node->key == '\0')
        func(str->str, node->data, user_data);

    if (node->child != NULL) {
        sb_string_t *child = sb_string_dup(str);
        child = sb_string_append_c(child, node->key);
        sb_trie_foreach_node(node->child, child, func, user_data);
        sb_string_free(child, true);
    }

    if (node->next != NULL)
        sb_trie_foreach_node(node->next, str, func, user_data);
}


void
sb_trie_foreach(sb_trie_t *trie, sb_trie_foreach_func_t func,
    void *user_data)
{
    if (trie == NULL || trie->root == NULL || func == NULL)
        return;

    sb_string_t *str = sb_string_new();
    sb_trie_foreach_node(trie->root, str, func, user_data);
    sb_string_free(str, true);
}
