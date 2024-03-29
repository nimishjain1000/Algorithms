#include <stdio.h>
#include <iostream>
#include <array>

using namespace std;
 int TrinarySearch(int a[], int n, int f);
int main() 
{
	//int a[] = {1,2,3,4,5,6,7,8,9,10};
	//int a[] = {1,2,3,4,5,6,7,8,9};
	//int a[] = {1,2,3,4,5,6,7,8,9,10,11};
	//int a[] = {1,3,4,5,7,8,9,10};
	//int a[] = {1,2,4,5,7,11,22,33,38,40,46,47};
	//int a[] = {1,2,8,9,10,11,15,19,20,23,29,30,32,35,47,90};
	int a[] = {3,4};
	//int a[] = {};

	int arraySize = sizeof(a)/sizeof(*a);
	int i = TrinarySearch(a,arraySize,3);
	printf("%d\n",i);
	if(i>=0)
		printf("%d\n",a[i]);


}

int TrinarySearch(int a[], int n, int f)
{
	int gap = n / 3;
	int start,end,left, right;
	if(gap <1)
	{
		start = left = 0;
		right = end = n-1;
	}
	else{
	start = 0;
	end = n-1;
	left = gap;
	right = gap*2;
	}
	while(left < right)
	{
		gap /= 3;
		if(f > a[right])
		{
			start = right ;
			left = start + gap;
			right = left + gap;
		}
		else if( f < a[left] )
		{
			end = left;
			left = start + gap;
			right = left + gap;


		}
		else if(f > a[left] && f < a[right]) 
		{
			start = left;
			end = right;
			left = start + gap;
			right = left + gap;
		}
		else if( f== a[left])
			return left;
		else if(f == a[right])
			return right;
	}

	return -1;
	


}
