// https://www.hackerrank.com/challenges/the-love-letter-mystery
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX 100000

 

int main()
{
	int T;
	char a[MAX];
	int n,i;
	int count ;
   // freopen("input.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		count = 0;
		scanf("%s",a);
		 n = strlen(a);
		 for(i = 0 ; i< n /2; i++)
		 {
			 if(a[n-i-1] < a[i])
			 {
				 count+=(a[i] - a[n-i-1]);
			 }
			 else
			 {
				 count += (a[n-i-1]-a[i]);
			 }
			 
		 }
		 printf("%d\n",count);
	}
	
    return 0;
}
