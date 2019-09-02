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
#include <stdlib.h>
#include <squareball/sb-error.h>
#include <squareball/sb-error-private.h>
#include <squareball/sb-strfuncs.h>
#include <squareball/sb-strerror.h>


static sb_error_type_t str_error = {
    .name = "string",
    .to_string_func = NULL,
    .free_func = NULL,
};


sb_error_t*
sb_strerror_new(const char *msg)
{
    sb_error_t *rv = sb_error_new_from_type(&str_error, sb_strdup(msg));
    rv->msg = rv->data;
    return rv;
}


sb_error_t*
sb_strerror_new_printf(const char *format, ...)
{
    if (format == NULL)
        return sb_strerror_new(NULL);

    va_list ap;
    va_start(ap, format);
    char *tmp = sb_strdup_vprintf(format, ap);
    va_end(ap);
    sb_error_t *rv = sb_strerror_new(tmp);
    free(tmp);
    return rv;
}
