// ConsoleApplication2.cpp : Defines the entry point for the console application.
//
// Keil Boring CS311 HW#1


#include <iostream>
#include <fstream>
#include <queue>
#include <deque>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

struct bank_state{
	int left_missionaries ;
	int left_cannibals ;
	int left_boats ;
	int right_missionaries ;
	int right_cannibals ;
	int right_boats ;

	//bank_state() {
	//	left_missionaries = 0;
	//	left_cannibals = 0;
	//	left_boats = 0;
	//	right_missionaries = 0;
	//	right_cannibals = 0;
	//	right_boats = 0;
	//}
};

struct node{
	bank_state state;
	int depth ;
	int heuristic;
	string parent_key ;
	string state_key ;

/*	node() {
		depth = 0;
	}*/
};

int NODES_EXPANDED = 0;

void print_node(node temp){
	cout << temp.state.left_missionaries << "," << temp.state.left_cannibals << "," << temp.state.left_boats << "," << temp.state.right_missionaries
		<< "," << temp.state.right_cannibals << "," << temp.state.right_boats << "," << "    depth=" << temp.depth <<  endl;

}
string IntToString(int a)
{
	ostringstream temp;
	temp << a;
	return temp.str();
}
string state_string(node temp){
	string temp_string = "";
	temp_string =  IntToString( temp.state.left_missionaries )  + ","  + IntToString( temp.state.left_cannibals )  + ","  + IntToString( temp.state.left_boats )  + ","  + IntToString( temp.state.right_missionaries
		)  + ","  + IntToString( temp.state.right_cannibals ) + ","  + IntToString( temp.state.right_boats );   
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

void printCompletePath(node nd, unordered_map<string, node> hashTable, string output_file){
	cout << "found soultion complete path from back to front" << endl;
	ofstream outFile;
	outFile.open(output_file);

	node temp_node = nd;
	stack<string> lines;
	do{ 		
		lines.push( state_string(temp_node) + " depth of " + IntToString(temp_node.depth));
		temp_node = hashTable[temp_node.parent_key];
	} while (temp_node.parent_key != "root");

	lines.push( state_string(temp_node) + " depth of " + IntToString(temp_node.depth));

	while (!lines.empty()){
		outFile << lines.top() << endl;
		cout << lines.top() << endl;
		lines.pop();
	}



	cout << "depth of soution was = " << nd.depth << "     " << endl;
	outFile << "depth of soution was = " << nd.depth << "   \n" << endl;
	cout << "expanded nodes" << NODES_EXPANDED << "      \n" << endl;
	outFile << "expanded nodes" << NODES_EXPANDED << "     \n" << endl;
	outFile.close();


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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
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
                                   new_node.heuristic =((new_node.state.right_cannibals + new_node.state.right_missionaries)/2);
				return true;
			}
		}
		break;
	default:
		cout << "no case mattched given successor number";
	}
	return false;
}

bool bfs(node starting_node, node goal_node, string output_file){
	unordered_map<string, node> hashTable;
	node nd;
	deque<node> fringe;
	fringe.push_front(starting_node);
	pair<string, node> mypair(starting_node.state_key, starting_node);
	hashTable.insert(mypair);

	while (!fringe.empty()){
		//get first node in queue
		nd = fringe.front();
		fringe.pop_front();
		print_node(nd);

		//Is this our goal node
		if (nodePassed(nd, goal_node)){
			printCompletePath(nd, hashTable, output_file);
			return true;
		}

		NODES_EXPANDED += 1;
		//expand node
		for (int i = 1; i <= 5; i++){
			node new_node = nd;
			if (ExpandNode(nd, i, new_node) == true){

				//if we have never seen state before add it
				if (hashTable.find(new_node.state_key) == hashTable.end()){
					pair<string, node> temp_pair(new_node.state_key, new_node);
					hashTable.insert(temp_pair);
					fringe.push_back(new_node);
				}
			}
		}
	}
	return false;
}


