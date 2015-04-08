// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <deque>
#include <string>
#include <set>

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
	//bank_state parent_node;
	int operation = 0;
	int depth = 0;
	int path_cost = 0;
	//node *parent_node;
	//string parents = "";
	string state_key = "";
};


void print_node(node temp){
	cout << temp.state.left_missionaries << "," << temp.state.left_cannibals << "," << temp.state.left_boats << "," << temp.state.right_missionaries
		<< "," << temp.state.right_cannibals << "," << temp.state.right_boats << "," << "    depth=" << temp.depth <<
		"		parent="
		/*		<< temp.parent_node.left_missionaries << "," << temp.parent_node.left_cannibals << "," << temp.parent_node.left_boats << "," << temp.parent_node.right_missionaries
			<< "," << temp.parent_node.right_cannibals << "," << temp.parent_node.right_boats << ",             "  */
			<< endl;
	//<< temp.parents << endl;
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

bool ExpandNode(node nd, int successor, node &new_node){


	switch (successor){
	case 1:
		///////////
		//Check 1. Put one missionary in the boat
		new_node = nd;
		//boat on right
		if (nd.state.right_boats == 1 && nd.state.right_missionaries >= 1){
			if (((nd.state.left_missionaries + 1 == 0) || (nd.state.left_missionaries + 1 >= nd.state.left_cannibals)) &&
				((nd.state.right_missionaries - 1 == 0) || (nd.state.right_missionaries - 1 >= nd.state.right_cannibals))){
				new_node.state.left_missionaries += 1;
				new_node.state.right_missionaries -= 1;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				//new_node.parent_node = nd.state;
				//new_node.parents = state_string(new_node) + "<--" + nd.parents;
				new_node.state_key = state_string(new_node);

			}
		}
		//boat on left
		else if (nd.state.left_boats == 1 && nd.state.left_missionaries >= 1){
			if (((nd.state.left_missionaries - 1 == 0) || (nd.state.left_missionaries - 1 >= nd.state.left_cannibals)) &&
				((nd.state.right_missionaries + 1 == 0) || (nd.state.right_missionaries + 1 >= nd.state.right_cannibals))){
				new_node.state.left_missionaries -= 1;
				new_node.state.right_missionaries += 1;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				//new_node.parent_node = nd.state;
				//new_node.parents = state_string(new_node) + "<--" + nd.parents;
				new_node.state_key = state_string(new_node);

			}
		}
		break;

	case 2:
		///////////
		//Check 2. Put two missionary in the boat

		//boat on right
		if (nd.state.right_boats == 1 && nd.state.right_missionaries >= 2){
			if (((nd.state.left_missionaries + 2 == 0) || (nd.state.left_missionaries + 2 >= nd.state.left_cannibals)) &&
				((nd.state.right_missionaries - 2 == 0) || (nd.state.right_missionaries - 2 >= nd.state.right_cannibals))){
				new_node.state.left_missionaries += 2;
				new_node.state.right_missionaries -= 2;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				//new_node.parent_node = nd.state;
				//new_node.parents = state_string(new_node) + "<--" + nd.parents;
				new_node.state_key = state_string(new_node);

			}
		}
		//boat on left
		else if (nd.state.left_boats == 1 && nd.state.left_missionaries >= 2){
			if (((nd.state.left_missionaries - 2 == 0) || (nd.state.left_missionaries - 2 >= nd.state.left_cannibals)) &&
				((nd.state.right_missionaries + 2 == 0) || (nd.state.right_missionaries + 2 >= nd.state.right_cannibals))){
				new_node.state.left_missionaries -= 2;
				new_node.state.right_missionaries += 2;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				//new_node.parent_node = nd.state;
				//new_node.parents = state_string(new_node) + "<--" + nd.parents;
				new_node.state_key = state_string(new_node);


			}
		}
		break;

	case 3:
		///////////
		//Check 3. Put one cannibal in the boat

		//boat on right
		if (nd.state.right_boats == 1 && nd.state.right_cannibals >= 1){
			if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals + 1)) &&
				((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals - 1))){
				new_node.state.left_cannibals += 1;
				new_node.state.right_cannibals -= 1;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				//new_node.parent_node = nd.state;
				//new_node.parents = state_string(new_node) + "<--" + nd.parents;
				new_node.state_key = state_string(new_node);


			}
		}
		//boat on left
		else if (nd.state.left_boats == 1 && nd.state.left_cannibals >= 1){
			if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals - 1)) &&
				((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals + 1))){
				new_node.state.left_cannibals -= 1;
				new_node.state.right_cannibals += 1;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				//new_node.parent_node = nd.state;
				//new_node.parents = state_string(new_node) + "<--" + nd.parents;
				new_node.state_key = state_string(new_node);


			}
		}
		break;

	case 4:
		///////////
		//Check 4. Put one cannibal and one missionary in the boat

		//boat on right
		if (nd.state.right_boats == 1 && nd.state.right_missionaries >= 1 && nd.state.right_cannibals >= 1){
			if (((nd.state.left_missionaries + 1 == 0) || (nd.state.left_missionaries + 1 >= nd.state.left_cannibals + 1)) &&
				((nd.state.right_missionaries - 1 == 0) || (nd.state.right_missionaries - 1 >= nd.state.right_cannibals - 1))){
				new_node.state.left_missionaries += 1;
				new_node.state.right_missionaries -= 1;
				new_node.state.left_cannibals += 1;
				new_node.state.right_cannibals -= 1;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				//new_node.parent_node = nd.state;
				//new_node.parents = state_string(new_node) + "<--" + nd.parents;
				new_node.state_key = state_string(new_node);


			}
		}
		//boat on left
		else if (nd.state.left_boats == 1 && nd.state.left_missionaries >= 1 && nd.state.left_cannibals >= 1){
			if (((nd.state.left_missionaries - 1 == 0) || (nd.state.left_missionaries - 1 >= nd.state.left_cannibals - 1)) &&
				((nd.state.right_missionaries + 1 == 0) || (nd.state.right_missionaries + 1 >= nd.state.right_cannibals + 1)))
			{
				new_node.state.left_missionaries -= 1;
				new_node.state.right_missionaries += 1;
				new_node.state.left_cannibals -= 1;
				new_node.state.right_cannibals += 1;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				//new_node.parent_node = nd.state;
				//new_node.parents = state_string(new_node) + "<--" + nd.parents;
				new_node.state_key = state_string(new_node);

			}
		}
		break;

	case 5:
		///////////
		//Check 5. Put two cannibal in the boat

		//boat on right
		if (nd.state.right_boats == 1 && nd.state.right_cannibals >= 2){
			if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals + 2)) &&
				((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals - 2))){
				new_node.state.left_cannibals += 2;
				new_node.state.right_cannibals -= 2;
				new_node.state.left_boats = 1;
				new_node.state.right_boats = 0;
				new_node.depth += 1;
				//new_node.parent_node = nd.state;


				//new_node.parents = state_string(new_node) + "<--" + nd.parents;
				new_node.state_key = state_string(new_node);


			}
		}
		//boat on left
		else if (nd.state.left_boats == 1 && nd.state.left_cannibals >= 2){
			if (((nd.state.left_missionaries == 0) || (nd.state.left_missionaries >= nd.state.left_cannibals - 2)) &&
				((nd.state.right_missionaries == 0) || (nd.state.right_missionaries >= nd.state.right_cannibals + 2))){
				new_node.state.left_cannibals -= 2;
				new_node.state.right_cannibals += 2;
				new_node.state.left_boats = 0;
				new_node.state.right_boats = 1;
				new_node.depth += 1;
				new_node.state_key = state_string(new_node);
			}
		}
		break;
	default:
		cout << "no case mattched given successor number";
	}
	return false;
}

