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
#include <squareball/sb-mem.h>
#include <squareball/sb-strfuncs.h>
#include <squareball/sb-parsererror.h>


static char*
sb_parser_error_to_string(sb_parser_error_t *pe)
{
    if (pe == NULL)
        return NULL;

    // "near" message isn't useful if line is empty
    if (pe->linestr == NULL || pe->linestr[0] == '\0')
        return sb_strdup(pe->msg ? pe->msg : "(unset)");

    return sb_strdup_printf("%s\nError occurred near line %zu, position %zu: %s",
        pe->msg ? pe->msg : "(unset)", pe->lineno, pe->pos, pe->linestr);
}


static void
sb_parser_error_free(sb_parser_error_t *pe)
{
    if (pe == NULL)
        return;

    free(pe->msg);
    free(pe->linestr);
    free(pe);
}


static sb_error_type_t parser_error = {
    .name = "parser",
    .to_string_func = (sb_error_to_string_func_t) sb_parser_error_to_string,
    .free_func = (sb_free_func_t) sb_parser_error_free,
};


sb_error_t*
sb_parser_error_new(const char *src, size_t src_len, size_t pos, const char *msg)
{
    size_t lineno = 1;
    size_t linestart = 0;
    size_t lineend = 0;
    size_t _pos = 1;

    for (size_t i = 0; src != NULL && i < src_len; i++) {
        char c = src[i];
        if (i < pos) {
            if ((i + 1) < src_len) {
                if ((c == '\n' && src[i + 1] == '\r') ||
                    (c == '\r' && src[i + 1] == '\n'))
                {
                    lineno++;
                    i++;
                    _pos = 1;
                    if ((i + 1) < src_len)
                        linestart = i + 1;
                    continue;
                }
            }
            if (c == '\n' || c == '\r') {
                lineno++;
                _pos = 1;
                if ((i + 1) < src_len)
                    linestart = i + 1;
                continue;
            }
            _pos++;
        }
        else if (c == '\n' || c == '\r') {
            lineend = i;
            break;
        }
    }

    if (lineend <= linestart && src_len >= linestart)
        lineend = src_len;

    sb_parser_error_t *pe = sb_malloc(sizeof(sb_parser_error_t));
    pe->msg = sb_strdup(msg);
    pe->linestr = src == NULL ? NULL : sb_strndup(src + linestart, lineend - linestart);
    pe->lineno = src == NULL ? 0 : lineno;
    pe->pos = src == NULL ? 0 :_pos;

    return sb_error_new_from_type(&parser_error, pe);
}


sb_error_t*
sb_parser_error_new_printf(const char *src, size_t src_len, size_t pos,
    const char *format, ...)
{
    if (format == NULL)
        return sb_parser_error_new(src, src_len, pos, NULL);

    va_list ap;
    va_start(ap, format);
    char *tmp = sb_strdup_vprintf(format, ap);
    va_end(ap);
    sb_error_t *rv = sb_parser_error_new(src, src_len, pos, tmp);
    free(tmp);
    return rv;
}
