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
#include <stdlib.h>
#include "sb-mem.h"

/**
 * @file squareball/sb-error.h
 * @brief Error reporting infrastructure.
 *
 * This implementation is heavily inspired by Golang's error reporting.
 * The main error object, that is used internally by squareball, and is
 * available for users, is just a string. See @ref squareball/sb-strerror.h.
 *
 * This header provides all the infrastructure needed to manipulate error
 * objects in a generic way, without caring about what is stored in the error
 * object, and to create custom error types.
 *
 * @example hello_custom_error_type.c
 *
 * @{
 */

/**
 * Function signature for the function that is used to convert a custom error
 * data to string.
 *
 * This should only be used when creating a custom error type.
 *
 * @param data  A pointer to custom data stored in the object.
 * @return      A newly-allocated string.
 */
typedef char* (*sb_error_to_string_func_t) (void *data);

/**
 * Data structure that represents an error type object.
 *
 * This should only be used when creating a custom error type.
 */
typedef struct {

    /**
     * Error type name.
     */
    const char *name;

    /**
     * Helper function to convert the custom error data to a string.
     */
    sb_error_to_string_func_t to_string_func;

    /**
     * Helper function to free the error data.
     */
    sb_free_func_t free_func;

} sb_error_type_t;

/**
 * Opaque data structure that represents an error object.
 */
typedef struct _sb_error_t sb_error_t;

/**
 * Function that creates a new error object from a custom error type and data.
 *
 * @param type  A pointer to a custom data type (@ref sb_error_type_t) object.
 * @param data  A pointer to data object.
 * @return      A newly-allocated error object.
 */
sb_error_t* sb_error_new_from_type(sb_error_type_t *type, void *data);

/**
 * Function that returns the name of the error type.
 *
 * @param err  An error object.
 * @return     A string.
 */
const char* sb_error_get_type_name(sb_error_t *err);

/**
 * Function that returns a pointer to data stored in an error object.
 *
 * @param err  An error object.
 * @return     A pointer to data object.
 */
const void* sb_error_get_data(sb_error_t *err);

/**
 * Function that returns a string representation of the data stored in an
 * error object.
 *
 * @param err  An error object.
 * @return     A string.
 */
const char* sb_error_to_string(sb_error_t *err);

/**
 * Function that frees memory allocated for an error object.
 *
 * @param err  An error object.
 */
void sb_error_free(sb_error_t *err);

/** @} */

#endif /* _SQUAREBALL_ERROR_H */
