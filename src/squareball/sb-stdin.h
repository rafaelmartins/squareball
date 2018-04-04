/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_STDIN_H
#define _SQUAREBALL_STDIN_H

/**
 * @file squareball/sb-stdin.h
 * @brief Standard input utilities.
 * @{
 */

/**
 * Function that reads the content of standard input.
 *
 * This function won't report errors, it will just stop reading when get an
 * error or \c EOF.
 *
 * @return  A nul-terminated string.
 */
char* sb_stdin_get_contents(void);

/** @} */

#endif /* _SQUAREBALL_STDIN_H */
