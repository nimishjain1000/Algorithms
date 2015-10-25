//https://www.hackerrank.com/challenges/utopian-tree

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int T, n, m,i;
    
    scanf("%d",&T);
    while(T--){
    	m=1;	
        scanf("%d\n",&n);
        if(n == 0)
            printf("1\n");
        else
            {
            for(i = 1 ; i<=n ; i++)
            {
            	if(i%2)
            	m*=2;
            	else
            	m+=1;
            		
            }
            printf("%d\n",m);
            
        }
        
        
    }
        
        
    return 0;
}
