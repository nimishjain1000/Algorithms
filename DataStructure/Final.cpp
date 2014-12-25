#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <ctime>
using namespace std;

typedef struct TS{
	std::string hoten;
	std::string ngaysinh;
	std::string noisinh;
	std::string coquan;
	int diem;
}TS;

typedef struct SV{
	std::string name;
	std::string makhoa;
	int mssv;
	int khoa;
}SV;

typedef struct Node{
	SV sv;
	Node *pNext;
}Node;

typedef struct NodeTS{
	TS ts;
	NodeTS *pNext;
}NodeTS;

typedef struct List{
	NodeTS *pHead;
	NodeTS *pTail;
}List;

typedef struct Tree{
	int x;
	struct Tree *leftNode;
	struct Tree *rightNode;
}Tree;

class Stack{
	private:
		int size;
		Node *top;
	public:
		Stack(){
			top = nullptr;
			size = 0;
		}

		void push(SV &sv){
			Node *tmp = new Node;
			tmp->sv = sv;
			tmp->pNext = top;
			top = tmp;
			size++;
		}

		SV pop(){
			Node *tmp = top;
			SV sv = top->sv;
			top = top->pNext;
			delete tmp;
			size--;
			return sv;
		}

		SV* getTop(){
			return &top->sv;
		}

		bool isEmpty(){
			return size == 0 ? true : false;
		}

		int getSize(){
			return size;
		}

		void printStack(){
			if (isEmpty()){
				cout << "Stack is empty" << endl;
			}else{
				Node *currentTop = top;
				while (currentTop){
					cout << "--- SV Info ---" << endl;
					cout << "Name :" << currentTop->sv.name << endl;
					cout << "SV-Code : " << currentTop->sv.mssv << endl;
					cout << "Grade : " << currentTop->sv.khoa << endl;
					cout << "Group : " << currentTop->sv.makhoa << endl;
					cout << "--- End SV Info ---" << endl;
					currentTop = currentTop->pNext;
				}
			}
		}
};

class Queue{
	private:
		int size;
		Node *front;
		Node *rear;
	public:
		Queue(){
			front = nullptr;
			rear = nullptr;
			size = 0;
		}

		void enQueue(SV sv){
			Node *tmp = new Node;
			tmp->sv = sv;
			if (isEmpty()){
				tmp->pNext = nullptr;
				front =  tmp;
				rear = tmp;
			}
			else{
				if (size == 1){
					front->pNext = tmp;
				}else{
					rear->pNext = tmp; // set current rear->nextNode =  temp Node
				}
				rear = tmp;
				rear->pNext = NULL;
			}
			size++;
		}

		void printQueue(){
			if (isEmpty()){
				cout << "Queue is empty" << endl;
			}else{
				Node *currentFront = front;
				while (currentFront){
					cout << "--- SV Info ---" << endl;
					cout << "Name :" << currentFront->sv.name << endl;
					cout << "SV-Code : " << currentFront->sv.mssv << endl;
					cout << "Grade : " << currentFront->sv.khoa << endl;
					cout << "Group : " << currentFront->sv.makhoa << endl;
					cout << "--- End SV Info ---" << endl;
					currentFront = currentFront->pNext;
				}
			}
		}

		SV deQueue(){
			if (!isEmpty()){
				Node *tmp = front;
				SV sv=front->sv;
				front = front->pNext;
				delete tmp;
				size--;
				return sv;
			}
			exit(1);
		}

		SV* getFront(){
			return &front->sv;
		}

		SV* getRear(){
			return &rear->sv;
		}

		int getSize(){
			return size;
		}

		bool isEmpty(){
			return size == 0 ? true : false;
		}
};

class LinkedList{
private:
	int size;
	List *list;
public:
	LinkedList(){
		list = new List;
		list->pHead = nullptr;
		list->pTail = nullptr;
		size = 0;
	}

