//https://www.hackerrank.com/challenges/maximizing-xor
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
/*
 * Complete the function below.
 */
int XOR ( int a, int b)
{
	
	int n = log(a)/log(2) + 1;
	int i, res = 0;
	int p= 0;

	for(i =0; i<= n; i++)
	{
		p= pow(2,i);
		res+= p*((((a/p)%2)+((b/p)%2))%2);
	}
	return res;
}
int maxXor(int l, int r) {

	int i,j;
	int max = 0;
	int res;
	for( i = l ; i<= r; i++)
		for(j = i; j<=r;j++)
		{
			res=XOR(j,i);
			max = res>max?res:max;
		}

	return max;
}

int main() {
    int res;
    int _l;
    scanf("%d", &_l);
    
    int _r;
    scanf("%d", &_r);
    
    res = maxXor(_l, _r);
    printf("%d", res);
    
    return 0;
}
