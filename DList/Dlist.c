#include<stdio.h>
#include "./Dlist.h"

//initial the list
void dlist_init(stDlistHead* dlist){
    dlist->size = 0;
    dlist->head = NULL;
    dlist->tail = NULL;
    return;
}

void destroy_list(stDlistHead* dlist){
    stDlistNode* pNode = NULL;
    while(dlist->size>0){
        //point to the head
        pNode = dlist->head;
        dlist->head = dlist->head->next;
        dlist->size--;
    }
    memset(dlist,0,sizeof(stDlistHead));
}

int dlist_insert_head(stDlistHead* dlist,stDlistNode* node,int data){
    if(node == NULL){
        
    }
}