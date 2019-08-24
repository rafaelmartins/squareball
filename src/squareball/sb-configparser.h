/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_CONFIGPARSER_H
#define _SQUAREBALL_CONFIGPARSER_H

#include <stdlib.h>
#include "sb-error.h"
#include "sb-slist.h"
#include "sb-trie.h"

/**
 * @file squareball/sb-configparser.h
 * @brief Functions to parse INI-style configuration files.
 * @example hello_configparser.c
 * @{
 */

/**
 * Configuration opaque structure.
 */
typedef struct _sb_config_t sb_config_t;

/**
 * Function that parses INI-style configuration from a string.
 *
 * @param src            String with the content to be parsed.
 * @param src_len        String length.
 * @param list_sections  List of strings with sections that should be parsed
 *                       as lists.
 * @param err            Return location for a \ref sb_error_t, or NULL.
 * @return               An object with the parsed data, or \c NULL.
 */
sb_config_t* sb_config_parse(const char *src, size_t src_len,
    const char *list_sections[], sb_error_t **err);

/**
 * Function that returns an array with configuration sections.
 *
 * @param config  A \ref sb_config_t object.
 * @return        An array of strings, or \c NULL. Must be free'd with
 *                \ref sb_strv_free.
 */
char** sb_config_list_sections(sb_config_t *config);

/**
 * Function that returns an array with configuration keys found in a given
 * configuration section.
 *
 * @param config   A \ref sb_config_t object.
 * @param section  A configuration section.
 * @return         An array of strings, or \c NULL. Must be free'd with
 *                 \ref sb_strv_free.
 */
char** sb_config_list_keys(sb_config_t *config, const char *section);

/**
 * Function that returns the value of a given configuration key, for a given
 * configuration section.
 *
 * @param config   A \ref sb_config_t object.
 * @param section  A configuration section.
 * @param key      A configuration key.
 * @return         The value of the given configuration key, or \c NULL.
 */
const char* sb_config_get(sb_config_t *config, const char *section,
    const char *key);

/**
 * Function that returns the value of a given configuration key, for a given
 * configuration section, or returns a default value if the key and/or section
 * does not exists.
 *
 * @param config    A \ref sb_config_t object.
 * @param section   A configuration section.
 * @param key       A configuration key.
 * @param default_  A default value to be returned, if the ken and/or section
 *                  does not exists.
 * @return          The value of the given configuration key, or \c default_.
 */
const char* sb_config_get_with_default(sb_config_t *config, const char *section,
    const char *key, const char *default_);

/**
 * Function that returns an array of values parsed as a list from a given section.
 *
 * The section must be included in the \c list_sections when calling
 * \ref sb_config_parse.
 *
 * @param config   A \ref sb_config_t object.
 * @param section  A configuration section.
 * @return         An NULL-terminated array of strings, that should be free'd
 *                 with \ref sb_strv_free.
 */
char** sb_config_get_list(sb_config_t *config, const char *section);

/**
 * Function that frees the memory allocated for a configuration object.
 *
 * @param config  The configuration object.
 */
void sb_config_free(sb_config_t *config);

/** @} */

#endif /* _SQUAREBALL_CONFIGPARSER_H */
