#ifndef _HASHTAB_H_
#define _HASHTAB_H_


typedef struct _hashtab_node{
    void * key;
    void * data;
    struct _hashtab_node * next;
}hashtab_node ;

typedef struct _hashtab{
    hashtab_node ** htables; /*hash桶*/
    int size;/*hash bucket max num*/
    int nel;/*hash bucket num of elements*/
    int (*hash_value)(struct _hashtab *h,const void *key);/*散列函数*/
    int (*keycmp)(struct _hashtab *h,const void *key1,const void *key2);/*hash key compare func,当hash一致使用*/
    void (*hash_node_free)(hashtab_node * node);
}hashtab;

#define HASHTAB_MAX_NODES (0xffffffff)

typedef int (*hash_value_func)(struct _hashtab* h,const void *key);//hash func
typedef int (*keycmp_func)(struct _hashtab* h,const void *key1,const void *key2);//hash key compare func
typedef void (*hash_node_free_func)(hashtab_node *node);
/*根据当前结构体元素地址 获取到结构体首地址*/
#define offsetof(TYPE,MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)
#define container(ptr,type,member) ({\
    const typeof( ((type *)0)->member) * _mptr = (ptr);\
    (type *) ((char*)_mptr - offsetof(type,member)); })
hashtab* hashtab_create(int size,hash_value_func hash_value,
    keycmp_func keycmp,hash_node_free_func hash_node_free);
void hashtab_destroy(hashtab *h);
int hashtab_insert(hashtab * h,void *key,void *data);
hashtab_node *hashtab_delete(hashtab* h,void *key);
void *hashtab_search(hashtab* h,void *key);

#endif

/*1.const void* ??
  2.根据当前结构体元素 offsetof获取首地址
  3.container？
  4.void* key ?
  5.typedef int (*hash_value_func)(struct _hashtab* h,const void *key);//hash func*/