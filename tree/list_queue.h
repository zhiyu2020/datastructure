#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

typedef struct _list_queue_node
{
    void *data;
    struct _list_queue_node* next;
}queue_node;

typedef struct _list_queue
{
    int num;
    queue_node *head;
    queue_node *tail;
}list_queue;

#define queue_is_empty(queue) ((queue->num)==0)
list_queue * list_queue_create();
int list_queue_enqueue(list_queue* queue,void *data);
int list_queue_dequeue(list_queue* queue,void ** data);//** cause it introduces a linked data type
#endif


//创建队列头
list_queue * list_queue_create()
{
    list_queue* queue;
    queue = (list_queue*)malloc(sizeof(list_queue));
    if(queue == NULL)
        return NULL;
    queue->num = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

int list_queue_enqueue(list_queue* queue,void *data)
{
    queue_node* ptmp = NULL;
    if(queue == NULL)
        return -1;
    ptmp = (queue_node*)malloc(sizeof(queue_node));
    if(ptmp == NULL)
        return -1;
    ptmp->data = data;
    ptmp->next = NULL;
    if(queue->head== NULL){
        queue->head = ptmp;//there is no head node in the queue
    }else{
        queue->tail->next = ptmp;
    }
    queue->tail = ptmp;//update the tail
    queue->num++;
}
int list_queue_dequeue(list_queue* queue,void ** data)
{
    queue_node* ptmp ;
    if(queue == NULL||(data == NULL)|| queue_is_empty(queue))
        return -1;
    *data = queue->head->data;
    ptmp = queue->head;
    queue->head = queue->head->next;
    queue->num--;
    if(queue->head == NULL){//队列已经为空 check deleted num
        queue->tail = NULL;
    }
    free(ptmp);
    return 0;
}