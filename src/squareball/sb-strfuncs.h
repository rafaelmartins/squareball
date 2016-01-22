/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_STRFUNCS_H
#define _SQUAREBALL_STRFUNCS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdarg.h>

/**
 * @file squareball/sb-strfuncs.h
 * @brief String related helper functions.
 *
 * @{
 */

char* sb_strdup(const char *s);
char* sb_strndup(const char *s, size_t n);
char* sb_strdup_vprintf(const char *format, va_list ap);
char* sb_strdup_printf(const char *format, ...);
bool sb_str_starts_with(const char *str, const char *prefix);
bool sb_str_ends_with(const char *str, const char *suffix);
char* sb_str_lstrip(char *str);
char* sb_str_rstrip(char *str);
char* sb_str_strip(char *str);
char** sb_str_split(const char *str, char c, unsigned int max_pieces);
char* sb_str_replace(const char *str, const char search, const char *replace);
void sb_strv_free(char **strv);
char* sb_strv_join(const char **strv, const char *separator);
unsigned int sb_strv_length(char **strv);

/** @} */

#endif /* _SQUAREBALL_STRFUNCS_H */
