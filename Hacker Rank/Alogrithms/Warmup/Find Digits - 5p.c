#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
//https://www.hackerrank.com/challenges/find-digits
//using namespace std;
long str2long(char *s)
{
    int i;
    long res = 0;
    for(i=0; i< strlen(s);i++)
	{
		res = res * 10 + (s[i] -'0');
	}
	return res;
    
}

int main()
{
    int i,T, count ;
    char s[11];
    long m;
    //freopen("input.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
		count = 0;
        scanf("%s",s);
		m = str2long(s);
		for(i = 0; i<strlen(s); i++ )
		{
			if(!(s[i] == '0') && !(m %(s[i]-'0')))
				count++;
		}
		printf("%d\n",count);   
    }
    return 0;
}