bool dfs(node starting_node, node goal_node, string output_file){
	unordered_map<string, node> hashTable;
	node nd;
	deque<node> fringe;
	fringe.push_front(starting_node);
	pair<string, node> mypair(starting_node.state_key, starting_node);
	hashTable.insert(mypair);

	while (!fringe.empty()){
		//get first node in queue
		nd = fringe.front();
		fringe.pop_front();
		print_node(nd);
		//Sleep(1000);
		//Is this our goal node
		if (nodePassed(nd, goal_node)){
			printCompletePath(nd, hashTable, output_file);
			return true;
		}
		
		NODES_EXPANDED += 1;

		//expand node
		for (int i = 5; i > 0; i--){
			node new_node = nd;
			if (ExpandNode(nd, i, new_node) == true){
				//print_node(new_node);
				//if we have never seen state before add it
				if (hashTable.find(new_node.state_key) == hashTable.end()){
					pair<string, node> temp_pair(new_node.state_key, new_node);
					hashTable.insert(temp_pair);
					fringe.push_front(new_node);
				}
				//else replace only if new depth is less
				else{
					node existing_node = hashTable[new_node.state_key];

					//should never be true for bfs
					if (existing_node.depth > new_node.depth){
						hashTable.erase(existing_node.state_key);
						pair<string, node> temp_pair(new_node.state_key, new_node);
						hashTable.insert(temp_pair);
						fringe.push_front(new_node);
					}
				}

			}
		}
	}
	return false;
}


