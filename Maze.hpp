#ifndef MAZE_H
#define MAZE_H

#include "Cell.hpp"
// #include "Maze.hpp"  // Why is this here???
#include "Dispenser.hpp"
#include <iostream>
	using std::string;
	using std::ostream;

/**
 * A simple maze with either no solution or a solution that does not require
 * any looping.
 * @author B. Bultena for VIU CSCI 161 Spring 2024
 */
class Maze {
private:
	char** grid;
	int rows, cols;
	Cell start, finish;
	Dispenser<Cell> path;

	// private recursive helper function 
	/**
	 * @param direction Can be "N", "S", "E", or "W".
	*/
	bool find_path(Cell src, Cell dest, string direction);

public:
/***************** Constructor / Destructor *************/
	/**
	 * Creates a maze from a list of strings containing only {'+''|''-'} characters
	 * that represent the walls of the maze and ' '(blank characters) 
	 * representing the open corridors.
	 * @param textmaze the array of such strings, each of equal length.
	 * @param num_strings the number of strings (rows of the maze).
	 * @param start the cell at the top of the maze that indicates the opening
	 *		for the start of the solution path.
	 * @param finish the cell at the bottom of the maze that indicates the opening
	 * 	for the end of the solution path.
	 */
	Maze(string* textmaze, int num_strings, Cell start, Cell finish);

	/**
	 * Removes any memory associated with the maze.
	 */
	~Maze();

	// No copy constructor: The maze will not need to be deep copied.
	Maze(Maze &copy) = delete;

/***************** Solving functions  *************/

	/**
	 * Solves the maze by finding a path and storing it as a stack of 
	 * Cell objects inside a Dispenser.
	 * Note that the stack, when emptied from the bottom produces the path in order.
	 * If there is no path, then the dispenser is empty.
	 * @return the dispenser of Cells.
	 */
	Dispenser<Cell>& solve();

	/**
	 * A string representation of a the maze as a grid of characters.
	 * The current path is represented as a trail of '#' characters.
	 * However, any character (other than {'-','|','+'} can be used to represent a path taken.
	 * @return the complete string that, when printed will represent the maze.
	 */
	string to_string();

	/**
	 * Overloads the << operator to direct a stream to an ostream object.
	 * @param out the ostream object.
	 * @param maze The maze to represent.
	 * @return the ostream object that is loaded with output from the to_string function.
	 */
	friend ostream& operator<<(ostream & out, Maze & maze);
};

#endif