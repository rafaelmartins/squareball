/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_UTF8_H
#define _SQUAREBALL_UTF8_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "sb-string.h"

/**
 * @file squareball/sb-utf8.h
 * @brief UTF-8 utilities.
 * @{
 */

/**
 * Function that checks if a string is UTF-8 encoded.
 *
 * @param str  The string.
 * @param len  Length of \c str.
 * @return     A boolean \c true if the string is UTF-8 encoded.
 */
bool sb_utf8_validate(const uint8_t *str, size_t len);

/**
 * Function that checks if a string object's content is UTF-8 encoded.
 *
 * @param str  The string object.
 * @return     A boolean \c true if the string is UTF-8 encoded.
 */
bool sb_utf8_validate_str(sb_string_t *str);

/**
 * Function that returns the length of the UTF-8 BOM, if found in the string.
 *
 * @param str  The string.
 * @param len  Length of \c str.
 * @return     The length of the UTF-8 BOM, or \c 0.
 */
size_t sb_utf8_bom_length(const uint8_t *str, size_t len);

#endif /* _SQUAREBALL_UTF8_H */
