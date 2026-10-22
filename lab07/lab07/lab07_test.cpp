/*******************************************
* Author:			Marc Penalosa
* Filename:			lab06_test.cpp
* Date Created:		1/24/26
*******************************************/
/*******************************************
* 
* Lab Assignment: Lab 7 - List Based Stack
* 
* Overview:
*		This program tests a Stack class's ctors and methods
* 
* Input:
*		None
* 
* Output:
*		Print strings on the console window that depends on whether
*		or not the tests passed
*******************************************/

#define _CRTDBG_MAP_ALLOC

// Define a function pointer type
typedef bool(*FunctionPointer)();

#include <crtdbg.h>
//#include <conio.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include "exception.h"
#include "stack.h"

// Test Class Ctors
bool Test_DefaultCtor();
bool Test_DefaultCtorComplex();
bool Test_CopyCtor();
bool Test_CopyCtorComplex();
bool Test_MoveCtor();
bool Test_MoveCtorComplex();
bool Test_OpEqual();
bool Test_OpEqualComplex();
bool Test_OpEqualMove();
bool Test_OpEqualMoveComplex();

// Test Class Functions
bool Test_GetNumElements();
bool Test_GetNumElementsComplex();
bool Test_IsEmpty();
bool Test_IsEmptyComplex();
bool Test_Pop();
bool Test_PopComplex();
bool Test_PopOnEmpty();
bool Test_PopOnEmptyComplex();
bool Test_Peek();
bool Test_PeekComplex();
bool Test_PeekOnEmpty();
bool Test_PeekOnEmptyComplex();

// Array of test functions
FunctionPointer test_functions[] = { Test_DefaultCtor, Test_DefaultCtorComplex,
Test_CopyCtor, Test_CopyCtorComplex, Test_MoveCtor, Test_MoveCtorComplex,
Test_OpEqual, Test_OpEqualComplex, Test_OpEqualMove, Test_GetNumElements, Test_GetNumElementsComplex,
Test_IsEmpty, Test_IsEmptyComplex, Test_Pop, Test_PopComplex, Test_PopOnEmpty, Test_PopOnEmptyComplex, 
Test_Peek, Test_PeekComplex, Test_PeekOnEmpty, Test_PeekOnEmptyComplex };

// Strings to test
const char* NAMES[] = { "Marc", "James", "Edgar", "Todd", "Connor", "Scott" };
const char* NAMES_BACKWARDS[] = { "Scott", "Connor", "Todd", "Edgar", "James", "Marc" };
const int NUM_NAMES = 6;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Run test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
			cout << "passed" << endl;
		else
			cout << "***** failed *****" << endl;
	}

	return 0;
}

bool Test_DefaultCtor()
{
	cout << "***** Class Ctors *****" << endl;
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack;

	// Check if it has the default number of elements
	if (intStack.getNumElements() != 0)
		pass = false;

	cout << "Test_DefaultCtor ";

	return pass;
}

bool Test_DefaultCtorComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack;

	// Check if it doesn't have the default number of elements
	if (stringStack.getNumElements() != 0)
		pass = false;

	cout << "Test_DefaultCtorComplex ";

	return pass;
}

bool Test_CopyCtor()
{
	bool pass = true;
	int test_data[] = { 1, 2, 3, 4 };

	// INITIALIZE
	// intStack = { 4, 3, 2, 1 }
	Stack<int> intStack;
	intStack.Push(4);
	intStack.Push(3);
	intStack.Push(2);
	intStack.Push(1);
	Stack<int> intStackCopy(intStack);

	// Check if it doesn't have the correct num of elements
	if (intStackCopy.getNumElements() != 4)
		pass = false;

	// Check if it didn't copy data correctly
	int numElements = intStackCopy.getNumElements();
	for (int i = 0; i < numElements; i++)
	{
		if (intStackCopy.Pop() != test_data[i])
			pass = false;
	}

	cout << "Test_CopyCtor ";

	return pass;
}

bool Test_CopyCtorComplex()
{
	bool pass = true;

	// INITIALIZE
	// stringStack = { Marc, James, Edgar, Todd, Connor, Scott }
	Stack<string> stringStack;
	for (int i = 0; i < NUM_NAMES; i++)
		stringStack.Push(NAMES[i]);
	Stack<string> stringStackCopy(stringStack);

	// Check if it doesn't have the correct num of elements
	if ((stringStackCopy.getNumElements() != 6))
		pass = false;

	// Check if it didn't copy data correctly
	for (int i = 0; i < NUM_NAMES; i++)
	{
		if (stringStackCopy.Pop() != NAMES_BACKWARDS[i])
			pass = false;
	}

	cout << "Test_CopyCtorComplex ";

	return pass;
}

