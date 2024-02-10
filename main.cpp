#include <iostream>
#include <ctime>
#include "BingoBall.hpp"
#include "List.hpp"
	using std::ostream;
	using std::cout;
	using std::endl;

int main() {
	List list;
	if (list.is_empty()) {
		cout << "The initial list is empty\n\n";
	} else {
		cout << "ERROR on is_empty\n\n";
	}

	// srand(time(0));
	// srand() % 75 + 1

	// CHANGE LOG:
	// Renamed these variables for no reason
	BingoBall b1(1);
	BingoBall b2(2);
	BingoBall b3(3);
	BingoBall b4(4);
	BingoBall b5(5);
	BingoBall b6(6);



	cout << "inserting a bingo ball\n\n";
	list.insert_first(b1);
	cout << "The list looks like:\n\n";
	cout << list;
	cout << "The first element is "<<list.get_first_element()<<endl;
	cout << "inserting another element: "<< b2 <<endl;
	list.insert_first(b2);
	cout << "updated:\n\n";
	cout << list;

	cout << "Inserting a couple of  them into the first position \n\n";
	list.insert_first(b3);
	list.insert_first(b4);
	cout << list << endl;

	Cursor* last_activity = list.get_current_location();
	cout << "The last bit of activity happened with "<<last_activity->get_element()<<endl;
	cout << "inserting "<<b5<<" after that:\n\n";
	last_activity = list.insert_after(b5,last_activity);
	cout << list << endl;

	cout << "Checking to see if "<<b3<< " is in the list\n\n";
	if (list.contains(b3)) {
		cout << "it is in the list\n\n";
	} else {
		cout << "it is not in the list\n\n";
	}

	cout << "Checking to see if "<<b6<<" is in the list\n\n";
	if (list.contains(b6)) {
		cout << "it is in the list\n\n";
		cout << "the current element is still "<<list.get_current_element()<<endl;
	} else {
		cout << "it is not in the list\n\n";
	}
	cout << "Adding it after the current location:\n\n";
	cout << "which would be after "<<last_activity->get_element()<<endl;
	list.insert_after(b6,last_activity);

	cout << "updated list:\n\n";
	cout << list << endl;

	/* removing the last element
	*/
	cout << "Checking the prev location of "<<b5<<endl; 
	last_activity = list.find_prev(b5);
	cout << "The previous element of "<< b5 << " is " <<last_activity->get_element() << endl;

	cout << "Moving the current location to the next one.\n\n";
	BingoBall b =  list.get_next();
	cout << "Now it points to "<< b<<endl;
	last_activity = list.get_current_location();

	// Had to do some debugging here, need to know what last_activity is right now.
	cout << "last_activity is: " << last_activity->get_element() << endl;


	cout << "Removing the element that comes after the last activity\n\n";
	BingoBall removed = list.remove_after(last_activity);
	cout << "Removed the element called "<<removed<<endl;
	cout << "the list has changed to "<<endl;
	cout << list << endl;

	cout << "Removing the last element "<<endl;
	last_activity = list.find_prev(b1);
	cout << "The one previous is "<<last_activity->get_element() << endl;
	b = list.remove_after(last_activity);
	cout << b << " has been removed "<<endl;
	cout << list << endl;

	cout << "trying to remove beyond the last elememt:\n\n";

	// DEBUG
	cout << last_activity->get_element() << endl;

	try {
		removed = list.remove_after(last_activity);
	} catch (CursorException &ce) {
		cout << "Exception caught\n\n";
		cout << ce << endl;
	}


	cout << "Trying to ask for the previous of the first element\n\n";
	cout << "the first element is "<< list.get_first_element() << endl;

	try {
		list.find_prev(list.get_first_element());
	} catch(CursorException &ce ) {
		cout << ce << endl;
	}

	cout << "The number of elements in the list is "<<list.get_num_elements()<<endl;

	BingoBall last_insert = list.remove_first();
	cout << "The last insert was "<<last_insert<<endl;

	cout << "After removing the first element, the list looks like\n\n";
	cout << list << endl;

	cout << "All done\n\n";
	return 0;
}
