#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;

/**
 * Linear Search - TÃ¬m tuyáº¿n tÃ­nh
 * @param array : List of number
 * @param x : Find x
 * @param n (array size)
 * return : 0 (Not found) or Postion found
 * --- Sá»‘ láº§n so sÃ¡nh ---
 * Best case  : 1
 * Worst case : N
 * Average    : (N+1)/2
 * Ä�á»™ phá»©c táº¡p : O (N)
 */
int LinearSearch(int array[],int x,int n){
	int i=0;
	/**
	 * Improve
	 * int a[n]=x;
	 * while(array[i]!=x) {i++;	}
	 * khÃ´ng cáº§n pháº£i so sÃ¡nh i<n (vÃ¬ i=n thÃ¬ array[i]=array[n]=x),sá»‘ phÃ©p so sÃ¡nh giáº£m cÃ²n n láº§n
	 */
	while(i<n && array[i]!=x) {i++;	}
	if(i==n)     { return 0;	}
	else         { return i; }
}
/**
 * Binary Search - TÃ¬m nhá»‹ phÃ¢n
 * @param array : List of number
 * @param x : Find x
 * @param n (array size)
 * return : 0 (Not found) or Postion found
 * --- Sá»‘ láº§n so sÃ¡nh ---
 * Tá»‘t nháº¥t : 1
 * Xáº¥u nháº¥t : log2(N)
 * Trung bÃ¬nh : log2(N)/2
 * Ä�á»™ phá»©c táº¡p O( log2(N))
 */
int BinarySearch(int array[],int x,int n){
	int left=0;
	int right=n-1;
	int mid=0;
	while(left<=right){
		mid=(left+right)/2;
		if (array[mid]==x) return mid;
		if (array[mid]<x) left=mid+1;
		else right=mid-1;
	}
	return 0;
}
/**
 * Interchange Sort - Ä�á»•i chá»— trá»±c tiáº¿p
 * @param array
 * @param n (array size)
 * --- Sá»‘ láº§n so sÃ¡nh ---
 * 	+ Tá»‘t nháº¥t : n(n-1)/2
 * 	+ Xáº¥u nháº¥t : n(n-1)/2
 * --- Sá»‘ láº§n hoÃ¡n vá»‹ ---
 *  + Tá»‘t nháº¥t : 0
 *  + Xáº¥u nháº¥t : n(n-1)/2
 */
void InterchangeSort(int array[], int n){
	int i,j;
	for(i = 0;i < n-1; i++){
		for (j = i+1; j < n; j++) {
			if(array[j]<array[i]){
				swap(array[i],array[j]);
			}
		}
	}
}
/**
 * Selection Sort - Chá»�n trá»±c tiáº¿p
 * @param array
 * @param n (array size)
 * --- Sá»‘ láº§n so sÃ¡nh ---
 *  + Tá»‘t nháº¥t : n(n-1)/2
 *  + Xáº¥u nháº¥t : n(n-1)/2
 * --- Sá»‘ phÃ©p gÃ¡n ---
 *  + Tá»‘t nháº¥t : 0 ??
 *  + Xáº¥u nháº¥t : 3n(n-1)/2
 */
void SelectionSort(int array[], int n){
	int i,j,min;
	for(i = 0; i < n-1; i++){
		min=i;		// GÃ¡n pháº§n tá»­ Ä‘áº§u tiÃªn trong dÃ£y lÃ  min
		for(j = i+1; j < n; j++){
			if(array[j]<array[min])
			min=j;
		}
		swap(array[min],array[i]);
	}
}
/**
 * Bubble Sort
 * @param array
 * @param n (array size)
 * --- Sá»‘ láº§n so sÃ¡nh ---
 *  + Tá»‘t nháº¥t : n(n-1)/2
 *  + Xáº¥u nháº¥t : n(n-1)/2
 * --- Sá»‘ láº§n hoÃ¡n vá»‹ ---
 *  + Tá»‘t nháº¥t : 0
 *  + Xáº¥u nháº¥t : n(n-1)/2
 */
void BubbleSort(int array[],int n){
	int i,j;
	for(i= 0; i < n-1; i++){
		for(j= n-1; j > i; j--){
			if(array[j]<array[j-1])
				swap(array[j],array[j-1]);
		}
	}
}
/**
 * Shaker Sort
 * @param array
 * @param n (array size)
 */
void ShakerSort(int array[],int n){
	int j;
	int left=0;
	int right=n-1;
	int k=right;
	while(left<right){
		for(j=right; j > left; j--){
			if(array[j]<array[j-1]){
				swap(array[j],array[j-1]);
				k=j;
			}
		}
		left=k;
		for(j=left; j < right; j++){
			if(array[j]>array[j+1]){
				swap(array[j],array[j+1]);
				k=j;
			}
		}
		right=k;
	}
}
/**
 * Insertion Sort - ChÃ¨n trá»±c tiáº¿p
 * @param array
 * @param n (array size)
 * --- Sá»‘ láº§n so sÃ¡nh ---
 *  + Tá»‘t nháº¥t : n-1
 *  + Xáº¥u nháº¥t : n(n-1)/2
 * --- Sá»‘ phÃ©p gÃ¡n ---
 *  + Tá»‘t nháº¥t : 2(n-1)
 *  + Xáº¥u nháº¥t : [n(n-1)/2]-1
 */
