/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2016 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <squareball/sb-configparser.h>
#include <squareball/sb-configparser-private.h>
#include <squareball/sb-error.h>
#include <squareball/sb-strfuncs.h>
#include <squareball/sb-trie.h>


typedef enum {
    CONFIG_START = 1,
    CONFIG_SECTION_START,
    CONFIG_SECTION,
    CONFIG_SECTION_KEY,
    CONFIG_SECTION_VALUE_START,
    CONFIG_SECTION_VALUE,
} sb_configparser_state_t;


sb_config_t*
sb_config_parse(const char *src, size_t src_len, sb_error_t **err)
{
    if (err != NULL && *err != NULL)
        return NULL;

    size_t current = 0;
    size_t start = 0;

    sb_trie_t *section = NULL;

    char *section_name = NULL;
    char *key = NULL;
    char *value = NULL;

    sb_config_t *rv = sb_malloc(sizeof(sb_config_t));
    rv->root = sb_trie_new((sb_free_func_t) sb_trie_free);

    sb_configparser_state_t state = CONFIG_START;

    while (current < src_len) {
        char c = src[current];
        bool is_last = current == src_len - 1;

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
                    state = CONFIG_SECTION_KEY;
                    continue;
                }
                if (err != NULL)
                    *err = sb_error_new_printf(SB_ERROR_CONFIGPARSER,
                        "File must start with section");
                break;

            case CONFIG_SECTION_START:
                start = current;
                state = CONFIG_SECTION;
                break;

            case CONFIG_SECTION:
                if (c == ']') {
                    section_name = sb_strndup(src + start, current - start);
                    section = sb_trie_new(free);
                    sb_trie_insert(rv->root, section_name, section);
                    free(section_name);
                    section_name = NULL;
                    state = CONFIG_START;
                    break;
                }
                if (c != '\r' && c != '\n')
                    break;
                if (err != NULL)
                    *err = sb_error_new_printf(SB_ERROR_CONFIGPARSER,
                        "Section names can't have new lines");
                break;

            case CONFIG_SECTION_KEY:
                if (c == '=') {
                    key = sb_strndup(src + start, current - start);
                    state = CONFIG_SECTION_VALUE_START;
                    break;
                }
                if (c != '\r' && c != '\n' && !is_last)
                    break;
                // key without value, should we support it?
                if (err != NULL) {
                    size_t end = is_last && c != '\n' && c != '\r' ? src_len :
                        current;
                    key = sb_strndup(src + start, end - start);
                    *err = sb_error_new_printf(SB_ERROR_CONFIGPARSER,
                        "Key without value: %s", key);
                    free(key);
                    key = NULL;
                }
                break;

            case CONFIG_SECTION_VALUE_START:
                start = current;
                state = CONFIG_SECTION_VALUE;
                break;

            case CONFIG_SECTION_VALUE:
                if (c == '\r' || c == '\n' || is_last) {
                    size_t end = is_last && c != '\n' && c != '\r' ? src_len :
                        current;
                    value = sb_strndup(src + start, end - start);
                    sb_trie_insert(section, sb_str_strip(key),
                        sb_strdup(sb_str_strip(value)));
                    free(key);
                    key = NULL;
                    free(value);
                    value = NULL;
                    state = CONFIG_START;
                    break;
                }
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
    free(value);

    return rv;
}


static void
list_keys(const char *key, const char value, sb_slist_t **l)
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

    unsigned int i = 0;
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

    sb_trie_t *s = sb_trie_lookup(config->root, section);
    if (s == NULL)
        return NULL;

    sb_slist_t *l = NULL;
    sb_trie_foreach(s, (sb_trie_foreach_func_t) list_keys, &l);

    char **rv = sb_malloc(sizeof(char*) * (sb_slist_length(l) + 1));

    unsigned int i = 0;
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

    sb_trie_t *s = sb_trie_lookup(config->root, section);
    if (s == NULL)
        return NULL;

    return sb_trie_lookup(s, key);
}


void
sb_config_free(sb_config_t *config)
{
    if (config == NULL)
        return;
    sb_trie_free(config->root);
    free(config);
}
