#include <stdio.h>

typedef struct DlistNode{// 双向链表中每个结点
    struct DlistNode* prev;// 前驱结点指针
    struct DlistNode* next;// 后驱结点指针
    int data;
}stDlistNode;

typedef struct Dlisthead{
    int size; // 链表长度
    stDlistNode *head; // 头指针
    stDlistNode *tail;//tail point
}stDlistHead;