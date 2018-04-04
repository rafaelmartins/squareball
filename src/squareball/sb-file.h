/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_FILE_H
#define _SQUAREBALL_FILE_H

/**
 * @file squareball/sb-file.h
 * @brief File utilities.
 * @example hello_file_read.c
 * @example hello_file_write.c
 * @example hello_dir_create.c
 * @{
 */

/**
 * Function that reads the content of a file.
 *
 * This function can generate errors with the following codes:
 *
 * - \c SB_ERROR_FILE_OPEN
 * - \c SB_ERROR_FILE_READ
 *
 * @param path  File path.
 * @param len   Location to store length of file, in bytes, or \c NULL.
 * @param err   Return location for a \ref sb_error_t, or NULL.
 * @return      A string with the content of the file, or \c NULL if some
 *              error happened.
 */
char* sb_file_get_contents(const char *path, size_t *len, sb_error_t **err);

/**
 * Function that reads the content of a file, checking if it is encoded in
 * UTF-8 and removing UTF-8 BOM, if needed.
 *
 * This function can generate errors with the following codes:
 *
 * - \c SB_ERROR_FILE_OPEN
 * - \c SB_ERROR_FILE_READ
 *
 * @param path  File path.
 * @param len   Location to store length of file, in bytes, or \c NULL.
 * @param err   Return location for a \ref sb_error_t, or NULL.
 * @return      A string with the content of the file, or \c NULL if some
 *              error happened.
 */
char* sb_file_get_contents_utf8(const char *path, size_t *len, sb_error_t **err);

/**
 * Function that writes content to a file.
 *
 * This function can generate errors with the following codes:
 *
 * - \c SB_ERROR_FILE_OPEN
 * - \c SB_ERROR_FILE_WRITE
 *
 * @param path      File path.
 * @param contents  Content.
 * @param len       Content length.
 * @param err       Return location for a \ref sb_error_t, or NULL.
 */
void sb_file_put_contents(const char *path, const char* contents, size_t len,
    sb_error_t **err);

/**
 * Function that creates directories recursively. It respects umask when
 * creating directories.
 *
 * This function can generate errors with the following codes:
 *
 * - \c SB_ERROR_DIR_CREATE
 *
 * @param path  Directory path.
 * @param err   Return location for a \ref sb_error_t, or NULL.
 */
void sb_mkdir_recursive(const char *path, sb_error_t **err);

/** @} */

#endif /* _SQUAREBALL_FILE_H */
