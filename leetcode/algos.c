/*
 * algos.c - Functions for the algorithms solutions
 */
#include "algos.h"

/* Unix-style error */
void
unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

/* Wrappers for dynamic storage allocation functions */
void
*Malloc(size_t size)
{
    void *p;

    if ((p  = malloc(size)) == NULL)
    unix_error("Malloc error");
    return p;
}

void
*Calloc(size_t nmemb, size_t size)
{
    void *p;

    if ((p = calloc(nmemb, size)) == NULL)
    unix_error("Calloc error");
    return p;
}

void
Free(void *ptr)
{
    free(ptr);
}
