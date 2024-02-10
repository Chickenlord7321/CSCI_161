#ifndef BINGO_BALL_H
#define BINGO_BALL_H

/**
 * The complete BingoBall class description.
 * Note that this file does not hide any information because all the functions are
 * inline descriptions.
 * Because the class definition is pretty simple, there seems no need for the implementation to 
 * be hidden.
 * @author B.Bultena & VIU CSCI 161 S24 N05 and N06 classes.
 * @version 1.0
 */

#include <iostream>
#include <sstream> // for the stringstream object in to_string.
	using std::cout;
	using std::endl;
	using std::string;
// the following are used for to_string and cout
	using std::ostream;
	using std::ostringstream;

/**
 * The BingoBall class is a simple object to illustrate the
 * basic class type in VIU CSCI 161 2024 course.
 * @author B.Bultena
 */
class BingoBall {

private:
	int num;
	bool inPlay;


public:
	// CONSTRUCTORS / DESTRUCTOR

	/*
	 * NOTE TO DESIGNER/PROGRAMMER:
	 * Since having a default constructor is wise, we need to determine what the number for a single ball will be.
	 * We could insist that a BingoBall 'always' have a number between 1 and 75, in which case we could handle the class
	 * in one of the following ways:
	 * <ul>
	 *		<li>Not allow a default constructor, which would make it very difficult to declare an array of BingoBall objects.</li>
	 *		<li>Make the default value a single number within the range, which could result in several duplicate balls.</li>
	 *		<li>throw an exception that dis-allows the construction, but we would still need a default constructor.</li>
	 * </ul>
	 *	For this version, we choose to make the default value 1, so the BingoBall is legimate.
	 * We leave it to the programmer, who uses the class, to worry about the duplicates.
	 */
	/**
	 * Creates a BingoBall object.
	 * The default BingoBall has a value of 1.
	 * @param num May be omitted, in which case the default value is 1, but if not omitted, then the value
	 * 	is checked to make sure it is between 1 and 75, inclusive.
	 *		No error occurs when the number is outside this range; the number for the ball is set to the default value.
	 */
	BingoBall(int num = 1) {
		if (num < 0 or num > 75) {
			this->num = 1;
		} else {
			this->num = num;
		}
		// A new ball is automatically not in play.
		this->inPlay = false;
	}

	/**
	 * Copy constructor is called by the system whenever a BingoBall object is passed by value.
	 * This definition matches the shallow copy that is achieved by the default copy constructor.
	 * @param copy the original
	 */
	BingoBall(const BingoBall &copy) {
		// This statement is added for the programmer's interest during runtime.

		this->num = copy.num;
		this->inPlay = copy.inPlay;
	}

	/**
	 * Overloads the assignment operator to make a copy.
	 * This definition matches the shallow copy that is achieved by the default copy constructor.
	 * @param copy the original
	 * @return a clone
	 */
	BingoBall& operator=(const BingoBall &copy) {
		// This statement is added for the programmer's interest during runtime.

		this->num = copy.num;
		this->inPlay = copy.inPlay;
		return *this;
	}

	/**
	 * Destructor called by the system when an instance of a BingoBall goes out of scope.
	 * This definition matches the action of a default destructor, which is to let the basic data types lose their scope.
	 */ 
	~BingoBall() {
		// This is what the compiler would do in the default case.
		// Add an output notification when a BingoBall is deleted.
	}

	// accessor / modifiers
	/**
	 * @return the Ball number.
	 */
	int get_num() const {
		return num;
	}

	/**
	 * @return the Ball character, one of 'B','I','N','G','0'.
	 */
	char get_char() const {
		if (num < 1) {
			return 'X';
		} else if (num < 16) {
			return 'B';
		} else if (num < 31) {
			return 'I';
		} else if (num < 46) {
			return 'N';
		} else if (num < 61) {
			return 'G';
		} else if (num < 76) {
			return 'O';
		} 
		return 'X';
	}

	/**
	 * Resets the ball number to a new number.
	 * @param new_num the new number, which must be between 1 and 75, inclusive.
	 *	If the new_num is out of range, then there is no change to the original ball number.
	 */
	void set_num(int new_num) {
		if (num < 1 or num > 75) {
			// when we get to more detailed exception handling, we can 'throw' an exception in this case.
			cout << "Illegal BingoBall number";
		} else {
			// leave it as it was
			num = new_num;
		}
	}

	/**
	 * @return true if the ball is currrently in play, false if it is not.
	 */
	bool is_in_play() const {
		return inPlay;
	}

	/**
	 * Sets the in_play attribute to true.
	 */
	void play() {
		inPlay = true;
	}

	/**
	 * Sets the in_play attribute to false.
	 */
	void stop_play() {
		inPlay = false;
	}

	/** 
	 * @return a string representation of the ball.
	 * The string is the character, followed by the number, for instance 'I22' or 'B3'.
	 */
	string to_string() const {
		ostringstream oss;
		oss << get_char() << num;
		return oss.str();
	}

	// comparison and cout functions
	/**
	 * Overloads the == operator to determine if two balls are equivalent.
	 * Equivalence is determined by the number.
	 * @param b1 the left operand.
	 * @param b2 the right operand.
	 * @return  true if the balls are equivalent, false if not.
	 */
	friend bool operator==(const BingoBall & b1, const BingoBall & b2) {
		return b1.num == b2.num;
	}

	/**
	 * Overloads the != operator to determine if two balls are not equivalent.
	 * Equivalence is determined by the ball's number.
	 * @param b1 the left operand
	 * @param b2 the right operand
	 * @return true if the balls are not equivalent, false if they are.
	 */
	friend bool operator!=(const BingoBall & b1, const BingoBall & b2) {
		return b1.num != b2.num;
	}

	// Currently we are not interested in an ordering for BingoBalls
	// So no further comparison operators are defined.
		
	/**
	 * Overloads the << operator to send string representation of the ball to the output stream.
	 * @param out the output stream (like cout or an open-for-writing file output stream).
	 * @param b the ball.
	 * @return the modified out stream object.
	 */
	friend ostream & operator<<(ostream & out, const BingoBall & b) {
		out << b.to_string();
		return out;
	}
};

#endif
