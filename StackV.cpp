/*
 * Author: Caleb Bronn
 * Date: 16 Feb 2024
 * Title: Assignment 5

 * This program contains a Vector-type implementation of a Stack ADT.
*/

#include "Stack.hpp"
	using std::string;
	using std::cout;
	using std::endl;


// HELPER FUNCTIONS
template <typename E>
void double_list(E * og_list, int & capacity) {
	// Hold the original list in a temporary array.
	E temp_list[capacity];
	for (int i = 0; i < capacity; i++) {
		temp_list[i] = og_list[i];
	}

	// Double list capacity.
	capacity *= 2;
	og_list = new E[capacity];
	for (int i = 0; i < (capacity / 2); i++) {
		og_list[i] = temp_list[i];
	}
}


template <typename E>
Stack<E>::Stack() {
	this->num_elements = 0;
	this->capacity = INIT_CAPACITY;
	this->list = new E[capacity];
}


template <typename E>
Stack<E>::~Stack() {
	delete[] list;
}


template <typename E>
bool Stack<E>::is_empty() const {
	return num_elements == 0;
}


template <typename E>
E Stack<E>::top() {
	// Return the item at the end of the list.
	return list[num_elements - 1];
}


template <typename E>
void Stack<E>::push(E & item) {
	// Add item to the list, doubling the size of the array if necessary.
	if (num_elements == capacity) {
		double_list(list, capacity);
	}

	list[num_elements] = item;
	num_elements++;
}


template <typename E>
E Stack<E>::pop() {
	// Decrease the list by 1 and return the item being popped.
	if (num_elements > 0) {
		num_elements--;
		return list[num_elements];
	} else {
		throw StackException("Stack.pop", "Stack is empty. Cannot pop from an empty stack.");
	}
}


/*
 * This is a required list of data types that can be elements.
 * It can be as long as necessary, but must have at least one 
 *	actual data type listed.
 * If you want to add other data types as possible elements,
 * for your stack objects,
 * make sure they are added to this list.
 * If you haven't had enough of BingoBall objects, you can add that, too.
*/
template class Stack<string>;
template class Stack<int>;
template class Stack<double>;  // I added doubles just to test :)


/*
int main() {
	// Test integers
	int i = 1;
	int j = 2;
	int k = 3;
	int l = 4;

	Stack<int> stack_test;

	// Test push() and top().
	stack_test.push(i);
	cout << "Added " << stack_test.top() << " to the stack\n"; 
	stack_test.push(j);
	cout << "Added " << stack_test.top() << " to the stack\n";
	stack_test.push(k);
	cout << "Added " << stack_test.top() << " to the stack\n";

	// Test double_array()
	cout << "\nAttempting to double the array...\n";
	stack_test.push(l);
	cout << "Added " << stack_test.top() << " to the stack\n";

	// Test pop()
	cout << "\nRemoving all elements and printing them out one by one: "; 
	for (int i = 0; i < l; i++) {
		cout << "\n\t" << stack_test.pop();
	}

	// Test is_empty() 
	if (stack_test.is_empty()) {
		cout << "\nStack is now empty.\n";
	}

	cout << "Everything works!\n";

	// Test StackException error catching
	cout << "\nThis should cause an exception to be thrown...\n";
	try {
		stack_test.pop();
		cout << "No error was caught.";
	} catch (StackException & error) {
		cout << error << endl;
	}
	
	return EXIT_SUCCESS;
} 
*/