	void addHead(TS ts){
		NodeTS *node = new NodeTS;
		node->ts = ts;
		if (isEmpty()){
			node->pNext = nullptr;
			list->pHead = node;
			list->pTail = node;
		}
		else{
			node->pNext = list->pHead;
			list->pHead = node;
		}
		size++;
	}

	void addTail(TS ts){
		NodeTS *node = new NodeTS;
		node->ts = ts;
		if (isEmpty()){
			node->pNext = NULL;
			list->pHead = node;
			list->pTail = node;
		}
		else{
			if (size == 1){
				list->pHead->pNext = node;
			}
			else{
				list->pTail->pNext = node; // set current rear->nextNode =  temp Node
			}
			list->pTail = node;
			list->pTail->pNext = nullptr;
		}
		size++;
	}

	TS searchList(std::string hoten){
		if (isEmpty()) exit(1);
		NodeTS *tmp = list->pHead;
		while (tmp->ts.hoten != hoten && tmp){
			tmp = tmp->pNext;
		}
		return tmp->ts;
	}

	void selectionSort(){
		NodeTS *nextNode, *minNode;
		NodeTS *currentHead = list->pHead;
		while (currentHead != list->pTail){
			minNode = currentHead;
			nextNode = currentHead->pNext;
			while (nextNode){
				if (nextNode->ts.diem < minNode->ts.diem){
					minNode = nextNode;
				}
				nextNode = nextNode->pNext;
			}
			TS tmp = minNode->ts;
			minNode->ts = currentHead->ts;
			currentHead->ts = tmp;
			currentHead = currentHead->pNext;
		}
	}

	void quickSortList(){
		NodeTS *p, *x;
		List l1, l2;
		if (list->pHead = list->pTail) return;

	}

	NodeTS* getNode(List &list,std::string hoten){
		if (!isEmpty()){
			NodeTS *tmp = list.pHead;
			while (tmp){
				if (tmp->ts.hoten == hoten){
					return tmp;
				}
				tmp = tmp->pNext;
			}
			size--;
			return tmp;
		}
		exit(1);
	}

	int deleteNode(List &list, TS ts){
//			if (!isEmpty()){
//				NodeTS *p=list.pHead;
//				NodeTS *q = nullptr;
//				while (p && (p->ts.hoten!=ts.hoten)){
//					q = p;
//					p = p->pNext;
//				}
//				if (p == NULL){ return 0; }
//				if (q != NULL){}
//				else{ removeHead(list, ts); }
//				size--;
//				return 1;
//			}
		return -1;
	}

	int removeHead(){
		if (isEmpty()){ return 0; }
		NodeTS *node=list->pHead;
		list->pHead = list->pHead->pNext;
		delete node;
		if (isEmpty()){
			list->pHead = nullptr;
			list->pTail = nullptr;
		}
		return 1;
	}

	int removeTail(){
		if (isEmpty()){ return 0; }
		NodeTS *headNode = list->pHead;
		while (headNode->pNext!=list->pTail){
			headNode = headNode->pNext;
		}
		NodeTS *tailNode = list->pTail;
		headNode->pNext = nullptr;
		delete tailNode;
		if (isEmpty()){
			list->pHead = nullptr;
			list->pTail = nullptr;
		}
	}

	bool isEmpty(){
		return size == 0 ? true : false;
	}

	void printList(){
		if (isEmpty()){
			cout << "List is empty" << endl;
		}
		else{
			NodeTS *currentFront = list->pHead;
			while (currentFront){
				cout << "Name :" << currentFront->ts.hoten << "  ---- Diem : " << currentFront->ts.diem << endl;
				currentFront = currentFront->pNext;
			}
		}
	}
};

class BinaryTree{
	private:
		int size;
	public:

		void createTree(Tree &tree){
			tree.leftNode= nullptr;
			tree.rightNode = nullptr;
			tree.x = NULL;
		}

