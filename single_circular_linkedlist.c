#include<stdio.h>
#include<malloc.h>

typedef struct Node{
    int data;
    struct Node * next;
}Node,* Linkedlist;

void InitList(Linkedlist head){
    head = (Linkedlist)malloc(sizeof(Node));
    head->next = head; // 指向head
    if(head  == NULL){
        printf("memory allocate failed!\n");
    }
    head->data = 0;
}

void createList(Linkedlist head){
    int length;
    printf("please input the length of the linked list");
    scanf("%d",&length);
    Linkedlist new_node,tail;
    tail = head;
    printf("please input data:");
    for(int i=1;i<=length;i++){
        new_node = (Linkedlist)malloc(sizeof(Node));
        if(new_node == NULL)
            printf("the memory allocation failed!");
        int x;
        scanf("%d",&x);
        new_node->data =x ;
        new_node->next = head;//must be the head,the final node is linked to the head
        tail->next = new_node;
        tail = new_node;
    }
}

void printLinkedlist(Linkedlist head){
    Linkedlist p = head->next;
    printf("print the linked list!\n");
    while(head->next){
        printf("%d ->",p->data);
    }
    printf("%d",head->data);
}
int GetLen(Linkedlist head){
    int length = 0;
    Linkedlist p = head->next;
    while(p->next!=head){
        length++;
        p = p->next;
    }
    return length;
}

//insert node to the linked list
void InsertNodetSCcLinklist(Linkedlist head,int pos,int data){
    Linkedlist new_node,p = head;
    pos = pos<0? 0:pos;
    //尾插法实现
    int j=0;
    while(j<pos){
        p = p->next;
        j++;
    }
    new_node = (Linkedlist)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = p->next;
    p->next = new_node;
}

void DeleteNode(Linkedlist head,int pos){
    Linkedlist cur,prev;
    cur = head->next;
    int j = 1;
    if (pos>GetLen(head) || pos<0){
        printf("input pos is wrong!");
        exit();
    }
    if(pos<GetLen(head)){
        while(j<pos){
            prev = cur;
            cur = cur->next;
            j++;
        }
        prev->next = cur->next;
        free(cur);
    }    
}

