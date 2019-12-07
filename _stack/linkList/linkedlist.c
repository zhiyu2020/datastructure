#include <stdio.h>
#include <string.h>
#include<malloc.h>

typedef struct linkedstack{
    int data;
    struct linkestack* next;
} LinkedStack;

#define stack_is_empty(linkstack) (linkstack->next==NULL)


LinkedStack* create()
{
    //哨兵链表 有头链表
    LinkedStack* stack;
    stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    if(stack == NULL)
        return NULL;
    stack->next = NULL;
    return stack;
}

void stack_destroy(LinkedStack* head)
{
    LinkedStack* tmp,*q ;// the first node
    q = head;
    while (stack_is_empty(head))
    {   
        tmp = q;
        q = q->next;
        free(tmp);
    }
}

// 头插法进行链栈实现
int stack_push(LinkedStack* head,int data){
    LinkedStack * q;
    q = (LinkedStack*)malloc(sizeof(LinkedStack));
    if(q == NULL)   
    {
        return -1;
    }
    q->data = data;
    q->next = head->next;
    head->next = q;
    return 1;
}
// 返回值为 pop值
int stack_pop(LinkedStack* head){
    int data;
    LinkedStack* tmp;
    tmp = head->next;
    data = tmp->data;
    head->next = tmp->next;
    free(tmp);
    return data;
}

void stack_dump(LinkedStack* head){
    LinkedStack* tmp;
    tmp = head->next;
    while(tmp){
        printf("\r\n data = %d",tmp->data);
        tmp = tmp->next;
    }
}

int main(){
    int Number,ret=0;
    printf("\r\n please input the stack number:");
    scanf("%d",&Number);
    LinkedStack * stack;
    stack = create();
    for(int i=0;i<Number;i++){
        ret = stack_push(stack,i);
        if(ret != 1){
            printf("\r\n stack push %d failed!",i);
        }   
    }
    stack_dump(stack);
    
    stack_pop(stack);

    stack_dump(stack);
    stack_destroy(stack);
    return 0;
}



