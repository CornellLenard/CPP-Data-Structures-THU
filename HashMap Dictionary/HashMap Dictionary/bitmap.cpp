/*********************************************************************************

  * FileName:       bitmap.cpp
  * Author:         Lenard Zhang
  * Version:        V1.00
  * Description:    The implementation of the class BitMap
  * Project:        The Data Structures - Hash Map Dictionary
  * Reference:      THU Data Structures

**********************************************************************************/


#include <memory>
#include "bitmap.h"


void BitMap::Init(int n)
{
	size_ = (n + 7) / 8;
	map_ = new char[size_];
	memset(map_, 0, size_);
}


BitMap::BitMap(int n)
{
	Init(n);
}


BitMap::~BitMap()
{
	delete[] map_;
	map_ = nullptr;
}


void BitMap::Set(int k)
{
	Expand(k);
	map_[k >> 3] |= (0x80 >> (k & 0x07));
}


void BitMap::Clear(int k)
{
	Expand(k);
	map_[k >> 3] &= ~(0x80 >> (k & 0x07));
}


bool BitMap::Test(int k)
{
	Expand(k);
	return map_[k >> 3] & (0x80 >> (k & 0x07));
}


void BitMap::Expand(int k)
{
	if (k < size_ * 8)
		return;

	int old_size = size_;
	char* old_map = map_;

	Init(2 * k);

	memcpy_s(map_, size_, old_map, old_size);
	delete[] old_map;
	old_map = nullptr;
}


