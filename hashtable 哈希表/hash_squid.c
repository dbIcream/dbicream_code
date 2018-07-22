/*********************************************************************
*squid开源程序中的哈希表算法实现简化
*
*
*文件名:
*程序功能：
*功能设计：
		- 初始化表，即创建桶，hash_create
		- 插入节点，使用示例，hash_join
		- 遍历hash表，hash_first, hash_next，与遍历与遍历所有桶基本等价
		- 释放hash表

	说明：
		
		
**********************************************************************/



#include "hash.h"
#include <math.h>

//函数前期声明
static void hash_next_bucket(hash_table *hid);


/*NULL 定义于unistd.h*/
//#define NULL 0
static int hash_primes[] = {
	103,
	229,
	467,
	977,
	1979,
	4019,
	6037,
	7951,
	12149,
	16231,
	33493,
	65357
};

unsigned int
hash_string(const void *data, unsigned int size)
{
	const char *s = data;
	unsigned int n = 0;
	unsigned int j = 0;
	unsigned int i = 0;
	while (*s) {
		j++;
		n ^= 271 * (unsigned) *s++;
	}
	i = n ^ (j * 271);
	return i % size;
}

/* the following function(s) were adapted from
 *    usr/src/lib/libc/db/hash_func.c, 4.4 BSD lite */

/* Hash function from Chris Torek. */
unsigned int
hash4(const void *data, unsigned int size)
{
	const char *key = data;
	size_t loop;
	unsigned int h;
	size_t len;

#define HASH4a   h = (h << 5) - h + *key++;
#define HASH4b   h = (h << 5) + h + *key++;
#define HASH4 HASH4b

	h = 0;
	len = strlen(key);
	loop = len >> 3;
	switch (len & (8 - 1)) {
	case 0:
		break;
	case 7:
		HASH4;
		/* FALLTHROUGH */
	case 6:
		HASH4;
		/* FALLTHROUGH */
	case 5:
		HASH4;
		/* FALLTHROUGH */
	case 4:
		HASH4;
		/* FALLTHROUGH */
	case 3:
		HASH4;
		/* FALLTHROUGH */
	case 2:
		HASH4;
		/* FALLTHROUGH */
	case 1:
		HASH4;
	}
	while (loop--) {
		HASH4;
		HASH4;
		HASH4;
		HASH4;
		HASH4;
		HASH4;
		HASH4;
		HASH4;
	}
	return h % size;
}

/*
传入参数：
		@cmp_func,hash表key的比较函数
		@hash_sz,hash表的桶数量
		@hash_func,hash表，从key转换到桶序号的散列函数
返回参数：新建的hash表的指针
函数功能：新建一个hash表，并返回其指针
函数设计：
*/
hash_table *
hash_create(HASHCMP *cmp_func, int hash_sz, HASHHASH *hash_func)
{
	hash_table *hid = calloc(1, sizeof(hash_table));
	if (!hash_sz)
		hid->size = (unsigned int) DEFAULT_HASH_SIZE;
	else
		hid->size = (unsigned int) hash_sz;
	/* allocate and null the buckets */
	/* void *calloc(size_t numElements,size_t sizeOfElement) */
	hid->buckets = calloc(hid->size, sizeof(hash_head));
	hid->cmp = cmp_func;
	hid->hash = hash_func;
	hid->next = NULL;
	hid->current_slot = 0;
	hid->max_bucket_count = 0;
	return hid;
}

/*
传入参数：
		@hid,hash表的指针
		@free_func,hash表释放每个节点的释放函数
函数功能：释放hash表里面的每个节点，深度释放
函数设计：
*/
void
hash_free_items(hash_table *hid, HASHFREE *free_func)
{
	hash_link *l;
	hash_link **list;
	int i = 0;
	int j;
	list = calloc(hid->count, sizeof(hash_link *));
	hash_first(hid);   /* 获取到第一个不为空的桶 */
	while ((l = hash_next(hid)) && i < hid->count) {
		*(list + i) = l;
		i++;
	}
	for (j = 0; j < i; j++)
		free_func(*(list + j)); /* 通过释放函数的函数指针，释放每个桶 */
	free(list);
}

/*
传入参数：
		@hid,hash表的指针
函数功能：释放hash表的桶和hash表本身占用的内存
函数设计：
*/
void
hash_destroy(hash_table *hid)
{
	assert(hid != NULL);
	if (hid->buckets)
		free(hid->buckets);
	free(hid);
}

