#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashTable.h"
#include<assert.h>

#ifdef MEMORY_TEST
#include<mcheck.h>
#endif

hashtab* hashtab_create(int size,hash_value_func hash_value,
    keycmp_func keycmp,hash_node_free_func hash_node_free){
        hashtab* h = NULL;//create a group of buckets = hash tab
        if((size<0)||(hash_value)==NULL||(keycmp)==NULL)
        {
            return NULL;
        }

        h = (hashtab*)malloc(sizeof(hashtab));
        if( h == NULL){
            return NULL;
        }

        h->htables = (hashtab_node**)malloc(size*sizeof(hashtab_node*));
        if(h->htables == NULL){
            return NULL;
        }

        h->size = size;
        h->nel = 0;
        h->hash_value = hash_value;
        h->keycmp = keycmp;
        h->hash_node_free = hash_node_free;

        //init nodes
        for(int i=0;i<size;i++){
            h->htables[i] = NULL;
        }
        return h;
    }

void hashtab_destroy(hashtab* h){
    hashtab_node * cur = NULL;
    hashtab_node * tmp = NULL;
    if( h == NULL)
        return ;
    for(int i=0;i<h->size;i++){
        cur = h->htables[i];
        while(cur){
            tmp = cur;
            cur = cur->next;
            h->hash_node_free(tmp);
        }
        h->htables[i] = NULL;
    }
    free(h->htables);
    free(h);
    return;
}

int hashtab_insert(hashtab * h,void *key,void *data){
    unsigned int hvalue = 0;
    hashtab_node* prev = NULL;
    hashtab_node* cur = NULL;
    hashtab_node* newnode = NULL;

    if((h==NULL)||(key == NULL)||(data == NULL))
        return 1;
    //get hash value
    hvalue = h->hash_value(h,key);
    cur = h->htables[hvalue];

    //hash row sort from small to big
    while((cur != NULL) &&(h->keycmp(h,key,cur->key)>0)){
        prev = cur;
        cur = cur->next; //update the row nodes
    }

    //if key and the current key are the same ,return ,the data already has
    if((cur!= NULL) &&(h->keycmp(h,key,cur->key)==0)){
        return 2;
    }

    //new node
    newnode = (hashtab_node*)malloc(sizeof(hashtab_node));
    if(newnode == NULL)
        return 3;
    
    newnode->key = key;
    newnode->data = data;
    if(prev == NULL){
        newnode->next=h->htables[hvalue];//
        h->htables[hvalue] = newnode;
    }else{
        //头插法
        newnode->next = prev->next;
        prev->next = newnode;
    }
    h->nel++;
    return 0;
}

hashtab_node *hashtab_delete(hashtab* h,void *key){
    int hvalue = 0;
    hashtab_node *cur = NULL;
    hashtab_node *prev = NULL;
    if ((h == NULL)||(key == NULL))
    {
        return NULL;
    }
    //hash value ;
    hvalue = h->hash_value(h,key);
    cur = h->htables[hvalue];
    while((cur!= NULL)&&(h->keycmp(h,key,cur->key)>0)){
        if(h->keycmp(h,key,cur->key)==0){
            if(prev==NULL){
                h->htables[hvalue] = cur->next;
            }
            else{
                prev->next = cur->next;
            }
            return cur;
        }
        prev = cur;
        cur = cur->next;
    }
    return NULL;  
}

void *hashtab_search(hashtab* h,void *key){
   int hvalue = 0;
    hashtab_node *cur = NULL;
    hashtab_node *prev = NULL;
    if ((h == NULL)||(key == NULL))
    {
        return NULL;
    }
    //hash value ;
    hvalue = h->hash_value(h,key);
    cur = h->htables[hvalue];
    while((cur!= NULL)&&(h->keycmp(h,key,cur->key)>0)){
        if(h->keycmp(h,key,cur->key)==0){
            return cur->data;
        }
        cur = cur->next;
    }    
    return NULL;    
}


