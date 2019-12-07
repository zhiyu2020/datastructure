#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct _array_queue{
    int size;// 队列大小
    int num;//当前存储数据大小
    int head;//队列的头
    int tail;//队列尾
    int *array;//存储数据区
} array_queue;

/*注意 define 后面是() instead of {}*/
#define arrary_queue_is_empty(array_queue) (array_queue->head == array_queue->tail)
#define array_queue_is_full(array_queue) ((array_queue->tail +1)%array_queue->size == array_queue->head)

array_queue * array_queue_create(int size){
    array_queue *queue;
    queue = (array_queue*)malloc(sizeof(array_queue));
    if(queue == NULL)
        return NULL;
    queue->array = (int*)malloc(size*sizeof(int));// size搞错了 导致无法创建array
    if(queue->array == NULL)
        free(queue);
    queue->size = size;
    queue->num = 0;
    queue->head = 0;
    queue->tail = 0;
    return queue;
}

void array_queue_destroy(array_queue* queue){
    if(queue == NULL)
        return;
    if(queue != NULL)
        free(queue->array);
    free(queue);
    return;
}

/*enqueue 加入队列*/
int array_queue_enqueue(array_queue * queue, int data){
    /*队列空 或者 满 return -1*/
    if(queue == NULL || array_queue_is_full(queue))
        return -1;
    queue->num++;
    queue->array[queue->tail] = data;// 循环指针 tail 位置没有位置
    queue->tail = (queue->tail + 1) % queue->size;
    return 0;
}

/*dequeue*/
int array_queue_deque(array_queue * queue){
    int data;
    if(queue == NULL || arrary_queue_is_empty(queue))
        return -1;
    data = queue->array[queue->num];
    queue->num--;
    queue->head = (queue->head + 1) % (queue->size);
    return data;
}

/*dump the queue*/
void array_queue_dump(array_queue* queue){
    if(queue == NULL || arrary_queue_is_empty(queue))
        printf("\r\n queue is empty!");
    int pos = 0,i;
    printf("\r\n size:%d,num:%d,head:%d,tail:%d",queue->size,queue->num,queue->head,queue->tail);
    for(i=0;i<queue->num;i++){
        pos = (queue->head + i ) % queue->size;
        printf("\r\n array[%d] = %d",pos,queue->array[pos]);
    }
    return;
}

int main(){
    int size;
    int ret = 0;
    array_queue* queue;
    printf("please input the size:");
    scanf("%d",&size);
    queue = array_queue_create(size);
    if(queue == NULL){
        printf("\r\n queue created failed!");
        return 0;
   }

    for(int i=0;i<size;i++){
        ret = array_queue_enqueue(queue,i);
        if(ret == -1)
            printf("\r\n queue %d enqueue failed!",i);
    }

    array_queue_dump(queue);

    for(int i=0;i<2;i++){
        array_queue_deque(queue);
    }
    array_queue_dump(queue);
    array_queue_destroy(queue);
    return 0;
}