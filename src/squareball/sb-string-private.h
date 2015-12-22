/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_STRING_PRIVATE_H
#define _SQUAREBALL_STRING_PRIVATE_H

#include <stddef.h>

struct _sb_string_t {
    char *str;
    size_t len;
    size_t allocated_len;
};

#endif /* _SQUAREBALL_STRING_PRIVATE_H */
