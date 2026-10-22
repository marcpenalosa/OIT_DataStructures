#include "cell.h"

Cell::Cell() : m_state(covered), m_numAdjacentBomb(0), m_isBomb(false)
{
}

Cell::Cell(CellState state) : m_state(state), m_numAdjacentBomb(0), m_isBomb(false)
{
}

Cell::Cell(const Cell& copy) : m_state(copy.m_state), m_numAdjacentBomb(copy.m_numAdjacentBomb), m_isBomb(copy.m_isBomb)
{
}

Cell::Cell(Cell&& copy) noexcept : m_state(copy.m_state), m_numAdjacentBomb(copy.m_numAdjacentBomb), m_isBomb(copy.m_isBomb)
{
}

Cell& Cell::operator=(const Cell& rhs)
{
	if (this != &rhs)
	{
		m_state = rhs.m_state;
		m_numAdjacentBomb = rhs.m_numAdjacentBomb;
		m_isBomb = rhs.m_isBomb;
	}
	return *this;
}

Cell& Cell::operator=(Cell&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_state = rhs.m_state;
		m_numAdjacentBomb = rhs.m_numAdjacentBomb;
		m_isBomb = rhs.m_isBomb;
	}
	return *this;
}

Cell::~Cell()
{
	m_state = covered;
	m_numAdjacentBomb = 0;
	m_isBomb = false;
}

/*
* Purpose:
*		Returns a state as a char so that it could be displayed as ASCII symbols on the console
* Precondition:
*		None
* Postcondition:
*		Returns a state as a char
*/
char Cell::GetState() const
{
	return m_state;
}

void Cell::SetState(CellState state)
{
	m_state = state;
}

bool Cell::IsBomb() const
{
	return m_isBomb;
}

void Cell::SetBomb(bool isBomb)
{
	m_isBomb = isBomb;
}

int Cell::GetNumAdjBomb() const
{
	return m_numAdjacentBomb;
}

/*
* Purpose:
*		Increment the number of adjacent bombs of this cell by 1
* Precondition:
*		None
* Postcondition:
*		m_numAdjacentBomb is incremented
*/
void Cell::IncrNumAdjBomb()
{
	m_numAdjacentBomb++;
}
