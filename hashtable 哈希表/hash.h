#ifndef SQUID_HASH_H
#define SQUID_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include <unistd.h>

#define DEFAULT_HASH_SIZE 7951

typedef void HASHFREE(void *);
typedef int HASHCMP(const void *, const void *);
typedef unsigned int HASHHASH(const void *, unsigned int);

typedef struct _hash_link {
	void *key;
	struct _hash_link *next;
}hash_link;

typedef struct _hash_head {
	int count;          /*桶里面元素的个数*/
	hash_link *next;
}hash_head;

typedef struct _hash_table {
	hash_head *buckets;     /*桶列表中各个桶的表头*/
	HASHCMP *cmp;          /*比较key的函数*/
	HASHHASH *hash;         /*计算桶序号的函数*/
	unsigned int size;      /*桶个数*/
	unsigned int current_slot;  /*用于遍历时，连接所有的桶时使用*/
	hash_link *next;        /*用于遍历时，连接所有的桶时使用*/
	int count;              /*桶里面元素的个数*/
	int max_bucket_count;   /*最大的桶里面的个数*/
} hash_table;

extern hash_table *hash_create(HASHCMP *, int, HASHHASH *);
extern void hash_free_items(hash_table *, HASHFREE *);
extern void hash_destroy(hash_table *);
extern void hash_join(hash_table *, hash_link *);
extern void hash_remove_link(hash_table *, hash_link *);
extern void *hash_lookup(hash_table *, const void *);
extern void hash_first(hash_table *);
extern void *hash_next(hash_table *);
extern void hash_last(hash_table *);
extern hash_link *hash_get_bucket(hash_table *, unsigned int);
extern int hash_prime(int n);
extern HASHHASH hash_string;
extern HASHHASH hash4;
extern const char *hash_keystr(hash_link *);


#endif /* SQUID_HASH_H */

