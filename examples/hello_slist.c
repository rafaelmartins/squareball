/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <squareball.h>


int
main(int argc, char **argv)
{
    sb_slist_t *l = NULL;

    l = sb_slist_append(l, sb_strdup("A list item"));
    l = sb_slist_append(l, sb_strdup("Another list item"));
    l = sb_slist_prepend(l, sb_strdup("Yet another list item"));

    printf("Number of list items: %zu\n\n", sb_slist_length(l));

    for (sb_slist_t *tmp = l; tmp != NULL; tmp = tmp->next)
        printf("    - %s\n", (char*) (tmp->data));

    sb_slist_free_full(l, free);
    return 0;
}
