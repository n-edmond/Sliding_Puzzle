#include "Board.h"


Board::Board(vector<vector<int>> puzzles)
{
	this->puzzles = puzzles;
	this->parent = nullptr;
}

Board::Board(const Board& rhs)
{
	this->puzzles = rhs.puzzles;
	this->parent = nullptr;
}

Board* Board::create_child_node(int x, int y, int pos)
{//creates the child node
	pair<int, int> coord = this->get_loc_of_space();//finds loc of blank space

	switch (pos)
	{//switches depending on the location of blank space
	case 0:
	{
		Board* newBoard = new Board(*this);
		newBoard->swap_pos(x, y, x, y - 1);
		return newBoard;
		break;
	}
	case(1):
	{
		Board* newBoard = new Board(*this);
		newBoard->swap_pos(x, y, x - 1, y);
		return newBoard;
		break;
	}
	case(2):
	{
		Board* newBoard = new Board(*this);
		newBoard->swap_pos(x, y, x, y + 1);
		return newBoard;
		break;
	}
	default:
	{//if case 3 should just move here. There should be no other possible cases
		Board* newBoard = new Board(*this);
		newBoard->swap_pos(x, y, x + 1, y);
		return newBoard;
		break;
	}
	}
}

pair<int, int> Board::get_loc_of_space() const
{//retrieves the location of the blank space
	pair<int, int> loc;//variable to hold loc of space
	for (size_t i = 0; i < this->puzzles.size(); ++i)
	{
		for (size_t j = 0; j < this->puzzles[i].size(); ++j)
		{
			if (this->puzzles[i][j] == 0)
			{
				loc = make_pair(i, j); //returns as a pair (coordinate)
			}
		}
	}
	return loc;//retruns coord of blank spot
}

bool Board::can_move(int x, int y, int pos)
{//checks if current position can move into given loc or not
	bool move_check = false;
	switch (pos)
	{
	case 0: move_check = y - 1 >= 0; break;
	case 1: move_check = x - 1 >= 0; break;
	case 2: move_check = y + 1 <= 2; break;
	case 3: move_check = x + 1 <= 2; break;
	}
	return move_check;//returns a bool 
}

void Board::swap_pos(int x, int y, int newX, int newY)
{//swaps positions of the x/y coord
	swap(this->puzzles[x][y], this->puzzles[newX][newY]);
}

bool Board::operator==(const Board& rhs)
{//overloading == op to compare objects
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		if (this->puzzles[i] != rhs.puzzles[i]) {
			return false;
		}
	}
	return true;
}

bool Board::operator<(const Board& rhs)
{//overloading < op to compare objects
	return this->f < rhs.f;
}

void Board::manhat(const Board & final)
{//calculates manhattan distance
	int dist = 0;
	for (int y = 0; y < 3; y++) //checking through col
	{
		for (int x = 0; x < 3; x++)//checking through row
		{
			int value = this->puzzles[y][x];
			if (value != 0)//if it is not a blank space
			{
				//this acts like the divmod function in python. returns quotent and remainder
				int goal_x = (value - 1) % 3;
				int goal_y = (value - 1) / 3;
				//calculates distance
				dist += abs(x - goal_x) + abs(y - goal_y);//calculates distance using divmod
			}
		}
	}
	this->h = dist;//sets h to be the calculated distance
}

void Board::calc_g(const Board& parent)
{//sets the value of g
	this->g = parent.g + 1;
}

void Board::set_parent_node(Board* parent)
{//sets the parent node
	this->parent = parent;
}

void Board::calc_f()
{//calculates f = g + h
	this->f = this->g + this->h;
}

int Board::get_f() const
{//returns the value of f
	return this->f;
}

void Board::get_count()
{
	this->move_count++;
	cout << this->move_count;
}

void Board::display_board()
{//displays the puzzle to the screen
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		for (size_t j = 0; j < this->puzzles[i].size(); ++j) {
			cout << this->puzzles[i][j] << ' ';
		}
		cout << endl;
	}
}

void Board::display_movesets()
{//displays the board with the piece that has been moved
	if (this->parent == nullptr) {
		this->display_board();//display the board
		cout << endl;

		return;
	}
	this->parent->display_movesets();
	this->display_board();
	cout << endl;
}

vector<vector<int>> Board::getPuzzles() const
{//retrieves the puzzle vector
	return this->puzzles;
}