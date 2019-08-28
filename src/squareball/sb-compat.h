/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2019 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_COMPAT_H
#define _SQUAREBALL_COMPAT_H

/**
 * @file squareball/sb-compat.h
 * @brief Compatibility helper functions.
 * @{
 */

/**
 * Function that converts a wait status returned by a child process (e.g.
 * the return value of \c system(3) function or the second argument of
 * \c waitpid(2) syscall) into a status code, as found in a shell.
 *
 * @param waitstatus  The wait status.
 * @return            The status code.
 */
int sb_compat_status_code(int waitstatus);

/** @} */

#endif /* _SQUAREBALL_COMPAT_H */
