/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2016 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_CONFIGPARSER_PRIVATE_H
#define _SQUAREBALL_CONFIGPARSER_PRIVATE_H

#include "sb-trie.h"

struct _sb_config_t {
    sb_trie_t *root;
};

#endif /* _SQUAREBALL_CONFIGPARSER_PRIVATE_H */
