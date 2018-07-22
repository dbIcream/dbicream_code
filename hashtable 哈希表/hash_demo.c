/*********************************************************************
*哈希表算法实现
*
*
*文件名:
*程序功能：
*功能设计：
		1、散列表的结构：键值key，数据data，下一个结点node
		2、散列表的表头：节点链表，用来存储每个键值对应的列表
		3、散列表，用来存储每个链表的表头
		4、散列函数，用来映射键值索引到表头解析过程

	说明：
		key值一般是一个字符串，基本不会像例子中的数字
		散列函数例子中简化了，直接取余，一般会更复杂
		
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned long

typedef struct hash_node_s hash_node_t;
typedef struct hash_head_s hash_head_t;


#define HASH_TABLE_LEN  100 /*哈希表长度*/

/* 每个数据结点，用链表的方式连接 */
struct hash_node_s
{
	uint16_t key;
	uint16_t data;
	struct hash_node_s *next;
}; 

/* 每个hash表的表头 */
struct hash_head_s
{
	hash_node_t *head;
};

/* hash表的散列表，大小是100，最多存储100个桶 */
static hash_head_t *Hash_Table[HASH_TABLE_LEN];

/* hash表的散列函数，直接求余 */
uint8_t hash_func(uint16_t key)
{
	uint8_t pos = 0;
	pos = key % HASH_TABLE_LEN;
	return pos;
}

hash_node_t * create_hash_node(void)
{
	hash_node_t * node;
	node = (hash_node_t *) malloc(sizeof(hash_node_t));
	if (node == NULL) {
		return NULL;
	}
	node->next = NULL;
	return node;
}

void init_hash_table(void)
{
	int i;
	printf("init_hash_table called\n");

	for (i = 0; i < HASH_TABLE_LEN; i++) {
		Hash_Table[i] = (hash_head_t *) calloc(1, sizeof(hash_head_t));
	}
}

void insert_hash_node(hash_node_t * new_node)
{
	if (new_node == NULL) {
		return;
	}
	hash_node_t *node, *node_next;
	uint8_t pos = 0;

	printf("insert_hash_node: key=%d, new_node=%p\n", new_node->key, new_node);

	pos = hash_func(new_node->key);	//用哈希函数获得位置
	if (Hash_Table[pos]->head == NULL) {	//判断是否为空链表
		Hash_Table[pos]->head = new_node;
		return;
	}
	else {
		node_next = node = Hash_Table[pos]->head;	//不是空链表时，获取该点的表头
		while (node_next != NULL) {	//遍历
			node = node_next;
			node_next = node->next;
		}
		node->next = new_node;	//在末尾插入新节点
	}
}

hash_node_t * get_hash_node(uint16_t key)
{
	hash_node_t * node;
	uint8_t pos = 0;

	pos = hash_func(key);			//用哈希函数获得位置
	node = Hash_Table[pos]->head;	//获取根节点

	while (node != NULL) {		//遍历
		if (node->key == key) {
			printf("get_hash_node: key=%d, node=%p\n", key, node);
			return node;
		}
		node = node->next;
	}

	printf("get_hash_node: key=%d, return NULL\n", key);
	return NULL;
}

int remove_hash_node(hash_node_t *delete_node)
{
#define FOUND_NODE 1
#define NOT_FOUND_NODE -1

	hash_node_t *node, *head_node;
	uint8_t pos = 0;

	pos = hash_func(delete_node->key);		//用哈希函数获得位置
	head_node = node = Hash_Table[pos]->head;	//获取根节点

	//删除根节点
	if (delete_node == head_node) {
		Hash_Table[pos]->head = delete_node->next;
		free(delete_node);
		delete_node = NULL;
		return FOUND_NODE;
	}

	//遍历找到要删除的节点并删除
	while (node != NULL) {
		if (node == delete_node) {
			free(delete_node);
			delete_node = NULL;
			return FOUND_NODE;
		}
		node = node->next;
	}

	return NOT_FOUND_NODE;	
}

uint16_t print_hash_table(void)
{
	hash_node_t * node;
	uint16_t i = 0;
	uint16_t num = 0;

	//遍历所有的key
	for (i = 0;i < HASH_TABLE_LEN;i++)
	{
		node = Hash_Table[i]->head;	//获取根节点
		if (node != NULL) {
			printf("Hash_Table[%d]:", i);
		}

		while (node != NULL) {	//遍历
			num++;
			printf("\t key=%d, data=%d\n", node->key, node->data);
			node = node->next;
		}
	}

	return num;
}


void free_hash_table()
{
	uint16_t i = 0;
	hash_node_t *node, *node_next;
	
	for (i = 0;i < HASH_TABLE_LEN;i++) {	//遍历
		node_next = Hash_Table[i]->head;//获取根节点
		while (node_next != NULL) {
			node = node_next;	//保存当前节点
			node_next = node->next;	//将next指向下一个要删除的节点
			free(node);		//删除当前节点
			node = NULL;
		}
	}
}

void insert_node_with_key_data(uint16_t key, uint16_t data)
{
	printf("insert_node_with_key_data:key=%d, data=%d\n", key, data);
	hash_node_t *node = create_hash_node();
	node->key = key;
	node->data = data;
	insert_hash_node(node);
}

int main()
{
	hash_node_t * node;
	uint8_t temp = 0;
	uint8_t i = 0;
	
	init_hash_table();
	insert_node_with_key_data(1, 2);
	insert_node_with_key_data(100, 101);
	insert_node_with_key_data(1002, 1001);
	insert_node_with_key_data(10000, 10001);
	insert_node_with_key_data(2, 10001);

	//查询key = 1000;
	node = get_hash_node(100);
	if (node != NULL) {
		remove_hash_node(node);
	}

	//查询key = 1001;
	node = get_hash_node(1001);

	int table_count = print_hash_table();
	printf("main: table_count=%d\n", table_count);

	free_hash_table();

	return 0;
}

