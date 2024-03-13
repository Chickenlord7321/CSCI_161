#ifndef CELL_H
#define CELL_H

#include <iostream>
	using std::ostream;

/**
 * A Cell is a single grid on a 2-dimensional array,
 * identified by its row and column number.
 */
class Cell {
public:
	/**
	 * The row 0...rows-1 index of the cell.
	 */
	int row;

	 /**
	  * The column 0...cols-1 index of the cell.
	  */
	 int col;

	/**
	 * Creates a single cell.
	 * @param r the row index (0 ... rows-1)
	 * @param c the col index (0 ... cols-1)
	 */
	Cell(int r=0, int c=0) {
		row = r;
		col = c;
	}
		
	/**
	 * Creates a duplicate cell.
	 * @param copy the cell to copy.
	 */
	Cell(const Cell& copy) {
		row = copy.row;
		col = copy.col;
	}

	/**
	 * Allows the assignment operator to make a copy.
	 * @param copy the Cell to be copied.
	 * @return the copied Cell.
	 */
	Cell& operator=(const Cell& copy) {
		row = copy.row;
		col = copy.col;
		return *this;
	}

/************* friendly operators  ****************/
	/**
	 * Compares two cells for equivalence: both row and col are equal.
	 * @param c1 one of the cells.
	 * @param c2 the other cell.
	 * @return true if they are equivalent.
	 */
	friend bool operator==(const Cell& c1, const Cell& c2) {
		return c1.row == c2.row && c1.col == c2.col;
	}

	/**
	 * Determines inequality of two cells.
	 * @param c1 one of the cells.
	 * @param c2 the other cell.
	 * @return true if they not equivalent.
	 */
	friend bool operator!=(const Cell& c1, const Cell& c2) {
		return !(c1 == c2);
	}

	/**
	 * Loads an output stream with the cell.
	 * @param out the output stream.
	 * @param cell the Cell.
	 * @return the loaded output stream.
	 */
	friend ostream& operator<<(ostream& out, const Cell cell) {
		out << "("<<cell.row<<","<<cell.col<<")";
		return out;
	}
};

#endif
