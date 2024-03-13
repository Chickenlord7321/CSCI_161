#ifndef DISPENSER_H
#define DISPENSER_H

#include <iostream>
#include <sstream>
	using std::string;
	using std::ostream;
	using std::ostringstream;

/**
 * The Dispenser (sometimes called a Deque, for 'double-ended queue') is a combination of the stack and queue, 
 * where inserts and removals can occur at either end of the sequence.
 * For our particular purposes, we use the dispenser object as a stack to find a path and then 'dispense'
 * the resulting stack from the bottom.  This effect allows for the bottom of the stack to act as a queue,
 * Thanks to Bruce for the name, which has more characters to type, but is a more suitable name than 'Deque'.
 * @author: B. Bultena for VIU CSCI 161 Spring 2024
 */

 template <typename E>
 class Dispenser {

 private:
	class Node{ 
		public:
			E element;
			Node* next;
			Node* prev;

			Node( const E & element, Node * prev = nullptr, Node * next = nullptr) {
				this->element = element;
				this->prev = prev;
				this->next = next;
			}
	};	
 	Node * first;
	Node * last;
	
				
public: 
	
	/**
	 * Creates an empty dispenser.
	 */
	Dispenser();

	/**
	 * Creates a dispenser that is an exact (deep) copy.
	 * @param copy The exact copy.
	 */
	Dispenser(const Dispenser<E> &copy);

	/**
	 * Allows the assignment operator to create a copy.
	 * @param copy The dispenser to copy.
	 * @return the address of the newly copied dispenser.
	 */
	Dispenser& operator = (const Dispenser<E>& copy);

	/**
	 * Constructs a dispenser that replaces the input dispenser.
	 * @param replace the dispenser to replace (which will be rendered inactive).
	 */
	Dispenser(Dispenser&& replace);
		
	/**
	 * Allows the assignment operator to replace the incoming dispenser.
	 * @param replace the dispenser to replace (which will be rendered inactive).
	 * @return the address of the replacement.
	 */
	Dispenser& operator = (Dispenser&& replace);

	/**
	 * Frees all the memory that was allocated to this sequence.
	 */
	~Dispenser();

	/**
	 * 'Looks at' the top element, but does not remove it.
	 * @return the element that was last inserted into the dispenser (simulating a stack).
	 * @throw DispenserException if the dispenser is empty.
	 */
	E top() const;

	/**
	 * 'Looks at' the bottom element, but does not remove it.
	 * @return the element that was first inserted into the dispenser (simulating a queue or providing access to the bottom of the stack).
	 * @throw DispenserException if the dispenser is empty.
	 */
	E bottom() const;

	/**
	 * @returns true if the dispenser is currently empty.
	 */
	bool is_empty() const;

	/**
	 * Inserts an element at the top (like a stack).
	 * @param element the element to 'push'.
	 */
	void push(E& element);

	/**
	 * Removes the element at the top of the stack (the last element that was pushed).
	 * @return the element that is removed.
	 * @throw DispenserException if the dispenser is empty.
	 */
	E pop();
	
	/**
	 * Removes the element at the bottom of the stack (the earliest element that was pushed).
	 * @return the element that is removed.
	 * @throw DispenserException if the dispnser is empty.
	 */
	E dispense();

	/**
	 * Empties the Dispenser.
	 */
	void clear();

	/**
	 * Creates a string representation of all the elements, from the bottom of the stack to the top
	 * (all one line, with a space between the individual elements).
	 * @return the string
	 */
	string elements_bottom_up() const;

	/**
	 * Creates a string representation of all the elements, from the top of the stack to the bottom.
	 * (all one line, with a space between the individual elements).
	 * @return the string
	 */
	string elements_top_down() const;

};

/**
 * An exception class, specific to the Dispenser class.
 */
class DispenserException {
private : 
	string location;
	string msg;
public:
	/**
	 * Creates the exception.
	 * @param where_thrown the location of the function identifies an exception.
	 * @param msg the cause of the exception: usually that the Dispenser is empty.
	 */
	DispenserException( const string& where_thrown, const string& msg) {
		location = where_thrown;
		this->msg = msg;
	}

	/**
	 * Creates a string representation of the exception that includes where_thrown and the msg.
	 * @return the statement as described above.
	 */
	string to_string() const {
		ostringstream oss;
		oss << "DispenserException in "<<location<<" : "<<msg;
		return oss.str();
	}

	/**
	 * Allows the string representation to be loaded onto an ostream object.
	 * @param out the ostream object to load.
	 * @param de The exception.
	 * @return the loaded ostream object.
	 */
	friend ostream& operator<<(ostream& out, const DispenserException& de) {
		out << de.to_string();
		return out;
	}
};
		
#endif	
		
