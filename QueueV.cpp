/**
 * Author: Caleb Bronn
 * Date: 1 Mar 2024
 * Title: Assignment 6
 * This program contains the definition for a Queue ADT, implemented using a Vector.
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
// Trying out the printf() function that someone recommended to me :)
#include <cstdio>
	using std::printf;


// HELPER FUNCTIONS

/*
 * NOTE:
 * So, just wanted to leave a note about how I approached the circular array problem.
 * I'll admit I don't read the assignments, I just skip to the code and go from there,
 * so I have no idea if this is the way I'm supposed to do it <(=﹏=)>

 * It's fairly simple to make the array go in a circle using the modulo operator, but
 * the part where it gets tricky is when you double the list.
 * Say you run enqueue and dequeue a few times and end up with a full array like this:

index:    0  1  2  3  4  5
		[ D, E, F, A, B, C ]	

 * where 'front' is 'A' (index 3), and 'back' has looped all the way round to index 3 
 * as well. If you just double the size and copy everything back in the way it was, 
 * you end up with:

		  0  1  2 ...			  ... 10  11
		[ D, E, F, A, B, C, _, _, _, _, _, _ ]

 * Where does 'G' go, then? How would you maintain alphabetical order and keep track of 
 * where the queue begins and ends? The easiest way I could think of was to just put 
 * everything back in linear order. Screw circles. So, here's how I'm doing it:

 * Step 1. Everything from index 'front' till the end of the array goes at the beginning.

		  0  1  2 ...			  ... 10  11
		[ A, B, C, _, _, _, _, _, _, _, _, _ ]

 * Step 2. Everything from 0 till index 'back' goes after where Step 1 left off.

		  0  1  2 ...			  ... 10  11
		[ A, B, C, D, E, F, _, _, _, _, _, _ ]

 * Ta-da! Who needs circles?
 * Jk idk if this is a good solution or not, but it's the best one I could come up with.
*/

template <typename E>
E * double_list(E * og_list, int & capacity, int & front, int & back) {
	E temp_list[capacity];
	for (int i = 0; i < capacity; i++) {
		temp_list[i] = og_list[i];
	}

	capacity *= 2;
	og_list = new E[capacity];

	// Take everything from the front of the queue till the end of temp array,
	// and put it back in starting from index 0.
	int last_index;
	for (last_index = front; last_index < (capacity / 2); last_index++) {
		og_list[last_index - front] = temp_list[last_index];

// DEBUG
// printf("%s, ", og_list[last_index - front]);
	}

	// Then take everything from the beginning of temp array till the back of 
	// the queue, and put it back in starting from where the last for-loop 
	// left off.
	last_index -= front;
	for (int z = 0; z < back; z++) {
		og_list[last_index + z] = temp_list[z];
		
// DEBUG
// printf("%s, ", og_list[last_index + z]);
	}

	front = 0;
	back = (capacity / 2);

// DEBUG
// printf("\nAfter doubling, List now looks like this: ");
// for (int i = 0; i < capacity; i++) {
// 	printf("%s, ", og_list[i]);
// }
// printf("\n\n");

	return og_list;
}


// QUEUE ADT METHODS

template <typename E>
Queue<E>::Queue() {
	this->capacity = INIT_CAPACITY;

	// the index position of the 'next served' element in the queue. 
	this->front = 0;

	// the index position of the first empty space available for an insert into the queue.
	this->back = 0;

	// the array to hold the elements. 
	this->list = new E[capacity];
}


template <typename E>
Queue<E>::~Queue() {
	delete[] list;
}


template <typename E>
bool Queue<E>::is_empty() const {
	// NOTE:
	// Because we double the array in enqueue() as soon as we realize 
	// the array is full, that means the array is NEVER full once the
	// enqueue() function has completed. It has just been doubled. And
	// so if we know the array is NOT full, then front == back can only
	// mean the array is empty.
	return front == back;
}


template <typename E>
E Queue<E>::peek() const{
	// UPDATE:
	// Added an exception throw here. Wasn't really necessary since the 
	// code would work fine anyway, but I figured to maintain consistency
	// with the Linked List version of the queue, this function should 
	// probably throw a Queue Exception too.
	if (front == back) {
		throw QueueException("peek()", "Queue is empty");
	}
	return list[front];
}


template <typename E>
void Queue<E>::enqueue(E & item) {

// DEBUG
// cout << "Inserting " << item << " at position " << back << endl;

	list[back] = item;
	back = (back + 1) % capacity;

	// NOTE:
	// It's important to double the array at the END of this function,
	// because right now front == back can only mean the array is full. 
	// Normally, front == back could mean the array is empty OR full,
	// but since we have just added an item to the queue, then 
	// front == back must mean the array is full.

	// See is_empty() for more notes on this.
	if (front == back) {
		list = double_list(list, capacity, front, back);
	}
}


template <typename E>
E Queue<E>::dequeue() {
	// Throw error if list is empty.
	if (front == back) {
		throw QueueException("dequeue", "Queue is empty");
	}

	E was_in_front = list[front];
	front = (front + 1) % capacity;
	return was_in_front;
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
	q_test.enqueue(h);
	q_test.enqueue(e);
	q_test.enqueue(c);
	cout << q_test.peek() << endl;

	// Test double array() and how the queue handles duplicates
	q_test.enqueue(k);
	q_test.enqueue(y); // Queue: H E C K Y

	h = q_test.dequeue();
	e = q_test.dequeue(); // Queue: _ _ C K Y

	q_test.enqueue(e);
	q_test.enqueue(a);
	q_test.enqueue(h); // Queue: A H C K Y E

	// Test is_empty() and dequeue()
	cout << "\n\n";
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