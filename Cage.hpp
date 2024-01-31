#ifndef CAGE_H
#define CAGE_H

#include <iostream>
#include "BingoBall.hpp"
	using std::ostream;

// Detailed user documentation is provided in the Assn2_UserGuide.pdf file

class Cage {
private:
	BingoBall * list;
	int num_elements; 
	int capacity;
	static const int INIT_CAPACITY = 3;

public:
	// Constructors
	Cage();
	Cage (const Cage &copy);

	//Assignment copy '=' overload 
	Cage& operator=(const Cage & copy);

	// Destructor
	~Cage();

	// Accessor / modifiers
	int get_num_elements() const;
	bool is_empty();


	// actions
	void insert( BingoBall & b);
	bool contains(const BingoBall & b);
	bool remove(BingoBall & b);

	// 
	/**
	 * @return a string representation of the cage.
	 * This is a list (in no particular order of all of the elements, on a single line, separated by commas.
	 */
	std::string to_string() const;

	/**
	 * Allows the string representation of this list to be printed to the console or to a file, with the stndard '<<' operator.
	 * @param out the ostream object that currently active (either the console output or an open file) output stream.
	 * @param cage the cage.
	 */
	friend ostream & operator<<(ostream & out, const Cage & cage);

};

#endif
