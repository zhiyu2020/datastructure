#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

void count_sort(int a[], int size){
    //count_sort 
    //1.先生成一个大小为max+1的空间 用于count[下标为数字]
    //2.将count 进行累加
    //3.重新生成一个空间res[size]用于排序 倒序遍历a 将其放再res
    //4.拷贝到a后 free
    int* count;
    int max = 0;
    for(int i=0;i<size;i++){
        if(max<a[i])
            max = a[i];
    }
    // count is used to store the time of numbers
    count = (int*)malloc(sizeof(int)*(max+1));
    memset(count,0,sizeof(int)*(max+1));//init the value
    // take result of a[] as the index of count[]
    for(int i=0;i<size;i++){
        count[a[i]]++;
    }
    //add the count value
    for(int i=1;i<=max;i++){
        count[i] += count[i-1];
    }
    // realloc the new space res
    int * res = (int*)malloc(sizeof(int)*(size));
    for(int i=size-1;i>=0;i--){
        res[count[a[i]]-1] = a[i];// 
        count[a[i]]--;// count[num] need to reduce the value
    }

    memcpy(a,res,sizeof(int)*size);
    free(res);
    free(count);
    return;
}

/*基数排序*/
//先低位后高位
//思路需要用到计数排序
int get_max(int a[],int size){
    int i,max;
    max = a[0];
    for(i = 0;i<size;i++){
        if(max<a[i])
            max = a[i];
    }
    return max;
}
/*
对数组按照某个位数进行排序
参数说明:
    a-- 数组
    size -- 长度
    exp 指数 对数组a按照该指数进行排序
*/
void count_sort_for_radix(int a[],int size,int exp){
    int* count = (int*)malloc(sizeof(int)*10);
    memset(count,0,sizeof(int)*(10));//0-9
    int* result = (int*)malloc(sizeof(int)*size);
    //count the 个位-十位...
    for(int i=0;i<size;i++){
        count[(a[i]/exp)%10]++;
    }
    //add the number
    for(int i=1;i<10;i++){
        count[i] += count[i-1];
    }
    //将数据存储到临时数组中去
    for(int i=size-1;i>=0;i--){
        result[count[(a[i]/exp)%10]-1]=a[i];
        count[(a[i]/exp)%10]--;
    }

    memcpy(a,result,sizeof(int)*size);
}

void radix_sort(int a[],int size){
    int exp;
    int max = get_max(a,size);
    for(exp=1;max/exp>0;exp*=10){//max/exp>0 can't = 0 otherwise the code blocks
        count_sort_for_radix(a,size,exp);
    }
}
/*
桶排序:
*/
void bucket_sort(int a[],int size){
    int max = get_max(a,size);
    int* buckets = (int*)malloc(sizeof(int)*(max+1));

    int i=0,j=0;
    for(i=0;i<size;i++){
        buckets[a[i]]++;
    }
    //sort: [0,max]
    for(i=0,j=0;i<max;i++){
        while(buckets[i]-->0)
            a[j++] = i;
    }
    free(buckets);
}


int main(){
    int i;
    int a[] = {53, 3, 542, 748, 14, 214, 154, 63, 616,955};
    //int ilen = strlen(a);
    printf("\r\n before sort:");
    for(i=0;i<10;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    //radix_sort(a,10);
    count_sort(a,10);
    //bucket_sort(a,10);
    printf("after count sort:\n");
    // printf("after radix sort:\n");
    for(i=0;i<10;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}