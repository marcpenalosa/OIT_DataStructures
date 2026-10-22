#include "board.h"

Board::Board() : m_cellArray(Array2D<Cell>()), m_rows(0), m_columns(0), m_numBombs(0)
{
}

Board::Board(int rows, int columns, int numBombs) : m_cellArray(Array2D<Cell>(rows, columns)), m_rows(rows),
	m_columns(columns), m_numBombs(numBombs)
{
	if (numBombs <= 0)
		throw Exception("Negative or zero number of bombs");
}

Board::Board(const Board& copy) : m_cellArray(copy.m_cellArray), m_rows(copy.m_rows), m_columns(copy.m_columns), m_numBombs(copy.m_numBombs)
{
}

Board::Board(Board&& copy) noexcept : m_cellArray(std::move(copy.m_cellArray)), m_rows(copy.m_rows), m_columns(copy.m_columns), m_numBombs(copy.m_numBombs)
{
}

Board& Board::operator=(const Board& rhs)
{
	if (this != &rhs)
	{
		m_cellArray = rhs.m_cellArray;
		m_rows = rhs.m_rows;
		m_columns = rhs.m_columns;
		m_numBombs = rhs.m_numBombs;
	}
	return *this;
}

Board& Board::operator=(Board&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_cellArray = std::move(rhs.m_cellArray);
		m_rows = rhs.m_rows;
		m_columns = rhs.m_columns;
		m_numBombs = rhs.m_numBombs;
	}
	return *this;
}

Board::~Board()
{
	m_rows = 0;
	m_columns = 0;
	m_numBombs = 0;
}

int Board::GetRows() const
{
	return m_rows;
}

int Board::GetColumns() const
{
	return m_columns;
}

int Board::GetNumBombs() const
{
	return m_numBombs;
}

/*
* Purpose:
*		Selects a specific Cell in the board to access their functionality
* Precondition:
*		m_cellArray must be initialized
* Postcondition:
*		Returns the address of a Cell in m_cellArray
*/
Cell& Board::SelectCell(int row, int column)
{
	return m_cellArray[row][column];
}

const Cell& Board::SelectCell(int row, int column) const
{
	return m_cellArray[row][column];
}

/*
* Purpose:
*		Places bombs at random cells except at a given row and column (the first turn position)
*		to avoid hitting mines on the first turn
* Precondition:
*		m_cellArray must be initialized
* Postcondition:
*		Sets random Cells' m_isBomb to true based on the number of bombs in the board
*/
void Board::PlaceBombsExcept(int row, int column)
{
	// srand func takes an integer as a seed
	// time(0) uses the current time as a random seed
	srand(time(0));
	int numBombPlaced = 0;
	int randomRow;
	int randomColumn;

	while (numBombPlaced != m_numBombs)
	{
		randomRow = rand() % m_rows;
		randomColumn = rand() % m_columns;
		//cout << "row: " << row << "\t column: " << column << endl;
		if (!m_cellArray[randomRow][randomColumn].IsBomb() && (randomRow != row || randomRow != column))
		{
			// Set the bomb as true for this tile
			m_cellArray[randomRow][randomColumn].SetBomb(true);
			numBombPlaced++;

			// Increment surrounding numbered tile
			IncrementAdjacentNum(randomRow, randomColumn);
		}
	}
}

/*
* Purpose:
*		Increments the bomb counter of valid adjacent bombs
* Precondition:
*		m_cellArray is initialized and number of bomb is greater than 0
* Postcondition:
*		Calls Cell::IncrNumAdjBomb on the surrounding Cells to increment their
*		m_numAdjacentBomb variable
*/
void Board::IncrementAdjacentNum(int row, int column)
{
	if (row - 1 >= 0 && column - 1 >= 0 && !m_cellArray[row - 1][column - 1].IsBomb())	// NW
		m_cellArray[row - 1][column - 1].IncrNumAdjBomb();
	if (row - 1 >= 0 && !m_cellArray[row - 1][column].IsBomb())	// N
		m_cellArray[row - 1][column].IncrNumAdjBomb();
	if (row - 1 >= 0 && column + 1 < m_columns && !m_cellArray[row - 1][column + 1].IsBomb())	// NE
		m_cellArray[row - 1][column + 1].IncrNumAdjBomb();
	if (column - 1 >= 0 && !m_cellArray[row][column - 1].IsBomb())	// W
		m_cellArray[row][column - 1].IncrNumAdjBomb();
	if (column + 1 < m_columns && !m_cellArray[row][column + 1].IsBomb()) // E
		m_cellArray[row][column + 1].IncrNumAdjBomb();
	if (row + 1 < m_rows && column - 1 >= 0 && !m_cellArray[row + 1][column - 1].IsBomb())	// SW
		m_cellArray[row + 1][column - 1].IncrNumAdjBomb();
	if (row + 1 < m_rows && !m_cellArray[row + 1][column].IsBomb())	// S
		m_cellArray[row + 1][column].IncrNumAdjBomb();
	if (row + 1 < m_rows && column + 1 < m_columns && !m_cellArray[row + 1][column + 1].IsBomb())	// SE
		m_cellArray[row + 1][column + 1].IncrNumAdjBomb();
}

