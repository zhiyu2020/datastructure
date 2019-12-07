#include<stdio.h>
#include<stdlib.h>
#define LEN(tree) sizeof(tree)/ sizeof(tree[0])

static int m_heap[50];
static int m_capacity = 50;
static int m_size = 0;



void swap(int arr[],int i,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
//minheap 
void heapify_min(int tree[],int n,int i){// i -> index
    // 忘记了返回递归终止条件
    if(i>=n) return;
    int c1 = 2*i+1;
    int c2 = 2*i+2;
    int min = i;
    if(c1<n && tree[min]>tree[c1]) min = c1; // c1< n 
    if(c2<n && tree[min]>tree[c2]) min = c2;
    //swap
    if(min != i){
        swap(tree,min,i);
        heapify_min(tree,n,min);
    }
}
// maxheap 
void heapify(int tree[],int n,int i){
    if(i>=n) return ;
    int c1 = 2*i + 1;
    int c2 = 2*i + 2;
    int max = i;
    // get p c1 c2中最大元素
    if(c1 < n && tree[c1]>tree[max]) max = c1;
    if(c2 < n && tree[c2]>tree[max]) max = c2;
    //max <--> i
    if(max != i){
        swap(tree,max,i);
        heapify(tree,n,max);// 继续递归堆化
    }
}
// 如果所有都是乱序 构建堆 最底层父亲节点开始 倒序做heapify 从后往前做heapify
//知道树的最后节点
void build_heap(int tree[],int n){
    int last_node = n-1;
    int parent = (last_node-1)/2;
    for(int i=parent;i>=0;i--){
        heapify(tree,n,i);
    }
}
//root <--> last / 砍断 last / heapify from root
void sort_heap(int tree[],int n){
    build_heap(tree,n);
    //from last
    for(int i=n-1;i>=0;i--){
        swap(tree,i,0);
        heapify(tree,i,0);
    }
}
//从heap中插入元素 
void heap_insert(int* tree,int data){
    if(m_size>=m_capacity) return;
    ++m_size;
    (tree[m_size-1]) = data;
    int i = m_size-1;
    while( (i-1)/2>0 && tree[i]<tree[(i-1)/2]){
        swap(tree,i,(i-1)/2);
        i = (i-1)/2;
    }
    //build_heap(tree,m_size);
}

//删除堆头 O(1)
int heap_delete(int tree[],int n){
    if(m_size == 0) return -1;
    tree[0] = tree[--m_size];
    heapify(tree,m_size,0);
}

int main(){
    int tree[50] = {3,2,6,8,10};
    int tree2[] = {12,11,23,15,18};
    int tree2_len = 5;
    m_size = 5;
    build_heap(tree,m_size);
    // for(int i=0;i<len;i++){
    //     printf(" %d",tree2[i]);
    // }
    // printf("\r\n---------------------");
    // printf("the max heap show");
    // printf("-------------------------\r\n");
    // for(int i=0;i<m_size;i++){
    //     printf(" %d \n",tree[i]);
    // }    
    printf("\r\n----------------------------\r\n");
    /*start to insert into the heap*/
    printf("start to insert heap elements !");
    for(int i=0;i<tree2_len;i++){
        printf("\r\n%d ",tree2[i]);
        heap_insert(tree,tree2[i]);
    }
    printf("\r\n-------------------------\n");
    for(int i=0;i<m_size;i++){
        printf(" %d \n",tree[i]);
    }  
    printf("\r\n-----delete--------------\n");
    heap_delete(tree,m_size);
    for(int i=0;i<m_size;i++){
        printf(" %d \n",tree[i]);
    }    
    return 0;
}