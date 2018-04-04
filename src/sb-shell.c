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
#include <string.h>
#include <squareball/sb-string.h>

char*
sb_shell_quote(const char *str)
{
    sb_string_t *rv = sb_string_new();
    sb_string_append_c(rv, '\'');
    if (str != NULL) {
        for (size_t i = 0; i < strlen(str); i++) {
            switch (str[i]) {
                case '!':
                    sb_string_append(rv, "'\\!'");
                    break;
                case '\'':
                    sb_string_append(rv, "'\\''");
                    break;
                default:
                    sb_string_append_c(rv, str[i]);
            }
        }
    }
    sb_string_append_c(rv, '\'');
    return sb_string_free(rv, false);
}
