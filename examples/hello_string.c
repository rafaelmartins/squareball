/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <squareball.h>


int
main(int argc, char **argv)
{
    sb_string_t *str = sb_string_new();

    sb_string_append(str, "Quem ");
    sb_string_append_len(str, "roubou a minha qewwqerwfdsfdf", 15);
    sb_string_append_c(str, 'b');
    sb_string_append_c(str, 'o');
    sb_string_append_c(str, 'l');
    sb_string_append_c(str, 'a');
    sb_string_append_c(str, ' ');
    sb_string_append_printf(str, "%s?", "quadrada");

    char *s = sb_string_free(str, false);

    printf("%s\n", s);

    free(s);
    return 0;
}
