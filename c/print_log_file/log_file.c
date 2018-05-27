/***************************************************************
文件名称：log_file.c
功能说明：日志打印到日志文件
功能设计：
		1、打开并初始化日志文件，debug_log_init()
		2、向日志中打印一个字符串：debug_log_str()
		3、向日志中打印一个格式化的字符串：debug_log_printf()
		4、向日志中打印时间，debug_log_difftime()

*************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>


static struct timeval debuglog_newtime, debuglog_oldtime;
static FILE *debuglog_file = NULL;


void debug_log_str(char *str);
int debug_log_printf(char *format, ...);


int debug_log_init(const char *debuglog_filename);
void debug_log_reset_difftime(void);
void debug_log_difftime();


void debug_log_str(char *str)
{
	if (debuglog_file && str) {
		fprintf(debuglog_file, "%s\n", str);
		printf("debug_buf: %s\n", str);
		return;
	}
	fclose(debuglog_file);
}

int debug_log_printf(char *fmt, ...) {
	if (debuglog_file == NULL) {
		return 0;
	}
	va_list ap;

	//generate time
	time_t cur_time;
	struct tm *tm_time;
	char str_time[32];
	time(&cur_time);
	if ((tm_time = localtime(&cur_time)) != NULL) {
		strftime(str_time, sizeof(str_time), "%m-%d %H:%M:%S", tm_time);
	}

	va_start(ap, fmt);
	fprintf(debuglog_file, "%s ", str_time);
	int i = vfprintf(debuglog_file, fmt, ap);
	va_end(ap);
	return i;
}




int debug_log_init(const char *debuglog_filename)
{
	if (debuglog_filename != NULL) {
		if ((debuglog_file = fopen(debuglog_filename, "a")) != NULL) {
			time_t tm;
			time(&tm);

			//set line buffered mode for debuglog_file
			setvbuf(debuglog_file, NULL, _IOLBF, BUFSIZ);

			fprintf(debuglog_file, "Starting - %s", ctime(&tm));
			gettimeofday(&debuglog_oldtime, NULL);
			return (0);
		} else {
				return (1);
		}
	} else {
		return (0);
	}
}

/*subtracts time structures and return the result in micro-seconds*/
static long timeval_subtract_us(struct timeval *start, struct timeval *end)
{
	long usec_part, sec_part;
	usec_part = end->tv_usec - start->tv_usec;
	sec_part = end->tv_sec - start->tv_sec;

    return ((1000000 * sec_part) + usec_part);
}

void debug_log_reset_difftime(void)
{
	gettimeofday(&debuglog_oldtime, NULL);
}


void debug_log_difftime(void)
{
	if (debuglog_file) {
		gettimeofday(&debuglog_newtime, NULL);
		fprintf(debuglog_file, "time:%ld\n", timeval_subtract_us(&debuglog_oldtime, &debuglog_newtime));
	}
}


//调用
int main()
{
	char buf[1024] = {"content"};

	debug_log_init("debug.log");

	debug_log_str(buf);
	debug_log_printf("main: %s\n", buf);

	debug_log_difftime();

	return 0;
}



