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

#define SB_STRING_CHUNK_SIZE 128

#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <squareball/sb-mem.h>
#include <squareball/sb-strfuncs.h>
#include <squareball/sb-string.h>


sb_string_t*
sb_string_new(void)
{
    sb_string_t* rv = sb_malloc(sizeof(sb_string_t));
    rv->str = NULL;
    rv->len = 0;
    rv->allocated_len = 0;

    // initialize with empty string
    rv = sb_string_append(rv, "");

    return rv;
}


char*
sb_string_free(sb_string_t *str, bool free_str)
{
    if (str == NULL)
        return NULL;
    char *rv = NULL;
    if (free_str)
        free(str->str);
    else
        rv = str->str;
    free(str);
    return rv;
}


sb_string_t*
sb_string_dup(sb_string_t *str)
{
    if (str == NULL)
        return NULL;
    sb_string_t* new = sb_string_new();
    return sb_string_append_len(new, str->str, str->len);
}


sb_string_t*
sb_string_append_len(sb_string_t *str, const char *suffix, size_t len)
{
    if (str == NULL)
        return NULL;
    if (suffix == NULL)
        return str;
    size_t old_len = str->len;
    str->len += len;
    if (str->len + 1 > str->allocated_len) {
        str->allocated_len = (((str->len + 1) / SB_STRING_CHUNK_SIZE) + 1) * SB_STRING_CHUNK_SIZE;
        str->str = sb_realloc(str->str, str->allocated_len);
    }
    memcpy(str->str + old_len, suffix, len);
    str->str[str->len] = '\0';
    return str;
}


sb_string_t*
sb_string_append(sb_string_t *str, const char *suffix)
{
    if (str == NULL)
        return NULL;
    const char *my_suffix = suffix == NULL ? "" : suffix;
    return sb_string_append_len(str, my_suffix, strlen(my_suffix));
}


sb_string_t*
sb_string_append_c(sb_string_t *str, char c)
{
    if (str == NULL)
        return NULL;
    size_t old_len = str->len;
    str->len += 1;
    if (str->len + 1 > str->allocated_len) {
        str->allocated_len = (((str->len + 1) / SB_STRING_CHUNK_SIZE) + 1) * SB_STRING_CHUNK_SIZE;
        str->str = sb_realloc(str->str, str->allocated_len);
    }
    str->str[old_len] = c;
    str->str[str->len] = '\0';
    return str;
}


sb_string_t*
sb_string_append_printf(sb_string_t *str, const char *format, ...)
{
    if (str == NULL)
        return NULL;
    va_list ap;
    va_start(ap, format);
    char *tmp = sb_strdup_vprintf(format, ap);
    va_end(ap);
    str = sb_string_append(str, tmp);
    free(tmp);
    return str;
}


sb_string_t*
sb_string_append_escaped(sb_string_t *str, const char *suffix)
{
    if (str == NULL)
        return NULL;
    if (suffix == NULL)
        return str;
    bool escaped = false;
    for (size_t i = 0; suffix[i] != '\0'; i++) {
        if (suffix[i] == '\\' && !escaped) {
            escaped = true;
            continue;
        }
        escaped = false;
        str = sb_string_append_c(str, suffix[i]);
    }
    return str;
}
