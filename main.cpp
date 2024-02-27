/*
 * Author: Caleb Bronn
 * Date: 16 Feb 2024
 * Title: Assignment 5

 * This program contains the main testing for two different implementations of 
 * a Stack ADT.
*/

#include "Stack.hpp"
	using std::cout;
	using std::endl;

int main() {
	// Test doubles, since that's what I added as a possible data type.
	double one = 1.1;
	double two = 2.2;
	double three = 3.3;
	double four = 4.4;

	Stack<double> stack_test;

	// Test push() and top()
	stack_test.push(one);
	cout << "Added " << stack_test.top() << " to the stack\n"; 
	stack_test.push(two);
	cout << "Added " << stack_test.top() << " to the stack\n";
	stack_test.push(three);
	cout << "Added " << stack_test.top() << " to the stack\n";

	// For Vector implementation, this also tests doubling the vector size.
	stack_test.push(four);
	cout << "Added " << stack_test.top() << " to the stack\n";

	// Test pop()
	cout << "\nRemoving all elements and printing them out one by one: "; 
	for (int i = 0; i < int(four); i++) {
		cout << "\n\t" << stack_test.pop();
	}

	// Test is_empty() 
	if (stack_test.is_empty()) {
		cout << "\nStack is now empty.\n";
	}

	// Test StackException error catching
	cout << "\nFinally, this should cause an exception to be thrown...\n";
	try {
		stack_test.pop();
		cout << "No error was caught.";
	} catch (StackException & error) {
		cout << error << endl;
	}

	cout << "\nEverything works!" << endl;
	return EXIT_SUCCESS;
}