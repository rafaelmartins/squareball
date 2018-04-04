/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <squareball.h>


int
main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    size_t len;
    sb_error_t *err = NULL;

    char *contents = sb_file_get_contents_utf8(argv[1], &len, &err);

    if (err != NULL) {
        fprintf(stderr, "error: %s\n", err->msg);
        sb_error_free(err);
        return 1;
    }

    sb_config_t *t = sb_config_parse(contents, len, NULL, &err);

    free(contents);

    if (err != NULL) {
        fprintf(stderr, "error: %s\n", err->msg);
        sb_error_free(err);
        return 1;
    }

    char **sections = sb_config_list_sections(t);
    char *sections_str = sb_strv_join(sections, ", ");
    printf("Sections: %s\n\n", sections_str);
    free(sections_str);

    for (size_t i = 0; sections[i] != NULL; i++) {
        printf("Keys for '%s':\n", sections[i]);
        char **keys = sb_config_list_keys(t, sections[i]);
        for (size_t j = 0; keys[j] != NULL; j++) {
            printf("    '%s' => '%s'\n", keys[j],
                sb_config_get(t, sections[i], keys[j]));
        }
        printf("\n");
        sb_strv_free(keys);
    }

    sb_strv_free(sections);
    sb_config_free(t);

    return 0;
}
