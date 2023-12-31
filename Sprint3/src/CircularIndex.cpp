//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "CircularIndex.h"

CircularIndex::CircularIndex(int buffSize)
{
	// need an assert to verify that buffSize is a power of 2
	this->size = buffSize;
	assert(buffSize > 1);
	this->mask = (unsigned int)(buffSize - 1);
	this->index = 0;
}

// postfix
int CircularIndex::operator++(int)
{
	this->index++;

	// Circular 
	this->index = this->index & (int)this->mask;

	return this->index;
}

bool CircularIndex::operator==(const CircularIndex& tmp)
{
	assert(this->size == tmp.size);
	return (this->index == tmp.index);
}

bool CircularIndex::operator!=(const CircularIndex& tmp)
{
	assert(this->size == tmp.size);
	return (this->index != tmp.index);
}

int CircularIndex::getIndex() const
{
	return this->index;
}

//---  End of File ---
