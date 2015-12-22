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

typedef void (*sb_free_func_t) (void *ptr);

void* sb_malloc(size_t size);
void* sb_realloc(void *ptr, size_t size);

#endif /* _SQUAREBALL_MEM_H */
