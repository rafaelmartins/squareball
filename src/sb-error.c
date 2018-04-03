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
#include <squareball/sb-error.h>
#include <squareball/sb-mem.h>
#include <squareball/sb-strfuncs.h>


sb_error_t*
sb_error_new(int code, const char *msg)
{
    sb_error_t *err = sb_malloc(sizeof(sb_error_t));
    err->code = code;
    err->msg = sb_strdup(msg);
    return err;
}


sb_error_t*
sb_error_new_printf(int code, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    char *tmp = sb_strdup_vprintf(format, ap);
    va_end(ap);
    sb_error_t *rv = sb_error_new(code, tmp);
    free(tmp);
    return rv;
}


void
sb_error_free(sb_error_t *err)
{
    if (err == NULL)
        return;
    free(err->msg);
    free(err);
}
