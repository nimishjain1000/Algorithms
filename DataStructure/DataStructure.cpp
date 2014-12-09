/*============================================================================
* Name        : DataStructure.cpp
* Author      : Do Minh Quan -- 11520616
* Email       : dominhquan.uit@gmail.com
* Mail GV     : phongtn@uit.edu.vn
* Type        : Data Structure & Algorithms
* Description : C++, ANSI-style
============================================================================*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <string>
#include <sstream>
using namespace std;

class Player{
	public :
		std::string name;
		int price_1;
		int price_2;
		int price_3;
};
class Node {
	public:
		Player player;
		Node *nextNode;
};
class ListQueue{
	private:
		Node *front;
		Node *rear;
		int size;
	public:
		ListQueue(){
			front=NULL;
			rear=NULL;
			size=0;
		}
		void enQueue(Player player){
			Node *tmpNode=new Node();
			tmpNode->player=player;   		// set data to new Node
			tmpNode->nextNode=NULL;   		// new Node ->nextNode =NULL (cuz rear)
			if(isEmpty()){			  		// check if ListQueue is empty
				front=rear=tmpNode;	  		// Yes, queue list now has only 1 Node
			}else{					  		// No
				rear->nextNode=tmpNode;  	// set previous rear->nextNode to new rear (tmpNode)
				rear=tmpNode;				// Now new Node become the rear.
			}
			size++; 						// increase quese size
		}
		Player deQueue(){
			Player player;
			if(!isEmpty()){
				player=front->player;
			    Node *tmpNode=front;
			    front=front->nextNode;
				size--;
				delete tmpNode;
			}
			return player;
		}
		Player getFront(){
			Player player;
			if(isEmpty()==true){
				player=front->player;
			}
			return player;
		}
		Player getRear(){
			Player player;
			if(isEmpty()==true){
				player=front->player;
			}
			return player;
		}
		int getSize(){
			return size;
		}
		bool isEmpty(){
			return size == 0?true:false;
		}
		void showList(){
			Node *node=new Node();
			node=front;
			if(isEmpty()){
				cout<<"\nEmpty Queue\n";
			}else{
				while(node!=NULL){
					Player player=node->player;
					cout<<player.name<<":"<<player.price_1<<"-"<<player.price_2<<"-"<<player.price_3<<endl;
					node=node->nextNode;
				}
			}

		}
		int findListValueUniqueInArray(int array[],int array_store[]){
			int count=0;
			for(int i=1;i<10;i++){
				if(checkUnique(i,array)==true){
					array_store[count]=array[i];
					count++;
				}
			}
			return count;
		}
		int findUniqueMinInArray(int array[],int size){
			int min=array[0];
			for(int i=0;i<size;i++){
				if(array[i]<min){
					min=array[i];
				}
			}
			return min;
		}
		bool checkUnique(int pos,int array[]){
			for(int i=1;i<10;i++){
				if(array[i]==array[pos] && i!=pos){
					return false;
				}
			}
			return true;
		}
};
int main(){
	srand (time(NULL));
	ListQueue listQueue;
	int array[10];
	int count=1;
	for (int i = 1;i <4;i++) {
		Player player;
		std::stringstream out;
		out<<i;
		player.name="Player-" +out.str();
		player.price_1=rand() % 20 + 1;
		player.price_2=rand() % 20 + 1;
		player.price_3=rand() % 20 + 1;
		array[count]=player.price_1;
		count++;
		array[count]=player.price_2;
		count++;
		array[count]=player.price_3;
		count++;
		listQueue.enQueue(player);
	}
	cout<<"-----------------List-----------------"<<endl;
	listQueue.showList();
	int* array_store = new int[10];
	int size=listQueue.findListValueUniqueInArray(array,array_store);
	if(size>0){
		int min=listQueue.findUniqueMinInArray(array_store,size);
		int pos_min=1;
		for (int i=1;i<10;i++){
			if(array[i]==min){
				pos_min=i;
			}
		}
		string player_win="1";
		if(pos_min >3 && pos_min<7){
			player_win="2";
		}
		if(pos_min<10 && pos_min>=7){
			player_win="3";
		}
		cout<<"Player win : "<<player_win<<" with price :"<<array[pos_min]<<endl;
	}else{
		cout<<"No one win this match "<<endl;
	}
}