bool Test_MoveCtor()
{
	bool pass = true;
	int test_data[] = { 1, 2, 3, 4 };

	// INITIALIZE
	Stack<int> intStack;
	intStack.Push(4);
	intStack.Push(3);
	intStack.Push(2);
	intStack.Push(1);
	// intStackCopy = { 4, 3, 2, 1 }
	Stack<int> intStackCopy(std::move(intStack));

	// Check if it doesn't have the correct num of elements
	if (intStackCopy.getNumElements() != 4)
		pass = false;

	// Check if it didn't copy data correctly
	int numElements = intStackCopy.getNumElements();
	for (int i = 0; i < numElements; i++)
	{
		if (intStackCopy.Pop() != test_data[i])
			pass = false;
	}

	cout << "Test_MoveCtor ";

	return pass;
}

bool Test_MoveCtorComplex()
{
	bool pass = true;

	// INITIALIZE
	// stringStack = { Marc, James, Edgar, Todd, Connor, Scott }
	Stack<string> stringStack;
	for (int i = 0; i < NUM_NAMES; i++)
		stringStack.Push(NAMES[i]);
	Stack<string> stringStackCopy(std::move(stringStack));

	// Check if it doesn't have the correct num of elements
	if (stringStackCopy.getNumElements() != 6)
		pass = false;

	// Check if it didn't copy data correctly
	for (int i = 0; i < NUM_NAMES; i++)
	{
		if (stringStackCopy.Pop() != NAMES_BACKWARDS[i])
			pass = false;
	}

	cout << "Test_MoveCtorComplex ";

	return pass;
}

bool Test_OpEqual()
{
	bool pass = true;
	int test_data[] = { 1, 2, 3, 4 };

	// INITIALIZE
	Stack<int> intStack;
	intStack.Push(4);
	intStack.Push(3);
	intStack.Push(2);
	intStack.Push(1);
	Stack<int> intStackCopy;
	intStackCopy = intStack;

	// Check if it doesn't have the correct num of elements
	if (intStackCopy.getNumElements() != 4)
		pass = false;

	// Check if it didn't copy data correctly
	int numElements = intStackCopy.getNumElements();
	for (int i = 0; i < numElements; i++)
	{
		if (intStackCopy.Pop() != test_data[i])
			pass = false;
	}

	cout << "Test_OpEqual ";

	return pass;
}

bool Test_OpEqualComplex()
{
	bool pass = true;

	// INITIALIZE
	// stringStack = { Marc, James, Edgar, Todd, Connor, Scott }
	Stack<string> stringStack;
	for (int i = 0; i < NUM_NAMES; i++)
		stringStack.Push(NAMES[i]);
	Stack<string> stringStackCopy;
	stringStackCopy = stringStack;

	// Check if it doesn't have the correct num of elements
	if (stringStackCopy.getNumElements() != 6)
		pass = false;

	// Check if it didn't copy data correctly
	for (int i = 0; i < NUM_NAMES; i++)
	{
		if (stringStackCopy.Pop() != NAMES_BACKWARDS[i])
			pass = false;
	}

	cout << "Test_OpEqualComplex ";

	return pass;
}

bool Test_OpEqualMove()
{
	bool pass = true;
	int test_data[] = { 1, 2, 3, 4 };

	// INITIALIZE
	Stack<int> intStack;
	intStack.Push(4);
	intStack.Push(3);
	intStack.Push(2);
	intStack.Push(1);
	// intStackCopy = { 4, 3, 2, 1 }
	Stack<int> intStackCopy;
	intStackCopy = std::move(intStack);

	// Check if it doesn't have the correct num of elements
	if (intStackCopy.getNumElements() != 4)
		pass = false;

	// Check if it didn't copy data correctly
	int numElements = intStackCopy.getNumElements();
	for (int i = 0; i < numElements; i++)
	{
		if (intStackCopy.Pop() != test_data[i])
			pass = false;
	}

	cout << "Test_OpEqualMove ";

	return pass;
}

bool Test_OpEqualMoveComplex()
{
	bool pass = true;

	// INITIALIZE
	// stringStack = { Marc, James, Edgar, Todd, Connor, Scott }
	Stack<string> stringStack;
	for (int i = 0; i < NUM_NAMES; i++)
		stringStack.Push(NAMES[i]);
	Stack<string> stringStackCopy;
	stringStackCopy = std::move(stringStack);

	// Check if it doesn't have the correct num of elements
	if (stringStackCopy.getNumElements() != 6)
		pass = false;

	// Check if it didn't copy data correctly
	for (int i = 0; i < NUM_NAMES; i++)
	{
		if (stringStackCopy.Pop() != NAMES_BACKWARDS[i])
			pass = false;
	}

	cout << "Test_OpEqualMoveComplex ";

	return pass;
}

bool Test_GetNumElements()
{
	cout << endl << "***** Class Functions *****" << endl;
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack;

	// Should be empty
	if (intStack.getNumElements() != 0)
		pass = false;

	intStack.Push(0);
	intStack.Push(0);
	// Should be 2 elements
	if (intStack.getNumElements() != 2)
		pass = false;

	intStack.Pop();
	intStack.Pop();
	// Should be empty
	if (intStack.getNumElements() != 0)
		pass = false;

	cout << "Test_GetNumElements ";

	return pass;
}

