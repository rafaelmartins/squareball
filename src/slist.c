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


sb_slist_t*
sb_slist_append(sb_slist_t *l, void *data)
{
    sb_slist_t *node = malloc(sizeof(sb_slist_t));
    if (node == NULL) {
        l = NULL;
        return l;
    }
    node->data = data;
    node->next = NULL;
    if (l == NULL)
        l = node;
    else {
        sb_slist_t *tmp;
        for (tmp = l; tmp->next != NULL; tmp = tmp->next);
        tmp->next = node;
    }
    return l;
}


void
sb_slist_free_full(sb_slist_t *l, sb_free_func_t free_func)
{
    while (l != NULL) {
        sb_slist_t *tmp = l->next;
        free_func(l->data);
        free(l);
        l = tmp;
    }
}


void
sb_slist_free(sb_slist_t *l)
{
    while (l != NULL) {
        sb_slist_t *tmp = l->next;
        free(l);
        l = tmp;
    }
}


unsigned int
sb_slist_length(sb_slist_t *l)
{
    unsigned int i;
    sb_slist_t *tmp;
    for (tmp = l, i = 0; tmp != NULL; tmp = tmp->next, i++);
    return i;
}
