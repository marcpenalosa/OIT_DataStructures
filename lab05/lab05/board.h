/******************************************************
* Author:		Marc Penalosa
* Filename:		board.h
* Date Created:	1/17/26
******************************************************/

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setfill;
using std::setw;
#include <cstdlib>
#include <string>
using std::string;

#include "cell.h"
#include "array2D.h"
#include "exception.h"

/*
* Class: Board
* 
* Purpose:
*		Creates a Board object using Cells and displays their information
*		The board is able place bombs randomly except at a given row and column as the first turn location
*			so that the player can never hit a mine on the first move
*		The board is also capable of selecting a specific Cell to call its functions
* 
* Manager Functions:
*		Board()
*			Calls the default Array2D<T> to make a default array of Cells
*			Sets the row, column, and number of bombs to 0
*		Board(int rows, int columns, int numBombs)
*			Take in paremeters for rows, columns, and numBombs to set their respective member variables and
*				uses rows and columns to make a 2D array of Cells
*		Board(const Board& copy)
*		Board(Board&& copy noexcept)
*		Board& oeprator=(const Board& rhs)
*		Board& operator=(Board&& rhs) noexcept
*		~Board()
* 
* Methods:
*		int GetRows() const
*		int GetColumns() const
*		int GetNumbBombs() const
*		Cell& SelectCell(int row, int column)
*			Selects a specfici cell in the board using a given row and column
*		const Cell& SelectCell(int row, int column) const
*		void PlaceBombsExcept(int row, int column)
*			Places bombs at random cells except at a specific row and column to avoid mines at first turn
*		void InrementAdjacentNum(int row, int column)
*			Gets called when placing bombs to increment all adjacent Cells' m_numAdjacentBomb
*		void DisplayBoard(bool bombRevealed)
*			Displays the entire board based on wether or not a bomb is hit
*			If a bomb is hit, all bombs will be displayed
*		string FormatNumDisplay(int num)
*			This returns a string that formats cout colors for numbered tiles
*/
class Board
{
public:
	Board();
	Board(int rows, int columns, int numBombs);
	Board(const Board& copy);
	Board(Board&& copy) noexcept;
	Board& operator=(const Board& rhs);
	Board& operator=(Board&& rhs) noexcept;
	~Board();

	int GetRows() const;
	int GetColumns() const;
	int GetNumBombs() const;
	Cell& SelectCell(int row, int column);
	const Cell& SelectCell(int row, int column) const;
	void PlaceBombsExcept(int row, int column);
	void IncrementAdjacentNum(int row, int column);
	void DisplayBoard(bool bombRevealed);
	string FormatNumDisplay(int num);
private:
	Array2D<Cell> m_cellArray;
	int m_rows;
	int m_columns;
	int m_numBombs;
};

#endif // !BOARD_H