bool Test_GetNumElementsComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack;

	// Should be empty
	if (stringStack.getNumElements() != 0)
		pass = false;
	
	stringStack.Push("Pizza");
	stringStack.Push("Pizza");
	// Should be 2 elements
	if (stringStack.getNumElements() != 2)
		pass = false;

	stringStack.Pop();
	stringStack.Pop();
	// Should be empty
	if (stringStack.getNumElements() != 0)
		pass = false;

	cout << "Test_GetNumElementsComplex ";

	return pass;
}

bool Test_IsEmpty()
{
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack1;
	Stack<int> intStack2;
	intStack2.Push(1);
	intStack2.Push(1);

	// intStack1 = 0 elements
	if (!intStack1.isEmpty())
		pass = false;
	// intStack2 = 2 elements
	if (intStack2.isEmpty())
		pass = false;

	cout << "Test_IsEmpty ";

	return pass;
}

bool Test_IsEmptyComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack1;
	Stack<string> stringStack2;
	stringStack2.Push("Marc");

	// stringStack1 = 0 elements
	if (!stringStack1.isEmpty())
		pass = false;
	// stringStack2 = 1 elements
	if (stringStack2.isEmpty())
		pass = false;

	cout << "Test_IsEmptyComplex ";

	return pass;
}

bool Test_Pop()
{
	bool pass = true;
	int test_data[] = { 1, 2, 1, 0 };
	int num_elements = 4;

	// INITIALIZE
	Stack<int> intStack;
	intStack.Push(0);
	intStack.Push(1);
	intStack.Push(2);
	intStack.Push(1);

	// intStack = { 0, 1, 2, 1 }
	// Should pop such as { 0, 1, 2, 1} -> { 0, 1, 2} ... popping the right 1 instead of the left 1
	for (int i = 0; i < num_elements; i++)
	{
		if (intStack.Pop() != test_data[i])
			pass = false;
	}

	// Do it a second time to prove popping to empty, then populating again works
	intStack.Push(0);
	intStack.Push(1);
	intStack.Push(2);
	intStack.Push(1);
	for (int i = 0; i < num_elements; i++)
	{
		if (intStack.Pop() != test_data[i])
			pass = false;
	}

	cout << "Test_Pop ";

	return pass;
}

bool Test_PopComplex()
{
	bool pass = true;
	const char* test_data[] = { "Marc", "Barc", "Marc", "Shark" };
	int num_elements = 4;

	// INITIALIZE
	Stack<string> stringStack;
	stringStack.Push("Shark");
	stringStack.Push("Marc");
	stringStack.Push("Barc");
	stringStack.Push("Marc");

	// stringStack = { Shark, Marc, Barc, Marc }
	// Should pop such as { Shark, Marc, Barc, Marc} -> { Shark, Marc, Barc} ... popping the 'right' Marc instead of the 'left' Marc
	for (int i = 0; i < num_elements; i++)
	{
		if (stringStack.Pop() != test_data[i])
			pass = false;
	}

	// Do it a second time to prove popping to empty, then populating again works
	stringStack.Push("Shark");
	stringStack.Push("Marc");
	stringStack.Push("Barc");
	stringStack.Push("Marc");
	for (int i = 0; i < num_elements; i++)
	{
		if (stringStack.Pop() != test_data[i])
			pass = false;
	}

	cout << "Test_PopComplex ";

	return pass;
}

bool Test_PopOnEmpty()
{
	bool pass = false;

	// INITIALIZE
	Stack<int> intStack;

	try
	{
		intStack.Pop();
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Test_PopOnEmpty ";

	return pass;
}

bool Test_PopOnEmptyComplex()
{
	bool pass = false;

	// INITIALIZE
	Stack<string> stringStack;

	try
	{
		stringStack.Pop();
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_PopOnEmptyComplex ";

	return pass;
}

bool Test_Peek()
{
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack;
	intStack.Push(1);
	intStack.Push(2);

	if (intStack.Peek() != 2)
		pass = false;

	cout << "Test_Peek ";

	return pass;
}

bool Test_PeekComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack;
	stringStack.Push("Marc");
	stringStack.Push("Markus");

	if (stringStack.Peek() != "Markus")
		pass = false;

	cout << "Test_PeekComplex ";

	return pass;
}

bool Test_PeekOnEmpty()
{
	bool pass = false;

	Stack<int> intStack;

	try
	{
		intStack.Peek();
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_PeekOnEmpty ";

	return pass;
}

bool Test_PeekOnEmptyComplex()
{
	bool pass = false;

	Stack<string> stringStack;

	try
	{
		stringStack.Peek();
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_PeekOnEmptyComplex ";

	return pass;
}
