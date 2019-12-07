#ifndef __BSEARCH_H
#define __BSEARCH_H

typedef int mytype;

typedef struct _bsearch_node
{
    int data;
    struct _bsearch_node* lchild;
    struct _bsearch_node* rchild;
}bstree_node;

typedef struct _bstree{
    int size;
    int (*compare)(int key1,int key2);
    int (*destory)(int data);
    bstree_node *root;
}bstree;

typedef int (*compare_func)(int key1,int key2);
typedef int (*destory_func)(int data);

#define bstree_is_empty(tree) (tree->size == 0)

bstree *bstree_create(compare_func compare,destory_func destory);

#endif