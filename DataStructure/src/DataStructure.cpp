//============================================================================
// Name        : DataStructure.cpp
// Author      : Do Minh Quan -- 11520616
// Version     :
// Copypos2   : Data Structure & Algorithms
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int ternary_search(int a[],int x,int pos1,int pos2,int n){

    if(pos1<0 || pos2>n-1 || pos1>pos2) {return -1;}
    if(x==pos1) {return pos1;}
    if(x==pos2) {return pos2;}

    if(x<pos1) {return ternary_search(a,x,pos1-1,pos2,n);}

    if(x>pos1 && x<pos2) {return ternary_search(a,x,pos1+1,pos2-1,n);}

    if(x>pos2) {return ternary_search(a,x,pos1,pos2+1,n);}

	return 0;
}
int main() {

	int array[]={0,3,5,6,7,8,12,14,15,16,20};
	int x;
	 cout << "Enter number for search:\n"; cin >> x;
	int size_array=sizeof(array);
    int pos1=size_array/3;
    int pos2=pos1*2;
    int result=ternary_search(array,x,pos1,pos2,size_array);
    cout << "Result :" <<result;
	return 0;
}
