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

/**
 * @file squareball/sb-string.h
 * @brief String object that grows automatically, as required by the content
 *        added to it.
 *
 * @{
 */

/** Automatically growing string structure. */
typedef struct {
    char *str;
    size_t len;
    size_t allocated_len;
} sb_string_t;

sb_string_t* sb_string_new(void);
char* sb_string_free(sb_string_t *str, bool free_str);
sb_string_t* sb_string_dup(sb_string_t *str);
sb_string_t* sb_string_append_len(sb_string_t *str, const char *suffix, size_t len);
sb_string_t* sb_string_append(sb_string_t *str, const char *suffix);
sb_string_t* sb_string_append_c(sb_string_t *str, char c);
sb_string_t* sb_string_append_printf(sb_string_t *str, const char *format, ...);

/** @} */

#endif /* _SQUAREBALL_STRING_H */
