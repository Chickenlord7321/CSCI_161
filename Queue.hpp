#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
	using std::string;
	using std::ostream;

/**
 * QueueException is a very simple exception class that is thrown 
 * to indicate a problem specific to a Queue.
 * The member functions are inline, therefore do not need to be included 
 * in the implementation files.
 */
class QueueException {
private:
	string location;
	string msg;
	
public:

	/**
 	* Creates a QueueException object.
 	* @param whereThrown the origin of the member function that threw the exception.
 	* @param message nn indication of what the problem was that triggered the exception.
 	*/
	QueueException(const string& whereThrown, const string& message) {
		location = whereThrown;
		msg = message;
	}

	/** 
	 * Provides a string version of the Exception object.
	 * @return An informative message.
 	*/
	string to_string() const {
		return "*** QueueException in "+ location + ": "+msg;
	}

	/**
 	* Allows for a direct stream of the error message using the << operator.
 	* @param out the ostream object on the left side of the << operator.
 	* @param se the exception to pass into the output stream.
 	* @return the loaded ostream object.
 	*/
 	friend ostream& operator<< (ostream& out, const QueueException& qe) {
 		out << qe.to_string();
		return out;
	}

}; // end of QueueException class description

/**
 * Class Queue is a basic queue ADT, a first-in-first-out sequence.
 * The type of elements is determined by the user, the description identifies
 * the type with a placeholder 'E' (for element).
 */
 
template <typename E>
class Queue {
	/**
	 * In the implementation file, the basic structure will be an expandible circular
	 * 	array or a singly-linked list.
	 */
//private:
// NOTE TO STUDENT:  When testing, this private can be changed to public
// to allow for the helper to_string function in the cpp file to print out the contents
// of the queue.
// Just swap the comment line: //

public:
	// for the array version only
	static const int INIT_CAPACITY = 3; // small enough to force at least one expansion.
	int capacity; // the actual size of the array (not necessarily the same as the number of elements)

	/** the array to hold the elements */
	E * list;

	/** the index position of the 'next served' element in the queue.*/ 
	int front; 

	/** the index position of the first empty space available for an insert into the queue.*/
	int back;



	// for the linked list version only
	class Node{
		public:
			E element;
			Node* next;

		// both a regular constructor and one with a default where next is pointing to a nullprt
		// useful for when inserting into the last position
		/**
		 * Creates a new node.
		 * @param element the element that enters the linked list.
		 * @param next the pointer to the next node in the list (nullptr by default).
		 */
		Node( const E& element, Node* next = nullptr) {
			this->element = element;
			this->next = next;
		}
	}; // end Node definition

	/** the position of the first element in the linked list. */
	Node* first;

	/** the position of the last element in the linked list. */
	Node* last;
	
public:

	/**
	 * Creates an empty queue.
	 */
	Queue();

	/**
	 * Copy constructor disabled for now. 
	 */
	Queue(const Queue& copy) = delete;

	/**
	 * Cleans up any memory that was allocated to the queue.
	 */
	~Queue();

	/**
	 * @return true if the queue is currently empty.
	 */
	bool is_empty() const;

	/**
	 * Looks at, but does not remove the next element that will be 
	 * removed from the front of the queue.
	 * @return The element at the front of the queue.
	 * @throw QueueException if the queue is empty.
	 */
	E peek() const;

	/**
	 * Inserts an element to the back of the queue.
	 * @param element the new addition to the queue.
	 */
	void enqueue(E & element);

	/**
	 * Removes the element from the front of the queue.
	 * @return the element that was removed.
	 * @throw QueueException if the queue is empty.
	 */
	E dequeue();
};

#endif
