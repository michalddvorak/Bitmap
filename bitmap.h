#include <iostream>

class Bitmap
{
public:
	Bitmap(size_t cols, size_t rows);

	~Bitmap();

	Bitmap(const Bitmap &other);

	/**
	 * Prints the Bitmap to the output stream @os.
	 * @param os - the output stream
	 */
	void Print(std::ostream &os) const;

	/**
	 * Sets the bit on given index to 1.
	 * @param row - the row index.
	 * @param col - the col index.
	 */

	void SetTrue(size_t row, size_t col);
	/**
	 * Sets the bit on given index to 0.
	 * @param row - the row index.
	 * @param col - the col index.
	 */
	void SetFalse(size_t row, size_t col);

	/**
	 * Checks if the bit on given index is 1.
	 * @param row - the row index.
	 * @param col - the col index.
	 */
	bool IsTrue(size_t row, size_t col) const;

	/**
	 * Checks if the bit on given index is 0.
	 * @param row - the row index.
	 * @param col - the col index.
	 */
	bool IsFalse(size_t row, size_t col) const { return !IsTrue(row, col); }

	/**
	 * Flips the bit on given index.
	 * @param row - the row index.
	 * @param col - the col index.
	 */
	void Flip(size_t row, size_t col);
	/**
	 * Gets the number of rows of this Bitmap.
	 * @return the number of rows.
	 */
	size_t GetRows() { return rows; }
	/**
	 * Gets the number of columns of this Bitmap.
	 * @return the number of columns.
	 */
	size_t GetCols() { return cols; }

private:
	/**
	 * Checks bounds
	 * @param row - the row index
	 * @param col - the col index
	 * @return true if bounds are okay, false otherwise
	 */
	bool CheckBounds(size_t row, size_t col) const
	{
		return (row >= 0) && (col >= 0) && (row < rows) && (col < cols);
	}

private:
	const size_t rows, cols, totalsize, totalcsize;
	char * const internal_array;
};