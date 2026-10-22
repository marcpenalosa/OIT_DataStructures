/******************************************************
* Author:		Marc Penalosa
* Filename:		minesweeper.h
* Date Created:	1/18/26
******************************************************/

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
using std::getline;
#include <regex>
using std::regex;
using std::regex_match;
using std::smatch;

#include "board.h"

/*
* Class: Minesweeper
* 
* Purpose:
*		This class is a controller that manages the size of the minesweeper board based on difficulty and determines
*			the win/lose condition
*		It reads user input to reveal, mark, and unmark tiles in the board
*		It's given the responsibility to reveal multiple adjacent empty tiles. This could have been in Board
* 
* Manager Functions:
*		Minesweeper()
*			Calls the default Board ctor, sets the m_bombRevealed to false, m_firstTurn as true, and the m_numTilesRevealed to 0
*		Minesweeper(const Minesweeper& copy)
*		Minesweeper(Minesweeper&& copy) noexcept
*		Minesweeper& operator=(const Minesweeper& rhs)
*		Minesweeper& operator=(Minesweeper && rhs) noexcept
*		~Minesweeper()
* 
* Methods:
*		void Start()
*			This function is responsible for calling other functions until certain conditions are met
*		void MakeBoard()
*			Prompt the user to creates a board that replaces the m_board depending on difficulty
*		void ReadInput()
*			This function reads the command input to reveal, mark, or unmark a cell
*		void RevealTile(int row, int column)
*			This function controls how cells are revealed based on certain conditions
*/
class Minesweeper
{
public:
	Minesweeper();
	Minesweeper(const Minesweeper& copy);
	Minesweeper(Minesweeper&& copy) noexcept;
	Minesweeper& operator=(const Minesweeper& rhs);
	Minesweeper& operator=(Minesweeper && rhs) noexcept;
	~Minesweeper();

	void Start();
	void MakeBoard();
	void ReadInput();
	void RevealTile(int row, int column);
private:
	Board m_board;
	bool m_isBombRevealed;
	bool m_isFirstTurn;
	int m_numTilesRevealed;
};

#endif // !MINESWEEPER_H
