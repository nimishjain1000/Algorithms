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

typedef struct NodeTS{
	TS ts;
	NodeTS *pNext;
}NodeTS;

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

typedef struct List{
	NodeTS *pHead;
	NodeTS *pTail;
}List;

typedef struct Tree{

}Tree;
class Stack{
	private:
		int size;
		Node *top;
	public:
		Stack(){
			top = NULL;
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
			front = NULL;
			rear = NULL;
			size = 0;
		}

		void enQueue(SV &sv){
			Node *tmp = new Node;
			tmp->sv = sv;
			if (isEmpty()){
				tmp->pNext = NULL;
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
			list->pHead = NULL;
			list->pTail = NULL;
			size = 0;
		}
		
		void addHead(TS ts){
			NodeTS *node = new NodeTS;
			node->ts = ts;
			if (isEmpty()){
				node->pNext = NULL;
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
			while (tmp->ts.hoten != hoten){
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
					if (nextNode->ts.diem < currentHead->ts.diem){
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

		void quickSortList(List &list){
			NodeTS *p, *x;
			List l1, l2;
			if (list.pHead = list.pTail) return;

		}
		void printList(){
			if (isEmpty()){
				cout << "List is empty" << endl;
			}
			else{
				NodeTS *currentFront = list->pHead;
				cout << "--- TS Info ---" << endl;
				while (currentFront){
					cout << "Name :" << currentFront->ts.hoten << "  ---- Diem : "<<currentFront->ts.diem<<endl;
					currentFront = currentFront->pNext;
				}
				cout << "--- End TS Info ---" << endl;
			}
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
			if (!isEmpty()){
				NodeTS *p=list.pHead;
				NodeTS *q = nullptr;
				while (p && (p->ts.hoten!=ts.hoten)){
					q = p;
					p = p->pNext;
				}
				if (p == NULL){ return 0; }
				if (q != NULL){}
				else{ removeHead(list, ts); }
				size--;
				return 1;
			}
			return -1;
		}
		
		int removeHead(List &list, TS ts){
			if (isEmpty()){ return 0; }
			NodeTS *node=list.pHead;
			node->ts = ts;
			list.pHead = list.pHead->pNext;
			delete node;
			if (isEmpty()){
				list.pHead = nullptr;
				list.pTail = nullptr;
			}
			return 1;
		}

		bool isEmpty(){
			return size == 0 ? true : false;
		}

};

class BinaryTree{
	
};

class SearchAndSort{
	
};

int main(){
	SV *sv = new SV;
	TS *ts = new TS;
	srand(time(NULL));
	LinkedList *list = new LinkedList;
	Stack *stack = new Stack;
	Queue *queue = new Queue;

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

	/* -----------------------------------  /
	/  ------------Linked list------------  /
	/  ----------------------------------- */
	for (int i = 1; i < 21; i++){
		std::stringstream out;
		out << i;
		ts->hoten = "TS.0" + out.str();
		ts->coquan = "UIT";
		ts->noisinh = "HCM City";
		ts->diem = rand() % 10 + 1;
		ts->ngaysinh = "1/1/1993";
		list->addHead(*ts);
	}
	cout << "-----------------Before Sort----------------" << endl;
	list->printList();
	list->selectionSort();
	cout << "-----------------After Sort----------------" << endl;
	list->printList();
//
//	/* -----------------------------------  / 
//	/  ---------------Stack---------------  / 
//	/  ----------------------------------- */
//	cout << "-----------------Before POP----------------" << endl;
//	stack->printStack();
//	*sv = stack->pop(); 
//	cout << "Pop :" << sv->name << endl; 
//	cout << "-----------------After POP----------------" << endl;
//	stack->printStack();
//	*sv = stack->pop(); 
//	cout << "Pop :" << sv->name << endl;
//	cout << "-----------------After POP----------------" << endl;
//	stack->printStack();
//	*sv = stack->pop();
//	cout << "Pop :" << sv->name << endl;
//	cout << "-----------------After POP----------------" << endl;
//	stack->printStack();
//
//	/* -----------------------------------  /
//	/  ---------------Queue---------------  /
//	/  ----------------------------------- */
//	cout << "-----------------Before Dequeue----------------" << endl;
//	queue->printQueue(); 
//    *sv=queue->deQueue();
//	cout << "Dequeue :" << sv->name << endl;
//	cout << "-----------------After Dequeue----------------" << endl;
//	queue->printQueue();
//	*sv = queue->deQueue();
//	cout << "Dequeue :" << sv->name << endl;
//	cout << "-----------------After Dequeue----------------" << endl;
//	queue->printQueue();
//	*sv = queue->deQueue();
//	cout << "Dequeue :" << sv->name << endl;
//	cout << "-----------------After Dequeue----------------" << endl;
//	queue->printQueue();



	/* -----------------------------------  /
	/  --------Binary Search Tree---------  /
	/  ----------------------------------- */




	return 0;
}