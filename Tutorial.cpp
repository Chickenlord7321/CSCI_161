/** 
 * Author: Caleb Bronn
 * Date: 18 Jan 2024
 * Title: Assignment 1

 * This program contains a basic class for a free online computer science tutorial.
*/

#include <iostream>
#include <sstream>
	using std::cout;
	using std::endl;
	using std::string;
	using std::ostringstream;
	using std::ostream;


class Tutorial {
	private:
		string url;
		string sitename;
		string topic;

	public:
		// Default and Regular Constructor
		Tutorial(string url = "", string sitename = "", string topic = "") {
			this->url = url;
			this->sitename = sitename;
			this->topic = topic;

			// Usually I don't think something like this would be necessary, but I was bored and
			// decided to let the user know whether they had created an empty object or not.
			if (url == "" and sitename == "" and topic == "") {
				cout << "Made an empty tutorial" << endl;
			} else {
				cout << "Made a tutorial" << endl;
			}
		}

		// Copy Constructor
		Tutorial(const Tutorial & copy) {
			this->url = copy.url;
			this->sitename = copy.sitename;
			this->topic = copy.topic;
			cout << "Copied the tutorial" << endl;
		}

		// Destructor
		~Tutorial() {
			cout << "Deleted allocated memory" << endl;
			// although no memory was allocated, so this does nothing.
		}


		// Get-attribute Methods
		string get_url() const {
			return url;
		}

		string get_sitename() const {
			return sitename;
		}

		string get_topic() const {
			return topic;
		}


		// Set-attribute Methods
		void set_url(string new_url) {
			url = new_url;
		}

 		void set_sitename(string new_sitename) {
			sitename = new_sitename;
		}

		void set_topic(string new_topic) {
			topic = new_topic;
		}


		// Returns a string version of the tutorial
		string to_string() const {
			ostringstream tutorial_as_text;
			tutorial_as_text << "Tutorial\n  url: " << get_url() << "\n  name: " << get_sitename() << "\n  topic: " << get_topic() << "\n";
			return tutorial_as_text.str();
		}


		// Overload operators
		friend bool operator == (const Tutorial & t1, const Tutorial & t2) {
			if (t1.url == t2.url and t1.sitename == t2.sitename and t1.topic == t2.topic) {
				return true;
			}
			return false;
		}

		friend bool operator != (const Tutorial & t1, const Tutorial & t2) {
			return not (t1 == t2);
		}

		friend ostream & operator << (ostream & print_object, const Tutorial & t) {
			print_object << t.to_string();
			return print_object;
		}
};  // end of Tutorial class


int main () {
	// Testing all 3 parameters.
	Tutorial w3_schools("https://www.w3schools.com/cpp/cpp_data_types.asp", "W3 Schools", "C++ Data Types");

	// Testing 2 parameters.
	Tutorial dev_docs("https://devdocs.io/", "DevDocs");

	// Testing default object construction.
	Tutorial programiz;

	// Testing copy constructor.
	Tutorial w3_copy(w3_schools);
	cout << w3_copy;

	// Testing 'get' member functions.
	cout << endl << w3_schools.get_sitename() << " has url: " << w3_schools.get_url() << " and topic: " << w3_schools.get_topic() << endl;

	// Testing 'set' member functions.
	cout << "\nThe empty object 'programiz' contains:\n" << programiz;
	programiz.set_sitename("Programiz");
	programiz.set_url("https://www.programiz.com/cpp-programming/operators");
	programiz.set_topic("Operators");
	cout << "\nNow it contains:\n" << programiz;

	// Testing operator overloading.
	if (w3_schools == programiz) {
		cout << "\nw3_schools == programiz is True" << endl;
	} else {
		cout << "\nw3_schools == programiz is False" << endl;
	}

	if (w3_schools != programiz) {
		cout << "w3_schools != programiz is True" << endl;
	} else {
		cout << "w3_schools != programiz is False" << endl;
	}

	cout << "\nEverything works!" << endl;
	return EXIT_SUCCESS;
}