//https://www.hackerrank.com/challenges/chocolate-feast

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int t, n, c, m;
    int w, n1, n2;
	int answer ; 
    scanf("%d", &t);
    while ( t-- )
    {
        scanf("%d%d%d",&n,&c,&m);
        answer = 0;
        /** Write the code to compute the answer here. **/
        w = n/c;
        answer += w;
        do{
        	n1 = w / m;
        	n2 = w % m ;
        	answer += n1;
        }
        while( (w= n1+n2) >=m);
        
        printf("%d\n",answer);
    }
    return 0;
}
