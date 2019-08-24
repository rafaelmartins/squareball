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
    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    sb_error_t *err = NULL;

    sb_mkdir_recursive(argv[1], &err);

    if (err != NULL) {
        fprintf(stderr, "error: %s\n", sb_error_to_string(err));
        sb_error_free(err);
        return 1;
    }

    printf("directory: %s\n", argv[1]);

    return 0;
}
