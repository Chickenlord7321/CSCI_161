/*
 * Author: Caleb Bronn
 * Date: 7 Mar 2024
 * Title: Assignment 7

 * This program contains the defintion for a Dispenser ADT (otherwise known as a Deque) that can dispense
 * elements from both the bottom and top, but can only add elements from the top.
*/

#include "Cell.hpp"
#include "Dispenser.hpp"
#include <iostream>
#include <sstream>
	using std::string;
	using std::ostream;
	using std::ostringstream;
	using std::cout;
	using std::endl;


/************* Constructors, Destructors ****************/

// default constructor:
template <typename E>
Dispenser<E>::Dispenser() {
	first = last = nullptr;
}

// copy constructors required because this object is returned by a function
template <typename E>
Dispenser<E>::Dispenser(const Dispenser<E> & copy) {
	first = last = nullptr;
	// copy the individual elements
	for (Node* temp = copy.last; temp != nullptr; temp = temp->prev) {
		this->push(temp->element);
	}
}

// also required for the same reason
template <typename E>
Dispenser<E>& Dispenser<E>::operator = (const Dispenser<E> & copy) {
	if (this != &copy) {
		clear();  // delete this previous version
		// copy the individual elements
		for (Node* tmp = copy.last; tmp != nullptr; tmp = tmp->prev) {
			push(tmp->element);
		}
	}
	return *this;
}

// The move constructor is more efficient.
// Whether it is used or not by the system is not under our control
template <typename E>
Dispenser<E>::Dispenser(Dispenser<E>&& replace) {
	// if first and last pointers are transferred, then all the nodes are accessble by the new pointers
	first = replace.first;
	last = replace.last;

	// the object that is replace is set up for the destructor
	replace.first = nullptr;
	replace.last = nullptr;
}
		
template <typename E>
// move assignment: same reasoning as above
Dispenser<E>& Dispenser<E>::operator  =(Dispenser<E>&& replace) { // move assignment operator.
	if (&replace == this) return *this;

	// do not want to release any of the internal nodes, just the first and last pointers
	first = replace.first;
	last = replace.last;

	replace.first = nullptr;
	replace.last = nullptr;

	return *this;
}

// All the dynamic memory is released when nodes are removed
template <typename E>
Dispenser<E>::~Dispenser() {
	// just call the clear function to empty the dispenser
	clear();
}


/********************* Stack Behaviour *********************/

template <typename E>
bool Dispenser<E>::is_empty() const {
	return first == nullptr and last == nullptr;
}


template <typename E>
E Dispenser<E>::top() const {
	if (is_empty()) {
		throw DispenserException("top()", "Dispenser is empty");
	}
	return last->element;
}


template <typename E>
E Dispenser<E>::bottom() const {
	if (is_empty()) {
		throw DispenserException("bottom()", "Dispenser is empty");
	}
	return first->element;
}


template <typename E>
void Dispenser<E>::push(E & element) {
	last = new Node(element, last);

	// Make the previous 'last' point to the new 'last'
	if (last->prev != nullptr) {
		last->prev->next = last;
	} else {
	// Last and first are the same if last has no previous Node
		first = last;
	}

	// DEBUG
	// cout << "last = " << last->element << endl;
}


template <typename E>
E Dispenser<E>::pop() {
	if (is_empty()) {
		throw DispenserException("pop()", "Dispenser is empty");
	}

	// Store values we're gonna need after deleting the last Node.
	Node * new_last = last->prev;
	E item_removed = last->element;

// DEBUG
// cout << "\n\tremoving: " << item_removed << endl;

	delete last;
	last = new_last;

// DEBUG
// if (last != nullptr) cout << "\n\tnew last is: " << last->element << endl;

	// Check if last is the only element, update prev and next accordingly.
	if (last != nullptr) {
		last->next = nullptr;

		if (last->prev == nullptr) {
			first = last;
		}
	} else {
		first = last;
	}

	return item_removed;
}


template <typename E>
E Dispenser<E>::dispense() {
	if (is_empty()) {
		throw DispenserException("dispense()", "Dispenser is empty");
	}

	// Store values we're gonna need after deleting the last Node
	Node * new_first = first->next;
	E item_removed = first->element;

// DEBUG
// cout << "\n\tremoving: " << item_removed << endl;

	delete first;
	first = new_first;

// DEBUG
// if (first != nullptr) cout << "\n\tnew first is: " << first->element << endl;
	
	// Check if first is the only element, update prev and next accordingly.
	if (first != nullptr) {
		first->prev = nullptr;

		if (first->next == nullptr) {
			last = first;
		}
	} else {
		last = first;
	}

	return item_removed;
}


