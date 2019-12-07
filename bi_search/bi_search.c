#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

/*normal Bi_search*/
int bi_search(int a[],int size,int value){
    int hi = size-1, lo = 0;
    while(lo<=hi){
        int mid = lo + (hi - lo) /2;
        if(a[mid] == value) return mid;
        else if(a[mid] > value)  hi = mid -1;
        else lo = mid + 1;
    }
    return -1;
}

/* recursion realize*/
int helper(int a[],int lo,int hi,int value){
    int mid = 0;
    if (lo > hi) return -1;
    mid = lo +((hi-lo)>>1);
    if(a[mid]==value) return mid;
    else if(a[mid]>value) return helper(a,lo,mid-1,value);
    else return helper(a,mid+1,hi,value);
    return -1;
}

int bi_search_recursion(int a[],int size,int value){
    return helper(a,0,size-1,value);
}

int main(){
    int a[10] ={5,6,8,9,10,11,23,42,53,123};
    int get_value = 0;
    int res = 0;
    printf("\r\nplease input a number:");
    scanf("%d",&get_value);
    //res = bi_search(a,10,get_value);
    res = bi_search_recursion(a,10,get_value);
    printf("data[%d] %s在数组中",get_value,(res != -1)?" ":"不");
    if(res != -1){
        printf("下标是 %d",res);
    }
    return 0;
}


