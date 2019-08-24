/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_PARSERERROR_H
#define _SQUAREBALL_PARSERERROR_H

#include <stdarg.h>
#include <stdlib.h>

/**
 * @file squareball/sb-parsererror.h
 * @brief Parser error object
 *
 * This is an implementation of @ref sb_error_t object, that is suitable to
 * report errors in parsers, including context of the point of the source
 * where the error happened.
 *
 * It is used by our configuration parser implementation, that is a good usage
 * example of this error object.
 *
 * @{
 */

/**
 * Data structure that represents a parser error data.
 */
typedef struct {

    /**
     * Error message.
     */
    char *msg;

    /**
     * String containing the line where the error happened.
     */
    char *linestr;

    /**
     * Number of the line where the error happened, starting from @c 1.
     */
    size_t lineno;

    /**
     * Position of the character where the error happened, relative to the
     * line and starting from @c 1.
     */
    size_t pos;

} sb_parser_error_t;

/**
 * Function that creates a new error object with message and parser current
 * position details.
 *
 * @param src      String with source that was being parsed.
 * @param src_len  Source string size.
 * @param pos      Current parser position, stating from \c 0.
 * @param msg      String with error message.
 * @return         An error object.
 */
sb_error_t* sb_parser_error_new(const char *src, size_t src_len, size_t pos,
    const char *msg);

/**
 * Function that creates a new error object, with printf(3)-like message
 * formatting and parser current position details.
 *
 * @param src      String with source that was being parsed.
 * @param src_len  Source string size.
 * @param pos      Current parser position, stating from \c 0.
 * @param format   Format for human-readable error message.
 * @param ...      One or more printf(3)-like parameters.
 * @return         An error object.
 */
sb_error_t* sb_parser_error_new_printf(const char *src, size_t src_len,
    size_t pos, const char *format, ...);

/** @} */

#endif /* _SQUAREBALL_PARSERERROR_H */
