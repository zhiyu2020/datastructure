#include<stdio.h>

int jiecheng(int n){
    if(n==1) return 1;
    else 
        return n*jiecheng(n-1);
}

int main(){
    int n;
    printf("\r\n please input the size :[n<=30]");
    scanf("%d",&n);
    if(n>30) return 0;
    int result = 0;
    result = jiecheng(n);
    printf("\r\n the result of jiecheng is %d",result);
    return 0;
}