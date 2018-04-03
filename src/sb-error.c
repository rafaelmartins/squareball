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


sb_error_t*
sb_error_new_printf_parser(int code, const char *src, size_t src_len, size_t current,
    const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    char *msg = sb_strdup_vprintf(format, ap);
    va_end(ap);

    size_t lineno = 1;
    size_t linestart = 0;
    size_t lineend = 0;
    size_t pos = 1;

    for (size_t i = 0; i < src_len; i++) {
        char c = src[i];
        if (i < current) {
            if ((i + 1) < src_len) {
                if ((c == '\n' && src[i + 1] == '\r') ||
                    (c == '\r' && src[i + 1] == '\n'))
                {
                    lineno++;
                    i++;
                    pos = 1;
                    if ((i + 1) < src_len)
                        linestart = i + 1;
                    continue;
                }
            }
            if (c == '\n' || c == '\r') {
                lineno++;
                pos = 1;
                if ((i + 1) < src_len)
                    linestart = i + 1;
                continue;
            }
            pos++;
        }
        else if (c == '\n' || c == '\r') {
            lineend = i;
            break;
        }
    }

    if (lineend <= linestart && src_len >= linestart)
        lineend = src_len;

    char *line = sb_strndup(src + linestart, lineend - linestart);

    sb_error_t *rv = NULL;

    if (line[0] == '\0')  // "near" message isn't useful if line is empty
        rv = sb_error_new(code, msg);
    else
        rv = sb_error_new_printf(code,
            "%s\nError occurred near line %d, position %d: %s", msg, lineno,
            pos, line);

    free(msg);
    free(line);

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
