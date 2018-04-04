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

#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif /* HAVE_SYS_STAT_H */

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <squareball/sb-error.h>
#include <squareball/sb-strfuncs.h>
#include <squareball/sb-string.h>
#include <squareball/sb-utf8.h>


static char*
file_get_contents(const char *path, bool utf8, size_t *len, sb_error_t **err)
{
    if (path == NULL || len == NULL)
        return NULL;

    if (err != NULL && *err != NULL)
        return NULL;

    *len = 0;

    FILE *fp = fopen(path, "r");
    int tmp_errno = errno;

    if (fp == NULL) {
        if (err != NULL)
            *err = sb_error_new_printf(SB_ERROR_FILE_OPEN,
                "Failed to open file (%s): %s", path, strerror(tmp_errno));
        return NULL;
    }

    sb_string_t *str = sb_string_new();

    char buffer[1024];
    char *tmp;

    while (!feof(fp) && !ferror(fp)) {
        size_t read_len = fread(buffer, sizeof(char), 1024, fp);
        tmp_errno = errno;
        if (ferror(fp)) {
            if (err != NULL)
                *err = sb_error_new_printf(SB_ERROR_FILE_READ,
                    "Failed to read from file (%s): %s", path,
                    strerror(tmp_errno));
            fclose(fp);
            *len = 0;
            sb_string_free(str, true);
            return NULL;
        }
        tmp = buffer;
        if (utf8 && str->len == 0 && read_len > 0) {
            // skipping BOM before validation, for performance. should be safe
            size_t skip = sb_utf8_bom_length((uint8_t*) buffer, read_len);
            read_len -= skip;
            tmp += skip;
        }
        *len += read_len;
        sb_string_append_len(str, tmp, read_len);
    }

    fclose(fp);

    if (utf8 && !sb_utf8_validate_str(str)) {
        if (err != NULL)
            *err = sb_error_new_printf(SB_ERROR_FILE_READ,
                "File content is not valid UTF-8: %s", path);
        sb_string_free(str, true);
        return NULL;
    }

    return sb_string_free(str, false);
}


char*
sb_file_get_contents(const char *path, size_t *len, sb_error_t **err)
{
    return file_get_contents(path, false, len, err);
}


char*
sb_file_get_contents_utf8(const char *path, size_t *len, sb_error_t **err)
{
    return file_get_contents(path, true, len, err);
}


void
sb_file_put_contents(const char *path, const char* contents, ssize_t len,
    sb_error_t **err)
{
    if (path == NULL || contents == NULL || len == 0)
        return;

    if (err != NULL && *err != NULL)
        return;

    FILE *fp = fopen(path, "w");
    int tmp_errno = errno;

    if (fp == NULL) {
        if (err != NULL)
            *err = sb_error_new_printf(SB_ERROR_FILE_OPEN,
                "Failed to open file (%s): %s", path, strerror(tmp_errno));
        return;
    }

    // TODO: optimize. write in chunks, maybe?
    if (len < 0)
        len = strlen(contents);
    size_t written_len = fwrite(contents, sizeof(char), len, fp);
    tmp_errno = errno;

    if (ferror(fp)) {
        if (err != NULL)
            *err = sb_error_new_printf(SB_ERROR_FILE_WRITE,
                "Failed to write to file (%s): %s", path, strerror(tmp_errno));
        fclose(fp);
        return;
    }

    fclose(fp);

    if (written_len != len && err != NULL)
        *err = sb_error_new_printf(SB_ERROR_FILE_WRITE,
            "Failed to write to file (%s): only %zu bytes written, from %zu",
            written_len, len);
}


void
sb_mkdir_recursive(const char *path, sb_error_t **err)
{
    if (path == NULL)
        return;

    if (err != NULL && *err != NULL)
        return;

    char *fname = sb_strdup(path);
    char *tmp = fname;

    while (1) {

        if (*tmp != '/' && *tmp != '\\' && *tmp != '\0') {
            tmp++;
            continue;
        }

#if defined(HAVE_SYS_STAT_H) && defined(HAVE_SYS_TYPES_H)
        char bkp = *tmp;
        *tmp = '\0';
        if ((strlen(fname) > 0) &&
#if defined(WIN32) || defined(_WIN32)
            (-1 == mkdir(fname)) &&
#else
            (-1 == mkdir(fname, 0777)) &&
#endif
            (errno != EEXIST))
        {
            if (err != NULL)
                *err = sb_error_new_printf(SB_ERROR_DIR_CREATE,
                    "Failed to create directory (%s): %s", path,
                    strerror(errno));
            break;
        }
        *tmp = bkp;
#else
        if (err != NULL)
            *err = sb_error_new_printf(SB_ERROR_DIR_CREATE,
                "Failed to create directory (%s): Unsupported platform", path);
        break;
#endif

        if (*tmp == '\0')
            break;

        tmp++;
    }
    free(fname);
}
