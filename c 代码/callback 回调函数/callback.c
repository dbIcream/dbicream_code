#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


typedef void FQDNH(const char *, void *);

static void
fqdnh_callback(const char *param_own, void *data)
{
    assert(data);
    printf("fqdnh_callback: call\n");
    char *str = (char *) data;
    if (param_own) {
        printf("param of own:%s\n", param_own);
    }

    if (str) {
        printf("param of callback:%s\n", str);
    }
}

void
do_something(char *addr, FQDNH * handler, void *handlerData)
{
    assert(handlerData);
    int something_done = 0;

    //do something to our own data
    char *str_own = "we have done something!";
    something_done = 1;

    if (something_done) {
        handler(str_own, handlerData);
    }  
}


int main() {
    char str[] = "123456";
    char  data[] = "this ia a callback data";
    do_something(str, fqdnh_callback, data);
    getchar();
    return 0;
}

