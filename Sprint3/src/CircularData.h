//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef CIRCULAR_DATA_H
#define CIRCULAR_DATA_H

#include "CircularIndex.h"

class CircularData
{
public:
	// needs to be a power of 2
	static const int CIRCULAR_DATA_SIZE = 1 << 5;

public:
	CircularData();

	CircularData(const CircularData&) = delete;
	const CircularData& operator = (const CircularData&) = delete;
	~CircularData() = default;

	bool PushBack(int val);
	bool PopFront(int& val);

private:
	int data[CIRCULAR_DATA_SIZE];

	CircularIndex front;
	CircularIndex back;
	bool empty;
	bool full;

	std::mutex mtx;
};

#endif

//---  End of File ---
