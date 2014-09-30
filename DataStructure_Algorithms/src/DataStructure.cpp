//============================================================================
// Name        : DataStructure.cpp
// Author      : Do Minh Quan -- 11520616
// Email       : dominhquan.uit@gmail.com
// Mail GV     : phongtn@uit.edu.vn
// Type        : Data Structure & Algorithms
// Description : C++, ANSI-style
//============================================================================

#include <iostream>
using namespace std;

/*
 * Ternary Search Recursive
 * @params
 */
int TernarySearch_Recursive(int a[],int x,int pos1,int pos2,int n){

//    if(pos1<0 || pos2>n-1 || pos1>pos2) {return -1;}
//    if(x==pos1) {return pos1;}
//    if(x==pos2) {return pos2;}
//
//    if(x<pos1) {return ternary_search(a,x,pos1-1,pos2,n);}
//
//    if(x>pos1 && x<pos2) {return ternary_search(a,x,pos1+1,pos2-1,n);}
//
//    if(x>pos2) {return ternary_search(a,x,pos1,pos2+1,n);}

	return 0;
}
/**
 * Ternary Search Increase
 * @params a[],n,x
 */
int TernarySearch(int a[], int n, int x){
	int left, right;
	int start=0;
	int end=n-1;
	int point = n / 3;     // Find the split point.
		if(point <1){
			left = 0;
			right = n-1;
		}else{
			left = point;
			right = point*2;
		}
		while(left <= right)	{
			point /= 3;
			if(x > a[right]){
				start = right ;
				left = start + point;
				right = left + point;
			}else if( x < a[left] ){
				end = left;
				left = start + point;
				right = left + point;
			}else if(x > a[left] && x < a[right]){
				start = left;
				end = right;
				left = start + point;
				right = left + point;
			} else if( x== a[left]) {return left;}
			  else if(x == a[right]) {return right;}
		}
	return -1; // Not found !!
}
/*
 * Binary Search Extend - N
 * @params
 */
int NSearch(int a[],int n, int x,int type){
	int start=0;
	int end=n-1;
	int split_point=n/type;
	return -1;
}
/**
 * Main method
 */
int main() {

	/*
	 * Some test case.
	 */

//		int a[]= {};
//		int a[]= {1};
//		int a[]= {1,2};
//		int a[]= {1,2,3};
//		int a[]= {1,2,3,4};
//		int a[] = {1,2,3,4,5,6,7,8,9,10};
//		int a[] = {1,2,4,5,7,11,22,33,38,40,46,47};
		int a[] = {1,2,8,9,10,11,15,19,20,23,29,30,32,35,47,90};
		int arraySize = sizeof(a)/sizeof(*a);
		int x;cout << "Enter number for search:\n"; cin >> x;
		int i = TernarySearch(a,arraySize,x);
		if(i>=0){
			cout << "Found at :"<< i<<endl;
		}else{
			cout << "Not found !";
		}
		return 0;
}
