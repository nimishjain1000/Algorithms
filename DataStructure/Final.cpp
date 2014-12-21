#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
using namespace std;

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
	Node *pHead;
	Node *pTail;
}List;

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
					rear = tmp;
					rear->pNext = NULL;
				}
				else{
					rear->pNext = tmp; // set current rear->nextNode =  temp Node
					rear = tmp;        // Now rear=temp Node
					rear->pNext = NULL;
				}
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
	void createList(List &list){
		list.pHead = NULL;
		list.pTail = NULL;
	}
	Node* createNode(SV sv){
		Node *tmp = new Node;
		if (tmp == NULL) exit(1);
		tmp->sv = sv;
		tmp->pNext = NULL;
		return tmp;
	}
	void addHead(List &list, Node* node){
		if (list.pHead == NULL){
			list.pHead = node;
			list.pTail = list.pHead;
		}
		else{
			node->pNext = list.pHead;
			list.pHead = node;
		}
	}
};

int main(){
	SV *sv = new SV;

	/* -----------------------------------  /
	/  ------------Linked list------------  /
	/  ----------------------------------- */


	/* -----------------------------------  / 
	/  ---------------Stack---------------  / 
	/  ----------------------------------- */
	Stack *stack = new Stack;
	for(int i = 1; i < 4; i++){
		std::stringstream out;
		out << i;
		sv->name = "SV." + out.str();
		sv->khoa = i;
		sv->makhoa = "MMT.0" + out.str();
		sv->mssv = 1152000 + i;
		stack->push(*sv);
	}
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
	Queue *queue = new Queue;
	for (int i = 1; i < 4; i++){
		std::stringstream out;
		out << i;
		sv->name = "SV." + out.str();
		sv->khoa = i;
		sv->makhoa = "MMT.0" + out.str();
		sv->mssv = 1152000 + i;
		queue->enQueue(*sv);
	}
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
	return 0;
}