// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
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
	bank_state parent_node;
	int operation = 0;
	int depth = 0;
	int path_cost = 0;
	string parents = "";
};

void print_node(node temp){
	//cout << temp.state.left_missionaries << "," << temp.state.left_cannibals << "," << temp.state.left_boats << "," << temp.state.right_missionaries
	//	<< "," << temp.state.right_cannibals << "," << temp.state.right_boats << "," << "    depth=" << temp.depth << "		parent=" 
	//	<< temp.parent_node.left_missionaries << "," << temp.parent_node.left_cannibals << "," << temp.parent_node.left_boats << "," << temp.parent_node.right_missionaries
	//	<< "," << temp.parent_node.right_cannibals << "," << temp.parent_node.right_boats << "," << endl;
	//ofstream myfile;
	//myfile.open("mcb_log.txt",ios::app);
	//myfile << temp.state.left_missionaries << "," << temp.state.left_cannibals << "," << temp.state.left_boats << "," << temp.state.right_missionaries
	//	<< "," << temp.state.right_cannibals << "," << temp.state.right_boats << "," << "    depth=" << temp.depth << "		parent="
	//	<< temp.parent_node.left_missionaries << "," << temp.parent_node.left_cannibals << "," << temp.parent_node.left_boats << "," << temp.parent_node.right_missionaries
	//	<< "," << temp.parent_node.right_cannibals << "," << temp.parent_node.right_boats << "," << endl;
	//myfile.close();

}
void print_node2(node temp){
	cout << temp.state.left_missionaries << "," << temp.state.left_cannibals << "," << temp.state.left_boats << "," << temp.state.right_missionaries
		<< "," << temp.state.right_cannibals << "," << temp.state.right_boats << "," << "    depth=" << temp.depth << 
		"		parent=" 
/*		<< temp.parent_node.left_missionaries << "," << temp.parent_node.left_cannibals << "," << temp.parent_node.left_boats << "," << temp.parent_node.right_missionaries
	<< "," << temp.parent_node.right_cannibals << "," << temp.parent_node.right_boats << ",             "  */ 
	<< temp.parents << endl;
	//ofstream myfile;
	//myfile.open("mcb_log.txt",ios::app);
	//myfile << temp.state.left_missionaries << "," << temp.state.left_cannibals << "," << temp.state.left_boats << "," << temp.state.right_missionaries
	//	<< "," << temp.state.right_cannibals << "," << temp.state.right_boats << "," << "    depth=" << temp.depth << "		parent="
	//	<< temp.parent_node.left_missionaries << "," << temp.parent_node.left_cannibals << "," << temp.parent_node.left_boats << "," << temp.parent_node.right_missionaries
	//	<< "," << temp.parent_node.right_cannibals << "," << temp.parent_node.right_boats << "," << endl;
	//myfile.close();

}
string state_string(node temp){
	string temp_string = "";
	temp_string =  to_string( temp.state.left_missionaries )  + ","  + to_string( temp.state.left_cannibals )  + ","  + to_string( temp.state.left_boats )  + ","  + to_string( temp.state.right_missionaries
		)  + ","  + to_string( temp.state.right_cannibals ) + ","  + to_string( temp.state.right_boats );   
	//ofstream myfile;
	//myfile.open("mcb_log.txt",ios::app);
	//myfile );  + to_string( temp.state.left_missionaries );  + ","  + to_string( temp.state.left_cannibals );  + ","  + to_string( temp.state.left_boats );  + ","  + to_string( temp.state.right_missionaries
	//	);  + ","  + to_string( temp.state.right_cannibals );  + ","  + to_string( temp.state.right_boats );  + ","  + to_string( "    depth=" );  + to_string( temp.depth );  + to_string( "		parent="
	//	);  + to_string( temp.parent_node.left_missionaries );  + ","  + to_string( temp.parent_node.left_cannibals );  + ","  + to_string( temp.parent_node.left_boats );  + ","  + to_string( temp.parent_node.right_missionaries
	//	);  + ","  + to_string( temp.parent_node.right_cannibals );  + ","  + to_string( temp.parent_node.right_boats );  + ","  + to_string( endl;
	//myfile.close();
	return temp_string;
}
bool nodePassed(node current, node goal){
	if (
		current.state.left_boats == goal.state.left_boats &&
		current.state.left_cannibals == goal.state.left_cannibals &&
		current.state.left_missionaries == goal.state.left_missionaries &&
		current.state.right_boats == goal.state.right_boats &&
		current.state.right_cannibals == goal.state.right_cannibals &&
		current.state.right_missionaries == goal.state.right_missionaries){
		return true;
	}
	else
		return false;
}


