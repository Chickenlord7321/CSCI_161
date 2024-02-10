#ifndef List_H
#define List_H

#include "BingoBall.hpp"
#include <iostream>
#include <sstream>
	using std::string;
	using std::ostream;
	using std::ostringstream;
	
/**
 * CursorException is an exception that is thrown when there is no cursor associated with the particular location in the list.
 * @author: B. Bultena for VIU CSCI 161 Spring 2024
 */
class CursorException {

public :
		string location;
		string msg;
public :
	//See UserGuide for public comments

	CursorException(const string & where_thrown, const string & msg) {
	 	location = where_thrown;
		this->msg = msg;
	}

	friend ostream & operator<<( ostream & out, const CursorException & ce ) {
		out << "*** CursorException in " << ce.location <<" : "<< ce.msg;
		return out;
	}
};


// CURSOR
class Cursor {
public:
	/** The stored element at the cursor position. */
	BingoBall element;

	/**
	 * Creates a Cursor object that stores the element.
	 * @param element the element.
	 */
	Cursor(const BingoBall& element) {
		this->element = element;
	}
	/**
	 * @return the element at the current cursor position.
	 */
	BingoBall get_element() const {
		return element;
	}
};


// LIST
class List {

private :
	/**
	 * A private inner Node class, that can only be accessed from within the List.
	 * It is basically a Cursor object, with extra functionality that allows this class to access the pointer to the <i>next</i> Node in the list.
	 * Because this is a private inner class, it does not show up in the Programmer's User Guide
	 * The class description is complete.
	 */
	class Node : public Cursor {

	public:
		/**
		 * A pointer to the next node in the list, or nullptr if the Node the last in the list.
		 */
		Node* next;

		/**
		 * Creates a node.
		 * @param value the element in the node.
		 * @param nextNode pointer to the next node.
		 */
		Node(const BingoBall & value, Node * nextNode = nullptr) 
			: Cursor(value) {
			next = nextNode;
		}
		using Cursor::element;
	
	};

	// The List attributes
	// A pointer to the first node in the list or nullptr if the list is empty.
	Node* first;

	// A pointer to the last node in the list, or nullptr if the list is empty.
	Node* last;

	// A pointer to the current node, usually the node that was last accessed through a call
	// to a member function.
	Node* current; // the cursor
	
	// A running total of the number of current elements.
	int num_elements;

public:
	// See the programmer user guide for documention on public members

	List();
	List(const List &copy);
	List& operator=(const List& copy);
	~List();

	/************* Getters and setters ************/

	int get_num_elements() const;
	int size() const;
	bool is_empty() const;

	/**************** Location getters and setters ************/

	Cursor* get_current_location();
	BingoBall get_first_element();
	BingoBall get_last_element();
	BingoBall get_current_element() const;
	BingoBall get_next();
	 
	/********* Search the list **************/
	bool contains(const BingoBall & target);
	Cursor* find_prev(const BingoBall & target);

	/********* inserting and removing elements ************/
	Cursor* insert_first(const BingoBall& element);
	Cursor* insert_last(const BingoBall& element);
	Cursor* insert_after(const BingoBall& element, Cursor* curr_pos);
	BingoBall remove_first();
	BingoBall remove_after(Cursor* prev);
		
	/********* print out the list *******************/
	string to_string() const;
	friend ostream& operator<<( ostream & out, const List& list );
};

#endif
