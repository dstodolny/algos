/*
 * algos.h - prototypes and definitions for algorithm solutions
 */

#ifndef __ALGOS_H__
#define __ALGOS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/* Error-handling functions */
void unix_error(char *msg);

/* Dynamic storage allocation wrappers */
void *Malloc(size_t size);
void *Calloc(size_t nmemb, size_t size);
void Free(void *ptr);

#endif
