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

#ifdef HAVE_STRINGS_H
#include <string.h>
#endif /* HAVE_STRINGS_H */

#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <squareball/sb-mem.h>
#include <squareball/sb-strfuncs.h>
#include <squareball/sb-string.h>

#if defined(WIN32) || defined(_WIN32)
#define strcasecmp _stricmp
#endif


char*
sb_strdup(const char *s)
{
    if (s == NULL)
        return NULL;
    size_t l = strlen(s);
    char *tmp = malloc(l + 1);
    if (tmp == NULL)
        return NULL;
    memcpy(tmp, s, l + 1);
    return tmp;
}


char*
sb_strndup(const char *s, size_t n)
{
    if (s == NULL)
        return NULL;
    size_t l = strnlen(s, n);
    char *tmp = malloc(l + 1);
    if (tmp == NULL)
        return NULL;
    memcpy(tmp, s, l);
    tmp[l] = '\0';
    return tmp;
}


char*
sb_strdup_vprintf(const char *format, va_list ap)
{
    if (format == NULL)
        return NULL;

    va_list ap2;
    va_copy(ap2, ap);
    int l = vsnprintf(NULL, 0, format, ap2);
    va_end(ap2);
    if (l < 0)
        return NULL;
    char *tmp = malloc(l + 1);
    if (!tmp)
        return NULL;
    int l2 = vsnprintf(tmp, l + 1, format, ap);
    if (l2 < 0) {
        free(tmp);
        return NULL;
    }
    return tmp;
}


char*
sb_strdup_printf(const char *format, ...)
{
    if (format == NULL)
        return NULL;

    va_list ap;
    va_start(ap, format);
    char *tmp = sb_strdup_vprintf(format, ap);
    va_end(ap);
    return tmp;
}


bool
sb_str_starts_with(const char *str, const char *prefix)
{
    int str_l = strlen(str);
    int str_lp = strlen(prefix);
    if (str_lp > str_l)
        return false;
    return strncmp(str, prefix, str_lp) == 0;
}


bool
sb_str_ends_with(const char *str, const char *suffix)
{
    int str_l = strlen(str);
    int str_ls = strlen(suffix);
    if (str_ls > str_l)
        return false;
    return strcmp(str + str_l - str_ls, suffix) == 0;
}


char*
sb_str_lstrip(char *str)
{
    if (str == NULL)
        return NULL;
    int i;
    size_t str_len = strlen(str);
    for (i = 0; i < str_len; i++) {
        if ((str[i] != ' ') && (str[i] != '\t') && (str[i] != '\n') &&
            (str[i] != '\r') && (str[i] != '\t') && (str[i] != '\f') &&
            (str[i] != '\v'))
        {
            str += i;
            break;
        }
        if (i == str_len - 1) {
            str += str_len;
            break;
        }
    }
    return str;
}


char*
sb_str_rstrip(char *str)
{
    if (str == NULL)
        return NULL;
    int i;
    size_t str_len = strlen(str);
    for (i = str_len - 1; i >= 0; i--) {
        if ((str[i] != ' ') && (str[i] != '\t') && (str[i] != '\n') &&
            (str[i] != '\r') && (str[i] != '\t') && (str[i] != '\f') &&
            (str[i] != '\v'))
        {
            str[i + 1] = '\0';
            break;
        }
        if (i == 0) {
            str[0] = '\0';
            break;
        }
    }
    return str;
}


char*
sb_str_strip(char *str)
{
    return sb_str_lstrip(sb_str_rstrip(str));
}


char**
sb_str_split(const char *str, char c, size_t max_pieces)
{
    if (str == NULL)
        return NULL;
    char **rv = sb_malloc(sizeof(char*));
    size_t i, start = 0, count = 0;
    for (i = 0; i < strlen(str) + 1; i++) {
        if (str[0] == '\0')
            break;
        if ((str[i] == c && (!max_pieces || count + 1 < max_pieces)) || str[i] == '\0') {
            rv = sb_realloc(rv, (count + 1) * sizeof(char*));
            rv[count] = sb_malloc(i - start + 1);
            memcpy(rv[count], str + start, i - start);
            rv[count++][i - start] = '\0';
            start = i + 1;
        }
    }
    rv = sb_realloc(rv, (count + 1) * sizeof(char*));
    rv[count] = NULL;
    return rv;
}


char*
sb_str_replace(const char *str, const char search, const char *replace)
{
    char **pieces = sb_str_split(str, search, 0);
    if (pieces == NULL)
        return NULL;
    char* rv = sb_strv_join(pieces, replace);
    sb_strv_free(pieces);
    if (rv == NULL)
        return sb_strdup(str);
    return rv;
}


char*
sb_str_find(const char *str, char c)
{
    // this is somewhat similar to strchr, but respects '\' escaping.
    if (str == NULL)
        return NULL;
    if (c == '\0')
        return (char*) str + strlen(str);
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\\') {
            i++;
            continue;
        }
        if (str[i] == c) {
            return (char*) str + i;
        }
    }
    return NULL;
}


bool
sb_str_to_bool(const char *str)
{
    if (str == NULL)
        return false;

    if (0 == strcmp(str, "1"))
        return true;

    if (0 == strcasecmp(str, "y"))
        return true;

    if (0 == strcasecmp(str, "yes"))
        return true;

    if (0 == strcasecmp(str, "true"))
        return true;

    if (0 == strcasecmp(str, "on"))
        return true;

    return false;
}


void
sb_strv_free(char **strv)
{
    if (strv == NULL)
        return;
    for (size_t i = 0; strv[i] != NULL; i++)
        free(strv[i]);
    free(strv);
}


char*
sb_strv_join(char **strv, const char *separator)
{
    if (strv == NULL || separator == NULL)
        return NULL;
    sb_string_t *str = sb_string_new();
    for (size_t i = 0; strv[i] != NULL; i++) {
        str = sb_string_append(str, strv[i]);
        if (strv[i + 1] != NULL)
            str = sb_string_append(str, separator);
    }
    return sb_string_free(str, false);
}


size_t
sb_strv_length(char **strv)
{
    if (strv == NULL)
        return 0;
    size_t i;
    for (i = 0; strv[i] != NULL; i++);
    return i;
}
