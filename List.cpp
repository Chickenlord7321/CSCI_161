/** 
 * Author: Caleb Bronn
 * Date: 9 Feb 2024
 * Title: Assignment 4

 * This program contains the definition for a linked list called 'List' (creative 
 * naming shcemes are our strong suit), which gives the user a Cursor object to 
 * navigate through the list.
*/

#include "BingoBall.hpp"
#include <iostream>
#include <ostream>
#include <sstream>
#include "List.hpp"
	using std::cout;
	using std::endl;
	using std::ostream;
	using std::ostringstream;
	using std::string;


List::List() {
	num_elements = 0;

	// Note to self:
	// All the following are Node * pointers but can be returned as Cursor * pointers
	// because Node is a child class of Cursor.
	first = nullptr;
	last = nullptr;
	current = nullptr; // the cursor
}

// FULLY IMPLEMENTED / NO NEED TO ALTER
List::List(const List & copy) {
	num_elements = 0;
	first = last = current = nullptr;
	if (copy.num_elements != 0) {
		for (Node* tmp = copy.first; tmp != nullptr; tmp = tmp->next) {
			this->insert_last(tmp->element);
		}
		// first and last Nodes are set by the insert function
		// The copy has a current element
		BingoBall el = copy.get_current_element();
		// this will set the current location to the same element in 'this'
		contains(el);  
	} 
	else {
		first = last = current = nullptr;
	}
}

// FULLY IMPLEMENTED / NO NEED TO ALTER
List & List::operator = (const List & copy) {
	// defend against self-assignment
	if (this != &copy) {
		// delete the previous version of 'this':
		// Remove all the nodes
		while (num_elements > 0) {
			remove_first();
		}
		// this will adjust the num_elements and the pointers
		// copy each element by inserting a new one.
		if (copy.num_elements != 0) {
			for (Node* tmp = copy.first; tmp != nullptr; tmp = tmp->next) {
				insert_last(tmp->element);
			}
		}
		BingoBall el = copy.get_current_element();
		// sets the current location in the new copy.
		contains(el);
	}
	return *this;
}

// FULLY IMPLEMENTED
// Provided the remove_first deletes the node, this will do fine.
List::~List() {
	while(first != nullptr) {
		remove_first();
	}
}


bool List::is_empty() const {
	return num_elements == 0;
}


int List::size() const {
	return num_elements;
}


int List::get_num_elements() const {
	return num_elements;
}


// FULLY IMPLEMENTED
Cursor * List::get_current_location() {
	// Here is an example of how to start with a check to make sure if 
	// current is null or not (if it is, then there are no elements either).

	if (current == nullptr) {
		throw CursorException("get_cursor", "Empty list");
	}
	// here's what happens if there is a current that is not null
	return current;
}


BingoBall List::get_first_element() {
	if (first == nullptr) {
		throw CursorException("get_first_element", "Element is null");
	}
	return first->element;
}


BingoBall List::get_last_element() {
	if (last == nullptr) {
		throw CursorException("get_last_element", "Element is null");
	}
	return last->element;
}


BingoBall List::get_current_element() const {
	if (current == nullptr) {
		throw CursorException("get_current_element", "Element is null");
	}
	return current->element;
}


BingoBall List::get_next() {
	if (current->next == nullptr) {
		throw CursorException("get_next", "Next element in the list is null");
	}
	return current->next->element;
}


bool List::contains(const BingoBall & target) {
	for (Node * curr_node = first; curr_node != nullptr; curr_node = curr_node->next) {
		if (curr_node->element == target) {
			return true;
		}
	}
	return false;
}
		

Cursor* List::find_prev(const BingoBall & target) {
	// If the target is the first element, then there is no previous node.
	if (first->element == target) {
		throw CursorException("find_prev", "Target is first element, no previous element before the first one");
	} 
	else {
		for (Node * curr_node = first; curr_node != nullptr; curr_node = curr_node->next) {
			if (curr_node->next->element == target) {
				current = curr_node;
				return current;
			}
		}

		// If the function could not find a match,
		throw CursorException("find_prev", "Target is not in the list");
	}
}


