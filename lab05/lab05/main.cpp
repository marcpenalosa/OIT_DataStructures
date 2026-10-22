/******************************************************
* Author:		Marc Penalosa
* Filename:		main.cpp
* Date Created:	1/17/26
******************************************************/
/******************************************************
* 
* Lab Assignment: Lab 5 - Minesweeper
* 
* Overview:
*		An ASCII-based Minesweeper game
* 
* Input:
*		None
* 
* Output:
*		A working ASCII Minesweeper game using the console
*		and text-based commands
******************************************************/

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::endl;

#include <regex>
using std::regex;
using std::smatch;

#include <string>

#include "array.h"
#include "minesweeper.h"
#include "board.h"
#include "cell.h"

/*
* ChatGPT AI Prompts (1/18/2026):
*	- I need a C++ regex for input validation in the form of: action_in_char row, column. Comment what each line does
*	- How do I extract the values from the input?
*	- Explain what std::regex_match and std::smatch does
* 
* ChatGPT Response in summary:
*	int main() {
*		string input;
*		getline(cin, input);
* 
*		// Regex with CAPTURE GROUPS:
*		// (1) action character
*		// (2) row number
*		// (3) column number
*		regex pattern(R"(^([A-Za-z])\s(\d+),\s?(\d+)$)");
* 
*		// smatch stores the captured substrings
*		std::smatch matches;
*
*		// Try to match the input against the regex
*		if (std::regex_match(input, matches, pattern)) {
*			// matches[0] -> the full matched string
*			// matches[1] -> the action character
*			// matches[2] -> the row
*			// matches[3] -> the column
*			
*			char action = matches[1].str()[0];	// convert string to char
*			int row = std::stoi(matches[2]);	// convert row to int
*			int column = std::stoi(matches[3]); // convert column to int
*		}
*		else {
*			std::cout << "Invalid input format.\n";
*		}
*		
*		return 0;
*	}
*	// std::regex_match checks whether a string matches a regular expression exactly.
*	// Example:
*		std::regex r("\\d+");
*		std::regex_match("123", r);		// true
*		std::regex_match("123abc", r);	// false
* 
*	// std::smatch is a container that stores the results of a regex match, including capture groups.
*	// if your regex has parentheses (), std::match captures them.
*/

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Minesweeper minesweeper;
	minesweeper.Start();

	return 0;
}