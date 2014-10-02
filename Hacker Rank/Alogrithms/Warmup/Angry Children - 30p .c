//https://www.hackerrank.com/challenges/angry-children/submissions/code/10166659
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX 100000
#define MAX_VAL 1000000001

long long candies[MAX];

 int  compare_longs (const void *a, const void *b)
{
  const long long  *da = (const long long *) a;
  const long long  *db = (const long long *) b;

  return (*da > *db) - (*da < *db);
}

 

int main()
{
	long long  unfairness;
	long long  min = 99999999;
	int N,K;
    int i;
    //freopen("input.txt","r",stdin);
	scanf("%d %d",&N,&K);
    for(i = 0;i < N;i++)
        scanf("%lld",&candies[i]);
	qsort(candies,N,sizeof(long long),compare_longs);
	for( i= 0 ;i <= N - K ; i++)
		{
			unfairness= candies[ i + K-1] - candies[i];
			if(unfairness < min)
				min = unfairness;
	}

	//for(i = 0;i < N;i++)
      //  printf("%lld\n",candies[i]);

	
  
   
    // Compute the min unfairness over here, using N,K,candies
        
    printf("%d\n",min);
    return 0;
}