bool idfs(node starting_node, node goal_node, string output_file){
	unordered_map<string, node> hashTable;
	node nd;
	deque<node> fringe;

	int max_depth = 1;

	while (max_depth){
		cout << "max depth=" << max_depth << endl;
		hashTable.clear();
		pair<string, node> mypair(starting_node.state_key, starting_node);
		hashTable.insert(mypair);
		fringe.push_front(starting_node);

		while (!fringe.empty()){
			//get front of queue
			nd = fringe.front();
			fringe.pop_front();
			//print_node(nd);

			//check if goal node
			if (nodePassed(nd, goal_node)){
				printCompletePath(nd, hashTable,output_file);
				return true;
			}

			NODES_EXPANDED += 1;
			//check if depth is passed max depth
			if (nd.depth <= max_depth){

				//expand node
				for (int i = 5; i > 0; i--){
					node new_node = nd;
					if (ExpandNode(nd, i, new_node) == true){
						//if we have never seen state before add it
						if (hashTable.find(new_node.state_key) == hashTable.end()){
							pair<string, node> temp_pair(new_node.state_key, new_node);
							hashTable.insert(temp_pair);
							fringe.push_front(new_node);
						}
						//else replace only if new depth is less
						else{
							node existing_node = hashTable[new_node.state_key];

							//should never be true for bfs
							if (existing_node.depth > new_node.depth){
								hashTable.erase(existing_node.state_key);
								pair<string, node> temp_pair(new_node.state_key, new_node);
								hashTable.insert(temp_pair);
								fringe.push_front(new_node);
							}
						}

					}
				}
			}

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

bool aStar(node starting_node, node goal_node, string output_file){
	unordered_map<string, node> hashTable;
	node nd;
	priority_queue<node, vector<node>, CompareHeuristic> pq;
	pq.push(starting_node);
	pair<string, node> mypair(starting_node.state_key, starting_node);
	hashTable.insert(mypair);

	while (!pq.empty()){
		//get first node in queue
		nd = pq.top();
		pq.pop();
		print_node(nd);

		//Is this our goal node
		if (nodePassed(nd, goal_node)){
			printCompletePath(nd, hashTable, output_file);
			return true;
		}

		NODES_EXPANDED += 1;
		//expand node
		for (int i = 1; i <= 5; i++){
			node new_node = nd;
			if (ExpandNode(nd, i, new_node) == true){

				//if we have never seen state before add it
				if (hashTable.find(new_node.state_key) == hashTable.end()){
					pair<string, node> temp_pair(new_node.state_key, new_node);
					hashTable.insert(temp_pair); 
					pq.push(new_node);
				}
				//else replace only if new depth is less
				else{
					node existing_node = hashTable[new_node.state_key];

					//should never be true for bfs
					if (existing_node.depth > new_node.depth){
						hashTable.erase(existing_node.state_key);
						pair<string, node> temp_pair(new_node.state_key, new_node);
						hashTable.insert(temp_pair);
						pq.push(new_node);
					}
				}

			}
		}
	}
	return false;
}


int main(int argc, char *argv[])
{
	deque<node> some_queue;
	node starting_node;
	node goal_node;
	vector<string> all_args;

	if (argc != 5){
		cout << "Total of 4 command line arguements must be given" << endl;
		return -1;
	}
	if (argc > 1) {
		all_args.assign(argv, argv + argc);
	}


	//startFile
	string line;
	ifstream startFile(all_args[1]);
	vector<string> mylist;
	string inputValues[8];
	if (startFile.is_open())
	{
		int i = 0;
		while (getline(startFile, line))
		{
			string delim = ",";
			auto start = 0U;
			auto end = line.find(delim);
			//inputValues[i] = line.substr(start, end - start);
			while (end != string::npos){
				inputValues[i] = line.substr(start, end - start);
				cout << line.substr(start, end - start) << endl;
				mylist.push_back(line.substr(start, end - start));
				start = end + delim.length();
				end = line.find(delim, start);
				i++;
			}
			cout << line.substr(start, end) << endl;
		}
		startFile.close();
	}
	for (int i = 0; i < 6; i++){
		if (inputValues[i] == ""){
			inputValues[i] = "0";
		}
	}
	starting_node.state.left_missionaries = stoi(inputValues[0]);
	starting_node.state.left_cannibals = stoi(inputValues[1]);
	starting_node.state.left_boats = 0;
	starting_node.state.right_missionaries = stoi(inputValues[2]);
	starting_node.state.right_cannibals = stoi(inputValues[3]);
	starting_node.state.right_boats = 1;
	starting_node.state_key = state_string(starting_node);
	starting_node.depth = 0;
	starting_node.heuristic = starting_node.state.right_cannibals + starting_node.state.right_missionaries;
	starting_node.parent_key = "root";

	//goal file



	cout << all_args[2] << endl;
	ifstream goalFile(all_args[2]);
	if (goalFile.is_open())
	{
		int i = 0;
		while (getline(goalFile, line))
		{
			string delim = ",";
			auto start = 0U;
			auto end = line.find(delim);
			while (end != string::npos){
				cout << line.substr(start, end - start) << endl;
				mylist.push_back(line.substr(start, end - start));
				inputValues[i] = "";
				inputValues[i] = line.substr(start, end - start);
				start = end + delim.length();
				end = line.find(delim, start);
				i++;
			}
			cout << line.substr(start, end) << endl;
		}
		goalFile.close();
	}
	for (int i = 0; i < 6; i++){
		if (inputValues[i] == ""){
			inputValues[i] = "0";
		}
	}
	goal_node.state.left_missionaries = stoi(inputValues[0]);
	goal_node.state.left_cannibals = stoi(inputValues[1]);
	goal_node.state.left_boats = 1;
	goal_node.state.right_missionaries = stoi(inputValues[3]);
	goal_node.state.right_cannibals = stoi(inputValues[4]);
	goal_node.state.right_boats = 0;



	//Mode
	if ( all_args[3] == "bfs"){
		cout << "bfs selected" << endl;
		bfs(starting_node, goal_node, all_args[4]);
	}
	else if (all_args[3] == "dfs"){
		cout << "dfs selected" << endl;
		dfs(starting_node, goal_node, all_args[4]);
	}
	else if (all_args[3] == "iddfs"){
		cout << "iddfs selected" << endl;
		idfs(starting_node, goal_node, all_args[4]);
	}
	else if (all_args[3] == "astar"){
		cout << "astar selected" << endl;
		aStar(starting_node, goal_node, all_args[4]);

	}
	cout << "Nodes expanded ="  << NODES_EXPANDED << endl;

	//getchar();
	return 0;
}


