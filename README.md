# SLIDING PUZZLE
This programming assignment uses guided search to solve a game problem. A* search is used to find the solution and the heuristic function h(x), uses  the sum of the Manhattan (city-block) distances for each tile from where it needs to be.  

For each puzzle, the program will show the moves required to solve the puzzle. If no solution is possible, the program will state that. Note: The longest possible shortest path for a solvable 8-puzzle has length 31. 

# THE PROBLEM:
Consider the 8-puzzle: 8 tiles each numbered 1-8 on a 3x3 grid, with one space empty. Any adjacent tile can be moved into the empty square (in effect swapping the locations of that tile and the empty square). This can be done by moving an adjacent tile vertically or horizontally (not diagonally). Thus the number of possible moves is at least 2  (if the empty square is in a corner) and at most 4 (if it’s in the center). 
The goal is to begin with some arbitrary arrangement and end with the tiles in the followingarrangement:

```
    1  2  3
    4  5  6
    7  8  E
```

where ‘E’ denotes the empty square. One  complication is that permutations of the game board fall into 2 disjoint sets of odd or even parity, only one of which can reach the goal. Thus, half of all possible tile arrangements cannot lead to a solution. (These states aren’t reachable by a physical puzzle.) 

This program detects whether a solution is possible or not using inversion.  

This program uses an input file where the first element, on a line by itself, is the number of puzzles contained in the file.  After that will be the specified number of puzzles in the above format (3 lines of 3 characters each, each character will be a digit 1-8 or an upper case ‘E’). Each puzzle is separated from the next by a blank line.

 
# WIKI LINK:
To see program useage and screenshots, pelase check out the [wiki page!](https://github.com/n-edmond/Sliding_Puzzle/wiki/Solving-an-8_Puzzle-using-A*-in-C--)


