/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_TRIE_PRIVATE_H
#define _SQUAREBALL_TRIE_PRIVATE_H

#include "sb-mem.h"
#include "sb-trie.h"

typedef struct _sb_trie_node_t {
    char key;
    void *data;
    struct _sb_trie_node_t *next, *child;
} sb_trie_node_t;

struct _sb_trie_t {
    sb_trie_node_t *root;
    sb_free_func_t free_func;
};

#endif /* _SQUAREBALL_TRIE_PRIVATE_H */
