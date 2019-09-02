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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <squareball/sb-error.h>
#include <squareball/sb-error-private.h>
#include <squareball/sb-mem.h>
#include <squareball/sb-strfuncs.h>


sb_error_t*
sb_error_new_from_type(sb_error_type_t *type, void *data)
{
    sb_error_t *err = sb_malloc(sizeof(sb_error_t));
    err->type = type;
    err->data = data;
    err->msg = NULL;
    return err;
}


const char*
sb_error_get_type_name(sb_error_t *err)
{
    if (err == NULL || err->type == NULL)
        return NULL;

    return err->type->name;
}


const void*
sb_error_get_data(sb_error_t *err)
{
    if (err == NULL)
        return NULL;

    return err->data;
}


const char*
sb_error_to_string(sb_error_t *err)
{
    if (err == NULL)
        return NULL;

    if (err->msg != NULL)
        return err->msg;

    if (err->type == NULL || err->type->to_string_func == NULL)
        return NULL;

    err->msg = err->type->to_string_func(err->data);
    return err->msg;
}


void
sb_error_free(sb_error_t *err)
{
    if (err == NULL)
        return;

    if (err->type != NULL && err->type->free_func != NULL)
        err->type->free_func(err->data);

    free(err->msg);
    free(err);
}
