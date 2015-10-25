//https://www.hackerrank.com/challenges/halloween-party
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    long long T,k;
	long long n,m;
	scanf("%lld",&T);
	while (T--)
	{
		scanf("%lld",&k);
		n=m= k/2;
		m = k%2?m+1:m;
		printf("%lld\n",n*m);
	}
    
    return 0;
}
