/**
 * Author: Caleb Bronn
 * Date: 2 Mar 2024
 * Title: Assignment 6
 * This program contains the definition for a Queue ADT, implemented using a Linked List.
*/

#include "Queue.hpp"
#include <iostream>
#include <ostream>
#include <sstream>
	using std::string;
	using std::ostringstream;
	using std::ostream;
	using std::cout;
	using std::endl;
#include <cstdio>
	// Trying out the printf() function that someone recommended to me :)
	using std::printf;


// QUEUE ADT METHODS

template <typename E>
Queue<E>::Queue() {
	this->first = nullptr;
	this->last = nullptr;
}

template <typename E>
Queue<E>::~Queue() {
	while (first != nullptr) {
		this->dequeue();
	}
}

template <typename E>
bool Queue<E>::is_empty() const {
	return first == nullptr;
}

template <typename E>
E Queue<E>::peek() const {
	if (first == nullptr) {
		throw QueueException("peek()", "Queue is empty");
	}
	return first->element;
}

template <typename E>
void Queue<E>::enqueue(E & item) {
	if (first == nullptr) {
		last = first = new Node(item, nullptr);
	} else {
		Node * prev_last = last;
		last = new Node(item, nullptr);
		prev_last->next = last;
	}
// DEBUG
// cout << "Added " << last->element << " to the queue!\n";
}

template <typename E>
E Queue<E>::dequeue() {
	// Queue is empty
	if (first == nullptr) {
		throw QueueException("dequeue()", "Queue is empty");
	}
	
	E item = first->element;

	// Queue has only one element
	if (first->next == nullptr) {
		delete first;
		last = first = nullptr;

	// Queue has muliple elements
	} else {
		Node * new_first = first->next;
		delete first;
		first = new_first;
		if (first->next == nullptr) {
			last = first;
		}
	}

// DEBUG
// cout << "\nRemoved " << item << " from the queue.\n";
	return item;
}


template class Queue<string>;
template class Queue<int>;
template class Queue<double>;
template class Queue<float>;


// TESTING
/* 
int main() {
	// Let's spell HECK YEAH, which is good for testing because it exceeds the capacity and 
	// has duplicates
	string h = "H";
	string e = "E";
	string c = "C";
	string k = "K";
	string y = "Y";
	string a = "A";

	Queue<string> q_test;

	// Test enqueue() and peek()
	cout << "Adding to the linked list...\n";
	q_test.enqueue(h);
	q_test.enqueue(e);
	q_test.enqueue(c);
	q_test.enqueue(k);
	q_test.enqueue(y); // Queue: H E C K Y
	// cout << q_test.peek() << endl;  // H

	cout << "\nRemoving two items from the linked list...\n";
	h = q_test.dequeue();
	e = q_test.dequeue(); // Queue: C K Y
	cout << "Front of queue is: " << q_test.peek() << "\n\n";  // C

	q_test.enqueue(e);
	q_test.enqueue(a);
	q_test.enqueue(h); // Queue: C K Y E A H

	// Test is_empty() and dequeue()
	cout << "\n\nAttempting to dequeue the whole list...\n";
	while (!q_test.is_empty()) {
		try {
			cout << q_test.dequeue();  // Output: CKYEAH
		} catch (QueueException & error) {
			cout << error << endl;
			printf("Something has gone wrong");
		}
	}

	printf("\n\nEverything works! HECK YEAH\n");
	return EXIT_SUCCESS;
}
 */