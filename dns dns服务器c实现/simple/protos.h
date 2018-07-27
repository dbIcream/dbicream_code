#ifndef __UTIL_H__
#define __UTIL_H__

#include <stddef.h>

/* util.c */
extern void * xmalloc(size_t size);
extern void *xcalloc(size_t nmemb, size_t size);
extern char *xstrdup(const char *str);
extern void *xrealloc(void *ptr, size_t size);

/* cyan_dns.c */
extern int epoll_loop();  /*  */
extern int init_socket(void);

/* debug.c */
extern void debug_log_str(char *str);
extern int debug_log_printf(char *format, ...);
extern int debug_log_init(const char *debuglog_filename);
extern void debug_log_reset_difftime(void);
extern void debug_log_difftime();

/* parse_config.c */
extern void recycle_all(void);
extern void read_conf_file(char *file_name);
extern void list_ns();

#endif