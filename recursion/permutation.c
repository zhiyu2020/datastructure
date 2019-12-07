#include<stdio.h>
#include<string.h>

void swap(int A[],int a,int b){
    int temp;
    temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}
void printAll(int A[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",A[i]);
    }
    printf("\n");
}
//去重的全排列 需要判断 交换元素是否相同
int isSwap(int A[],int start,int end){
    for(int i=start;i<end;i++){
        if(A[end] == A[i]) return 0;//判断每个元素是否和end相等
    }
    return 1;
}
void permutation(int A[],int start,int end){
    if(start == end) printAll(A,end+1);
    else{
            for (int i = start; i <= end; i++)
            {
                if(isSwap(A,start,i)){//check 去重全排列
                    swap(A,i,start);//swap(A[i],A[0]) 错误 如果A[0] 只有一个结果 1 2 3
                    permutation(A,start+1,end);//[start+1,end]之间进行全排列
                    swap(A,i,start);//swap(A[i],A[0])                   
                }

            }
        }  
}


int main(){
    int A[4] = {1,2,2,3};
    permutation(A,0,3);
    return 0;
}