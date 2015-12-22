/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_SLIST_H
#define _SQUAREBALL_SLIST_H

#include "sb-mem.h"

typedef struct _sb_slist_t sb_slist_t;

sb_slist_t* sb_slist_append(sb_slist_t *l, void *data);
void sb_slist_free_full(sb_slist_t *l, sb_free_func_t free_func);
void sb_slist_free(sb_slist_t *l);
unsigned int sb_slist_length(sb_slist_t *l);

#endif /* _SQUAREBALL_SLIST_H */
