/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2016 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#ifndef _SQUAREBALL_SLIST_H
#define _SQUAREBALL_SLIST_H

#include "sb-mem.h"

/**
 * @file squareball/sb-slist.h
 * @brief Singly-linked list implementation
 * @example hello_slist.c
 * @{
 */

/** Singly-linked list node structure. */
typedef struct _sb_slist_t {

    /** Next node from the list. */
    struct _sb_slist_t *next;

    /** Pointer to data stored in the current list node. */
    void *data;

} sb_slist_t;

/**
 * Function that appends a node to the singly-linked list.
 *
 * @param l     The singly-linked list.
 * @param data  The pointer to the data that will be stored in the new
 *              list node.
 * @return      The singly-linked list itself.
 */
sb_slist_t* sb_slist_append(sb_slist_t *l, void *data);

/**
 * Function that frees all the memory used by the singly-linked list.
 *
 * @param l  The singly-linked list.
 */
void sb_slist_free(sb_slist_t *l);

/**
 * Function that frees all the memory used by the singly-linked list, and the
 * data stored in the list nodes, using the provided helper function.
 *
 * @param l          The singly-linked list.
 * @param free_func  Helper function, to free data stored in each node.
 */
void sb_slist_free_full(sb_slist_t *l, sb_free_func_t free_func);

/**
 * Function that counts the number of nodes in the provided singly-linked list.
 *
 * @param l  The singly-linked list.
 * @return   The number of nodes in the singly-linked list.
 */
unsigned int sb_slist_length(sb_slist_t *l);

/** @} */

#endif /* _SQUAREBALL_SLIST_H */
