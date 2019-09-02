/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_ERROR_PRIVATE_H
#define _SQUAREBALL_ERROR_PRIVATE_H

struct _sb_error_t {
    sb_error_type_t *type;
    void *data;
    char *msg;
};

#endif /* _SQUAREBALL_ERROR_PRIVATE_H */
