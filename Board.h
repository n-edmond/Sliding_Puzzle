#include <iostream>
#include <vector>
#include <utility>//used for pairs, swap alg, hash

using namespace std;

class Board {
  public:
    //CONSTRUCTORS
    Board(vector<vector<int>> puzzles);//constructor
	  Board(const Board& rhs);// creates board to compare against
    //NODES
	  Board* create_child_node(int x, int y,int pos);//generates child node
    void set_parent_node(Board* parent);//sets the parent node
    //OPERATOR OVERLOADS
	  bool operator==(const Board& rhs);
	  bool operator<(const Board& rhs);
    //A* IMPLEMENTATION
	  void manhat(const Board& final);//calculates h
	  void calc_g(const Board& parent);//calculates g
	  void calc_f();//calculates f
	  bool canGenerate(int x, int y, int pos);//checks if this slot can be used
    //GETTERS
	  pair<int,int> get_loc_of_space()const;//gets loc of 0
	  int get_f() const;//gets f
    vector<vector<int>> getPuzzles()const;//gets puzzle
    //VISUALS
	  void display_board();//displays the board
	  void display_movesets();//displays the board with the new moves
    int count= 0;
    


private:
	vector<vector<int>> puzzles;//puzzle matrix
	int h = 0;//calculated using manhattan distance
	int g = 0;//path length
	int f = 0;//g + h 
	Board* parent;//parent node
	void swap_pos(int x, int y, int newX, int newY);//swaps positions.
};
