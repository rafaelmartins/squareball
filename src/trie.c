/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdlib.h>
#include "squareball.h"


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
    if (node == NULL)
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
    if (data == NULL || key == NULL)
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
    if (trie->root == NULL || key == NULL)
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
sb_trie_size_node(sb_trie_node_t *node, unsigned int *count)
{
    if (node == NULL)
        return;

    if (node->key == '\0')
        (*count)++;

    sb_trie_size_node(node->next, count);
    sb_trie_size_node(node->child, count);
}


unsigned int
sb_trie_size(sb_trie_t *trie)
{
    if (trie == NULL)
        return 0;

    unsigned int count = 0;
    sb_trie_size_node(trie->root, &count);
    return count;
}


static void
sb_trie_foreach_node(sb_trie_node_t *node, sb_string_t *str, void (*func)(const char *key, void *data))
{
    if (node == NULL)
        return;

    if (node->key == '\0') {
        func(str->str, node->data);
        sb_string_free(str, true);
    }

    if (node->child != NULL) {
        sb_string_t *child = sb_string_new();
        child = sb_string_append(child, str->str);
        child = sb_string_append_c(child, node->key);
        sb_trie_foreach_node(node->child, child, func);
    }

    if (node->next != NULL)
        sb_trie_foreach_node(node->next, str, func);

    if (node->child != NULL && node->next == NULL)
        sb_string_free(str, true);
}


void
sb_trie_foreach(sb_trie_t *trie, void (*func)(const char *key, void *data))
{
    if (trie->root == NULL)
        return;

    sb_string_t *str = sb_string_new();
    sb_trie_foreach_node(trie->root, str, func);
}