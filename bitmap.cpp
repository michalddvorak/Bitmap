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

void Bitmap::Print(ostream& os) const
{
	//char c goes by 1, 2, 4, 8, 16, 32, 64, 128, 0 - 256 eqs 0 (char is 1B (8 bits))
	//q - counts 8 bits
	//i - iterates over chararray
	//t - count totalsize
	char        c = 1;
	for (size_t i = 0, q = 0, t = 0; i < totalcsize && t < totalsize; q++, t++)
	{
		q &= -(q != cols); // If q reached cols reset it to 0;
		os << (bool)(c & internal_array[i]);
		if (q == cols - 1)
			os << endl;
		c <<= 1;
		i += (c ==
		      0); //if c is actually zero, we wish to increment i - move to the next element of the actual char array
		c |= (c == 0); //if c is zero, we OR c with 00000001 - making it 1 :)
	}
}

void Bitmap::SetTrue(size_t row, size_t col)
{
	assert(CheckBounds(row,col));
	size_t actcoord = cols * row + col;
	size_t bitcoord = actcoord / CHAR_SIZE;
	size_t realbit  = actcoord % CHAR_SIZE;
	internal_array[bitcoord] |= (1 << (realbit));
}

void Bitmap::SetFalse(size_t row, size_t col)
{
	assert(CheckBounds(row,col));
	size_t actcoord = cols * row + col;
	size_t bitcoord = actcoord / CHAR_SIZE;
	size_t realbit  = actcoord % CHAR_SIZE;
	internal_array[bitcoord] &= ~(1 << (realbit));
}

bool Bitmap::IsTrue(size_t row, size_t col) const
{
	assert(CheckBounds(row,col));
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
	assert(CheckBounds(row,col));
	size_t actcoord = cols * row + col;
	size_t bitcoord = actcoord / CHAR_SIZE;
	size_t realbit  = actcoord % CHAR_SIZE;
	internal_array[bitcoord] ^= (1 << (realbit));
}