void InsertionSort(int array[],int n){
	int pos,i;
	int tmp;
	for( i=1; i < n ; i++){
		tmp=array[i];
		pos=i-1;
		while(pos>=0 && array[pos]>tmp){
			array[pos+1]=array[pos];
			pos--;
		}
		array[pos+1]=tmp;
	}
}
/**
 * Binary Insertion Sort - ChÃ¨n nhá»‹ phÃ¢n
 * @param array
 * @param n (array size)
 */
void BinaryInsertionSort(int array[],int n){
	int left,right,mid,i,tmp;
	for( i=1; i < n ; i++ ){
		tmp=array[i];
		left=1;
		right=n-1;
		while(i<=right){
			mid=(left+right)/2;
			if(tmp<array[mid]){
				right=mid-1;
			}else{
				left=mid+1;
			}
		}

	}
}
/**
 * Shell Sort - Insertion Sort Improve
 *
 */
void ShellSort(){
	int step,i,j,tmp,length;

}
/**
 *
 */
void HeapSort(){

}
/**
 *
 */
void QuickSort(){

}
/**
 *
 */
void MergeSort(){

}
/**
 *
 */
void RadixSort(){

}









/**
 * Swap function
 * @param &a
 * @param &b
 */
void swap(int &a,int &b){
	a=a+b;
	b=a-b;
	a=a-b;
}
/**
 * Print array function
 * @param array
 */
void printArray(int array[],int size){
	int i;
	for( i=0; i<size; i++){
		cout << array[i] << "-";
    }
}
/**
 * Main application
 * Test cÃ¡c giáº£i thuáº­t tÃ¬m kiáº¿m , sáº¯p xáº¿p
 */
int main(){
	 int array_size=10;
	 int array[array_size];
	 int array_interchange[array_size];
	 int array_selection[array_size];
	 int array_bubble[array_size];
	 int array_shaker[array_size];
	 int array_insertion[array_size];
	 int array_binsertion[array_size];
	 srand((unsigned)time(0));
	 for(int i=0; i<array_size; i++){
	    array[i] = (rand()%100)+1;
	    array_interchange[i]=array[i];
	    array_selection[i]=array[i];
	    array_bubble[i]=array[i];
	    array_shaker[i]=array[i];
	    array_insertion[i]=array[i];
	    array_binsertion[i]=array[i];
	 }
	cout<<endl;
//	int array[] = {1,2,5,8,9,10,11,15,19,20,23,29,30,32,35,47,90};
//	int array_size=sizeof(array)/sizeof(*array);

	/**
	 * Linear & Binary Search
	 */
    int result_LinearSearch=LinearSearch(array,5,array_size);
    int result_BinarySearch=BinarySearch(array,5,array_size);
    if(result_LinearSearch>0){
    			cout << "Linear Search found at position :"<< result_LinearSearch<<endl;
    }
    if(result_LinearSearch>0){
       			cout << "Binary Search found at position :"<< result_BinarySearch<<endl;
    }
    /**
     * Origin random array
     */
    cout<<"Random array : ";
    printArray(array,array_size);
    cout<<" Time taken : " <<endl;
    /**
      * Interchange Sort
      */
    cout<<"After do Interchange Sort " <<endl;
    InterchangeSort(array_interchange,array_size);
    printArray(array_interchange,array_size);
    cout<<" Time taken : " <<endl;
    /*
     * Selection Sort
     */
    cout<<"After do Selection Sort " <<endl;
    SelectionSort(array_selection,array_size);
    printArray(array_selection,array_size);
    cout<<" Time taken : " <<endl;
    /*
     * Bubble Sort
     */
    cout<<"After do Bubble Sort " <<endl;
    BubbleSort(array_bubble,array_size);
    printArray(array_bubble,array_size);
    cout<<" Time taken : " <<endl;
    /*
     * Shaker Sort
     */
    cout<<"After do Shaker Sort " <<endl;
    ShakerSort(array_shaker,array_size);
    printArray(array_shaker,array_size);
    cout<<" Time taken : " <<endl;
    /*
     * Insertion Sort
     */
    cout<<"After do Insertion Sort " <<endl;
    InsertionSort(array_insertion,array_size);
    printArray(array_insertion,array_size);
    cout<<" Time taken : " <<endl;
    /*
     * Binary Insertion Sort
     */
    cout<<"After do Binary Insertion Sort " <<endl;
    BinaryInsertionSort(array_binsertion,array_size);
    printArray(array_binsertion,array_size);
    cout<<" Time taken : " <<endl;
	return 0;
}
