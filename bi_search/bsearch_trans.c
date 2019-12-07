#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

/*二分查找算法的变形问题
 *1、查找第一个等于给定数值的元素
 *2、查找最后一个等于给定数值的元素
 *3、查找第一个大于等于给定数值的元素
 *4、查找第一个小于等于给定数值的元素
 */

//1、查找第一个等于给定数值的元素
int bisearch_1(int a[],int size,int value){
    int hi = size-1,lo = 0;
    while(lo<=hi){
        int mid = lo + ((hi-lo)>>1);
        if(a[mid] > value) hi = mid-1;
        else if(a[mid] < value) lo = mid + 1;
        else{
            if(mid == 0 || a[mid-1] != value)
                return mid;
            else 
                hi = mid - 1;
        }
    }
    return -1;
}

// 2、查找最后一个等于给定数值的元素
int bisearch_2(int a[],int size,int value){
    int hi = size-1,lo = 0;
    while(lo<=hi){
        int mid = lo + ((hi-lo)>>1);
        if(a[mid] > value) hi = mid -1;
        else if(a[mid] < value) lo = mid +1;
        else {
            if((mid == size-1) || a[mid + 1] != value)
                 return mid;
            else 
                lo = mid +1 ;
        }
    }
}
// *3、查找第一个大于等于给定数值的元素
int bisearch_3(int a[],int size,int value){
    int hi = size-1,lo = 0;
    while(lo<=hi){
        int mid = lo + ((hi -lo)>>1);
        if(a[mid]<value) lo = mid+1;
        else{
            if(mid == 0 || (a[mid-1] < value))
                return mid;
            else
                hi = mid -1;
        }
    }
    return -1;
}

// *4、查找第一个小于等于给定数值的元素
int bisearch_4(int a[],int size,int value){
    int hi = size-1,lo = 0;
    while(lo<=hi){
        int mid = lo + ((hi -lo)>>1);
        if(a[mid]> value) hi = mid -1;
        // <= from back to front num
        else{
            if(mid == size-1 || a[mid + 1] > value) 
                return mid;
            else 
                lo = mid +1;
        }
    }    
    return -1;
}

int main()
{
	int a[10] = {5,6,6,9,10,11,11,22,33,33};
    int data = 0;
	int i = 0;
	int res =0;

	printf("\r\n");
    for(i = 0; i < 10 ; i++)
	{
		printf("%d ",a[i]);
	}
	printf("\r\n");
	printf("\r\n输入一个整数");
	scanf("%d",&data);
    res = mybsearch_1(a,10,data);
	printf("第一个等于data[%d]，下标是%d",data,res);
	
	printf("\r\n输入一个整数");
	scanf("%d",&data);
    res = mybsearch_2(a,10,data);
	printf("最后一个等于data[%d]，下标是%d",data,res);

	printf("\r\n输入一个整数");
	scanf("%d",&data);
    res = mybsearch_2(a,10,data);
	printf("第一个大于等于data[%d]，下标是%d",data,res);

	printf("\r\n输入一个整数");
	scanf("%d",&data);
    res = mybsearch_2(a,10,data);
	printf("第一个小等于data[%d]，下标是%d",data,res);
	return;
}









