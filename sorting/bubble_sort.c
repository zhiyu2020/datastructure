#include<stdio.h>
#include<stdlib.h>

/*冒泡排序*/
void bubbleSort(int a[],int n){
    if(n<=1) return;
    //flag 提前退出循环
    int flag = 0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                flag = 1;
            }
        }
        if(!flag) break;//没有数据交换 已经有序 提前退出
    }
}
/*插入排序*/
void insertionSort(int a[],int n){
    if(n<=1) return;
    for(int i=1;i<n;i++){//需要插入元素的个数 
        int value = a[i];//保存插入的元素数据
        int j = i-1;//set j 
        for(;j>=0;j--){// find the location which need to move
            if(a[j]>value) a[j+1] = a[j];// move 
            else break;
        }
        a[j+1] = value;//insert data
    }
    return;
}

/**选择排序*/
void selection_sort(int a[],int size){
    int i = 0,j = 0, min = 0;
    for(i=0;i<size-1;i++){
        min = i;
        for(j=i+1;j<size;j++){
            if(a[j]<a[min])
                min = j;
        }
        if(min != i)//enhance productivity
        {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
    return;
}

void dump(int a[],int size){
    int i = 0;
    printf("\r\n");
    for(i=0;i<size;i++){
        printf("%d ",a[i]);
    }
    printf("\r\n");
    return;
}

int main(){
    int a[10] = {9,11,4,15,16,3,20,44,5,10};
    bubbleSort(a,10);
    // insertionSort(a,10);
    //selection_sort(a,10);
    dump(a,10);
    return 0;
}