/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_SLIST_PRIVATE_H
#define _SQUAREBALL_SLIST_PRIVATE_H

struct _sb_slist_t {
    struct _sb_slist_t *next;
    void *data;
};

#endif /* _SQUAREBALL_SLIST_PRIVATE_H */
