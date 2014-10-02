//https://www.hackerrank.com/challenges/is-fibo
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int IsFibo(unsigned long long  n)
{
	unsigned long long fn_2 = 0;
	unsigned long long fn_1 =1;
	unsigned long long fn =0;
    unsigned long long m ;
	int i = 0;
	if(n ==1 || n== 0 )
		return 1;
	else
	{
		
		
		do
		{
			fn= fn_2+fn_1;
			//printf("%ld  ",fn);
			
			if(fn > n  )
				break;
			else
			{
				if(fn == n)
					return 1;
				fn_2= fn_1;
				fn_1= fn;
				i++;
			}

		} while (1);
			
		
		
		return 0;
	}
}




int main()
{
    int i = 0,T, count =0;
	long long n ;
	
   // freopen("input.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
		scanf("%lld",&n);
		if(IsFibo(n))
			printf("IsFibo\n");
		else
			printf("IsNotFibo\n");

		
    }

    return 0;
}
