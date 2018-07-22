/***************************************************************
文件名称：url_type.c
功能说明：获取相对路径中的文件格式（后缀）
功能设计：
		1、获取到相对路径中的第一个.的位置，为空时表示没有相应后缀
		2、与定义好的图片后缀的字符串比较，如"jpg"等
		3、获取到对应的图片格式后缀的枚举类型，枚举类型与字符串需一一匹配


*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define URL_DEMO_1 "/a.jpg"
#define URL_DEMO_2 "/a.png"
#define URL_DEMO_3 "/a.gif"
#define URL_DEMO_4 "/a"
#define URL_DEMO_5 "/a."
#define URL_DEMO_6 "/a.ab"

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

enum {
	PIC_FORMAT_UNKNOW = -1,
	PIC_FORMAT_JPG = 0,
	PIC_FORMAT_JPEG,
	PIC_FORMAT_PNG,
	PIC_FORMAT_GIF,
	PIC_FORMAT_WEBP,
	PIC_FORMAT_ENUM_END,
} pic_format_type;


static const char *pic_format_strs[] = {
	"jpg",
	"jpeg",
	"png",
	"gif",
	"webp",
};


int get_pic_format(const char *relative_url) {
	if (relative_url == NULL) {
		return -1;
	}

	int i;
	char *format = NULL;

	format = strchr(relative_url, '.');
	if (format == NULL) {
		return PIC_FORMAT_UNKNOW;
	}

	
	for (i = 0; i < PIC_FORMAT_ENUM_END; i++) {
		if (strcasestr(format, pic_format_strs[i]) != NULL) {
			return i;
		}
	}

	return PIC_FORMAT_UNKNOW;
}

void print_pic_format(const char *relative_url)
{
	int pic_format = get_pic_format(relative_url);
	if (pic_format == PIC_FORMAT_UNKNOW) {
		printf("main: %s has no format\n", relative_url);
	} else {
		printf("main: %s format is %s\n\n", relative_url, pic_format_strs[pic_format]);
	}
}

int main()
{	
	print_pic_format(URL_DEMO_1);
	print_pic_format(URL_DEMO_2);
	print_pic_format(URL_DEMO_3);
	print_pic_format(URL_DEMO_4);
	print_pic_format(URL_DEMO_5);
	print_pic_format(URL_DEMO_6);

	return 0;
}
