/*
@function: 将ASCII码的字符串转换成原来的字符串
@example: 	"A00000734D638A"(orig) -> "4130303030303733344436333841"(bit64)
			what we do is Opposite process
@detail:  将ASCII码里面的 abcdef, ABCDEF, 1234567890, 三组字符串转换成十进制数，然后直接按位从数组里面取就可以得到转换的值。
@author: dbicream
*/

#define TEST_OPEN 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	16进制数字符与ASCII码对照表
	0-9  48-57 A-Z  65-90 a-z  97-122
*/
static int tb_bit16_to_num[] = {
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,//0-14
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,//15-29
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,//30-44
	0,   0,   0,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   0,//45-59
	0,   0,   0,   0,   0,   0XA, 0XB, 0XC, 0XD, 0XE, 0XF, 0,   0,   0,   0,//60-74
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,//75-89
	0,   0,   0,   0,   0,   0,   0,   0XA, 0XB, 0XC, 0XD, 0XE, 0XF, 0,   0,//90-104
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,//105-119
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,//120-134
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,//240-254
	0,
};

/*
@param_in : bit64_str
@param_out: 
@example:  "4130303030303733344436333841"(bit64) -> "A00000734D638A"(orig)
*/
static char* bit16_to_char(char *bit16_str)
{
	static char imei[256];
	char bit_high, bit_low;
	int i = 0;
	int len;

	if (bit16_str == NULL) {
		return NULL;
	}

	len = strlen(bit16_str);
	if (len >= 256) {
		printf("bit16_to_char: strlen >= 256\n");
	}

	memset(imei, 0, sizeof(imei));
	for(i = 0; (i + i < len) && (i + i < 256); i++) {
		bit_high = tb_bit16_to_num[bit16_str[i + i]];
		bit_low = tb_bit16_to_num[bit16_str[i + i + 1]];
		imei[i] = (bit_high << 4) + bit_low;
	}
	
	return imei;
}

#if TEST_OPEN
static void show_tb_bit16_to_num()
{
	int i;
	for (i = 0; i < 255; i++) {
		if (tb_bit16_to_num[i] != 0) {
			printf("[%d] = %d\n", i, tb_bit16_to_num[i]);
		}
	}
}

#endif

int main()
{
	/* 声明测试用的字符串列表 */
	char header_id1[] = "4130303030303733344436333841"; 	//A00000734D638A
	char header_id2[] = "383637373032303238343034303133"; 	//867702028404013
	char header_id4[] = "7E";

#if TEST_OPEN
	show_tb_bit16_to_num();
#endif

	printf("main: bit16_to_char(%s)=%s\n", header_id1, bit16_to_char(header_id1));
	printf("main: bit16_to_char(%s)=%s\n", header_id2, bit16_to_char(header_id2));
	printf("main: bit16_to_char(%s)=%s\n", header_id4, bit16_to_char(header_id4));
	return 0;
}