template <typename E>
void Dispenser<E>::clear() {
	while (first != nullptr) {
		pop();
	}
}


// Note:

// I'm curious why these two functions seemingly work backwards. bottom_up() prints 
// from the last (i.e. top) element, and top_down() prints from the first (i.e. bottom) 
// element. After some testing, I saw that this is because find_path() is recursively
// going through the elements and, once it has found the exit, reversing the order of
// the dispenser. So a dispenser that looks like (0,1)...(8,9) becomes (8,9)...(0,1).
// Why is that?

template <typename E>
string Dispenser<E>::elements_bottom_up() const {
	if (last == nullptr) {
		throw DispenserException("elements_bottom_up","no elements");
	}

	ostringstream oss;
	Node * t=last;

	for(; t->prev != nullptr; t=t->prev) {
		oss << t->element << " ";
	}
	if (!is_empty()) {
		oss << t->element<<endl;
	}
	return oss.str();
}


template <typename E>
string Dispenser<E>::elements_top_down() const {
	if (first == nullptr) {
		throw DispenserException("elements_top_down","no_elements");
	}

	ostringstream oss;
	Node* t=first;

	for (; t->next != nullptr; t=t->next) {
		oss << t->element << " ";
	}
	if (!is_empty()) {
		oss << t->element<<endl;
	}
	return oss.str();
}


template class Dispenser<Cell>;
template class Dispenser<string>;
template class Dispenser<int>;


// TESTING
/* 
int main() {
	string green = "Green candy";
	string yellow = "Yellow candy";
	string blue = "Blue candy";
	string red = "Red candy";
	string pink = "Pink candy";

	Dispenser<string> pez;

	// Test push()
	cout << "Adding green, yellow, and blue to the Pez Dispenser...\n";
	pez.push(green);  // Bottom
	pez.push(yellow);
	pez.push(blue);  // Top

	// Test bottom() and top()
	cout << "\nThe candy at the top of the Pez is: " << pez.top() << endl;  // Blue
	cout << "The candy at the bottom of the Pez is: " << pez.bottom() << endl;  // Green

	// Test pop() and dispense()
	cout << "\nPopping the candy at the top...\n"; 
	cout << "\t" << pez.pop() << " removed\n";  // Blue

	cout << "Dispensing the candy at the bottom...\n";
	cout << "\t" << pez.dispense() << " removed \n";  // Green

	cout << "\nNow there is only the " << pez.bottom() << " left\n";  // Yellow

	cout << "\nAdding red and pink...\n";
	pez.push(red);
	pez.push(pink); // Dispenser: Yellow, Red, Pink
	cout << "\nThe candy at the top of the Pez is: " << pez.top() << endl;  // Pink
	cout << "The candy at the bottom of the Pez is: " << pez.bottom() << endl;  // Yellow

	// Test emptying the dispenser
	cout << "\nEmptying the Pez now...\n";
	cout << pez.dispense() << "\n";  // Yellow
	cout << pez.dispense() << "\n";  // Red
	cout << pez.dispense() << "\n";  // Pink

	// Test error handling
	cout << "\nThis should cause an error to be thrown...\n";
	try {
		pez.pop();
		cout << "Error wasn't caught, something has gone wrong";
	} catch (DispenserException & error) {
		cout << error << endl;
	}

	cout << "\n\nLet's test just to make sure the 'print all elements' functions work...\n";
	pez.push(green);  // Bottom
	pez.push(yellow);
	pez.push(blue);
	pez.push(red);
	pez.push(pink);  // Top

	// Should be: Green, yellow, blue, red, pink
	cout << "Bottom should be: " << pez.bottom() << endl;
	cout << "Top should be: " << pez.top() << endl;
	cout << "Here are the elements bottom-up:\n\t" << pez.elements_bottom_up();
	
	// Should be: Pink, red, blue, yellow, green.
	cout << "\nHere are the elements top-down:\n\t" << pez.elements_top_down();

	pez.clear();
	
	cout << "\n\nEverything works!\n";
	return 0;
} 
*/
