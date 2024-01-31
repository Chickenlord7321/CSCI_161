#include <iostream>
#include <ctime>
#include "BingoBall.hpp"
#include "Cage.hpp"
	using std::ostream;
	using std::cout;
	using std::endl;

/**
 * The main function is mainly used to test the Cage class thoroughly.
 * @return 0 as a matter of convention, to let the system know that the program has completed without errors.
 */
int main() {
	cout << "Creating a single cage with 3 empty spots:\n";
	Cage cage;
	cout << "Number of elements: "<<cage.get_num_elements() << endl;
	cout << "Current state of the cage:\n";
	cout << cage;
	if (cage.is_empty()) {
		cout << "is_empty behaved well.\n";
	} else { 
		cout << "CHECK is_empty"<< endl;
	}

	srand(time(0));

	cout <<"\nCreating 7 BingoBall objects:\n";
	BingoBall b1(rand()%75+1);
	BingoBall b2(rand()%75+1);
	BingoBall b3(rand()%75+1);
	BingoBall b4(rand()%75+1);
	BingoBall b5(rand()%75+1);
	BingoBall b6(rand()%75+1);
	BingoBall b7(rand()%75+1);
	
	cout <<"\nAdding the first balls to the cage\n";
	cage.insert(b1);
	cage.insert(b2);
	cage.insert(b3);
	cout << "Current state of the cage:\n";
	cout << cage;

	// try removing one of them:
	cout <<"\nRemoving the second ball from the cage:\n";
	cage.remove(b2);
	cout << "Current state of the cage:\n";
	cout << cage;

	// keep adding
	cout << "\ninserting four more balls to into the cage:\n";
	cage.insert(b4);
	cage.insert(b5);
	cage.insert(b6);
	cage.insert(b7);
	cout << "Current state of the cage:\n";
	cout << cage;

	BingoBall b_extra(rand()%75+1);
	cout << "Created a bingo ball that is not going into the cage.\n";
	cout << "contents\n" << cage <<endl;
	cout << "It is "<<b_extra<<endl;
	if (cage.contains(b_extra)) {
		cout << "The cage already contains a ball equal to this one.\n";
	} else {
		cout << "This ball is not already in the cage.\n";
	}

	cout << "Trying to invoke the copy constructor\n";
	Cage dup(cage);
	cout << "The new one:\n";
	cout << dup;
	dup.remove(b6);
	cout << "After "<<b6<<" is removed\n";
	cout << dup << endl;

	cout << "That's all for now\n";
	return 0;
}
