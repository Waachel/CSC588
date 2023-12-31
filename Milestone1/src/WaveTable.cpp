//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "WaveTable.h"
#include "StringThis.h"

using namespace ThreadFramework;

WaveTable::Table::Table()
	: wave_id(Wave::ID::Empty),
	status(Wave::Status::EMPTY)
{
	
}

WaveTable::WaveTable()
	: table(),
	mtx()
{

}

WaveTable::~WaveTable()
{

}

WaveTable::Table *WaveTable::Find(const Wave::ID wave_id)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	Table *pTable = this->privFind(wave_id);

	return pTable;
}

WaveTable::Table *WaveTable::privFind(const Wave::ID _wave_id)
{
	Table *pTable = nullptr;

	for(int i = 0; i < WaveTable::TABLE_COUNT; i++)
	{
		if(table[i].wave_id == _wave_id)
		{
			pTable = &table[i];
			break;
		}
	}

	return pTable;
}

void WaveTable::Register(const Wave::ID _wave_id, const Wave::Status _status)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	Table *pTable = this->privFindEmpty();

	// is it FILLED?
	assert(pTable);

	pTable->wave_id = _wave_id;
	pTable->status = _status;
}

void WaveTable::Update(const Wave::ID _wave_id, const Wave::Status _status)
{
	std::lock_guard<std::mutex> lock(this->mtx);

	Table *pTable = this->privFind(_wave_id);
	assert(pTable);

	assert(pTable->wave_id == _wave_id);
	pTable->status = _status;
	
}

WaveTable::Table *WaveTable::privFindEmpty()
{
	Table *pTable = nullptr;

	for(int i = 0; i < WaveTable::TABLE_COUNT; i++)
	{
		if(table[i].status == Wave::Status::EMPTY)
		{
			pTable = &table[i];
			break;
		}
	}

	return pTable;
}

void WaveTable::Dump()
{
	std::lock_guard<std::mutex> lock(this->mtx);

	Debug::out("   --- Wave Table ---\n");

	for(int i = 0; i < WaveTable::TABLE_COUNT; i++)
	{
		Debug::out("   %2d: %-14s  %s \n", i, StringMe(table[i].wave_id), StringMe(table[i].status));
	}
}

// --- End of File ---