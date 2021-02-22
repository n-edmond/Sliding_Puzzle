#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Board.h"

using namespace std;

struct Comparator
{ //used to help determine which path to select, returns bool value
	bool operator()(Board* left, Board* right)
	{
		return left->get_f() > right->get_f();
	}
};
void read_files(string filename);//reads the files and completes program
size_t hashing(vector<vector<int>> puzzles);
int get_inversion_count(vector<vector<int>> puzzle); //gets inversion
bool is_solvable_check(const Board& board); //checks if a puzzle is solveable
void solve(Board* start, const Board* final); //will begin solving if yes


int main() {
	string file = "input.txt";
	read_files(file);

	//USED FOR TESTING
	  //e_puzzle = new Board(matrix);
	  //solve(e_puzzle, win_condition);
	  //delete e_puzzle;//deleting pointer
	  //delete win_condition;//deleting pointer
	return 0;
}

size_t hashing(vector<vector<int>> puzzles)
{//using to get hash values of string
	string result;
	for (size_t i = 0; i < puzzles.size(); ++i) {
		for (size_t j = 0; j < puzzles[i].size(); ++j) {
			string tmp = to_string(puzzles[i][j]);//converting to string
			result += tmp;//concatinating to result
			cout << result;
		}
	}
	return hash<string>{}(result);
}

int getInvCount(vector<vector<int>> puzzle)
{//idea retrieved from geeksForGeeks
//checks if values are in revers order of goal state
	vector<int> tmp(9);//creates temp vector
	for (size_t i = 0; i < puzzle.size(); ++i)
	{
		for (size_t j = 0; j < puzzle[i].size(); ++j)
		{
			tmp[i * puzzle[i].size() + j] = puzzle[i][j];
		}
	}

	int count = 0;
	for (size_t i = 0; i < tmp.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < tmp.size(); ++j)
		{
			if (tmp[j] && tmp[i] && tmp[i] > tmp[j])
				++count;
		}
	}
	return count;//returns number of inversions found
}

bool isSolvable(const Board& board)
{//idea retrieved from geeksForGeeks
//calls for inversion counter to see if puzzle is solveable
	vector<vector<int>> puzzle = board.getPuzzles();
	int count = getInvCount(puzzle);
	return count % 2 == 0; //if even it is solvable, otherwise it is false
}

void solve(Board* start, const Board* final)
{//solves the given puzle
	if (!isSolvable(*start))
	{//if the puzzle cannot be solved, state it and end
		cout << "This puzzle cannot be solved!" << endl;
		return;
	}

	//creating a priority queue to store each board
	priority_queue<Board*, std::vector<Board*>, Comparator> board_store;
	//creating map to keep see whcih states have been visited
	unordered_map<size_t, vector<vector<int>>> visited;

	start->manhat(*final);//calculates heuristics using manhattan distance
	start->calc_f();//calcualtes f to determine start point
	board_store.push(start);

	while (!board_store.empty())
	{//while the vector holding all the boards isnt empty
		Board* min = board_store.top();
		board_store.pop();
		size_t key = hashing(min->getPuzzles());
		visited[key] = min->getPuzzles();

		if (*min == *final)
		{
			min->display_movesets();
			return;
		}
		for (size_t i = 0; i < 4; ++i)
		{
			pair<int, int> coord = min->get_loc_of_space();
			if (min->canGenerate(coord.first, coord.second, i))
			{
				Board* tmp = min->create_child_node(coord.first, coord.second, i);
				tmp->set_parent_node(min);
				tmp->manhat(*final);
				tmp->calc_g(*min);
				tmp->calc_f();
				size_t tmpKey = hashing(tmp->getPuzzles());
				if (visited.find(tmpKey) == visited.end())
				{
					board_store.push(tmp);
					visited[tmpKey] = tmp->getPuzzles();
				}
			}
		}
	}
}

void read_files(string filename)
{
	vector<vector<int>> goal = { {1,2,3}, {4,5,6}, {7,8,0} };//goal state
	vector<vector<int>> data;//holds the data from the file
	Board* win_condition = new Board(goal);//setting the win gate for class use
	Board* e_puzzle;//eight puzzle pointer
	int counter = 1;//counter to go through all puzzle solutions
	int num_of_puzzles;//saves how many puzzles to solve in a file
	string tmpString;//saves item as a string for conversion later

	ifstream file;
	file.open(filename);//open file here

	file >> num_of_puzzles;

	while (!file.eof()) {

		while (counter < num_of_puzzles + 1) {
			cout << "Solving puzzle #" << counter << endl;
			for (int i = 0; i < 3; i++)
			{
				vector<int> tmpVec;
				for (int j = 0; j < 3; j++)
				{
					file >> tmpString;
					if (tmpString == "E")
					{//if E is found, change it to 0, then convert to an int
						tmpString = "0";
						int true_val = stoi(tmpString);//returns val of string
						//cout<<tmpString<< endl;
						tmpVec.push_back(true_val);//
					}
					else
					{//change tempstring to int value if E is not encountered
						int myint1 = stoi(tmpString);
						//cout<<tmpString<< endl;
						tmpVec.push_back(myint1);
					}
				}
				data.push_back(tmpVec);
			}
			e_puzzle = new Board(data);
			solve(e_puzzle, win_condition);
			delete e_puzzle;//deleting pointer
			delete win_condition;//deleting pointer

			counter++;//increment counter to swap to next puzzle 
			//PRINTS THE ARRAY. USED FOR TESTING
			data.clear();//erase the vector
			//continue;
		}
	}
	file.close();

}