bool general_search(int problem, queue<node> &myqueue){

	//create queue
	node starting_node;
	node goal_node;
	node nd;

	goal_node.state.left_missionaries = 3;
	goal_node.state.left_cannibals = 3;
	goal_node.state.left_boats = 1;
	goal_node.state.right_missionaries = 0;
	goal_node.state.right_cannibals = 0;
	goal_node.state.right_boats = 0;


	starting_node.state.left_missionaries = 0;
	starting_node.state.left_cannibals = 0;
	starting_node.state.left_boats = 0;
	starting_node.state.right_missionaries = 3;
	starting_node.state.right_cannibals = 3;
	starting_node.state.right_boats = 1;
	starting_node.parents = state_string(starting_node);
	myqueue.push(starting_node);


	cout << "myquue contains:" << endl;
	while (!myqueue.empty()){
		nd = myqueue.front();
		print_node(nd);

		///////////
		//Check 1. Put one missionary in the boat

		//boat on right
		if (nd.state.right_boats == 1 && nd.state.right_missionaries >= 1){
			if (((nd.state.left_missionaries + 1 == 0) || (nd.state.left_missionaries + 1 >= nd.state.left_cannibals)) &&
				((nd.state.right_missionaries - 1 == 0 ) || (nd.state.right_missionaries - 1 >= nd.state.right_cannibals))){
				node new_node = nd;
				new_node.state.left_missionaries += 1;
				new_node.state.right_missionaries -= 1;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				new_node.parent_node = nd.state;
				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}
		//boat on left
		else if(nd.state.left_boats == 1 && nd.state.left_missionaries >= 1){
			if (((nd.state.left_missionaries - 1 == 0 ) || (nd.state.left_missionaries - 1 >= nd.state.left_cannibals)) &&
				((nd.state.right_missionaries + 1 == 0) || (nd.state.right_missionaries + 1 >= nd.state.right_cannibals))){
				node new_node = nd;
				new_node.state.left_missionaries -= 1;
				new_node.state.right_missionaries += 1;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				new_node.parent_node = nd.state;
				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}
		///////////
		//Check 2. Put two missionary in the boat

		//boat on right
		if (nd.state.right_boats == 1 && nd.state.right_missionaries >= 2){
			if (((nd.state.left_missionaries  + 2 == 0) || (nd.state.left_missionaries + 2 >= nd.state.left_cannibals)) &&
				((nd.state.right_missionaries - 2 == 0) || (nd.state.right_missionaries - 2 >= nd.state.right_cannibals))){
				node new_node = nd;
				new_node.state.left_missionaries += 2;
				new_node.state.right_missionaries -= 2;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				new_node.parent_node = nd.state;
				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}
		//boat on left
		  else if(nd.state.left_boats == 1 && nd.state.left_missionaries >= 2){
			if (((nd.state.left_missionaries - 2 == 0) || (nd.state.left_missionaries - 2 >= nd.state.left_cannibals)) &&
				((nd.state.right_missionaries + 2 == 0) || (nd.state.right_missionaries + 2 >= nd.state.right_cannibals))){
				node new_node = nd;
				new_node.state.left_missionaries -= 2;
				new_node.state.right_missionaries += 2;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				new_node.parent_node = nd.state;
				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}

		///////////
		//Check 3. Put one cannibal in the boat

		//boat on right
		 if (nd.state.right_boats == 1 && nd.state.right_cannibals >= 1){
			if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals + 1)) &&
				((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals - 1))){
				node new_node = nd;
				new_node.state.left_cannibals += 1;
				new_node.state.right_cannibals -= 1;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				new_node.parent_node = nd.state;
				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}
		//boat on left
		  else if(nd.state.left_boats == 1 && nd.state.left_cannibals >= 1){
			if (((nd.state.left_missionaries == 0 ) || (nd.state.left_missionaries >= nd.state.left_cannibals - 1)) &&
				((nd.state.right_missionaries == 0 ) || (nd.state.right_missionaries >= nd.state.right_cannibals + 1))){
				node new_node = nd;
				new_node.state.left_cannibals -= 1;
				new_node.state.right_cannibals += 1;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				new_node.parent_node = nd.state;
				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}

		///////////
		//Check 4. Put one cannibal and one missionary in the boat

		//boat on right
 if (nd.state.right_boats == 1 && nd.state.right_missionaries >= 1 && nd.state.right_cannibals >= 1 ){
			if (((nd.state.left_missionaries + 1 == 0) || (nd.state.left_missionaries + 1 >= nd.state.left_cannibals + 1)) &&
				((nd.state.right_missionaries - 1 == 0) || (nd.state.right_missionaries - 1 >= nd.state.right_cannibals - 1))){
				node new_node = nd;
				new_node.state.left_missionaries += 1;
				new_node.state.right_missionaries -= 1;
				new_node.state.left_cannibals += 1;
				new_node.state.right_cannibals -= 1;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				new_node.parent_node = nd.state;
				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}
		//boat on left
		  else if(nd.state.left_boats == 1 && nd.state.left_missionaries >= 1 && nd.state.left_cannibals >= 1){
			if (((nd.state.left_missionaries  - 1 == 0) || (nd.state.left_missionaries - 1 >= nd.state.left_cannibals - 1)) &&
				((nd.state.right_missionaries + 1 == 0) || (nd.state.right_missionaries + 1 >= nd.state.right_cannibals + 1)))
			{
				node new_node = nd;
				new_node.state.left_missionaries -= 1;
				new_node.state.right_missionaries += 1;
				new_node.state.left_cannibals -= 1;
				new_node.state.right_cannibals += 1;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				new_node.parent_node = nd.state;
				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}


		///////////
		//Check 5. Put two cannibal in the boat

		//boat on right
		if (nd.state.right_boats == 1 && nd.state.right_cannibals >= 2){
			if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals + 2)) &&
				((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals - 2))){
				node new_node = nd;
				new_node.state.left_cannibals += 2;
				new_node.state.right_cannibals -= 2;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				new_node.parent_node = nd.state;


				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}
		//boat on left
		  else if(nd.state.left_boats == 1 && nd.state.left_cannibals >= 2){
			if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals - 2)) &&
				((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals + 2))){
				node new_node = nd;
				new_node.state.left_cannibals -= 2;
				new_node.state.right_cannibals += 2;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				new_node.parent_node = nd.state;

				new_node.parents = state_string(new_node) + "<--" + nd.parents;
				myqueue.push(new_node);
				if (nodePassed(new_node, goal_node)){
					return true;
				}
			}
		}


		myqueue.pop();
	}
	while (!myqueue.empty()){
		node temp = myqueue.front();
		print_node(temp);
		myqueue.pop();
	}


	return false;

}

int main(int argc, _TCHAR* argv[])
{
	queue<node> some_queue;

	if (general_search(5,some_queue)){
		print_node(some_queue.front());
		printf("found a soultion\n");


		node temp = some_queue.back();
		print_node2(temp);
		some_queue.pop();

	}
	  else {
		printf("failed to find a soultion\n");
	}
	printf("\nhello world\n");
	getchar();
	return 0;
}


