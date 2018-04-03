/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdlib.h>
#include <squareball.h>


int
main(int argc, char **argv)
{
    char *quoted = sb_shell_quote("echo 'Hello, shell!'");
    char *command = sb_strdup_printf("echo Look at this: %s", quoted);
    int rv = system(command);
    free(quoted);
    free(command);
    return rv;
}
