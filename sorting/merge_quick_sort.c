#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>

/*merge sort*/
void merge_sort(int a[],int size){
    __merge_sort(a,0,size-1);
}

void __merge_sort(int a[],int start,int end){
    int mid;
    if(start>=end) return;
    mid = (start+end)/2;
    __merge_sort(a,start,mid);
    __merge_sort(a,mid+1,end);
    __merge(a,start,mid,end);
}

void __merge(int a[],int start,int mid,int end){
    int * tmp = (int*)malloc(sizeof(int)*(end-start+1));
    if(!tmp) return;
    int i= start, j = mid+1, index = 0;
    while(i<=mid && j<= end){
        if(a[i]>a[j]){
            tmp[index++] = a[j++];// 将字母顺序排到tmp文件里面
        }else
        {
            tmp[index++] = a[i++];
        }
    }
    //还有剩余部分
    while(i<=mid){
        tmp[index++] = a[i++];
    }
    while(j<=end){
        tmp[index++] = a[j++];
    }
    //拷贝排序位置
    memcpy(a+start,tmp,sizeof(int)*(end-start+1));// a+start: a的首地址 + 排序开始位置 
    free(tmp);
}

void dump(int a[],int size){
    for(int i=0;i<size;i++){
        printf("%d ",a[i]);
    }
    printf("\r\n");
}

void merge_test(){
	int test[10] = {5, 8, 9, 23, 67, 1, 3, 7, 31, 56};

	merge_sort(test, 10);
    dump(test,10);
}
/*quick sort*/
void quick_sort(int a[],int size){
    _quick_sort(a,0,size-1);
}

void _quick_sort(int a[],int start,int end){
    if(start>end) return;
    int pivot = partition(a,start,end);
    _quick_sort(a,start,pivot-1);
    _quick_sort(a,pivot+1,end);
}

int partition(int a[],int start,int end){
    // generate value [start,end]
    int new_value = (rand()%(end - start + 1))+start;
    int pivot_value= a[new_value];
    swap(a,new_value,end);// exchange to the end pos
    int savedIdx = end;// save the last idx
    end--;// before pos

    while(start<=end){
        if(a[start] > pivot_value){
            swap(a,start,end);
            end--;
        }else
        {
            start++;
        }
    }
    swap(a,start,savedIdx);
    return start;
}

void swap(int a[],int low,int hi){
    int temp = a[low];
    a[low] = a[hi];
    a[hi] = temp;
}

void quick_test(){
	int test[10] = {5, 8, 9, 23, 67, 1, 3, 7, 31, 56};

	quick_sort(test, 10);
    dump(test,10);
}

int main(){
    quick_test();
    // for(int i=0;i<50;i++){
    //     int a = rand() % 15 + 2;
    //     printf("\r\n a:%d",a);
    // }
    return 0;
}