/*
 * Author: Caleb Bronn
 * Date: 16 Feb 2024
 * Title: Assignment 5

 * This program contains a List-type implementation of a Stack ADT.
*/

#include "Stack.hpp"
	using std::string;
	using std::cout;
	using std::endl;
	

template <typename E>
Stack<E>::Stack() {
	this->num_elements = 0;
	this->first = nullptr;
	this->last = nullptr;
}


template <typename E>
Stack<E>::~Stack() {
	while(first != nullptr) {
		this->pop();
	}
}


template <typename E>
bool Stack<E>::is_empty() const {
	return num_elements == 0;
}


template <typename E>
E Stack<E>::top() {
	return first->element;
}


template <typename E>
void Stack<E>::push(E & item) {
	first = new Node(item, first);

	// Last and first are the same thing if the number of elements was 0.
	if (num_elements == 0) {
		last = first;
	}
	num_elements++;
}


template <typename E>
E Stack<E>::pop() {
	// Delete the node being 'popped' and return the element it contained.
	if (first == nullptr) {
		throw StackException("Stack.pop()", "Stack is empty. Cannot pop from empty Stack.");
	}

	Node * next_first = first->next;
	// Forgot to include this variable at first and was wondering why it wasn't 
	// returning the element being popped, lol.
	E popped_element = first->element;

	delete first;
	num_elements--;

	first = next_first;
	return popped_element;
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
template class Stack<double>;  // Just adding this to test :)

/* 
int main() {
	// Test integers
	int i = 1;
	int j = 2;
	int k = 3;
	int l = 4;

	Stack<int> stack_test;

	// Test push() and top()
	stack_test.push(i);
	cout << "Added " << stack_test.top() << " to the stack\n"; 
	stack_test.push(j);
	cout << "Added " << stack_test.top() << " to the stack\n";
	stack_test.push(k);
	cout << "Added " << stack_test.top() << " to the stack\n";
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

