#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct _list_queue_node{
    int data;
    struct _list_queue_node* next;
}queue_node;

typedef struct _list_queue{
    int num;
    queue_node* head;
    queue_node* rear;
}list_queue;

#define list_queue_is_empty(list_queue) (list_queue->num == 0)

//create head node
list_queue* list_queue_create(){
    list_queue* queue;
    queue = (list_queue*)malloc(sizeof(list_queue));
    if(queue == NULL)
        return NULL;
    queue->num = 0;
    queue->head = NULL;
    queue->rear = NULL;
    return queue;
}

void list_queue_destroy(list_queue* queue){
    if(queue == NULL || list_queue_is_empty(queue))
        return;
    queue_node* tmp;// node 结点
    while(!list_queue_is_empty(queue)){
        tmp = queue->head;
        queue->head = queue->head->next;
        queue->num--;
        free(tmp);
    }
    free(queue);
    return;
}

int list_queue_enqueue(list_queue* queue,int data){
    queue_node* tmp = NULL;
    if(queue == NULL)
        return -1;
    tmp = (queue_node*)malloc(sizeof(queue_node));
    if(tmp == NULL)
        return -1;
    tmp->data = data;
    tmp->next = NULL;
    //IF head == NULL head = tmp
    //else tail = tmp 
    if(queue->head == NULL)
        queue->head = tmp;
    else
    {
        queue->rear->next = tmp;
    }
    queue->rear = tmp;// update the node
    queue->num ++;
    return 0;
}

int list_queue_dequeue(list_queue* queue){
    int data;
    if(queue == NULL || list_queue_is_empty(queue))
        return -1;
    data = queue->head->data;
    queue_node* tmp;
    tmp = queue->head;
    queue->head = queue->head->next;
    queue->num--;
    
    free(tmp);
    return 0;
}

void list_queue_dump(list_queue * queue){
    int i = 0;
    queue_node* ptmp ;
    if(queue == NULL || list_queue_is_empty(queue))
        return;
    ptmp = queue->head;

    printf("\r\n--------------dump queue num = %d----",queue->num);
    while(ptmp){
        printf("\r\n array[%d] = %d",i,ptmp->data);
        ptmp = ptmp->next;
        i++;
    }
    printf("\r\n-------------------------------\r\n");
    return;
}

int main(){
    list_queue * queue;
    queue = list_queue_create();
    int size;
    printf("\r\n pleas input the size of queue:");
    scanf("%d",&size);
    for(int i=0;i<size;i++){
        list_queue_enqueue(queue,i);
    }
    list_queue_dump(queue);

    for(int i=0;i<3;i++){
        list_queue_dequeue(queue);
    }
    list_queue_dump(queue);

    list_queue_destroy(queue);

    return 0;
}