bool bfs(node starting_node, node goal_node, deque<node> &fringe){
	set<string> myset;
	node nd;

	auto result_set = myset.insert(starting_node.state_key);
	fringe.push_back(starting_node);
	while (!fringe.empty()){
		node new_node = nd;
		nd = fringe.front();
		print_node(nd);



		ExpandNode(nd, 0, new_node);


		result_set = myset.insert(new_node.state_key);
		if (result_set.second)
			fringe.push_back(new_node);
		if (nodePassed(new_node, goal_node)){
			return true;
		}
		fringe.pop_front();
	}
	return false;
}

bool general_search(int problem, deque<node> &myqueue){

	//create queue

	//while (!myqueue.empty()){
	//	node temp = myqueue.front();
	//	print_node(temp);
	//	myqueue.pop();
	//}


	return false;

}

int main(int argc, _TCHAR* argv[])
{
	deque<node> some_queue;
	node starting_node;
	node goal_node;

	goal_node.state.left_missionaries = 100;
	goal_node.state.left_cannibals = 90;
	goal_node.state.left_boats = 1;
	goal_node.state.right_missionaries = 0;
	goal_node.state.right_cannibals = 0;
	goal_node.state.right_boats = 0;


	starting_node.state.left_missionaries = 0;
	starting_node.state.left_cannibals = 0;
	starting_node.state.left_boats = 0;
	starting_node.state.right_missionaries = 100;
	starting_node.state.right_cannibals = 90;
	starting_node.state.right_boats = 1;
	starting_node.state_key = state_string(starting_node);

	if (general_search(5,some_queue)){
		print_node(some_queue.front());
		printf("found a soultion\n");


		node temp = some_queue.back();
		print_node(temp);
		some_queue.pop_front();

	}
	  else {
		printf("failed to find a soultion\n");
	}
	printf("\nhello world\n");
	getchar();
	return 0;
}


