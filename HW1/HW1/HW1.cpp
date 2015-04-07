// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

struct bank_state{
	int left_missionaries = 0;
	int left_cannibals = 0;
	int left_boats = 0;
	int right_missionaries = 0;
	int right_cannibals = 0;
	int right_boats = 0;
};

struct node{
	bank_state state;
	int parent_node;
	int operation;
	int depth;
	int path_cost;
};

void print_node(node temp){
	cout << temp.state.left_missionaries << "," << temp.state.left_cannibals << "," << temp.state.left_boats << "," << temp.state.right_missionaries
		<< "," << temp.state.right_cannibals << "," << temp.state.right_boats << "," << endl;
}


bool general_search(int problem){


	//create queue
	queue<node> myqueue;
	queue<int> testqueue;
	node starting_node;
	node nd;

	starting_node.state.left_missionaries = 0;
	starting_node.state.left_cannibals = 0;
	starting_node.state.left_boats = 0;
	starting_node.state.right_missionaries = 3;
	starting_node.state.right_cannibals = 3;
	starting_node.state.right_boats = 1;

	myqueue.push(starting_node);
	testqueue.push(0);


	cout << "myquue contains:" << endl;
	//while (!myqueue.empty()){
	nd = myqueue.front();
	print_node(nd);

	///////////
	//Check 1. Put one missionary in the boat

	//boat on right
	if (nd.state.right_boats == 1){
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries + 1 >= nd.state.left_cannibals)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries - 1 >= nd.state.right_cannibals))){
			node new_node = nd;
			new_node.state.left_missionaries += 1;
			new_node.state.right_missionaries -= 1;
			new_node.state.left_boats = 1;
			new_node.state.right_boats = 0;
			myqueue.push(new_node);
			testqueue.push(1);
		}
	}
	//boat on left
	else{
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries - 1 >= nd.state.left_cannibals)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries + 1 >= nd.state.right_cannibals))){
			node new_node = nd;
			new_node.state.left_missionaries -= 1;
			new_node.state.right_missionaries += 1;
			new_node.state.left_boats = 0;
			new_node.state.right_boats = 1;
			myqueue.push(new_node);
			testqueue.push(1);
		}
	}
	///////////
	//Check 2. Put two missionary in the boat

	//boat on right
	if (nd.state.right_boats == 1){
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries + 2 >= nd.state.left_cannibals)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries - 2 >= nd.state.right_cannibals))){
			node new_node = nd;
			new_node.state.left_missionaries += 2;
			new_node.state.right_missionaries -= 2;
			new_node.state.left_boats = 1;
			new_node.state.right_boats = 0;
			myqueue.push(new_node);
			testqueue.push(2);
		}
	}
	//boat on left
	else{
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries - 2 >= nd.state.left_cannibals)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries + 2 >= nd.state.right_cannibals))){
			node new_node = nd;
			new_node.state.left_missionaries -= 2;
			new_node.state.right_missionaries += 2;
			new_node.state.left_boats = 0;
			new_node.state.right_boats = 1;
			myqueue.push(new_node);
			testqueue.push(2);
		}
	}

	///////////
	//Check 3. Put one cannibal in the boat

	//boat on right
	if (nd.state.right_boats == 1){
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals + 1)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals - 1))){
			node new_node = nd;
			new_node.state.left_cannibals += 1;
			new_node.state.right_cannibals -= 1;
			new_node.state.left_boats = 1;
			new_node.state.right_boats = 0;
			myqueue.push(new_node);
			testqueue.push(3);
		}
	}
	//boat on left
	else{
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals - 1)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals + 1))){
			node new_node = nd;
			new_node.state.left_cannibals -= 1;
			new_node.state.right_cannibals += 1;
			new_node.state.left_boats = 0;
			new_node.state.right_boats = 1;
			myqueue.push(new_node);
			testqueue.push(3);
		}
	}

	///////////
	//Check 4. Put one cannibal and one missionary in the boat

	//boat on right
	if (nd.state.right_boats == 1){
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries + 1 >= nd.state.left_cannibals + 1)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries - 1 >= nd.state.right_cannibals - 1))){
			node new_node = nd;
			new_node.state.left_missionaries += 1;
			new_node.state.right_missionaries -= 1;
			new_node.state.left_cannibals += 1;
			new_node.state.right_cannibals -= 1;
			new_node.state.left_boats = 1;
			new_node.state.right_boats = 0;
			myqueue.push(new_node);
			testqueue.push(4);
		}
	}
	//boat on left
	else{
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries - 1 >= nd.state.left_cannibals - 1)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries + 1 >= nd.state.right_cannibals + 1)))
		{
			node new_node = nd;
			new_node.state.left_missionaries -= 1;
			new_node.state.right_missionaries += 1;
			new_node.state.left_cannibals -= 1;
			new_node.state.right_cannibals += 1;
			new_node.state.left_boats = 0;
			new_node.state.right_boats = 1;
			myqueue.push(new_node);
			testqueue.push(4);
		}
	}


	///////////
	//Check 5. Put two cannibal in the boat

	//boat on right
	if (nd.state.right_boats == 1){
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals + 2)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals - 2))){
			node new_node = nd;
			new_node.state.left_cannibals += 2;
			new_node.state.right_cannibals -= 2;
			new_node.state.left_boats = 1;
			new_node.state.right_boats = 0;
			myqueue.push(new_node);
			testqueue.push(5);
		}
	}
	//boat on left
	else{
		if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals - 2)) &&
			((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals + 2))){
			node new_node = nd;
			new_node.state.left_cannibals -= 2;
			new_node.state.right_cannibals += 2;
			new_node.state.left_boats = 0;
			new_node.state.right_boats = 1;
			myqueue.push(new_node);
			testqueue.push(5);
		}
	}


	myqueue.pop();
	testqueue.pop();

	while (!myqueue.empty()){
		node temp = myqueue.front();
		print_node(temp);
		myqueue.pop();
	}







	return true;

}

int main(int argc, _TCHAR* argv[])
{
	general_search(5);
	printf("\nhello world\n");
	getchar();
	return 0;
}


