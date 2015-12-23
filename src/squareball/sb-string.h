/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_STRING_H
#define _SQUAREBALL_STRING_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef SB_STRING_CHUNK_SIZE
#define SB_STRING_CHUNK_SIZE 128
#endif /* SB_STRING_CHUNK_SIZE */

typedef struct {
    char *str;
    size_t len;
    size_t allocated_len;
} sb_string_t;

char* sb_strdup(const char *s);
char* sb_strndup(const char *s, size_t n);
char* sb_strdup_vprintf(const char *format, va_list ap);
char* sb_strdup_printf(const char *format, ...);
bool sb_str_starts_with(const char *str, const char *prefix);
bool sb_str_ends_with(const char *str, const char *suffix);
char* sb_str_strip(char *str);
char** sb_str_split(const char *str, char c, unsigned int max_pieces);
char* sb_str_replace(const char *str, const char search, const char *replace);
void sb_strv_free(char **strv);
char* sb_strv_join(const char **strv, const char *separator);
unsigned int sb_strv_length(char **strv);

sb_string_t* sb_string_new(void);
char* sb_string_free(sb_string_t *str, bool free_str);
sb_string_t* sb_string_dup(sb_string_t *str);
sb_string_t* sb_string_append_len(sb_string_t *str, const char *suffix, size_t len);
sb_string_t* sb_string_append(sb_string_t *str, const char *suffix);
sb_string_t* sb_string_append_c(sb_string_t *str, char c);
sb_string_t* sb_string_append_printf(sb_string_t *str, const char *format, ...);

#endif /* _SQUAREBALL_STRING_H */