void hashtab_dump(hashtab *h){
    hashtab_node* cur;
    if(h == NULL)
        return;
    printf("\r\n-----start--size[%d],nel[%d]--------",h->size,h->nel);
    for(int i=0;i<h->size;i++){
        printf("\r\n htables[%d]:",i);
        cur = h->htables[i];
        while(cur){
            printf("key[%s],data[%s]",cur->key,cur->data);
            cur = cur->next;
        }
    }
    printf("\r\n-----end--size[%d],nel[%d]",h->size,h->nel);
}

struct test_node{
    char key[80];
    char data[80];
} test_node;

//register?????
unsigned int simple_hash(const char* str){
    register unsigned int hash = 0;
    register unsigned int seed = 122;

    while(*str){
        hash = hash*seed + *str++;
    }

    return hash & (0x7FFFFFFF);
}

int hashtab_hvalue(hashtab * h,const void*key){
    return (simple_hash(key) % h->size);
}
//const void* key1 : create a point which could be any type
int hashtab_keycmp(hashtab* h,const void* key1,const void* key2){
    return strcmp(key1,key2);
}

void hashtab_node_free(hashtab_node* node){
    struct test_node *ptmp = NULL;
    ptmp = container(node->key,struct test_node,key);

    free(ptmp);
    free(node);
}

int main(){
	int i = 0;
	int res = 0;
	char *pres = NULL;
	hashtab_node * node = NULL;
	struct test_node *p = NULL;
    hashtab *h = NULL;
    #ifdef MEMORY_TEST
	setenv("MALLOC_TRACE","1.txt",1);
    mtrace();
    #endif
    /*setenv用来改变或增加环境变量内容*/
    /*mtrace 用于开启内存使用记录 内存使用记录到一个文件里面*/
    /*muntrace 用于取消内存使用记录*/

	h = hashtab_create(5,hashtab_hvalue,hashtab_keycmp,hashtab_node_free);
    assert(h!= NULL);
    /*condition 条件错误 终止程序*/
	while(1)
	{
		p = (struct test_node*)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 和value，当可以等于\"quit\"时退出");
        scanf("%s",p->key);
		scanf("%s",p->data);

		if(strcmp(p->key,"quit") == 0)
		{
			free(p);
			break;
		}

        res = hashtab_insert(h,p->key,p->data);
		if (res != 0)
		{
			free(p);
			printf("\r\n key[%s],data[%s] insert failed %d",p->key,p->data,res);
		}
		else
		{
			printf("\r\n key[%s],data[%s] insert success %d",p->key,p->data,res);
		}
	}

	hashtab_dump(h);

	while(1)
	{
		p = (struct test_node*)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 查询value的数值，当可以等于\"quit\"时退出");
        scanf("%s",p->key);

		if(strcmp(p->key,"quit") == 0)
		{
			free(p);
			break;
		}
        pres = hashtab_search(h,p->key);
		if (pres == NULL)
		{
			printf("\r\n key[%s] search data failed",p->key);
		}
		else
		{
			printf("\r\n key[%s],search data[%s] success",p->key,pres);
		}
		free(p);
	}
	hashtab_dump(h);
	while(1)
	{
		p = (struct test_node*)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 删除节点的数值，当可以等于\"quit\"时退出");
        scanf("%s",p->key);

		if(strcmp(p->key,"quit") == 0)
		{
			free(p);
			break;
		}
        node = hashtab_delete(h,p->key);
		if (node == NULL)
		{
			printf("\r\n key[%s] delete node failed ",p->key);
		}
		else
		{
			printf("\r\n key[%s],delete data[%s] success",node->key,node->data);
		    h->hash_node_free(node);
		}
		free(p);
	    hashtab_dump(h);
	}

	hashtab_destroy(h);
    #ifdef MEMORY_TEST
    muntrace();
    #endif
	return 0;
}