/*
传入参数：
		@hid,hash表的指针
		@lnk,每个节点的指针
函数功能：将要添加的节点加入到对应桶的链接头部
函数设计：
*/
void
hash_join(hash_table *hid, hash_link *lnk)
{
	int i;
	i = hid->hash(lnk->key, hid->size); /* 计算出桶的位置 */
	lnk->next = hid->buckets[i].next;   /* 插入到桶的头部位置 */
	hid->buckets[i].next = lnk;
	hid->count++;                       /* hash表计数+1 */
	hid->buckets[i].count++;            /* 桶计数+1 */
	if (hid->buckets[i].count > hid->max_bucket_count) {    /* 记录最大桶的元素数 */
		hid->max_bucket_count = hid->buckets[i].count;
	}
}

/*
传入参数：
		@hid,hash表的指针
		@hl,每个节点的指针
函数功能：通过一个已知的桶里面的数据，从hash表中删除掉这个数据
函数设计：
		1、先找到节点对应桶的表头
		2、遍历桶里面的链表找到节点
		3、将该节点从hash表中移除，并不释放该节点对应的内存空间。
		4、调用时需要另外处理节点的空间问题
*/
void
hash_remove_link(hash_table *hid, hash_link *hl)
{
	assert(hl != NULL);
	hash_link **P;
	int i;
	i = hid->hash(hl->key, hid->size);
	for (P = &hid->buckets[i].next; *P; P = &(*P)->next) {
		if (*P != hl)
			continue;
		*P = hl->next;
		if (hid->next == hl) {
			hid->next = hl->next;
			if (NULL == hid->next)
				hash_next_bucket(hid);
		}
		hid->count--;
		hid->buckets[i].count--;
		return;
	}
	assert(0);
}

/*
传入参数：
		@hid,hash表的指针
		@k,要查找一节点的key
返回参数：返回key对应的节点，节点不存在时，返回NULL
函数功能：通过key，查找对应的节点并返回
函数设计：
		1、先找到节点对应桶的表头
		2、遍历桶里面的链表找到节点
		3、返回节点，未找到时返回NULL
*/
void *
hash_lookup(hash_table *hid, const void *k)
{
	assert(k != NULL);
	hash_link *walker;
	int b;
	b = hid->hash(k, hid->size);    /* 获取到桶的序号 */
	for (walker = hid->buckets[b].next; walker != NULL; walker = walker->next) {
		/* strcmp of NULL is a SEGV */
		if (NULL == walker->key)
			return NULL;
		if ((hid->cmp) (k, walker->key) == 0)   /* 通过比较函数，比较key */
			return (walker);
		assert(walker != walker->next); /* 断言，元素与next相同时，表示异常情况 */
	}
	return NULL;
}

/*
传入参数：hash表的指针
函数功能：获取到第一个非空桶的表头
函数设计：
	1、先将当前桶设计0，将hid->next指向0号桶的表头
	2、如果0号桶为空，调用hash_next_bucket去获取下一个非空桶
	3、最终效果是hash->next为第一个非空桶的表头
*/
void
hash_first(hash_table *hid)
{
	assert(NULL == hid->next);
	hid->current_slot = 0;
	hid->next = hid->buckets[hid->current_slot].next;
	if (NULL == hid->next)
		hash_next_bucket(hid);  /* 获取到下一个不为空的桶 */
}

/*
传入参数：hash表的指针
函数功能：获取到下一个非空桶的表头
函数设计：
	1、索引是current_slot，索引的范围是[0, hid->size)
	2、如果当前桶为空，继续查找下一个桶
	3、最终效果是hash->next为下一个非空桶的表头，且current_slot值为当前桶序号
*/
static void
hash_next_bucket(hash_table *hid)
{
	while (hid->next == NULL && ++hid->current_slot < hid->size)
		hid->next = hid->buckets[hid->current_slot].next;
}

/*
传入参数：hash表的指针
函数功能：获取到下一个非空桶的表头
函数设计：
	1、如果桶已经遍历完了，返回NULL
	2、如果当前桶的链表非空，遍历当前桶的链表
	3、如果当前桶的链表已经遍历完了，返回下一个非空桶的表头
*/
void *
hash_next(hash_table *hid)
{
	hash_link *this = hid->next;
	if (NULL == this)
		return NULL;
	hid->next = this->next;
	if (NULL == hid->next)
		hash_next_bucket(hid);  /* 获取到下一个不为空的桶 */
	return this;
}

