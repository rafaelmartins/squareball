/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_SHELL_H
#define _SQUAREBALL_SHELL_H

/**
 * @file squareball/sb-shell.h
 * @brief Shell-related utilities.
 * @example hello_shell.c
 * @{
 */

/**
 * Function that quotes a string to be safely passed to a shell.
 *
 * @param command  The string to be quoted.
 * @return         A newly-allocated string.
 */
char* sb_shell_quote(const char *str);

/** @} */

#endif /* _SQUAREBALL_SHELL_H */
