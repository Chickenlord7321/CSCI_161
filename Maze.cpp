/*
 * Author: Caleb Bronn
 * Date: 9 Mar 2024
 * Title: Assignment 7

 * This program contains an algorithm for brute-force solving a text maze.
*/

// NOTE:
// I have used 'o' to represent the stones and 'X' to mark the exit being found.
// I just found these two characters to be more readable than '#'.

// I also plan on updating Maze.hpp after submitting this cos I think it would
// be fun to not simply put stones down, but rather use 'v', '^', '<', and '>'
// to indicate the direction the maze-solver went in. But that requires adding an 
// argument to find_path(), so it'll have to be something I implement outside of 
// this assignment :)


#include "Maze.hpp"
#include <iostream>
	using std::cout;
	using std::endl;

// HELPER FUNCTION

bool Maze::find_path(Cell source, Cell destination, string direction) {
	path.push(source);

	// Base case: found the maze exit!
	if (source == destination) {
		grid[source.row][source.col] = 'X';
		return true;

	// Base case: this cell is not open, so it can't be the right path.
	} else if (grid[source.row][source.col] != ' ') {
		source = path.pop();
		return false;
	}

	// Put down a stone in the current cell.
	if (direction == "N") {
		grid[source.row][source.col] = '^';
	} else if (direction == "S") {
		grid[source.row][source.col] = 'v';
	} else if (direction == "E") {
		grid[source.row][source.col] = '>';
	} else if (direction == "W") {
		grid[source.row][source.col] = '<';
	} else {
		grid[source.row][source.col] = 'S';
	}
	
	// DEBUG
	/* 
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			cout << grid[r][c];
		}
		cout << endl;
	} 
	 */

	// Check south
	Cell south(source.row + 1, source.col);
	if (find_path(south, destination, "S")) {
		return true;
	}

	// Check east
	Cell east(source.row, source.col + 1);
	if (find_path(east, destination, "E")) {
		return true;
	}

	// Check west
	if (source.col > 0) {
		Cell west(source.row, source.col - 1);
		if (find_path(west, destination, "W")) {
			return true;
		}
	}

	// Check north
	if (source.row > 0) {
		Cell north(source.row - 1, source.col);
		if (find_path(north, destination, "N")) {
			return true;
		}
	}
	
	// Base case: this path doesn't lead anywhere.
	grid[source.row][source.col] = ' ';
	source = path.pop();
	return false;
}  // end of find_path()


// CONSTRUCTORS / DESTRUCTORS

Maze::Maze(string * textmaze, int num_strings, Cell start, Cell finish) {
	this->start = start;  // Cell
	this->finish = finish;  //Cell

	this->rows = num_strings;  // int
	this->cols = textmaze[0].length();  // int

	this->grid = new char*[rows];  // char**

	// https://stackoverflow.com/questions/1403150/how-do-you-dynamically-allocate-a-matrix

	// Had to google matrixes again. Found this really interesting thread where user isekaijin
	// Points out another way of creating a matrix that allows for normal accessing, but 
	// creates the array arthimetically instead of using two for-loops. Basically, this method
	// creates a single giant array at grid[0] by lining up the rows end-to-end, and then uses
	// arithmetic to make the remaining "rows" point to their starting locations in the giant
	// array. It also has the advantage of making the destrctor much simpler!
	// Sounded pretty neat to me, so I'm giving it a go :P

	grid[0] = new char[rows * cols];
	for (int r = 1; r < rows; r++) {
		grid[r] = grid[0] + r * cols;

		// Add characters from maze string to the grid
		for (int c = 0; c < cols; c++) {
			grid[r - 1][c] = textmaze[r - 1][c];

			// Because this loop only goes to row - 1, we should add the final row as well.
			if (r + 1 == rows) {
				grid[r][c] = textmaze[r][c];
			}
		}  // end of columns loop
	}  // end of rows loop

	// DEBUG
	/* 
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			cout << grid[r][c];
		}
		cout << endl;
	}
	cout << "Maze created with " << rows << " rows and " << cols << " columns.\n";  
	*/
}  // end of constructor


Maze::~Maze() {
	delete[] grid[0];
	delete[] grid;
}


// SOLVING FUNCTIONS

Dispenser<Cell> & Maze::solve() {
	// Path found, return the solved path to the user
	// if (find_path (start, finish, "start")) {
	// 	return path;
	// }

	// // Path not found, return an empty path to the user.
	// path.clear();
	// return path;

	// Simpler version:
	bool path_was_found = find_path(start, finish, "start");
	return path;
}


string Maze::to_string() {
	string maze_as_text = "";

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			maze_as_text += grid[r][c];
		}
		maze_as_text += "\n";
	}
	return maze_as_text;
}


ostream & operator << (ostream & out, Maze & maze) {
	out << maze.to_string();
	return out;
}