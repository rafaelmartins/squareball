/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <squareball/sb-configparser.h>
#include <squareball/sb-configparser-private.h>
#include <squareball/sb-error.h>
#include <squareball/sb-parsererror.h>
#include <squareball/sb-strfuncs.h>
#include <squareball/sb-string.h>
#include <squareball/sb-trie.h>


typedef enum {
    CONFIG_START = 1,
    CONFIG_SECTION_START,
    CONFIG_SECTION,
    CONFIG_SECTION_KEY,
    CONFIG_SECTION_VALUE_START,
    CONFIG_SECTION_VALUE_QUOTE,
    CONFIG_SECTION_VALUE_POST_QUOTED,
    CONFIG_SECTION_VALUE,
    CONFIG_SECTION_LIST_START,
    CONFIG_SECTION_LIST_QUOTE,
    CONFIG_SECTION_LIST_POST_QUOTED,
    CONFIG_SECTION_LIST,
} sb_configparser_state_t;

typedef enum {
    CONFIG_SECTION_TYPE_MAP = 1,
    CONFIG_SECTION_TYPE_LIST,
} sb_configparser_section_type_t;

typedef struct {
    sb_configparser_section_type_t type;
    void *data;
} sb_configparser_section_t;


static void
free_section(sb_configparser_section_t *section)
{
    if (section == NULL)
        return;

    switch (section->type) {
        case CONFIG_SECTION_TYPE_MAP:
            sb_trie_free(section->data);
            break;
        case CONFIG_SECTION_TYPE_LIST:
            sb_slist_free_full(section->data, free);
            break;
    }
    free(section);
}


