//https://www.hackerrank.com/challenges/service-lane/submissions/code/10169614
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 100000

 

int main()
{
	int N, T;
	int a[MAX] ;
	int k;
	int i, j;
	int min;
   // freopen("input.txt","r",stdin);
	scanf("%d %d",&N,&T);
	for(k = 0; k<N ; k++)
		scanf("%d",&a[k]);

	while(T--)
	{
		min = 4;
		scanf("%d %d",&i,&j);
		for(;i <= j; i++)
		{
			if(a[i] < min)
			{
				min = a[i];
			}
		}
		printf("%d\n",min);
	}
	
    return 0;
}
