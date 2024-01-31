/**
 * Author: Caleb Bronn
 * Date: 26 Jan 2024
 * Title: Assignment 2
 * This program is a class definition for a Bingo Cage that contains BingoBall objects.
 * Detailed user documentation is provided in the Assn2_UserGuide.pdf file.
*/

#include <iostream>
#include "BingoBall.hpp"
#include "Cage.hpp"
	using std::ostream;
	using std::string;
	using std::cout;
	using std::endl;


// HELPER FUNCTION:
/**
 * Takes an array of BingoBall objects and doubles the size of the array. 
 * Note that both parameters are pointers/references and WILL BE changed by this function.
 * @param list An array of BingoBall objects. This array will now be exactly two times the size.
 * @param capacity The original max capacity of the BingoBall array. This value will also be doubled.
*/
void double_capacity(BingoBall * list, int & capacity) {
	// Create a temporary copied list to hold the Bingo Balls 
	// so they can be transferred to the larger array.
	BingoBall temp_list[capacity];
	for (int i = 0; i < capacity; i++) {
		temp_list[i] = list[i];
	}

	// Double list capacity.
	capacity *= 2;
	list = new BingoBall[capacity];
	for (int i = 0; i < (capacity / 2); i++) {
		list[i] = temp_list[i];
	}

	// DEBUG
	// cout << "\n----- Doubled Capacity\n" << endl;
}


// CLASS METHODS

// Constructors
Cage::Cage() {
	this->capacity = this->INIT_CAPACITY;
	this->num_elements = 0;
	this->list = new BingoBall[capacity];

	// DEBUG
	// cout << "\n----- Capacity: " << capacity << ", num elements: " <<  num_elements << endl;
}


Cage::Cage(const Cage & copy) {
	this->num_elements = copy.num_elements;
	this->capacity = copy.capacity;

	// Make a NEW array and copy all the elements from copy.list into it.
	this->list = new BingoBall[capacity];
	for (int i = 0; i < num_elements; i++) {
		list[i] = copy.list[i];
	}

	// DEBUG
	// cout << "\n----- Copied the cage\n" << endl;
}


// Destructor
Cage::~Cage() {
	// Delete the list array.
	delete[] list;

	// DEBUG
	// cout << "\n----- Deleted allocated memory\n" << endl;
}


//Assignment copy '=' overload 
Cage & Cage::operator = (const Cage & copy) {
	// Note:
	// I don't know why this operator overload was giving me errors when
	// I simply returned copy, but I was in the middle of writing it so 
	// maybe it was something else. Anyway, calling the copy constructor
	// and making it static worked, so ¯\_(ツ)_/¯
	
	static Cage assign_cage(copy);
	return assign_cage;
}


// Accessor / modifiers
int Cage::get_num_elements() const {
	// DEBUG
	// cout << "\n----- get_num_elements works\n" << endl;

	return num_elements;
}


bool Cage::is_empty() {
	// DEBUG
	// cout << "\n----- is_empty works\n" << endl;
	
	return num_elements == 0;
}


// Actions
void Cage::insert( BingoBall & ball) {
	// Check if list is at full capacity, and if so double the size of the array.
	if (num_elements == capacity) {
		double_capacity(list, capacity);
	}

	list[num_elements] = ball;
	num_elements++;
	
	// DEBUG
	// cout << "\n----- Element inserted\n" << endl;
}


bool Cage::contains(const BingoBall & ball) {
	for (int i = 0; i < num_elements; i++) {
		if (list[i] == ball) {
			// DEBUG
			// cout << "\n----- The bingo ball is indeed inside the cage!\n" << endl;
			return true;
		}
	}
	return false;
}


bool Cage::remove(BingoBall & ball) {
	for (int i = 0; i < num_elements; i++) {
		if (list[i] == ball) {
			// DEBUG
			// cout << "\n----- This is the ball being removed: " << list[i] << endl;

			// Remove BingoBall object by moving the last object in the list to its position.
			// Unfortunately, there's no real way to remove elements from an array in C++.
			// So I just decrement num_elements and pretend like it's not there, even though it is :P
			list[i] = list[num_elements - 1];
			num_elements--;

			// DEBUG
			// cout << "\n----- Bingo ball removed!\n" << endl;
			return true;
		}
	}
	return false;
}


string Cage::to_string() const {
	// Just in case the list is empty,
	if (num_elements != 0) {
		string all_elements = list[0].to_string();

		// DEBUG
		// cout << "\n----- Added first bingo ball to string" << endl;

		for (int i = 1; i < num_elements; i++) {
			all_elements += ", " + list[i].to_string();
		}

		// DEBUG
		// cout << "\n-----  Added all the bingo balls to the string" << endl;

		return all_elements;
	}
	return "";
}


ostream & operator << (ostream & print_obj, const Cage & cage) {
	print_obj << cage.to_string() << "\n";
	return print_obj;
}

