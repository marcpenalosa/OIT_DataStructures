/******************************************************
* Author:		Marc Penalosa
* Filename:		cell.h
* Date Created:	1/17/26
******************************************************/

#ifndef CELL_H
#define CELL_H

enum CellState
{							// ASCII
	covered = (char)63,		// ?
	uncovered = (char)35,	// #
	marked = (char)109		// m
};

/*
* Class: Cell
* 
* Purose:
*		Creates a Cell object that has different states (covered, uncovered, marked). It also has member variables that determines
*		how many bombs there are in the tile or if the tile is a bomb
* 
* Manager Functions:
*		Cell()
*			Creates a default Cell that is covered, no adjacent bombs, and is not a bomb
* 		Cell(CellState state)
*		Cell(const Cell& copy)
*		Cell(Cell&& copy) noexcept
*		Cell& operator=(const Cell& rhs)
*		Cell& operator=(Cell&& rhs) noexcept
*		~Cell();
* 
* Methods:
*		char GetState() const
*			returns the state of the cell as char values that represent symbols in ascii
*		void SetState(CellState state)
*		bool IsBomb() const
*		void SetBomb(bool isBomb)
*		int GetNumAdjBomb() const
*		void IncrNumAdjBomb()
*			increment the number of adjacent bombs this tile has
*/
class Cell
{
public:
	Cell();
	Cell(CellState state);
	Cell(const Cell& copy);
	Cell(Cell&& copy) noexcept;
	Cell& operator=(const Cell& rhs);
	Cell& operator=(Cell&& rhs) noexcept;
	~Cell();

	char GetState() const;
	void SetState(CellState state);
	bool IsBomb() const;
	void SetBomb(bool isBomb);
	int GetNumAdjBomb() const;
	void IncrNumAdjBomb();
private:
	char m_state;
	int m_numAdjacentBomb;
	bool m_isBomb;
};

#endif // !CELL_H
