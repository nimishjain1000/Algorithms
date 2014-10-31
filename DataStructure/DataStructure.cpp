////============================================================================
//// Name        : DataStructure.cpp
//// Author      : Do Minh Quan -- 11520616
//// Email       : dominhquan.uit@gmail.com
//// Mail GV     : phongtn@uit.edu.vn
//// Type        : Data Structure & Algorithms
//// Description : C++, ANSI-style
////============================================================================
//
//#include <iostream>
//using namespace std;
//
///**
// * Ternary Search Increase.
// * @params a[],n,x
// * @return :
// * 				+ Not found(-1).
// * 				+ Found (location in array).
// */
//int TernarySearch(int a[], int n, int x){
//	int left, right;
//	int start=0;
//	int end=n-1;
//	int point = n / 3;     // Find the split point.
//		if(point <1){
//			left = start;
//			right = end;
//		}else{
//			left = point;
//			right = point*2;
//		}
//		while(left <= right)	{
//			point /= 3;
//			if(x > a[right]){
//				start = right ;
//				left = start + point;
//				right = left + point;
//			}else if( x < a[left] ){
//				end = left;
//				left = start + point;
//				right = left + point;
//			}else if(x > a[left] && x < a[right]){
//				start = left;
//				end = right;
//				left = start + point;
//				right = left + point;
//			} else if( x== a[left]) {return left;}
//			  else if(x == a[right]) {return right;}
//		}
//	return -1; // Not found !!
//}
///*
// * Binary Search Extend - N
// * @params
// */
//int NSearch(int a[],int n, int x,int type){
//	int start=0;
//	int end=n-1;
//	int split_point = n/type;
//	int compare_point; // 1st compare point
//	while(start<=end){
//		while(split_point>=1){
//			int *list_of_compare_point=new int[n];
//				int count_list=0;
//				while(compare_point<=end-split_point){
//					list_of_compare_point[count_list]=compare_point;
//					compare_point+=split_point;
//					count_list++;
//				}
//				for(int i=count_list-1;i>0;i--){
//					if(a[list_of_compare_point[i]]==x){
//						return i;
//					}if(x>a[list_of_compare_point[i]] && x<end){
//						start=a[list_of_compare_point[i]];
//					}if(x<a[list_of_compare_point[i]]){
//						end=a[list_of_compare_point[i]];
//					}else if(x==start) {return start;}
//					 else if(x==end) {return end;}
//				}
//			split_point/=type;
//		}
//	}
//	return -1;
//}
///**
// * Main method
// */
//int main() {
//
//	/*
//	 * Some test case.
//	 */
//
////		int a[]= {};
////		int a[]= {1};
////		int a[]= {1,2};
////		int a[]= {1,2,3};
////		int a[]= {1,2,3,4};
////		int a[] = {1,2,3,4,5,6,7,8,9,10};
////		int a[] = {1,2,4,5,7,11,22,33,38,40,46,47};
//		int a[] = {1,2,8,9,10,11,15,19,20,23,29,30,32,35,47,90};
//		int arraySize = sizeof(a)/sizeof(*a);
//		int x;cout << "Enter number for search:\n"; cin >> x;
//		int type=4;
//		int i = TernarySearch(a,arraySize,x);
////		int i=NSearch(a,arraySize,x,type);
//		if(i>=0){
//			cout << "Found at position :"<< i<<endl;
//		}else{
//			cout << "Not found !";
//		}
//		return 0;
//}
