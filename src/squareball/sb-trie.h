/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_TRIE_H
#define _SQUAREBALL_TRIE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include "sb-mem.h"

typedef struct _sb_trie_t sb_trie_t;

sb_trie_t* sb_trie_new(sb_free_func_t free_func);
void sb_trie_free(sb_trie_t *trie);
void sb_trie_insert(sb_trie_t *trie, const char *key, void *data);
void* sb_trie_lookup(sb_trie_t *trie, const char *key);
unsigned int sb_trie_size(sb_trie_t *trie);
void sb_trie_foreach(sb_trie_t *trie, void (*func)(const char *key, void *data));

#endif /* _SQUAREBALL_TRIE_H */
