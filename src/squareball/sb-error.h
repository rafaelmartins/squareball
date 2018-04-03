/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_ERROR_H
#define _SQUAREBALL_ERROR_H

#include <stdarg.h>

/**
 * @file squareball/sb-error.h
 * @brief Error reporting infrastructure.
 *
 * This implementation is meant to be simple and easy to use, without global
 * variables, etc. If user needs something more advanced, like support to
 * repeated error codes, splitted error types for each type of error, etc.,
 * such solution should be implemented in the application itself.
 *
 * @{
 */

/**
 * Data structure that represents an error object.
 */
typedef struct {

    /**
     * Integer that stores the error code.
     *
     * Negative error codes are reserved for internal usage, and should not be
     * used by applications developed with this library. Also, 0 is not a good
     * value for an error code, as it may be confused with "no error".
     */
    int code;

    /**
     * Human-readable error message.
     */
    char *msg;

} sb_error_t;

/**
 * Internal error codes.
 *
 * This is an enum with all error codes used by squareball library itself.
 * They start from 262144 (0x1000000) to avoid conflicts with application
 * error codes.
 */
enum {
    SB_ERROR_FILE_OPEN = -1,
    SB_ERROR_FILE_READ = -2,
    SB_ERROR_FILE_WRITE = -3,
    SB_ERROR_DIR_CREATE = -4,

    SB_ERROR_CONFIGPARSER = -10,
};

/**
 * Function that creates a new error object.
 *
 * @param code  Error code.
 * @param msg   Human-readable error message.
 * @return      An error object.
 */
sb_error_t* sb_error_new(int code, const char *msg);

/**
 * Function that creates a new error object, with printf(3)-like message
 * formatting.
 *
 * @param code    Error code.
 * @param format  Format for human-readable error message.
 * @param ...     One or more printf(3)-like parameters.
 * @return        An error object.
 */
sb_error_t* sb_error_new_printf(int code, const char *format, ...);

/**
 * Function that frees memory allocated for an error object.
 *
 * @param err  An error object.
 */
void sb_error_free(sb_error_t *err);

/** @} */

#endif /* _SQUAREBALL_ERROR_H */
