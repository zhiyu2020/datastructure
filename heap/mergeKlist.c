#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
/*index 从0开始
 *size  为heap的大小*/
typedef struct ListNode{
    int val;
    struct ListNode* next;
}ListNode;

typedef struct heap_s{
    struct ListNode** values;
    int size;
    int index;
}heap_f;

ListNode* heap_pop(heap_f* heap){
    ListNode* last,*start;
    int max = 0,tmp = 0;
    if(heap->index <= 0)
        return NULL;
    start = heap->values[0];
    last = heap->values[--heap->index]; // 尾巴
    heap->values[0] = last;
    //heapify delete from 0 heap->index = size
    while(max< heap->index){
        int c2 = 2*tmp + 2;
        int c1 = 2*tmp + 1;        
        if(c1 < heap->index && heap->values[c1]>heap->values[max]) max = c1;
        if(c2 < heap->index && heap->values[c2]>heap->values[max]) max = c2;
        if(max != tmp){
            int temp = heap->values[max];
            heap->values[max] = heap->values[tmp];
            heap->values[tmp] = temp;
            //update
            tmp = max;
        }else break;
    }
    return start;
}

void heap_insert(heap_f* heap,ListNode* v){
    int parent, index;
    if(heap->index >= heap->size)
        return;
    heap->index++;
    index = heap->index;
    heap->values[index] = v;
    /*heapify*/
    while(index>0){
        parent = (heap->index - 1)/2;
        if(v > heap->values[parent]){
            int temp = heap->values[index];
            heap->values[index] = heap->values[parent];
            heap->values[parent] = temp;
            index = parent;
        }else break;
    }
    
}

heap_f* heap_create(int size){
    heap_f* heap = calloc(1,sizeof(heap_f));
    if(heap== NULL)
        return NULL;
    heap->values =calloc(size,sizeof(ListNode*));
    if(heap->values == NULL)    return NULL;
    heap->size = size;
    heap->index = 0;
    return heap;
}



ListNode* mergeKLists(ListNode** lists, int listsSize){
    int i;
    heap_f * heap;
    ListNode* head,*pre,*next;
    if(listsSize == 0) return NULL;
    heap = heap_create(listsSize);
    if(heap== NULL) return NULL;
    //插入每个链表头节点
    for(i=0;i<listsSize;i++){
        if(lists[i] == NULL) continue;
        heap_insert(heap,lists[i]);
    }
    //
    head = heap_pop(heap);
    if(head == NULL) return NULL;

    if(head->next != NULL) 
        heap_insert(heap,head->next);
    pre = head;

    do{
        next = heap_pop(heap);
        pre->next = next;
        if(next == NULL) break;
        if(next->next != NULL)
            heap_insert(heap,next->next);
        pre = pre->next;
    }while(1);
    return head;
}

