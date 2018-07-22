#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 128


/*
功能测试：sscanf的正则使用
参考链接：http://blog.csdn.net/tujiaw/article/details/6139896

*/

int main()
{

    char url[] = "https://a.com/a.jpg";
    char proto[MAX_STR_LEN];
    char host[MAX_STR_LEN];
    char urlpath[MAX_STR_LEN];

    sscanf(url, "%[^:]://%[^/]%[^\r\n]", proto, host, urlpath);
    printf("proto=%s, host=%s, urlpath=%s\n", proto, host, urlpath);


    int i;
    char str[10];
    for (i = 0; i < 10; i++) {
        str[i] = '!';
    }
    sscanf( "123456", "%s", str);
    printf("str = %s\n", str);      //123456
    sscanf( "123456", "%3s", str);
    printf("str = %s\n", str);      //123
    sscanf( "aaaAAA", "%[a-z]", str);
    printf("str = %s\n", str);      //aaa

    //可以多次匹配%，^类似!, %*过滤条件
    sscanf( "AAAaaaBBB", "%[^a-z]", str);
    printf("str2 = %s\n", str);      //AAA
    sscanf( "AAAaaaBBB", "%[A-Z]%[a-z]", str);
    printf("str2 = %s\n", str);     //AAA
    sscanf( "AAAaaaBBB", "%*[A-Z]%[a-z]", str);
    printf("str2 = %s\n", str);     //aaa
    sscanf( "AAAaaaBBB", "%[a-z]" , str) ;
    printf("str2 = %s\n", str);     //aaa
    sscanf( "AAAaaaBC=", "%*[A-Z]%*[a-z]%[^a-z=]", str);
    printf("str2 = %s\n", str);     //BC

    int k;
    sscanf( "AAA123BBB456", "%*[^0-9]%i" , &k);
    printf("k = %d\n", k);
    // int sscanf( const char *buffer, const char *format [, argument ] ... );
    // int swscanf( const wchar_t *buffer, const wchar_t *format [, argument ] ... );
    //
    // 可以直接使用正则
    sscanf("12", "%s", str);
    printf("str = %s\n", str);
    sscanf("123334abcd123", "%[0-9]*",str);
    printf("str = %s\n", str);
}
