/***************************************************************
文件名称：ua_check.c
功能说明：解析User-agent头部中的浏览器版本信息
功能设计：
		1、根据浏览器的关键字来获取到版本位置，UA中浏览器及版本格式示例：Firefox/57.0
		2、获取到浏览器关键字之后的版本信息
		3、打印出版本信息


注：
	1、_GNU_SOURCE宏定义必须有，否则编译会strcasestr()会有Warning警告信息
	2、浏览器UA 字串的标准格式为： 浏览器标识 (操作系统标识; 加密等级标识; 浏览器语言) 渲染引擎标识 版本信息+

*************************************************************/


//宏定义必须有，否则编译会strcasestr()会有Warning警告信息
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define UA_SAFARI_DEMO "Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN) AppleWebKit/533.21.1 (KHTML, like Gecko) Version/5.0.5 Safari/533.21.1"
#define UA_FIREFOX_DEMO "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:57.0) Gecko/20100101 Firefox/57.0"
#define UA_CHROME_DEMO "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.181 Safari/537.36"
#define UA_CURL_DEMO "curl/7.19.7 (x86_64-redhat-linux-gnu) libcurl/7.19.7 NSS/3.14.0.0 zlib/1.2.3 libidn/1.18 libssh2/1.4.2"
#define UA_IE_DEMO "User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E)"
#define UA_QIHOO_EE_DEMO "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36 QIHU 360EE"

#define UA_ERROR_DEMO "Firefox"
#define UA_ERROR2_DEMO "Firefox/"


#define VER_LEN 32
#define MAX_BROWER_NUM 3
struct brower_info_s {
	char brower_name[VER_LEN];
	char brower_version[VER_LEN];
};

struct ua_info_s {
	int brower_num;
	struct brower_info_s brower[MAX_BROWER_NUM];
};

enum {
	BROWER_UNKNOWN = -1,
	BROWER_CHROME = 0,
	BROWER_SAFARI,
	BROWER_FIREFOX,
	BROWER_ENUM_END
} browser_type;

typedef struct brower_info_s brower_info_t;
typedef struct ua_info_s ua_info_t;


static const char *brower_list[] = {
	"Chrome",
	"Safari",
	"Firefox"
};

#if _WIN32
static char *
strcasestr (const char *s1, const char *s2)
{
	ssize_t s1len = strlen (s1);
	ssize_t s2len = strlen (s2);

	if (s2len > s1len)
		return NULL;

	for (ssize_t i = 0; i <= s1len - s2len; ++i)
    {
		size_t j;
		for (j = 0; j < s2len; ++j)
			if (tolower (s1[i + j]) != tolower (s2[j]))
				break;
		if (j == s2len)
			return (char *) s1 + i;
    }

	return NULL;
}
#endif


static int get_version_from_str(const char* ua_str, char* ver)
{
	int i;
	for(i = 0; i < VER_LEN; i++) {
		if ((ua_str[i] >= '0' && ua_str[i] <= '9') || ua_str[i] == '.') {
			ver[i] = ua_str[i];
		} else {
			ver[i] = '\0';
			return i;
		}
	}
	ver[i]='\0';

	return i;
}


static int parse_useragent(const char *ua_str, ua_info_t *ua_info)
{
	if (ua_info == NULL) {
		return -1;
	}

	memset(ua_info, 0x00, sizeof(ua_info_t));

	/*match each brower in brower_list*/
	int brower_index;
	int ua_len = strlen(ua_str);
	for(brower_index = 0; brower_index < BROWER_ENUM_END; brower_index++) {
		const char *brower_name = brower_list[brower_index];
		char *match = strcasestr(ua_str, brower_name);
		if(match && (match - ua_str + 1 > ua_len)) {
			brower_info_t *each_brower_info = &ua_info->brower[ua_info->brower_num];
			if (get_version_from_str(match +strlen(brower_name) + 1,
				each_brower_info->brower_version) > 0) {
				strncpy(each_brower_info->brower_name,  brower_name, VER_LEN - 1);
				ua_info->brower_num++;
			}
		}
	}

	if (ua_info->brower_num == 0) {
		return -1;
	}
	return 0;
}


void print_parse_demo(char *ua_str)
{
	int i;
	int ret;
	ua_info_t ua_info;
	brower_info_t *each_brower;

	memset(&ua_info, 0x00, sizeof(ua_info_t));
	ret = parse_useragent(ua_str, &ua_info);
	printf("main: %s : %d\n", ua_str, ret);
	for(i = 0; i < ua_info.brower_num; i++) {
		each_brower = &ua_info.brower[i];
		printf("main: %s: %s\n\n", each_brower->brower_name, each_brower->brower_version);
	}
}

int main()
{
	print_parse_demo(UA_CHROME_DEMO);
	print_parse_demo(UA_FIREFOX_DEMO);
	print_parse_demo(UA_SAFARI_DEMO);
	print_parse_demo(UA_IE_DEMO);
	print_parse_demo(UA_QIHOO_EE_DEMO);

	print_parse_demo(UA_ERROR_DEMO);
	print_parse_demo(UA_ERROR2_DEMO);

	return 0;
}



