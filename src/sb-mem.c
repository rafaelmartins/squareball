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
#include <stdio.h>
#include <squareball/sb-mem.h>


void*
sb_malloc(size_t size)
{
    // simple things simple!
    void *rv = malloc(size);
    if (rv == NULL) {
        fprintf(stderr, "fatal: Failed to allocate memory!\n");
        exit(1);
    }
    return rv;
}


void*
sb_realloc(void *ptr, size_t size)
{
    // simple things even simpler :P
    void *rv = realloc(ptr, size);
    if (rv == NULL && size != 0) {
        fprintf(stderr, "fatal: Failed to reallocate memory!\n");
        free(ptr);
        exit(1);
    }
    return rv;
}
