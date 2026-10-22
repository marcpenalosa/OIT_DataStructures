#include "minesweeper.h"

Minesweeper::Minesweeper() : m_board(Board()), m_isBombRevealed(false), m_isFirstTurn(true), m_numTilesRevealed(0)
{
}

Minesweeper::Minesweeper(const Minesweeper& copy) : m_board(copy.m_board), m_isBombRevealed(copy.m_isBombRevealed), m_isFirstTurn(copy.m_isFirstTurn), m_numTilesRevealed(copy.m_numTilesRevealed)
{
}

Minesweeper::Minesweeper(Minesweeper&& copy) noexcept : m_board(std::move(copy.m_board)), m_isBombRevealed(copy.m_isBombRevealed), m_isFirstTurn(copy.m_isFirstTurn), m_numTilesRevealed(copy.m_numTilesRevealed)
{
}

Minesweeper& Minesweeper::operator=(const Minesweeper& rhs)
{
	if (this != &rhs)
	{
		m_board = rhs.m_board;
		m_isBombRevealed = rhs.m_isBombRevealed;
		m_isFirstTurn = rhs.m_isFirstTurn;
		m_numTilesRevealed = rhs.m_numTilesRevealed;
	}
	return *this;
}

Minesweeper& Minesweeper::operator=(Minesweeper&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_board = std::move(rhs.m_board);
		m_isBombRevealed = rhs.m_isBombRevealed;
		m_isFirstTurn = rhs.m_isFirstTurn;
		m_numTilesRevealed = rhs.m_numTilesRevealed;
	}
	return *this;
}

Minesweeper::~Minesweeper()
{
	m_isBombRevealed = false;
	m_isFirstTurn = true;
	m_numTilesRevealed = 0;
}

/*
* Purpose:
*		Controls the flow of the game by calling other methods
* Precondition:
*		None
* Postcondition:
*		Outputs a string on the console based on wether or not the player has won the game
*/
void Minesweeper::Start()
{
	// While the user isn't following the correct select difficulty format
	while (m_board.GetNumBombs() <= 0)
	{
		MakeBoard();
	}

	int winCondition = m_board.GetColumns() * m_board.GetRows() - m_board.GetNumBombs();

	m_board.DisplayBoard(m_isBombRevealed);

	// While a bomb is not hit and while all safe tiles aren't revealed
	while (!m_isBombRevealed && m_numTilesRevealed < winCondition)
	{
		ReadInput();
	}

	if (m_isBombRevealed)
	{
		cout << endl << "***********************" << endl;
		cout << "***** YOU LOSE :( *****" << endl;
		cout << "***********************" << endl;
	}
	else
	{
		cout << endl << "***********************" << endl;
		cout << "***** YOU WON! :) *****" << endl;
		cout << "***********************" << endl;
	}

}

/*
* Purpose:
*		Prompts the user for difficulty
* Precondition:
*		None
* Postcondition:
*		Makes a board to replace m_board based on difficulty
*/
void Minesweeper::MakeBoard()
{
	char difficulty;
	cout << "b = beginner | i = intermediate | e = expert | t = testing environment" << endl;
	cout << "Select Difficulty: ";
	cin >> difficulty;
	cin.clear();
	cin.ignore();

	if (difficulty == 'b')
		m_board = Board(10, 10, 10);
	else if (difficulty == 'i')
		m_board = Board(16, 16, 40);
	else if (difficulty == 'e')
		m_board = Board(16, 30, 100);
	else if (difficulty == 't')
		m_board = Board(2, 2, 2);	// a 2x2 board with 2 bombs for testing
}

