#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
16进制数转数字的对照表
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

static char* bit16_to_char(char *str)
{
	static char imei[256];
	char bit_high, bit_low;
	int i = 0;
	int len;

	if (str == NULL) {
		return NULL;
	}

	len = strlen(str);
	memset(imei,0,sizeof(imei));
	for(i = 0; (i + i < len) && (i + i < 256); i++) {
		bit_high = tb_bit16_to_num[str[i + i]];
		bit_low = tb_bit16_to_num[str[i + i + 1]];
		imei[i] = (bit_high << 4) + bit_low;
	}
	
	return imei;
}


/*
原本字符值的值:fda02f36e047bdc90a5e507798fa2d62
转成16进制后值变成:6664613032663336653034376264633930613565353037373938666132643632
最终头部：:6664613032663336653034376264633930613565353037373938666132643632


bit16_to_char(6664613032663336653034376264633930613565353037373938666132643632)=fda02f36e047bdc90a5e507798fa2d62
bit16_to_char(4130303030303733344436333841A00000734D638A)=fda02f36e047bdc90a5e5
bit16_to_char(383637373032303238343034303133867702028404013)=fda02f36e047bdc90a5e507

*/

void show_tb_bit16_to_num()
{
	int i;
	for (i = 0; i < 255; i++) {
		if (tb_bit16_to_num[i] != 0) {
			printf("[%d] = %d\n", i, tb_bit16_to_num[i]);
		}
	}
}

int main()
{
	char header_id1[] = "4130303030303733344436333841"; 		//A00000734D638A
	char header_id2[] = "383637373032303238343034303133"; 	//867702028404013
	//fda02f36e047bdc90a5e507798fa2d62
	char header_id3[] = "6664613032663336653034376264633930613565353037373938666132643632";
	char header_id4[] = "7E";

	show_tb_bit16_to_num();

	printf("main: bit16_to_char(%s)=%s\n", header_id1, bit16_to_char(header_id1));
	printf("main: bit16_to_char_orignal(%s)=%s\n\n", header_id1,
			bit16_to_char_orignal(header_id1, strlen(header_id1)));

	printf("main: bit16_to_char(%s)=%s\n", header_id2, bit16_to_char(header_id2));
	printf("main: bit16_to_char_orignal(%s)=%s\n\n", header_id2,
			bit16_to_char_orignal(header_id2, strlen(header_id2)));
	
	printf("main: bit16_to_char(%s)=%s\n", header_id3, bit16_to_char(header_id3));
	printf("main: bit16_to_char_orignal(%s)=%s\n\n", header_id3,
			bit16_to_char_orignal(header_id3, strlen(header_id3)));

	printf("main: bit16_to_char(%s)=%s\n", header_id4, bit16_to_char(header_id4));
	printf("main: bit16_to_char_orignal(%s)=%s\n\n", header_id4,
			bit16_to_char_orignal(header_id4, strlen(header_id4)));
	
	return 0;
}