/*
 *  hash_last - resets hash traversal state to NULL
 *  清空hash表的遍历状态
 */
void
hash_last(hash_table *hid)
{
	assert(hid != NULL);
	hid->next = NULL;
	hid->current_slot = 0;
}

/*
传入参数：
		hid,hash表的指针
		bucket,桶的序号
函数功能：返回特定序号桶的表头
函数设计：
	
*/
hash_link *
hash_get_bucket(hash_table *hid, unsigned int bucket)
{
	if (bucket >= hid->size)
		return NULL;
	return (hid->buckets[bucket].next);
}

/*
传入参数：
		n,数据的总个数
函数功能：返回最合适的桶大小
函数设计：
	
*/
int
hash_prime(int n)
{
	int I = sizeof(hash_primes) / sizeof(int);
	int i;
	int best_prime = hash_primes[0];
	double min = fabs(log((double) n) - log((double) hash_primes[0]));
	double d;
	for (i = 0; i < I; i++) {
		d = fabs(log((double) n) - log((double) hash_primes[i]));
		if (d > min)
			continue;
		min = d;
		best_prime = hash_primes[i];
	}
	return best_prime;
}

/*
 * return the key of a hash_link as a const string
 */
const char *
hash_keystr(hash_link *hl)
{
	return (const char *) hl->key;
}


/*
	hash放在第一个位置，通过获取到hash_link的大小来获取到hash表,
	通过获取到整个node类型的大小来获取到节点，没有放在第一个位置时，
		可以通过offsetof()函数来操作
*/
struct hash_node_s {
	hash_link hash;		//key, next
	int id;				//桶序号，作为节点数据，可以自定义
};
typedef struct hash_node_s hash_node_t;


hash_table *hello_hash_table;/* NULL */
#define KEY_STR_1 "model1"
#define KEY_STR_2 "model2"
#define KEY_STR_3 "model3"
#define KEY_STR_4 "model4"
#define HASH_TABLE_LEN 100

void free_hash_node(void *data)
{
	hash_node_t *node = data;
	free(node->hash.key);
}

void add_hash_key(const char *key_str)
{
	hash_node_t *node = NULL;
	if ((node = (hash_node_t *)hash_lookup(hello_hash_table, key_str)) != NULL) {
		printf("model_lib:repet record.key_str=[%s] \n",key_str);
	} else {
		node = calloc(1, sizeof(hash_node_t));
		node->hash.key = strdup(key_str);
		node->id = hash4(key_str, HASH_TABLE_LEN);
		hash_join(hello_hash_table, &node->hash);
	}
}

int main()
{
	const char *key_str = NULL;
	hash_node_t *node = NULL;

	/*初始化hash表*/
	if (hello_hash_table == NULL) {
		hello_hash_table = hash_create((HASHCMP *)strcmp, HASH_TABLE_LEN, hash4);
	}

	/*添加数据到hash表里面*/
	add_hash_key(KEY_STR_1);
	add_hash_key(KEY_STR_2);
	add_hash_key(KEY_STR_3);
	add_hash_key(KEY_STR_4);

	/*查找hash表*/
	node = NULL;
	key_str = KEY_STR_2;
	if ((node = (hash_node_t *)hash_lookup(hello_hash_table, key_str)) != NULL) {
		printf("main:found key_str=[%s], id=%d\n", node->hash.key, node->id);
	} else {
		printf("main:not found key_str=[%s] \n", key_str);
	}

	/*打印hash表*/
	hash_first(hello_hash_table);
	while((node = hash_next(hello_hash_table)) !=NULL) {
		printf("main:key_str=[%s] id=[%d]\n", node->hash.key, node->id);
	}

	/*打印hash表，等价于下面的操作*/
	int i;
	for (i = 0; i < HASH_TABLE_LEN; i++) {
		hash_link *hash = hash_get_bucket(hello_hash_table, i);
		while (hash != NULL) {
			printf("main:key_str=[%s] id=[%d]\n", hash->key, i);
			hash = hash->next;
		}
	}

	/*释放hash表，先释放hash表里面的桶，最后释放hash表本身*/
	if(hello_hash_table) {
		hash_free_items(hello_hash_table, free_hash_node);
		hash_destroy(hello_hash_table);
		hello_hash_table = NULL;
	}
	return 0;
}


//gcc -g -o main main.c hash.c -lm