		void addNode(Tree &tree,int x){
			if(tree.x==NULL){
				tree.x = x;
				tree.leftNode = nullptr;
				tree.rightNode = nullptr;
			}else if (x<tree.x){
				if (tree.leftNode == NULL){
					tree.leftNode = new Tree;
					createTree(*tree.leftNode);
				}
				return addNode(*tree.leftNode, x);
			}
			else if (x>tree.x) {
				if (tree.rightNode == NULL){
					tree.rightNode = new Tree;
					createTree(*tree.rightNode);
				}
				return addNode(*tree.rightNode, x);
			}
		}

		void deleteTreeNode(Tree &tree, int x){
			if (tree.x != NULL){
				
			}
		}

		Tree* searchTreeNode(Tree *tree, int x){
			Tree *root = tree;
			while (root!=NULL)	{
				if (root->x == x) {
					return root;
				}if (root->x>x){
					root = root->leftNode;
				}else if (root->x<x){
					root = root->rightNode;
				}
			}
			return NULL;
		}

		int countNode(Tree *tree){
			int count = tree==NULL?0:1;
			Tree *root = tree;
			if (root->leftNode != NULL){
				count += countNode(root->leftNode);
			}
			if (root->rightNode != NULL){
				count += countNode(root->rightNode);
			}
			return count;
		}

		bool isEmpty(Tree *tree) {
			return tree == NULL ? true : false;
		}

};

class SearchAndSort{
public:

	int LinearSearch(int array[],int x,int n){
		int i = 0;
		while (array[i] != x && i<n) { i++; }
		if (i == n) { return 0; }
		return i;
	}

	int BinarySearch(int array[], int x,int n){
		int left=0,mid= 0;
		int right = n - 1;
		while (left <= right){
			mid = (left + right) / 2;
			if (array[mid] == x) return mid;
			if (array[mid] < x) left = mid + 1;
			else right = mid - 1;
		}
		return 0;
	}

	void interchangeSort(int array[],int n){
		int i,j;
		for (i = 0; i < n - 1; i++){
			for (j = i + 1; j < n ; j++){
				if (array[j]>array[i]){
					swap(array[i], array[j]);
				}
			}
		}
	}

	void selectionSort(int array[], int n){
		int i, j, min;
		for (i = 0; i < n - 1; i++){
			min = i;
			for (j = i + 1; j < n ; j++){
				if (array[j] > array[min])
				min = j;
			}
			swap(array[min], array[i]);
		}
	}

	void bubbleSort(int array[], int n){
		int i, j;
		for (i = 0; i < n - 1; i++){
			for (j = n - 1; j>i; j--){
				if (array[j] > array[j - 1])
					swap(array[j], array[j - 1]);
			}
		}
	}

	void InsertionSort(int array[], int n){
		int pos, i, tmp;
		for (i = 1; i < n; i++){
			tmp = array[i];
			pos = i - 1;
			while (pos >= 0 && array[pos]>tmp){
				array[pos + 1] = array[pos];
				pos--;
			}
			array[pos + 1] = tmp;
		}
	}

	void BinaryInsertionSort(int array[], int n){
		int left, mid, right, i, tmp;
		for (i = 1; i < n; i++){
			tmp = array[i];
			left = 1;
			right = n - 1;
			while (i <= right){
				mid = (left + right) / 2;
				if (tmp < array[mid]) right = mid - 1;
				else left = mid + 1;
			}
		}
	}

	void printArray(int array[], int size){
		int i = 0;
		cout << "Array : ";
		for (i = 0; i < size; i++){
			cout << array[i] << " ";
		}
		cout << endl;
	}

	void swap(int &a, int &b){
		a = a + b;
		b = a - b;
		a = a - b;
	}

	void createRandomArray(int array[],int size){
		for(int i=0; i<size; i++){
			array[i] = (rand()%100)+1;
		}
	}

};

