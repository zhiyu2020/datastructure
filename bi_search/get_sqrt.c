#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#define E 1e-6

double get_sqrt(double num){
    double start = 0.0;
    double end = num;
    double mid = start + (end-start)/2;
    while (fabs(mid*mid - num)>E)
    {
        mid = start + (end - start)/2;
        if(mid * mid > num) end = mid;
        else if(mid*mid < num) start = mid;

    }
    return mid;
}

int main()
{
	double num = 0.0;

	/*这里需要注意：double的输入方式*/
	scanf("%lf",&num);
	printf("\r\nnum %lf的平方根是%lf",num,get_sqrt(num));

	return 0;
}