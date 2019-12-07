#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct array_stack{
    int size;/*栈大小*/
    int pos;/*栈顶元素pos*/
    int *array;/*数据存储区*/
}stArrayStack;

#define arrayStack_size(arraystack) (arraystack->size)
#define arrayStack_is_empty(arraystack) (arraystack->pos == -1)
#define arrayStack_is_full(arraystack) (arraystack->pos == (arraystack->size -1))

/*create and initialize the array stack*/
stArrayStack* arraystack_create(int size){
    stArrayStack* stack ;
    // allocate dynamic space
    stack = (stArrayStack*)malloc(sizeof(stArrayStack));
    // judge whether the space is allocated
    if(stack == NULL){
        return NULL;
    }
    // initialize the space
    stack->size = size;
    stack->pos = -1;// no element in the stack
    stack->array = (int*)malloc(sizeof(int)*size);
    //check whether the array is allocated with space
    if(stack->array == NULL){
        free(stack);
        return NULL;
    }
    return stack;
}

/*delete the order stack*/
/*free array first then free stack*/
void arraystack_destroy(stArrayStack* stack){
    //check whether the stack is empty
    if(stack == NULL)
        printf("the stack is already is empty");
    if(stack->array != NULL)
        free(stack->array);
    free(stack);
}

/*pop stack*/
int arrayStack_pop(stArrayStack* stack){
    int data = 0;
    if(arrayStack_is_empty(stack))
        return -1;
    data = stack->array[stack->pos];
    stack->pos--;
    return data;
}

/*push stack*/
int arrayStack_push(stArrayStack* stack,int data){
    if(arrayStack_is_full(stack))
        return -1;
    //push stack
    stack->pos++;
    stack->array[stack->pos] = data;
    return 1;
}

/*special situation: dynamic enlarge space*/
int arrayStack_push_new(stArrayStack* stack,int data){
    if(!arrayStack_is_full(stack)){
        return arrayStack_push(stack,data);
    }
    else
    {
        //enlarge the space dynamically not stack
        int* tmp;
        tmp = (int*)malloc(sizeof(int)*2*stack->size);
        if(tmp == NULL)
            return -1;
        memcpy(tmp,stack->array,stack->size*sizeof(int));
        //free the original space
        free(stack->array);
        // new operations
        stack->array = tmp;
        stack->size *= 2;
        stack->pos ++;
        stack->array[stack->pos] = data;
        return 1;
    }
}

/*dump the whole stack*/
void arrayStack_dump(stArrayStack* stack){
    int i = 0;
    if(arrayStack_is_empty(stack))
        printf("the stack is empty!\n");
    printf("\r\n stack size is %d, stack pos is %d",stack->size,stack->pos);
    for(;i<=stack->pos;i++){
        printf("\r\n arrary[%d] = %d",i,stack->array[i]);
    }
}

int main(){
    stArrayStack * stack = NULL;
    printf("\r\n create 4 size stack:");
    int ret = 0;
    stack = arraystack_create(4);
    if(stack == NULL){
        printf("\r\n create 4 size arraystack failed!");
    }
    for(int i = 0; i < 5; i++)
    {
        ret = arrayStack_push(stack,i);
        if(ret == -1){
            printf("\r\n push size = %d arraystack failed!",i);
        }
    }

    arrayStack_dump(stack);

    ret = arrayStack_push_new(stack,4);
    if(ret != 0){
        printf("\r\n push size = %d arraystack failed",4);
    }
    arrayStack_dump(stack);

    arraystack_destroy(stack);
    return 0;
}