sb_config_t*
sb_config_parse(const char *src, size_t src_len, const char *list_sections[],
    sb_error_t **err)
{
    if (err != NULL && *err != NULL)
        return NULL;

    size_t current = 0;
    size_t start = 0;

    sb_configparser_section_t *section = NULL;

    char *section_name = NULL;
    char *key = NULL;
    sb_string_t *value = NULL;
    bool escaped = false;

    sb_config_t *rv = sb_malloc(sizeof(sb_config_t));
    rv->root = sb_trie_new((sb_free_func_t) free_section);

    sb_configparser_state_t state = CONFIG_START;

    while (current < src_len) {
        char c = src[current];
        bool is_last = current == src_len - 1;

        if (escaped) {
            sb_string_append_c(value, c);
            escaped = false;
            current++;
            continue;
        }

        if (value != NULL && c == '\\') {
            escaped = true;
            current++;
            continue;
        }

        switch (state) {

            case CONFIG_START:
                if (c == '#' || c == ';') {
                    while (current < src_len) {
                        if (src[current] == '\r' || src[current] == '\n')
                            break;
                        current++;
                    }
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
                    break;
                if (c == '[') {
                    state = CONFIG_SECTION_START;
                    break;
                }
                if (section != NULL) {
                    start = current;
                    switch (section->type) {
                        case CONFIG_SECTION_TYPE_MAP:
                            state = CONFIG_SECTION_KEY;
                            break;
                        case CONFIG_SECTION_TYPE_LIST:
                            state = CONFIG_SECTION_LIST_START;
                            if (value == NULL)
                                value = sb_string_new();
                            break;
                    }
                    continue;
                }
                if (err != NULL)
                    *err = sb_parser_error_new(src, src_len, current,
                        "configparser: File must start with section.");
                break;

            case CONFIG_SECTION_START:
                start = current;
                state = CONFIG_SECTION;
                break;

            case CONFIG_SECTION:
                if (c == ']') {
                    section_name = sb_strndup(src + start, current - start);
                    section = sb_malloc(sizeof(sb_configparser_section_t));
                    section->type = CONFIG_SECTION_TYPE_MAP;
                    if (list_sections != NULL) {
                        for (size_t i = 0; list_sections[i] != NULL; i++) {
                            if (0 == strcmp(section_name, list_sections[i])) {
                                section->type = CONFIG_SECTION_TYPE_LIST;
                                break;
                            }
                        }
                    }
                    switch (section->type) {
                        case CONFIG_SECTION_TYPE_MAP:
                            section->data = sb_trie_new(free);
                            break;
                        case CONFIG_SECTION_TYPE_LIST:
                            section->data = NULL;
                            break;
                    }
                    sb_trie_insert(rv->root, section_name, section);
                    free(section_name);
                    section_name = NULL;
                    state = CONFIG_START;
                    break;
                }
                if (c != '\r' && c != '\n')
                    break;
                if (err != NULL)
                    *err = sb_parser_error_new(src, src_len, current,
                        "configparser: Section names can't have new lines.");
                break;

            case CONFIG_SECTION_KEY:
                if (c == '=') {
                    key = sb_strndup(src + start, current - start);
                    state = CONFIG_SECTION_VALUE_START;
                    if (is_last) {
                        sb_trie_insert(section->data, sb_str_strip(key),
                            sb_strdup(""));
                        free(key);
                        key = NULL;
                        break;
                    }
                    if (value == NULL)
                        value = sb_string_new();
                    break;
                }
                if (c != '\r' && c != '\n' && !is_last)
                    break;
                // key without value, should we support it?
                if (err != NULL) {
                    size_t end = is_last && c != '\n' && c != '\r' ? src_len :
                        current;
                    key = sb_strndup(src + start, end - start);
                    *err = sb_parser_error_new_printf(src, src_len, current,
                        "configparser: Key without value: %s.", key);
                    free(key);
                    key = NULL;
                }
                break;

            case CONFIG_SECTION_VALUE_START:
                if (c == ' ' || c == '\t' || c == '\f' || c == '\v')
                    break;
                if (c == '"') {
                    state = CONFIG_SECTION_VALUE_QUOTE;
                    break;
                }
                if (c == '\r' || c == '\n' || is_last) {
                    state = CONFIG_SECTION_VALUE;
                    continue;
                }
                sb_string_append_c(value, c);
                state = CONFIG_SECTION_VALUE;
                break;

            case CONFIG_SECTION_VALUE_QUOTE:
                if (c == '"') {
                    sb_trie_insert(section->data, sb_str_strip(key),
                        sb_string_free(value, false));
                    free(key);
                    key = NULL;
                    value = NULL;
                    state = CONFIG_SECTION_VALUE_POST_QUOTED;
                    break;
                }
                sb_string_append_c(value, c);
                break;

            case CONFIG_SECTION_VALUE_POST_QUOTED:
                if (c == ' ' || c == '\t' || c == '\f' || c == '\v')
                    break;
                if (c == '\r' || c == '\n' || is_last) {
                    state = CONFIG_START;
                    break;
                }
                *err = sb_parser_error_new(src, src_len, current,
                    "configparser: Invalid value for key, should not have anything "
                    "after quotes.");
                break;

            case CONFIG_SECTION_VALUE:
                if (c == '\r' || c == '\n' || is_last) {
                    if (is_last && c != '\r' && c != '\n')
                        sb_string_append_c(value, c);
                    sb_trie_insert(section->data, sb_str_strip(key),
                        sb_strdup(sb_str_rstrip(value->str)));
                    free(key);
                    key = NULL;
                    sb_string_free(value, true);
                    value = NULL;
                    state = CONFIG_START;
                    break;
                }
                sb_string_append_c(value, c);
                break;

            case CONFIG_SECTION_LIST_START:
                if (c == ' ' || c == '\t' || c == '\f' || c == '\v')
                    break;
                if (c == '"') {
                    state = CONFIG_SECTION_LIST_QUOTE;
                    break;
                }
                sb_string_append_c(value, c);
                state = CONFIG_SECTION_LIST;
                break;

            case CONFIG_SECTION_LIST_QUOTE:
                if (c == '"') {
                    section->data = sb_slist_append(section->data,
                        sb_string_free(value, false));
                    value = NULL;
                    state = CONFIG_SECTION_LIST_POST_QUOTED;
                    break;

                }
                sb_string_append_c(value, c);
                break;

            case CONFIG_SECTION_LIST_POST_QUOTED:
                if (c == ' ' || c == '\t' || c == '\f' || c == '\v')
                    break;
                if (c == '\r' || c == '\n' || is_last) {
                    state = CONFIG_START;
                    break;
                }
                *err = sb_parser_error_new(src, src_len, current,
                    "configparser: Invalid value for list item, should not have "
                    "anything after quotes.");
                break;

            case CONFIG_SECTION_LIST:
                if (c == '\r' || c == '\n' || is_last) {
                    if (is_last && c != '\r' && c != '\n')
                        sb_string_append_c(value, c);
                    section->data = sb_slist_append(section->data,
                        sb_strdup(sb_str_strip(value->str)));
                    sb_string_free(value, true);
                    value = NULL;
                    state = CONFIG_START;
                    break;

                }
                sb_string_append_c(value, c);
                break;

        }

        if (err != NULL && *err != NULL) {
            sb_config_free(rv);
            rv = NULL;
            break;
        }

        current++;
    }

    free(section_name);
    free(key);
    sb_string_free(value, true);

    return rv;
}


static void
list_keys(const char *key, const char *value, sb_slist_t **l)
{
    *l = sb_slist_append(*l, sb_strdup(key));
}


char**
sb_config_list_sections(sb_config_t *config)
{
    if (config == NULL)
        return NULL;

    sb_slist_t *l = NULL;
    sb_trie_foreach(config->root, (sb_trie_foreach_func_t) list_keys, &l);

    char **rv = sb_malloc(sizeof(char*) * (sb_slist_length(l) + 1));

    size_t i = 0;
    for (sb_slist_t *tmp = l; tmp != NULL; tmp = tmp->next, i++)
        rv[i] = tmp->data;
    rv[i] = NULL;

    sb_slist_free(l);

    return rv;
}


char**
sb_config_list_keys(sb_config_t *config, const char *section)
{
    if (config == NULL)
        return NULL;

    sb_configparser_section_t *s = sb_trie_lookup(config->root, section);
    if (s == NULL)
        return NULL;

    if (s->type != CONFIG_SECTION_TYPE_MAP)
        return NULL;

    sb_slist_t *l = NULL;
    sb_trie_foreach(s->data, (sb_trie_foreach_func_t) list_keys, &l);

    char **rv = sb_malloc(sizeof(char*) * (sb_slist_length(l) + 1));

    size_t i = 0;
    for (sb_slist_t *tmp = l; tmp != NULL; tmp = tmp->next, i++)
        rv[i] = tmp->data;
    rv[i] = NULL;

    sb_slist_free(l);

    return rv;
}


const char*
sb_config_get(sb_config_t *config, const char *section, const char *key)
{
    if (config == NULL)
        return NULL;

    sb_configparser_section_t *s = sb_trie_lookup(config->root, section);
    if (s == NULL)
        return NULL;

    if (s->type != CONFIG_SECTION_TYPE_MAP)
        return NULL;

    return sb_trie_lookup(s->data, key);
}


const char*
sb_config_get_with_default(sb_config_t *config, const char *section,
    const char *key, const char *default_)
{
    const char *rv = sb_config_get(config, section, key);
    if (rv == NULL)
        return default_;
    return rv;
}


char**
sb_config_get_list(sb_config_t *config, const char *section)
{
    if (config == NULL)
        return NULL;

    sb_configparser_section_t *s = sb_trie_lookup(config->root, section);
    if (s == NULL)
        return NULL;

    if (s->type != CONFIG_SECTION_TYPE_LIST)
        return NULL;

    char **rv = sb_malloc(sizeof(char*) * (sb_slist_length(s->data) + 1));

    size_t i = 0;
    for (sb_slist_t *tmp = s->data; tmp != NULL; tmp = tmp->next, i++)
        rv[i] = sb_strdup(tmp->data);
    rv[i] = NULL;

    return rv;
}


void
sb_config_free(sb_config_t *config)
{
    if (config == NULL)
        return;
    sb_trie_free(config->root);
    free(config);
}
