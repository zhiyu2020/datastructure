#include<stdio.h>
#include<malloc.h>
//链表结构
//实现LRU算法
//实现单链表 
//循环链表 双链表
//双向链表
//双向循环链表
//写熟练以下操作
//单链表反转 链表中环的检测 两个有序的链表合并
//删除链表倒数n个结点  求链表的中间结点
/*
单链表实现需要的内容:
create , initial , find , delete
*/


// define the linked list
typedef struct Node{
    int data;
    struct Node* next;
} Node,* Linkedlist;

Linkedlist initialLinkedlist(){
    Linkedlist head;
    head = (Node *)malloc(sizeof(Node));
    // check whether we have enough space
    if(head == NULL){
        printf("apply for the space fail!");
    }
    head->next = NULL;// next -> null
    return head;
}
/*get foundamental element*/
void getElement(Linkedlist head,int i){
    Node* p = head;
    int j=0;
    if(head->next==NULL && i<j)
        return -1;
    while(j<i){
        p = p->next;
        j++;
    }
    printf("the element is:%d",p->data);
}
// insert the node from the head
void LinkedCreateHead(Node* head){
    int x;// input the data 
    //0 is the end of the list
    // while(scanf("%d",&x)!= EOF){
        //create a new node
    scanf("%d",&x);
    Node* node;
    node = (Node *)malloc(sizeof(Node));
    node->data = x;
    node->next=head->next;
    head->next = node;
    // }
    //return head;
}

//insert the node from tails
void LinkedCreateTail(Node* head){
    int x;// input the data
    Node* current;
    current = head;
    while(current->next!=NULL){
        current = current->next;
    }
    scanf("%d",&x);
    Node* new_node;
    new_node = (Node *)malloc(sizeof(Node));
    new_node->data = x;
    current->next = new_node;
    current = new_node;
    current->next = NULL;
}

//single linked list insert
void LinkedlistInsert(Linkedlist head,int pos,int element){
    Node * node = head;
    int i=0;
    for(;i<pos;i++){
        node = node->next;
    }// update to the final pos node
    Node* new_node;
    new_node = (Node*)malloc(sizeof(Node));
    new_node->data = element;
    new_node->next =node->next;
    node->next = new_node;
    //return head;
}
// single linked list delete element
void LinklistDelete(Node* L,int x){
    Node* pre,*cur;
    cur = L->next;// first node
    while (cur->data != x)// find the appointed node
    {
        pre = cur;
        cur = cur->next;
    }
    //delete the node
    pre->next = cur->next;
    free(cur);
   // return L;
}

//print the node
void printNode(Linkedlist head,int number){
    Node* print =head;
    print = print->next;//first node
    for(int i=0;i<number;i++){
        printf("%d ->",print->data);
        print = print->next;
    }
    printf("NULL\n");
}

// reverse the single list
int ListReserve(Linkedlist head){
    Linkedlist p,q;
    p = head->next;//fisrt node
    head->next = NULL;//set null head->null
    while(p){
        q = p;//q赋值为p
        p = p->next;
        //插入q
        q->next = head->next;
        head->next = q;
    }
    return 1;
}
// check the loop
int checkLoop(Linkedlist head){
    if(head == NULL || head->next == NULL)
        return 0;
    Linkedlist pFast = head;
    Linkedlist pSlow = head;
    while(pFast != NULL && pFast->next != NULL){
        pFast = pFast->next->next;
        pSlow = pSlow->next;// 快慢指针
        if(pFast == pSlow)
            return 1;
    }
    return 0;
}
//get the middle node
//fast slow node
Linkedlist getMidNode(Linkedlist head){
    if(head == NULL && head->next == NULL)
        return head;
    Linkedlist pFast = head;
    Linkedlist pSlow = head;
    while (pFast != NULL && pFast->next != NULL)
    {
        /* code */
        pFast = pFast->next->next;
        pSlow = pSlow->next;
    }
    printf("the middle node is : %d\n",pSlow->data);
    return pSlow;   
}
//merge two sorted linked lists
Linkedlist mergeNode(Linkedlist pNode,Linkedlist qNode){
    if(pNode == NULL && pNode->next == NULL) 
        return qNode;
    if(qNode == NULL && qNode->next == NULL)
        return pNode;
    Linkedlist p = pNode->next;
    Linkedlist q = qNode->next;
    Linkedlist resNode = (Linkedlist)malloc(sizeof(Node));
    resNode->next = NULL;// create head node return the head node
    //create a backup version
    Linkedlist r = resNode;
    while(p && q){
        if(p->data< q->data){
            r->next = p;
            r =p;
            p = p->next;
        }
        else
        {
            r->next = q;
            r = q;
            q = q->next;
        }
    }
    //the linked lists are not the same size
    if(p){
        r->next = p;
    }
    else
    {
        r->next =q ;
    }
    return resNode;
}

// delete No N element O(1)
Linkedlist removeNnode(Linkedlist head,int n){
    if(head == NULL && head->next == NULL)
        return head;
    Linkedlist prev = head;
    Linkedlist cur = head;
    for(int i=0;i<n;i++){
        cur = cur->next;
    }
    // judge the cur node 
    if(cur == NULL)
        return head->next;
    while(cur->next!= NULL){
        prev = prev->next;
        cur = cur->next;
    }
    prev->next = prev->next->next;
    return head;
}

int main(){
    Linkedlist p,q;
    p = initialLinkedlist();// head node
    q = initialLinkedlist();
    int Number,Number2;
    printf("please input the number for iteration for No1:");
    scanf("%d",&Number);// numbers 
    printf("please input the number for iteration for No2:");
    scanf("%d",&Number2);// numbers 
    printf("using head insert methods for No1!\n");
    for(int i=0;i<Number;i++){
        LinkedCreateTail(p);
    }
    printf("using tail insert methods for No2!\n");
    for(int i=0;i<Number2;i++){
        LinkedCreateTail(q);
    }
    printNode(p,Number);
    printNode(q,Number2);
    printf("\n");
    p = mergeNode(p,q);
    printNode(p,Number+Number2);
    printf("\n");
    ////////////////////////////////////////////////////
    int n;printf("please input the last N node to be deleted:\n");
    scanf("%d",&n);
    
    p = removeNnode(p,n);
    --Number;
    printNode(p,Number+Number2);
    ///////////////////////////////////////////////////////
    p = getMidNode(p);
    ////////////////////////////////////////////////
    // merge nodes

    //test loop linked list
    // printf("testing the loop in the linked list:\n");
    // int flag = checkLoop(p);
    // if(flag){
    //     printf("There is loop in the linked list\n");
    // }
    // else
    // {
    //     printf("no loop\n");
    // }
    
    // printf("please input the insert node pos:element:\n");
    // int pos,element;
    // scanf("%d %d",&pos,&element);
    // LinkedlistInsert(p,pos,element);
    // ++Number;

    // printNode(p,Number);
    // printf("\n");
    // printf("please input the delete number:\n");
    // int deletenum;
    // scanf("%d",&deletenum);
    // --Number;
    // LinklistDelete(p,deletenum);

    // printNode(p,Number);
    // printf("\n");
    // printf("reverse the linked list:\n");
    // ListReserve(p);
    // printNode(p,Number);
    // free 
    free(p);
    return 0;
}