int main(){

	int i = 10;

	i = i-- + --i;
	printf("%d", i);
	int test;
	std::string data;
	cout << " Enter number :"; cin >> test; cout << endl;
	while (test > 0)	{
		cout << "Enter String :"; cin >> data;
		test--;
	}
	int array[30];
	srand(time(nullptr));

	/* Data Structure*/
	SV *sv = new SV;
	TS *ts = new TS;
	Tree *tree = new Tree;

	/* Class */
	LinkedList *list = new LinkedList;
	Stack *stack = new Stack;
	Queue *queue = new Queue;
	SearchAndSort *search_and_sort = new SearchAndSort;
	BinaryTree *binaryTree = new BinaryTree;


	for (int i = 1; i < 4; i++){
		std::stringstream out;
		out << i;
		sv->name = "SV." + out.str();
		sv->khoa = i;
		sv->makhoa = "MMT.0" + out.str();
		sv->mssv = 1152000 + i;
		stack->push(*sv);
		queue->enQueue(*sv);
	}
	for (int i = 1; i < 10; i++){
		std::stringstream out;
		out << i;
		ts->hoten = "TS.0" + out.str();
		ts->coquan = "UIT";
		ts->noisinh = "HCM City";
		ts->diem = rand() % 10 + 1;
		ts->ngaysinh = "1/1/1993";
		list->addHead(*ts);
	}


	/* -----------------------------------  /
	/  ---------Search and sort-----------  /
	/  ----------------------------------- */

	search_and_sort->createRandomArray(array, 30);
	search_and_sort->printArray(array, 30);
	search_and_sort->interchangeSort(array, 30);
//	search_and_sort->selectionSort(array, 30);
	search_and_sort->bubbleSort(array, 30);
	search_and_sort->printArray(array, 30);

	/* -----------------------------------  /
	/  ------------Linked list------------  /
	/  ----------------------------------- */

	cout << "-----------------Before Sort----------------" << endl;
	list->printList();
	list->selectionSort();
	cout << "-----------------After Sort----------------" << endl;
	list->printList();

	/* -----------------------------------  /
	/  ---------------Stack---------------  /
	/  ----------------------------------- */
	cout << "-----------------Before POP----------------" << endl;
	stack->printStack();
	*sv = stack->pop();
	cout << "Pop :" << sv->name << endl;
	cout << "-----------------After POP----------------" << endl;
	stack->printStack();
	*sv = stack->pop();
	cout << "Pop :" << sv->name << endl;
	cout << "-----------------After POP----------------" << endl;
	stack->printStack();
	*sv = stack->pop();
	cout << "Pop :" << sv->name << endl;
	cout << "-----------------After POP----------------" << endl;
	stack->printStack();

	/* -----------------------------------  /
	/  ---------------Queue---------------  /
	/  ----------------------------------- */

	cout << "-----------------Before Dequeue----------------" << endl;
	queue->printQueue();
	*sv=queue->deQueue();
	cout << "Dequeue :" << sv->name << endl;
	cout << "-----------------After Dequeue----------------" << endl;
	queue->printQueue();
	*sv = queue->deQueue();
	cout << "Dequeue :" << sv->name << endl;
	cout << "-----------------After Dequeue----------------" << endl;
	queue->printQueue();
	*sv = queue->deQueue();
	cout << "Dequeue :" << sv->name << endl;
	cout << "-----------------After Dequeue----------------" << endl;
	queue->printQueue();

	/* -----------------------------------  /
	/  --------Binary Search Tree---------  /
	/  ----------------------------------- */

	binaryTree->createTree(*tree);
	binaryTree->addNode(*tree, 44);binaryTree->addNode(*tree, 18);binaryTree->addNode(*tree, 13);
	binaryTree->addNode(*tree, 15);binaryTree->addNode(*tree, 37);binaryTree->addNode(*tree, 23);
	binaryTree->addNode(*tree, 40);binaryTree->addNode(*tree, 88);binaryTree->addNode(*tree, 59);
	binaryTree->addNode(*tree, 108);binaryTree->addNode(*tree, 55);binaryTree->addNode(*tree, 73);binaryTree->addNode(*tree, 50);
	Tree *treeNode=binaryTree->searchTreeNode(tree, 55);
	int count = binaryTree->countNode(tree);
	return 0;
}
