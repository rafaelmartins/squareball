/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2016 Rafael G. Martins <rafael@rafaelmartins.eng.br>
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

/**
 * @file squareball/sb-trie.h
 * @brief Implementation of a trie data structure.
 *
 * This trie implementation is mostly designed to be used as a replacement for
 * a hash table, where the keys are always strings (arrays of \c char elements).
 * @example hello_trie.c
 * @{
 */

/**
 * Trie opaque structure.
 */
typedef struct _sb_trie_t sb_trie_t;

/**
 * Function that creates a new trie.
 *
 * @param free_func  The \ref sb_free_func_t to be used to free the memory
 *                   allocated for the elements automatically when needed. If
 *                   NULL, the trie won't touch the elements when free'ing
 *                   itself.
 * @return           A new trie.
 */
sb_trie_t* sb_trie_new(sb_free_func_t free_func);

/**
 * Function that frees the memory allocated for a trie, and for its elements
 * (using the free function provided when creating the trie).
 *
 * @param trie  The trie.
 */
void sb_trie_free(sb_trie_t *trie);

/**
 * Function that inserts an element on the trie. If the key already exists,
 * its current element is free'd (using the free function provided when
 * creating the trie) and replaced with new one.
 *
 * @param trie  The trie.
 * @param key   The key string.
 * @param data  The data to be stored for the key. Users should not free it
 *              explicitly if the tree was initialized with a valid free
 *              function.
 */
void sb_trie_insert(sb_trie_t *trie, const char *key, void *data);

/**
 * Function that searches the trie for a given key, and return its data.
 *
 * @param trie  The trie.
 * @param key   The key string to be looked for.
 * @return      The date stored for the given key, if found, otherwise NULL.
 */
void* sb_trie_lookup(sb_trie_t *trie, const char *key);

/**
 * Function that returns the size of a given trie.
 *
 * @param trie  The trie.
 * @return      The size of the given trie.
 */
unsigned int sb_trie_size(sb_trie_t *trie);

/**
 * Function that calls a given function for each element of a trie.
 *
 * @param trie  The trie.
 * @param func  The function that should be called for each element.
 */
void sb_trie_foreach(sb_trie_t *trie, void (*func)(const char *key, void *data));

/** @} */

#endif /* _SQUAREBALL_TRIE_H */
