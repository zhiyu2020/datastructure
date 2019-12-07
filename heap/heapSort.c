#include<stdio.h>
#include<stdlib.h>



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

void heapify2(int tree[],int n,int i){
    while(i<n){
        int c1 = 2*i + 1;
        int c2 = 2*i + 2;
        int max = i;
        // get p c1 c2中最大元素
        if(c1 < n && tree[c1]>tree[max]) max = c1;
        if(c2 < n && tree[c2]>tree[max]) max = c2;
        //max <--> i
        if(max != i){
            swap(tree,max,i);
            i = max;
        }
        else break;
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


int main(){
    int tree[] = {4,10,3,5,1,2};
    int n = 6;
    // build_heap(tree,n);
    build_heap(tree,n);
    for(int i=0;i<n;i++){
        printf(" %d \n",tree[i]);
    }
    return 0;
}