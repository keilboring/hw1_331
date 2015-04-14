// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
// Keil Boring CS311 HW#1


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <deque>
#include <string>
#include <set>
#include <unordered_map>
#include <conio.h>
#include <windows.h>
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
	//int operation = 0;
	int depth = 0;
	int heuristic;
	string parent_key = "";
	string state_key = "";
};

int NODES_EXPANDED = 0;

void print_node(node temp){
	cout << temp.state.left_missionaries << "," << temp.state.left_cannibals << "," << temp.state.left_boats << "," << temp.state.right_missionaries
		<< "," << temp.state.right_cannibals << "," << temp.state.right_boats << "," << "    depth=" << temp.depth <<  endl;

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

void printCompletePath(node nd,unordered_map<string,node> hashTable){
	cout << "found soultion complete path from back to front" << endl;

	node temp_node = nd;

	do{ 		
		print_node(temp_node);
		temp_node = hashTable[temp_node.parent_key];
	} while (temp_node.parent_key != "root");
	print_node(temp_node);
	cout << "depth of soution was = " << nd.depth << endl;
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
				new_node.parent_key = nd.state_key;
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;
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
				new_node.parent_key = nd.state_key;
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;
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
				new_node.parent_key = nd.state_key;				
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;
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
				new_node.parent_key = nd.state_key;
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;
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
				new_node.parent_key = nd.state_key;
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;

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
				new_node.parent_key = nd.state_key;
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;
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
				new_node.parent_key = nd.state_key;
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;

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
				new_node.parent_key = nd.state_key;
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;
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
				new_node.parent_key = nd.state_key;
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;

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
				new_node.parent_key = nd.state_key;
				new_node.heuristic = new_node.state.right_cannibals + new_node.state.right_missionaries;
				return true;
			}
		}
		break;
	default:
		cout << "no case mattched given successor number";
	}
	return false;
}

bool bfs(node starting_node, node goal_node, deque<node> &fringe){
	unordered_map<string, node> hashTable;
	node nd;

	fringe.push_front(starting_node);
	hashTable.emplace(starting_node.state_key, starting_node);

	while (!fringe.empty()){
		//get first node in queue
		nd = fringe.front();
		fringe.pop_front();
		print_node(nd);

		//Is this our goal node
		if (nodePassed(nd, goal_node)){
			printCompletePath(nd, hashTable);
			return true;
		}

		//expand node
		for (int i = 1; i <= 5; i++){
			node new_node = nd;
			if (ExpandNode(nd, i, new_node) == true){

				//if we have never seen state before add it
				if (hashTable.find(new_node.state_key) == hashTable.end()){
					hashTable.emplace(new_node.state_key, new_node);
					fringe.push_back(new_node);
				}
			}
		}
		NODES_EXPANDED += 1;
	}
	return false;
}


bool dfs(node starting_node, node goal_node, deque<node> &fringe){
	unordered_map<string, node> hashTable;
	node nd;

	fringe.push_front(starting_node);
	hashTable.emplace(starting_node.state_key, starting_node);

	while (!fringe.empty()){
		//get first node in queue
		nd = fringe.front();
		fringe.pop_front();
		print_node(nd);

		//Is this our goal node
		if (nodePassed(nd, goal_node)){
			printCompletePath(nd, hashTable);
			return true;
		}

		//expand node
		for (int i = 5; i > 0; i--){
			node new_node = nd;
			if (ExpandNode(nd, i, new_node) == true){

				//if we have never seen state before add it
				if (hashTable.find(new_node.state_key) == hashTable.end()){
					hashTable.emplace(new_node.state_key, new_node);
					fringe.push_front(new_node);
				}
				//else replace only if new depth is less
				else{
					node existing_node = hashTable[new_node.state_key];

					//should never be true for bfs
					if (existing_node.depth > new_node.depth){
						hashTable.erase(existing_node.state_key);
						hashTable.emplace(new_node.state_key, new_node);
						fringe.push_front(new_node);
					}
				}

			}
		}
		NODES_EXPANDED += 1;
	}
	return false;
}


bool idfs(node starting_node, node goal_node, deque<node> &fringe){
	unordered_map<string, node> hashTable;
	node nd;


	int max_depth = 1;

	while (max_depth){
		cout << "max depth=" << max_depth << endl;
		hashTable.clear();
		hashTable.emplace(starting_node.state_key, starting_node);
		fringe.push_front(starting_node);

		while (!fringe.empty()){
			//get front of queue
			nd = fringe.front();
			fringe.pop_front();
			//print_node(nd);

			//check if goal node
			if (nodePassed(nd, goal_node)){
				printCompletePath(nd, hashTable);
				return true;
			}

			//check if depth is passed max depth
			if (nd.depth <= max_depth){

				//expand node
				for (int i = 5; i > 0; i--){
					node new_node = nd;
					if (ExpandNode(nd, i, new_node) == true){
						//if we have never seen state before add it
						if (hashTable.find(new_node.state_key) == hashTable.end()){
							hashTable.emplace(new_node.state_key, new_node);
							fringe.push_front(new_node);
						}
						//else replace only if new depth is less
						else{
							node existing_node = hashTable[new_node.state_key];

							//should never be true for bfs
							if (existing_node.depth > new_node.depth){
								hashTable.erase(existing_node.state_key);
								hashTable.emplace(new_node.state_key, new_node);
								fringe.push_front(new_node);
							}
						}

					}
				}
			}

			NODES_EXPANDED += 1;
		}
		max_depth += 1;
	}
	return false;
}



class CompareHeuristic {
public:
	bool operator()(node& n1, node& n2)
	{
		if (n1.depth + n1.heuristic < n2.depth + n2.heuristic){
			return true;
		}

		return false;
	}
};

bool aStar(node starting_node, node goal_node, deque<node> &fringe){
	unordered_map<string, node> hashTable;
	node nd;
	priority_queue<node, vector<node>, CompareHeuristic> pq;
	pq.push(starting_node);
	hashTable.emplace(starting_node.state_key, starting_node);

	while (!pq.empty()){
		//get first node in queue
		nd = pq.top();
		pq.pop();
		print_node(nd);

		//Is this our goal node
		if (nodePassed(nd, goal_node)){
			printCompletePath(nd, hashTable);
			return true;
		}

		//expand node
		for (int i = 1; i <= 5; i++){
			node new_node = nd;
			if (ExpandNode(nd, i, new_node) == true){

				//if we have never seen state before add it
				if (hashTable.find(new_node.state_key) == hashTable.end()){
					hashTable.emplace(new_node.state_key, new_node);
					pq.push(new_node);
				}
				//else replace only if new depth is less
				else{
					node existing_node = hashTable[new_node.state_key];

					//should never be true for bfs
					if (existing_node.depth > new_node.depth){
						hashTable.erase(existing_node.state_key);
						hashTable.emplace(new_node.state_key, new_node);
						pq.push(new_node);
					}
				}

			}
		}
		NODES_EXPANDED += 1;
	}
	return false;
}


int main(int argc, _TCHAR* argv[])
{
	deque<node> some_queue;
	node starting_node;
	node goal_node;

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
	starting_node.state_key = state_string(starting_node);
	starting_node.depth = 0;
	starting_node.heuristic = starting_node.state.right_cannibals + starting_node.state.right_missionaries;
	starting_node.parent_key = "root";


	if (aStar(starting_node, goal_node, some_queue)){
		cout << "found a soultion\n";
		cout << "Nodes expanded ="  << NODES_EXPANDED << endl;
	}
	else
		cout << "failed to find a soultion";

	getchar();
	return 0;
}


