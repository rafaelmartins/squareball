/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_STRERROR_H
#define _SQUAREBALL_STRERROR_H

#include <stdarg.h>
#include "sb-error.h"

/**
 * @file squareball/sb-strerror.h
 * @brief String error object.
 *
 * This is an implementation of @ref sb_error_t object, that only contains a
 * string representing the error. Most of the internal @c squareball errors
 * are reported using this error type.
 *
 * It is based on Golang's @c errorString type, as implemented in the @c errors
 * package: https://golang.org/pkg/errors/
 *
 * Users wanting to include custom/non-string data in the error objects should
 * implement a custom error type, as described in @ref squareball/sb-error.h
 * documentation.
 *
 * @{
 */

/**
 * Function that creates a new string error object.
 *
 * @param msg   Human-readable error message.
 * @return      An error object.
 */
sb_error_t* sb_strerror_new(const char *msg);

/**
 * Function that creates a new string error object, with printf(3)-like message
 * formatting.
 *
 * @param format  Format for human-readable error message.
 * @param ...     One or more printf(3)-like parameters.
 * @return        An error object.
 */
sb_error_t* sb_strerror_new_printf(const char *format, ...);

/** @} */

#endif /* _SQUAREBALL_STRERROR_H */
