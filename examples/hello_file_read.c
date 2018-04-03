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

    size_t len;
    sb_error_t *err = NULL;

    char *contents = sb_file_get_contents(argv[1], &len, &err);

    if (err != NULL) {
        fprintf(stderr, "error: %s\n", err->msg);
        sb_error_free(err);
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Size: %zu\n", len);
    printf("--------------------------------------------------------------\n");
    printf("%*s", (int) len, contents);

    free(contents);

    return 0;
}
