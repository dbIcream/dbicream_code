#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "protos.h"

void * xmalloc(size_t size)
{
	void *p;
	p = malloc(size);
	if (NULL == p) {
		debug_log_printf("malloc failed\n");
		abort();
	}
	return p;
}

void *xcalloc(size_t nmemb, size_t size)
{
	void *p;
	p = xmalloc(nmemb * size);
	memset(p, 0, nmemb * size);
	return p;
}

char *xstrdup(const char *str)
{
	char *p;
	p = (char *)xmalloc(strlen(str) + 1);
	strcpy(p, str);
	return p;
}

void *xrealloc(void *ptr, size_t size)
{
	void *p;
	p = realloc(ptr, size);
	if (NULL == p) {
		debug_log_printf("realloc failed\n");
		abort();
	}
	return p;
}