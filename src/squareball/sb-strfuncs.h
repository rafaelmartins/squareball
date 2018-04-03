/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
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

/**
 * Replacement for glibc's strdup(3).
 *
 * @param s  The string to be duplicated.
 * @return   A newly-allocated string.
 */
char* sb_strdup(const char *s);

/**
 * Replacement for glibc's strndup(3).
 *
 * @param s  The string to be duplicated.
 * @param n  Maximum number of bytes to copy from \c s
 * @return   A newly-allocated string.
 */
char* sb_strndup(const char *s, size_t n);

/**
 * Function that creates a dynamically allocated string, with a vprintf(3)-like
 * interface.
 *
 * @param format  A printf(3) format.
 * @param ap      A va_list variable, as used in vprintf(3).
 * @return        A newly-allocated string.
 */
char* sb_strdup_vprintf(const char *format, va_list ap);

/**
 * Function that creates a dynamically allocated string, with a printf(3)-like
 * interface.
 *
 * @param format  A printf(3) format.
 * @param ...     One or more printf(3)-like parameters.
 * @return        A newly-allocated string.
 */
char* sb_strdup_printf(const char *format, ...);

/**
 * Function that checks if a string starts with a given prefix.
 *
 * @param str     The string.
 * @param prefix  The prefix that should be looked for in the string.
 * @return        A boolean that indicates if the string starts with the given
 *                prefix.
 */
bool sb_str_starts_with(const char *str, const char *prefix);

/**
 * Function that checks if a string ends with a given suffix.
 *
 * @param str     The string.
 * @param suffix  The suffix that should be looked for in the string.
 * @return        A boolean that indicates if the string ends with the given
 *                suffix.
 */
bool sb_str_ends_with(const char *str, const char *suffix);

/**
 * Function that strips whitespace from the beginning of a given string.
 *
 * @param str  The string.
 * @return     A pointer to the new start of the string. Please note that the
 *             string is changed in-place, and no new memory is allocated.
 */
char* sb_str_lstrip(char *str);

/**
 * Function that strips whitespace from the end of a given string.
 *
 * @param str  The string.
 * @return     A pointer to the start of the string. It is usually the same as
 *             \c str. Please note that the string is changed in-place, and
 *             no new memory is allocated.
 */
char* sb_str_rstrip(char *str);

/**
 * Function that strips whitespace from the beginnning and from the end of a
 * given string.
 *
 * @param str  The string.
 * @return     A pointer to the new start of the string. Please note that the
 *             string is changed in-place, and no new memory is allocated.
 */
char* sb_str_strip(char *str);

/**
 * Function that splits a string in all occurences of a given character,
 * excluding this character from the resulting elements.
 *
 * @param str         The string.
 * @param c           The character that should be looked for.
 * @param max_pieces  The max number of pieces that should be splitted. After
 *                    this, the character will be kept untouched. If \c 0,
 *                    split until the end of the string.
 * @return            An NULL-terminated array of strings, that should be
 *                    free'd with \ref sb_strv_free.
 */
char** sb_str_split(const char *str, char c, size_t max_pieces);

/**
 * Function that replaces all the occurences of a given character in a string
 * with another given string.
 *
 * @param str      The string.
 * @param search   The character that should be replaced.
 * @param replace  The string that should replace all the occurences of \c c.
 * @return         A newly-allocated string.
 */
char* sb_str_replace(const char *str, const char search, const char *replace);

/**
 * Function that returns a pointer to the first occurrence of character in a
 * string.
 *
 * This is somewhat similar to strchr, but respects '\' escaping.
 *
 * @param str  The string.
 * @param c    The character that should be searched in the string.
 * @return     The pointer to the first occurrence of \c c in \c str.
 */
char* sb_str_find(const char *str, char c);

/**
 * Function that frees the memory allocated for a NULL-terminated array of
 * strings.
 *
 * @param strv  The NULL-terminated array of strings.
 */
void sb_strv_free(char **strv);

/**
 * Function that joins a NULL-terminated array of strings in a single string,
 * using a given string as separator.
 *
 * @param strv       The NULL-terminated array of strings.
 * @param separator  The string to be used as separator.
 * @return           A newly-allocated string.
 */
char* sb_strv_join(char **strv, const char *separator);

/**
 * Function that returns the number of elements in a NULL-terminated array of
 * strings.
 *
 * @param strv  The NULL-terminated array of strings.
 * @return      The length of the given NULL-terminated array of strings.
 */
size_t sb_strv_length(char **strv);

/** @} */

#endif /* _SQUAREBALL_STRFUNCS_H */
