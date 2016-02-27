/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2016 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <squareball.h>


static void
foreach_callback(const char *key, void *data)
{
    printf("    %s: %s\n", key, (char*) data);
}


int
main(int argc, char **argv)
{
    sb_trie_t *t = sb_trie_new(free);

    sb_trie_insert(t, "bola", sb_strdup("asd"));
    sb_trie_insert(t, "quadrada", sb_strdup("qwe"));
    sb_trie_insert(t, "quadrado", sb_strdup("zxc"));

    printf("Trie size: %u\n", sb_trie_size(t));
    printf("The value for key 'bola' is: %s\n\n",
        (char*) sb_trie_lookup(t, "bola"));

    printf("All available keys:\n");
    sb_trie_foreach(t, foreach_callback);

    sb_trie_free(t);
    return 0;
}
