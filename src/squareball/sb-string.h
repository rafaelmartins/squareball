/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_STRING_H
#define _SQUAREBALL_STRING_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @file squareball/sb-string.h
 * @brief String object that grows automatically, as required by the content
 *        added to it.
 * @example hello_string.c
 * @{
 */

/**
 * Automatically growing string structure.
 */
typedef struct {

    /**
     * The raw string. Always nul-terminated. Should not be written manually
     * by user
     */
    char *str;

    /**
     * The length of \ref str. Should not be written manually by user.
     */
    size_t len;

    /**
     * The size of the memory actually allocated for \ref str. Should not be
     * touched by user, despite being part of public interface.
     */
    size_t allocated_len;

} sb_string_t;

/**
 * Function that creates an empty string object.
 *
 * @return  New string object.
 */
sb_string_t* sb_string_new(void);

/**
 * Function that frees memory allocated for a string object. If \c free_str
 * is \c false, it will only free the memory allocated for the object, and
 * return the string stored on it.
 *
 * @param str       The string object.
 * @param free_str  Boolean that indicates if the memory allocated to internal
 *                  string should be free'd.
 * @return          Internal string, passing ownership of it to the caller of
 *                  the function, if \c free_str is \c false, or NULL.
 */
char* sb_string_free(sb_string_t *str, bool free_str);

/**
 * Function that duplicates a string object.
 *
 * @param str  The string object.
 * @return     A newly-allocated copy of \c str.
 */
sb_string_t* sb_string_dup(sb_string_t *str);

/**
 * Function that appends \c len bytes from \c suffix to the string object.
 *
 * @param str     The string object.
 * @param suffix  The suffix to append to the string object.
 * @param len     The number of bytes from \c suffix to append to the string
 *                object.
 * @return        The modified string object.
 */
sb_string_t* sb_string_append_len(sb_string_t *str, const char *suffix, size_t len);

/**
 * Function that appends a nul-terminated \c suffix to the string object.
 *
 * @param str     The string object.
 * @param suffix  The nul-terminated suffix to append to the string object.
 * @return        The modified string object.
 */
sb_string_t* sb_string_append(sb_string_t *str, const char *suffix);

/**
 * Function that appends a character to the string object.
 *
 * @param str  The string object.
 * @param c    The character to append to the string object.
 * @return     The modified string object.
 */
sb_string_t* sb_string_append_c(sb_string_t *str, char c);

/**
 * Function that appends to an string object with a printf(3)-like interface.
 *
 * @param str     The string object.
 * @param format  A printf(3) format.
 * @param ...     One or more printf(3)-like parameters.
 * @return        The modified string object.
 */
sb_string_t* sb_string_append_printf(sb_string_t *str, const char *format, ...);

/** @} */

#endif /* _SQUAREBALL_STRING_H */
