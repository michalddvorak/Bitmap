#include <iostream>
#include <cassert>
#include <cstring>
#include "bitmap.h"

constexpr size_t CHAR_SIZE = sizeof(char);
using namespace std;

Bitmap::Bitmap(size_t cols, size_t rows) :
		rows(rows),
		cols(cols),
		totalsize(rows * cols),
		totalcsize(totalsize / CHAR_SIZE + 1),
		internal_array(new char[totalcsize])
{
	fill_n(internal_array, totalsize, 0);
}

Bitmap::Bitmap(const Bitmap &other) :
		rows(other.rows),
		cols(other.cols),
		totalsize(other.totalsize),
		totalcsize(other.totalcsize),
		internal_array(new char[totalcsize])
{
	memcpy(internal_array, other.internal_array, totalsize * CHAR_SIZE);
}

void Bitmap::Print(ostream &os) const
{
	/**
	 * 'c' changes: 1, 2, 4, 8, 16, 32, 64, 128, 0
	 * 'q' counts until 'columns', then a newline is printed
	 * 'i' iterates over 'internal_array'
	 * 't' counts until 'totalsize', then the print ends
	 */
	char c = 1;

	for (size_t i = 0, q = 0, t = 0; i < totalcsize && t < totalsize; q++, t++)
	{
		q &= -(q != cols); //If q reached cols, reset it to 0
		os << (bool)(c & internal_array[i]); //Print 0 or 1
		if (q == cols - 1) //If q is almost cols, we  end the row
			os << endl;
		c <<= 1;
		i += (c == 0); //Whenever c == 0 - we increment i by 1.
		c |= (c == 0); //And reset c to start from 1 again.
	}
}

void Bitmap::SetTrue(size_t row, size_t col)
{
	assert(CheckBounds(row, col));
	size_t actcoord = cols * row + col;
	size_t bitcoord = actcoord / CHAR_SIZE;
	size_t realbit  = actcoord % CHAR_SIZE;
	internal_array[bitcoord] |= (1 << (realbit));
}

void Bitmap::SetFalse(size_t row, size_t col)
{
	assert(CheckBounds(row, col));
	size_t actcoord = cols * row + col;
	size_t bitcoord = actcoord / CHAR_SIZE;
	size_t realbit  = actcoord % CHAR_SIZE;
	internal_array[bitcoord] &= ~(1 << (realbit));
}

bool Bitmap::IsTrue(size_t row, size_t col) const
{
	assert(CheckBounds(row, col));
	size_t actcoord = cols * row + col;
	size_t bitcoord = actcoord / CHAR_SIZE;
	size_t realbit  = actcoord % CHAR_SIZE;
	return (bool)(internal_array[bitcoord] & (1 << (realbit)));
}

Bitmap::~Bitmap()
{
	delete[] internal_array;
}

void Bitmap::Flip(size_t row, size_t col)
{
	assert(CheckBounds(row, col));
	size_t actcoord = cols * row + col;
	size_t bitcoord = actcoord / CHAR_SIZE;
	size_t realbit  = actcoord % CHAR_SIZE;
	internal_array[bitcoord] ^= (1 << (realbit));
}