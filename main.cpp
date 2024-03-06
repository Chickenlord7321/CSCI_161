/*
 * Author: Caleb Bronn
 * Date: 2 Mar 2024
 * Title: Assignment 6

 * This program tests a Queue ADT, which has been implemented in two different 
 * ways (using a linked list and an array). 
*/

#include "Queue.hpp"
#include <iostream>
	using std::cout;
	using std::endl;


int main() {
	cout << "Let's add the letters A through H in alphabetical order to the queue!\n\n";

	string a = "A";
	string b = "B";
	string c = "C";
	string d = "D";
	string e = "E";
	string f = "F";
	string g = "G";
	string h = "H";

	Queue<string> q_test;

	// Test enqueue() and peek()
	cout << "Adding A through E to the linked list...\n";
	q_test.enqueue(a);
	q_test.enqueue(b);
	q_test.enqueue(c);
	q_test.enqueue(d);
	q_test.enqueue(e); // Queue: A B C D E
	cout << "Front of queue is: " << q_test.peek() << endl;  // A

	cout << "\nRemoving A and B from the linked list...\n";
	a = q_test.dequeue();
	b = q_test.dequeue(); // Queue: C D E
	cout << "Now front of queue is: " << q_test.peek() << "\n";  // C

	cout << "\nAdding F through H to the linked list...\n";
	q_test.enqueue(f);
	q_test.enqueue(g);
	q_test.enqueue(h); // Queue: C D E F G H

	// Test is_empty() and dequeue()
	cout << "\nAttempting to dequeue the whole list...\n";
	while (!q_test.is_empty()) {
		try {
			cout << q_test.dequeue();  // Output: CDEFGH
		} catch (QueueException & error) {
			cout << error << endl;
			cout << "Something has gone wrong\n";
		}
	}

	cout << "\n\nEverything works!\n";
	return EXIT_SUCCESS;
}