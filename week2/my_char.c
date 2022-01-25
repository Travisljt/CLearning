/*#include<stdio.h>

int main()
{
    
    int a;
    a = 2147483647;
    printf("%d",a);
    char c;
    while ((c=getchar())!=EOF)
    {
        putchar(c);
        putchar(c);
        
    }
    putchar('\n');
    
    return 0;
}
*/


#include <stdio.h>
#include <stdlib.h>
 
#define N 1000000//定义范围小于50000
int hailstone(int i)//函数为了计算雹石序列并返回长度值
{
	int length=1;
 
	while(i!=1)//得到雹石序列
	{
		length++;
		if (i%2==0)
		{
			i=i/2;
		}
		else
		{
			i=3*i+1;
		}
	
	}
	return length;
}
 
int hailstonemax(int i)//函数计算雹石序列并返回长度值
{
	int max=1;
	while(i!=1)//得到雹石序列
 
	{
		if (i%2==0)
		{
			i=i/2;
		}
		else
		{
			i=3*i+1;
		}
		if(i>max)
		{
			max=i;
		}
	
	}
	return max;
}
 
int main( )
{
    int j,n,num,jnum,nummax=1,max=0,jmax;
	for(j=1;j<N;j++)
	{
	
	
		n=hailstone(j);
		if(max<n)//比较不同序列的长度
		{
			max=n;//最长的雹石序列
			jmax=j;//最长雹石序列所对应的初始数字
		}
		
		
		num=hailstonemax(j);
		if(nummax<num)
		{
			nummax=num;//雹石序列中的最大数字
			jnum=j;//雹石序列中最大数字所对应的初始数字
		}
 
	}
	
	 printf("最长的雹石序列的长度是 %d 初始数字是%d.\n", max, jmax);
	 printf("最大的雹石序列是%d 对应的初始数字是 %d.\n", nummax, jnum);
	
	return 0;
}
