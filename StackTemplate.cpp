#include "Stack.hpp"
	using std::string;
	using std::cout;
	using std::endl;
	
// This is the basic template for either the StackV version (stored in StackV.cpp)
// or the StackL version (stored in StackLL.cpp)
// The template information is provided.
// The program will not compile as is; there isn't enough informaton about the element types yet.
// This is provided to help you set up the templates the way C++ requires so that 'E' is a substitute for 
// whatever data type the elements will be.

template <typename E>
Stack<E>::Stack() {
}

template <typename E>
Stack<E>::~Stack() {
}

template <typename E>
bool Stack<E>::is_empty() const {
}

template <typename E>
E Stack<E>::top() {
}

template <typename E>
void Stack<E>::push(E & item) {
}

template <typename E>
E Stack<E>::pop() {
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

/*
 *this is an example of how a main function could begin for 
 *either Stack implementations.
 *Note that because elements in the stack are passed by reference,
 *that only elements that have been previously stored can be used.
 * NO LITERAL VALUES ALLOWED.
*/

/*
int main() {
	// because we pass by reference, the element values need
	// to be stored somewhere first.
	int i = 1;
	int j = 2;
	int k = 3;

	// note how the Stack is initialized with real datatype,
	// where the E has been used in the definitions.
	// This is required; main (and the user programmer may not use 'E' because it is just a place
	// holder.  The data type is selected and the user commits to it when they invoke the constructor.
	// You can create other stack objects with elements of a different data type.

	Stack<int> s;

	// once declared with a data type, we carry on as usual.
	s.push(i);
	s.push(j);
	s.push(k);

	cout << "so far so good\n";
	
	return 0;
}
*/
