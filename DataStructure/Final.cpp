#include <iostream>
using namespace std;

class Stack{
	private:
		typedef struct node{
			node *next;
			int data;
		}Node;
		Node *top;
	public:
			Stack(){
				top=NULL;
			}
			void deStack(){
				while(top){
					Node *temp=top;
					top=top->next;
					delete temp;
				}
			}
			void push(int data){
				Node *tmp=new Node;
				tmp->next=top;
				tmp->data=data;
				top=tmp;
			}
			int pop(){
				Node *tmp=top;
				int data=top->data;
				top=top->next;
				delete tmp;
				return data;
			}
			void printStack(){
				Node *TOP=top;
				while(TOP){
					cout<<TOP->data<<" ";
					TOP=TOP->next;
				}
				cout<<endl;
			}
			int getTop(){
				return top->data;
			}
};
class Queue{
private :
	typedef struct Node{
		Node *next;
		int data;
	}Node;
	Node *head;
};
int main(){
	Stack *stack=new Stack;
	stack->push(10);
	stack->push(20);
	stack->push(30);
	stack->push(40);
	stack->push(50);
	stack->push(60);
	stack->printStack();
	cout<<"Top of the stack : " <<stack->getTop() <<endl;
	stack->pop();
	stack->pop();
	stack->pop();
	stack->printStack();
	cout<<"Top of the stack : " <<stack->getTop() <<endl;
//	stack->deStack();
//	stack->printStack();
//	cout<<"Top of the stack : " <<stack->getTop() <<endl;
	return 0;
}
