#ifndef STACK_H
#define STACK_H

#include <iostream>
	using std::string;
	using std::ostream;

/**
 * StackException is a very simple exception class that is thrown
 * to indicate a problem specific to a Stack.
 * The member functions are inline, therefore do not need to be included
 * in the implementation files.
 */
class StackException {
	private:
		string location;
		string msg;

	public:
		/**
		 * Creates a StackException object.
		 * @param whereThrown The origin of the member function that threw the exception.
		 * @param message An indication of what the problem was that caused the exception.
		 */
		StackException(const string& whereThrown, const string & message) {
			location = whereThrown;
			msg = message;
		}

		/**
		 * Provides a printout of the Exception object.
		 * @return A string message.
		 */
		string to_string() const {
			return "*** StackException in " + location + ": " + msg;
		}

		/**
		 * Allows for a direct printout of the error message.
		 */
		friend ostream& operator<< (ostream & out, const StackException & se) {
			out << se.to_string();
			return out;
		}
};

/**
 * Class Stack is a basic stackADT, using templates to allow for element types 
 *		to be the user's choice.
 */
template <typename E>
class Stack {
	/*
	 * In the implementation file used, not all of the following attributes will be necessary.
	 * Any attribute that is not used, can be ignored.  Because they are all private, the user
	 * has no access to any of them.
	 * The Stack can be implemented with an array or a singly-linked data structure, depending on which
	 * implementation is used
	 */
	private:
		// for the array version only
		static const int INIT_CAPACITY = 3; // array version only
		int capacity;
		E * list;

		// for the linked list version only
		class Node {
			public: 

			E element;
			Node* next;

			Node(const E & element, Node * next) {
				this->element = element;
				this->next = next;
			}
		};
		Node * first;
		Node * last;

		// for either version
		int num_elements; // either version

	public:
		/**
		 * Creates an empty stack containing no elements.
		 */
		Stack();

		// in this assignment, no copies of the stack are allowed.
		Stack(const Stack & copy) = delete;

		/**
		 * Frees memory for the deleted stack.
		 */
		~Stack();

		/**
		 * @return True if the stack is empty, false if not.
		 */
		bool is_empty() const;

		/**
		 * @return the top item in the stack without removing it.
		 * @throw StackException if the stack is empty.
		 */
		E top();

		/**
		 * Pushes an element onto the stack.
		 * @item The element to put onto the stack.
		 */
		void push(E & element);

		/**
		 * @return the top item in the stack which is removed in the process.
		 * @throw StackException if the stack is empty.
		 */
		E pop();

	};

#endif
