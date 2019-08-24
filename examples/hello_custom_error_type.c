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

typedef struct {
    int a;
    char *b;
} my_error_data_t;


static char*
my_error_to_string(void *data)
{
    if (data == NULL)
        return sb_strdup("");

    my_error_data_t *d = data;
    return sb_strdup_printf("my error: %s (%d)", d->b, d->a);
}


static void
my_error_free(void *data)
{
    if (data == NULL)
        return;

    my_error_data_t *d = data;
    free(d->b);
    free(d);
}


static sb_error_type_t my_error = {
    .name = "my_error",
    .to_string_func = my_error_to_string,
    .free_func = my_error_free,
};


sb_error_t*
my_error_new(int a, const char *b)
{
    my_error_data_t *d = sb_malloc(sizeof(my_error_data_t));
    d->a = a;
    d->b = sb_strdup(b);
    return sb_error_new_from_type(&my_error, d);
}


int
main(int argc, char **argv)
{
    sb_error_t *err = my_error_new(123, "bola");
    fprintf(stderr, "%s\n", sb_error_to_string(err));
    sb_error_free(err);
    return 0;
}