/*
* Purpose:
*		Reads an input from the user and validate it using a regex
* Precondition:
*		None
* Postcondition:
*		Changes states of Cells based on user input
*/
void Minesweeper::ReadInput()
{
	char action;
	int row;
	int column;

	cout << "Command Format: 'action' row, column" << endl;
	cout << "Actions" << endl;
	cout << "r = reveal\n" << "m = mark\n" << "u = unmark" << endl << endl;
	cout << "Enter command: ";
	// ****************************************************************************************************
	// START OF AI-GENERATED CODE

	/*ChatGPT AI Prompts(1 / 18 / 2026) :
	* -I need a C++ regex for input validation in the form of : action_in_char row, column.Comment what each line does
	* -How do I extract the values from the input ?
	* -Explain what std::regex_match and std::smatch does
	*/

	string input;
	getline(cin, input);

	// Regex with CAPTURE GROUPS:
	// (1) action character
	// (2) row number
	// (3) column number
	regex pattern(R"(^([A-Za-z])\s(\d+),\s?(\d+)$)");

	// smatch stores the captured substrings
	smatch matches;

	// Try to match the input against the regex
	if (std::regex_match(input, matches, pattern))
	{
		// matches[0] -> the full matched string
		// matches[1] -> the action character
		// matches[2] -> the row
		// matches[3] -> the column

		action = matches[1].str()[0];	// convert string to char
		row = std::stoi(matches[2]);	// convert row to int
		column = std::stoi(matches[3]); // convert column to int

		// ******************************************************
		// Start of personal code
		
		// Avoids going out of bounds
		// Reveal
		if (action == 'r' && row >= 0 && row < m_board.GetRows() && column >= 0 && column < m_board.GetColumns())
		{
			if (m_board.SelectCell(row, column).IsBomb())
			{
				m_isBombRevealed = true;
			}
			else
				RevealTile(row, column);
		}
		// Mark
		if (action == 'm' && row >= 0 && row < m_board.GetRows() && column >= 0 && column < m_board.GetColumns())
		{
			m_board.SelectCell(row, column).SetState(marked);
		}
		// Unmark
		if (action == 'u' && row >= 0 && row < m_board.GetRows() && column >= 0 && column < m_board.GetColumns())
		{
			m_board.SelectCell(row, column).SetState(covered);
		}

		// End of personal code
		// ******************************************************
	}
	else
	{
		std::cout << "Invalid input format.\n";
	}
	// END OF AI-GENERATED CODE
	// ****************************************************************************************************

	m_board.DisplayBoard(m_isBombRevealed);
}

/*
* Purpose:
*		Recursively reveals blank tiles until it hits a numbered/uncovered/marked tiles
* Precondition:
*		Board is initialized
* Postcondition:
*		Changes the state of Cells to uncovered
*/
void Minesweeper::RevealTile(int row, int column)
{
	// Check if it's first turn
	if (m_isFirstTurn)
	{
		m_isFirstTurn = false;
		m_board.PlaceBombsExcept(row, column);
		RevealTile(row, column);
	}
	// If there's no adjacent, reveal until a numbered tile is hit
	else if (m_board.SelectCell(row, column).GetNumAdjBomb() == 0 && 
		!m_board.SelectCell(row, column).IsBomb() && 
		m_board.SelectCell(row, column).GetState() != uncovered &&
		m_board.SelectCell(row, column).GetState() != marked)	// *
	{
		m_board.SelectCell(row, column).SetState(uncovered);
		m_numTilesRevealed++;
		if (row - 1 >= 0 && column - 1 >= 0)	// NW
			RevealTile(row - 1, column - 1);
		if (row - 1 >= 0)	// N
			RevealTile(row - 1, column);
		if (row - 1 >= 0 && column + 1 < m_board.GetColumns()) // NE
			RevealTile(row - 1, column + 1);
		if (column - 1 >= 0)	// W
			RevealTile(row, column - 1);
		if (column + 1 < m_board.GetColumns())	// E
			RevealTile(row, column + 1);
		if (row + 1 < m_board.GetRows() && column - 1 >= 0)	// SW
			RevealTile(row + 1, column - 1);
		if (row + 1 < m_board.GetRows())	// S
			RevealTile(row + 1, column);
		if (row + 1 < m_board.GetRows() && column + 1 < m_board.GetColumns())	// SE
			RevealTile(row + 1, column + 1);
	}
	// If it's a number
	else if (m_board.SelectCell(row, column).GetNumAdjBomb() > 0 && 
		!m_board.SelectCell(row, column).IsBomb() && 
		m_board.SelectCell(row, column).GetState() != uncovered && 
		m_board.SelectCell(row, column).GetState() != marked)
	{
		m_board.SelectCell(row, column).SetState(uncovered);
		m_numTilesRevealed++;
	}
}
