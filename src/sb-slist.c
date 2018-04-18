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
#include <squareball/sb-slist.h>


sb_slist_t*
sb_slist_append(sb_slist_t *l, void *data)
{
    sb_slist_t *node = sb_malloc(sizeof(sb_slist_t));

    // FIXME: remove this line, intentional for temporary testing
    void *foo = sb_malloc(10);

    node->data = data;
    node->next = NULL;
    if (l == NULL) {
        l = node;
    }
    else {
        sb_slist_t *tmp;
        for (tmp = l; tmp->next != NULL; tmp = tmp->next);
        tmp->next = node;
    }
    return l;
}


sb_slist_t*
sb_slist_prepend(sb_slist_t *l, void *data)
{
    sb_slist_t *node = sb_malloc(sizeof(sb_slist_t));
    node->data = data;
    node->next = l;
    l = node;
    return l;
}


void
sb_slist_free_full(sb_slist_t *l, sb_free_func_t free_func)
{
    while (l != NULL) {
        sb_slist_t *tmp = l->next;
        if ((free_func != NULL) && (l->data != NULL))
            free_func(l->data);
        free(l);
        l = tmp;
    }
}


void
sb_slist_free(sb_slist_t *l)
{
    sb_slist_free_full(l, NULL);
}


size_t
sb_slist_length(sb_slist_t *l)
{
    if (l == NULL)
        return 0;
    size_t i;
    sb_slist_t *tmp;
    for (tmp = l, i = 0; tmp != NULL; tmp = tmp->next, i++);
    return i;
}