/*
* Purpose:
*		Displays the entire board on the console
* Precondition:
*		m_cellArray must be intialized
* Postcondition:
*		Displays the entire board on the console
*/
void Board::DisplayBoard(bool bombRevealed)
{
	// ANSI Color Codes
	string black = "\033[30m";		// black
	string whiteBG = "\033[47m";	// white background
	string reset = "\033[0m";		// reset

	system("cls");	// clear console

	// COLUMN NUMBER
	cout << black << whiteBG << "    " << (char)179;
	for (int i = 0; i < m_columns; i++)
		cout << "[" << setfill(' ') << setw(2) << i << "]";
	cout << endl;
	cout << "    " << (char)195;
	for (int i = 0; i < m_columns; i++)
		cout << (char)196 << (char)196 << (char)196 << (char)196;
	cout << " " << endl;

	for (int i = 0; i < m_rows; i++)
	{
		// ROW NUMBER
		cout << black << whiteBG << "[" << setfill(' ') << setw(2) << i << "]";
		cout << (char)179 << reset;

		// Print cell (covered / bomb / blank / numbered)
		for (int j = 0; j < m_columns; j++)
		{
			// If the Cell is a bomb and you've already hit a bomb
			if (m_cellArray[i][j].IsBomb() && bombRevealed)
				cout << whiteBG << black << "[" << reset << setfill(' ') << setw(2) << (char)162 << reset << whiteBG << black << "]";
			// If the Cell is covered OR marked
			else if (m_cellArray[i][j].GetState() == covered ||
				m_cellArray[i][j].GetState() == marked)
				cout << whiteBG << black << "[" << setfill(' ') << setw(2) << m_cellArray[i][j].GetState() << "]" << reset;
			// If the cell is uncovered AND not a bomb AND a blank
			else if (m_cellArray[i][j].GetState() == uncovered && !m_cellArray[i][j].IsBomb() && m_cellArray[i][j].GetNumAdjBomb() == 0)
				cout << whiteBG << black << " " << " " << FormatNumDisplay(m_cellArray[i][j].GetNumAdjBomb()) << reset
				<< whiteBG << black << " " << reset;
			// If the cell is uncovered AND not a bomb, then it's a number to be printed
			else if (m_cellArray[i][j].GetState() == uncovered && !m_cellArray[i][j].IsBomb())
				cout << whiteBG << black << "[" << " " << FormatNumDisplay(m_cellArray[i][j].GetNumAdjBomb()) << reset
				<< whiteBG << black << "]" << reset;
		}
		cout << reset << endl;
	}
}

/*
* Purpose:
*		Formats the colored of given numbers 0-8 to be outputted to the console
* Precondition:
*		None
* Postcondition:
*		Returns a string with ANSI color codes
*/
string Board::FormatNumDisplay(int num)
{
	string result;

	switch (num)
	{
	case 0:
		result = "\033[30m ";
		break;
	case 1:
		result = "\033[1;34m1";	// light blue
		break;
	case 2:
		result = "\033[32m2";	// green
		break;
	case 3:
		result = "\033[1;31m3";	// red
		break;
	case 4:
		result = "\033[34m4";	// blue
		break;
	case 5:
		result = "\033[31m5";	// dark red
		break;
	case 6:
		result = "\033[36m6";	// cyan
		break;
	case 7:
		result = "\033[30m7";	// black
		break;
	case 8:
		result = "\033[1;37m8";	// bold white
		break;
	default:
		result = "\033[0mE";	// reset E for error
		break;
	}

	return result;
}
