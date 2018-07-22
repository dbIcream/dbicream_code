/***************************************************************
文件名称：signal_secure.c
功能说明：测试信号机制和进程安全
功能设计：
		1、主进程创建一个链表
		2、注册异步处理信号
		3、主进程循环打印这个链表
		4、通过kill杀死这个进程，异常信号获取并修改了链表里面的值
		5、主进程打印的数据变化，我们无法确定某一时刻数据是处理前的值还是数据处理后的值


注：
	1、异步操作安全性要考虑清楚，不建议在异常处理函数里面处理指针
	2、参考链接：https://blog.csdn.net/yusiguyuan/article/details/14229017
		1）信号处理函数尽量只执行简单的操作，譬如只是设置一个外部变量，其它复杂的操作留在信号处理函数之外执行；
		2）errno 是线程安全，即每个线程有自己的 errno，但不是异步信号安全。如果信号处理函数比较复杂，且调用了可能会改变 errno 值的库函数，必须考虑在信号处理函数开始时保存、结束的时候恢复被中断线程的 errno 值；
		3）信号处理函数只能调用可以重入的 C 库函数；譬如不能调用 malloc（），free（）以及标准 I/O 库函数等；
		4）信号处理函数如果需要访问全局变量，在定义此全局变量时须将其声明为 volatile，以避免编译器不恰当的优化。

	3、 linux c之信号signal处理机制，https://blog.csdn.net/u011068702/article/details/54602566

*************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define N 5

typedef struct list_s{
	struct list_s *next;
	int value;
} list_t;

list_t *head = NULL;

void print_lists(list_t *hd)
{
	printf("print_lists: ");
	while(hd) {
		printf("%d -> ", hd->value);
		hd = hd->next;
	}
	printf("NULL\n\n");
}

void sign_handle(int sig)
{
	int i;
	list_t *p, *p_tmp;
	i = 0;
	p = head;
	while(p && i < 2) {
		p = p->next;
		i ++;
	}
	while(p) {
		p_tmp = p->next;

		//free memory
		p->next = NULL;
		free(p);

		p = p_tmp;
	}
}

int main(int argc, char *argv[])
{
	int i;
	list_t *item, *p;
	// init
	head = (list_t *)malloc(sizeof(list_t));
	head->next = NULL;
	head->value = 0;
	for(i = 0; i < N; i ++) {
		item = (list_t *)malloc(sizeof(list_t));
		item->next = NULL;
		item->value = i + 1;
		p = head;
		while(p->next)
			p = p->next;
		p->next = item;
	}

	//注册信息处理函数
	signal(SIGTERM, sign_handle);

	// display
	while(1) {
		print_lists(head);
		sleep(1);
	}
	return 0;
}
