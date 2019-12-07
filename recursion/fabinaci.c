#include<stdio.h>

int fab(int n){
    if(n==1) return 1;
    else if(n==2) return 2;
    else
        return fab(n-1) + fab(n-2);
}

int main(){
    int n;
    printf("\r\n please input the size :[n<=30]");
    scanf("%d",&n);
    int result = 0;
    result = fab(n);
    printf("\r\n the result of fab is %d",result);
    return 0;
}