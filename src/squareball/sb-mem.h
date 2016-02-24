/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_MEM_H
#define _SQUAREBALL_MEM_H

#include <stddef.h>

/**
 * @file squareball/sb-mem.h
 * @brief Memory allocation related helpers.
 * @{
 */

/**
 * Function signature for helpers that are used to free memory of custom types.
 *
 * Each function should receive the pointer, and free the memory used by the
 * type as needed.
 *
 * The @ref sb_slist_free_full function is an example of usage of these helper
 * functions.
 */
typedef void (*sb_free_func_t) (void *ptr);

/**
 * Safe malloc replacement function. This function validates the output of
 * the libc's malloc call and aborts if needed. See malloc(3) for details.
 *
 * @param size  Number of bytes to be allocated.
 * @return      A pointer to the allocated memory.
 */
void* sb_malloc(size_t size);

/**
 * Safe realloc replacement function. This function validates the output of
 * the libc's realloc call and aborts if needed. See realloc(3) for details.
 * @param ptr   A pointer to be resized.
 * @param size  New number of bytes allocated after reallocation.
 * @return      A pointer to the reallocated memory.
 */
void* sb_realloc(void *ptr, size_t size);

/** @} */

#endif /* _SQUAREBALL_MEM_H */
