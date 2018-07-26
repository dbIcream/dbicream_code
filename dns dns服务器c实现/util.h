#ifndef __UTIL_H__
#define __UTIL_H__

#include <stddef.h>

extern void * xmalloc(size_t size);
extern void *xcalloc(size_t nmemb, size_t size);
extern char *xstrdup(const char *str);
extern void *xrealloc(void *ptr, size_t size);

#endif