Cursor* List::insert_first(const BingoBall & element) {
	// Create new Node and make it the first element in the list.
	// It points to the previous first element.
	first = new Node(element, first);

	// last and first are the same element if the list was empty to begin with.
	if (num_elements == 0) {
		last = first;
	}

	current = first;
	num_elements++;
	return current;
}


Cursor* List::insert_last(const BingoBall & element) {
	if (num_elements == 0) {
		return insert_first(element);
	} 

	// Hold the previous last element so we can make it point to the new last element.
	Node* previous_last = last;
	last = new Node(element);
	previous_last->next = last;

	current = last;
	num_elements++;
	return current;
}


Cursor* List::insert_after(const BingoBall & element, Cursor * curr_position) {
	if (num_elements == 0) {
		throw CursorException("insert_after","Empty list");
	} 
	else {
		// Cast the Cursor to a Node
		Node * curr_node = (Node *)curr_position;
		current = new Node(element, curr_node->next);

		// In case curr_position was the last element
		if (current->next == nullptr) {
			last = current;
		}

		curr_node->next = current;
		num_elements++;

		// Note to Prof. Bette:

		// Thanks for answering my question about this in class!

		// I initially tried to just say curr_position->next, but because curr_position
		// is a Cursor and not a Node, that didn't work. So then I tried using the loop
		// down below to check if the BingoBall element in the Cursor matches any BingoBall
		// in the list of Nodes, which was the only way I could think of to get the right 
		// Node object.

		// The problem with this method is that if there were two of the same BingoBall 
		// element, this loop would stop when it found the first one and ignore the second. 
		// Probably not the biggest error since it's just bingo balls (which shouldn't have 
		// duplicates anyway), but it would've been a problem for another data type.

		/*
		for (Node * curr_node = first; curr_node != nullptr; curr_node = curr_node->next) {
			if (curr_node->element == curr_position->element) {
				current = new Node(element, curr_node->next);
				curr_node->next = current;
			}
		}
		*/
	}
	return current;
}


BingoBall List::remove_first() {
	// Throw error message if list is empty
	if (num_elements == 0) {
		throw CursorException("remove_first", "List is empty, there is nothing to remove");
	}

	// Temporary containers to hold: 
	// 1) the next node in the list,
	// 2) the BingoBall within the first node. This is the return value.
	Node * temp_ptr = first->next;
	BingoBall temp_ball = first->element;

	delete first;
	num_elements--;

	first = temp_ptr;
	return temp_ball;
}


BingoBall List::remove_after(Cursor * prev) {
	Node * prev_node = (Node *)prev;

	// Throw error messages if the list is empty or the parameter is the last element.
	if (num_elements == 0) {
		throw CursorException("remove_after", "List is empty");
	} else if (prev_node->next == nullptr ) {
		throw CursorException("remove_after", "The parameter passed in is the last element in the list");
	}

	// Temporary containers to hold:
	// 1) the node that the 'prev' parameter is pointing to (i.e. the node we want to remove),
	// 2) the next node in the list,
	// 3) the BingoBall within the node being removed. This is the return value.
	Node * current = prev_node->next;
	Node * current_was_pointing_to = current->next; // this is a bit of a silly variable name, but it helped me remember :)
	BingoBall temp_ball = current->element;

	delete current;
	num_elements--;

	// prev should now point to the node which current was originally pointing to.
	prev_node->next = current_was_pointing_to;
	current = prev_node;

	// In case the node being removed was the last element:
	if (current_was_pointing_to == nullptr) {
		last = current;
	}
	return temp_ball;
}


// BOTH OF THE FOLLOWING ARE DONE FOR YOU
string List::to_string() const {
	ostringstream oss;
	oss << "List: with "<< num_elements << " elements:\n";
	for (List::Node * nodePtr = first; nodePtr != nullptr; nodePtr = nodePtr->next) {
		oss << " " <<nodePtr->element<<"\n";
	}
	return oss.str();
}

	
ostream & operator << (ostream & out, const List & list){
	out << list.to_string();
	return out;
}

