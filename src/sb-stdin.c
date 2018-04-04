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

#include <stdbool.h>
#include <stdio.h>
#include <squareball/sb-string.h>
#include <squareball/sb-stdin.h>


// splitted in single file to make it easier to test
char*
sb_stdin_get_contents(void)
{
    int c;
    sb_string_t *rv = sb_string_new();
    while (EOF != (c = fgetc(stdin)))
        sb_string_append_c(rv, c);
    return sb_string_free(rv, false);
}
