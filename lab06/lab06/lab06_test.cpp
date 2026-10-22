/*******************************************
* Author:			Marc Penalosa
* Filename:			lab06_test.cpp
* Date Created:		1/24/26
*******************************************/
/*******************************************
* 
* Lab Assignment: Lab 6 - Array Based Stack
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
bool Test_1ArgCtor();
bool Test_1ArgCtorComplex();
bool Test_1ArgCtorNegativeSize();
bool Test_1ArgCtorNegativeSizeComplex();
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
bool Test_GetSize();
bool Test_GetSizeComplex();
bool Test_IsEmpty();
bool Test_IsEmptyComplex();
bool Test_IsFull();
bool Test_IsFullComplex();
bool Test_PushOnZeroSize();
bool Test_PushOnZeroSizeComplex();
bool Test_PushOnFull();
bool Test_PushOnFullComplex();
bool Test_Pop();
bool Test_PopComplex();
bool Test_PopOnZeroSize();
bool Test_PopOnZeroSizeComplex();
bool Test_PopOnEmpty();
bool Test_PopOnEmptyComplex();
bool Test_Peek();
bool Test_PeekComplex();
bool Test_PeekOnEmpty();
bool Test_PeekOnEmptyComplex();
bool Test_SetSizeOnEmpty();
bool Test_SetSizeOnEmptyComplex();
bool Test_SetSizeOnFullDecrease();
bool Test_SetSizeOnFullDecreaseComplex();
bool Test_SetSizeOnFullIncrease();
bool Test_SetSizeOnFullIncreaseComplex();
bool Test_SetSizeNegativeLength();
bool Test_SetSizeNegativeLengthComplex();

// Array of test functions
FunctionPointer test_functions[] = { Test_DefaultCtor, Test_DefaultCtorComplex, Test_1ArgCtor,
Test_1ArgCtorComplex, Test_1ArgCtorNegativeSize, Test_1ArgCtorNegativeSizeComplex,
Test_CopyCtor, Test_CopyCtorComplex, Test_MoveCtor, Test_MoveCtorComplex,
Test_OpEqual, Test_OpEqualComplex, Test_OpEqualMove, Test_GetNumElements, Test_GetNumElementsComplex,
Test_GetSize, Test_GetSizeComplex, Test_IsEmpty, Test_IsEmptyComplex, Test_IsFull,
Test_IsFullComplex, Test_PushOnZeroSize, Test_PushOnZeroSizeComplex, Test_PushOnFull, Test_PushOnFullComplex,
Test_Pop, Test_PopComplex, Test_PopOnZeroSize, Test_PopOnZeroSizeComplex, Test_PopOnEmpty, Test_PopOnEmptyComplex, Test_Peek,
Test_PeekComplex, Test_PeekOnEmpty, Test_PeekOnEmptyComplex, Test_SetSizeOnEmpty, 
Test_SetSizeOnEmptyComplex, Test_SetSizeOnFullDecrease, Test_SetSizeOnFullDecreaseComplex, 
Test_SetSizeOnFullIncrease, Test_SetSizeOnFullIncreaseComplex, Test_SetSizeNegativeLength, 
Test_SetSizeNegativeLengthComplex };

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

	// Check if it has the default number of elements and size
	if (intStack.getNumElements() != 0 || intStack.getSize() !=0)
		pass = false;

	cout << "Test_DefaultCtor ";

	return pass;
}

bool Test_DefaultCtorComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack;

	// Check if it doesn't have the default number of elements and size
	if (stringStack.getNumElements() != 0 || stringStack.getSize() != 0)
		pass = false;

	cout << "Test_DefaultCtorComplex ";

	return pass;
}

bool Test_1ArgCtor()
{
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack(5);

	// Check if it doesn't have the given size and check if it touched the num of elements
	if (intStack.getSize() != 5 || intStack.getNumElements() != 0)
		pass = false;

	cout << "Test_1ArgCtor ";

	return pass;
}

bool Test_1ArgCtorComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack(5);

	// Check if it doesn't have the given size and check if it touched the num of elements
	if (stringStack.getSize() != 5 || stringStack.getNumElements() != 0)
		pass = false;

	cout << "Test_1ArgCtorComplex ";

	return pass;
}

bool Test_1ArgCtorNegativeSize()
{
	bool pass = false;

	try
	{
		Stack<int> intStack(-5);
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Test_1ArgCtorNegativeSize ";

	return pass;
}

bool Test_1ArgCtorNegativeSizeComplex()
{
	bool pass = false;

	try
	{
		Stack<string> stringStack(-5);
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_1ArgCtorNegativeSizeComplex ";

	return pass;
}

bool Test_CopyCtor()
{
	bool pass = true;
	int test_data[] = { 1, 2, 3, 4 };

	// INITIALIZE
	// intStack = { 4, 3, 2, 1 }
	Stack<int> intStack(5);
	intStack.Push(4);
	intStack.Push(3);
	intStack.Push(2);
	intStack.Push(1);
	Stack<int> intStackCopy(intStack);

	// Check if it doesn't have the correct size and num of elements
	if (intStackCopy.getSize() != 5 || intStackCopy.getNumElements() != 4)
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
	Stack<string> stringStack(6);
	for (int i = 0; i < NUM_NAMES; i++)
		stringStack.Push(NAMES[i]);
	Stack<string> stringStackCopy(stringStack);

	// Check if it doesn't have the correct size and num of elements
	if (stringStackCopy.getSize() != 6 || (stringStackCopy.getNumElements() != 6))
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
	Stack<int> intStack(5);
	intStack.Push(4);
	intStack.Push(3);
	intStack.Push(2);
	intStack.Push(1);
	// intStackCopy = { 4, 3, 2, 1 }
	Stack<int> intStackCopy(std::move(intStack));

	// Check if it doesn't have the correct size and num of elements
	if (intStackCopy.getSize() != 5 || intStackCopy.getNumElements() != 4)
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
	Stack<string> stringStack(6);
	for (int i = 0; i < NUM_NAMES; i++)
		stringStack.Push(NAMES[i]);
	Stack<string> stringStackCopy(std::move(stringStack));

	// Check if it doesn't have the correct size and num of elements
	if (stringStackCopy.getSize() != 6 || stringStackCopy.getNumElements() != 6)
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
	Stack<int> intStack(5);
	intStack.Push(4);
	intStack.Push(3);
	intStack.Push(2);
	intStack.Push(1);
	Stack<int> intStackCopy;
	intStackCopy = intStack;

	// Check if it doesn't have the correct size and num of elements
	if (intStackCopy.getSize() != 5 || intStackCopy.getNumElements() != 4)
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
	Stack<string> stringStack(6);
	for (int i = 0; i < NUM_NAMES; i++)
		stringStack.Push(NAMES[i]);
	Stack<string> stringStackCopy;
	stringStackCopy = stringStack;

	// Check if it doesn't have the correct size and num of elements
	if (stringStackCopy.getSize() != 6 || (stringStackCopy.getNumElements() != 6))
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
	Stack<int> intStack(5);
	intStack.Push(4);
	intStack.Push(3);
	intStack.Push(2);
	intStack.Push(1);
	// intStackCopy = { 4, 3, 2, 1 }
	Stack<int> intStackCopy;
	intStackCopy = std::move(intStack);

	// Check if it doesn't have the correct size and num of elements
	if (intStackCopy.getSize() != 5 || intStackCopy.getNumElements() != 4)
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
	Stack<string> stringStack(6);
	for (int i = 0; i < NUM_NAMES; i++)
		stringStack.Push(NAMES[i]);
	Stack<string> stringStackCopy;
	stringStackCopy = std::move(stringStack);

	// Check if it doesn't have the correct size and num of elements
	if (stringStackCopy.getSize() != 6 || stringStackCopy.getNumElements() != 6)
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
	Stack<int> intStack(3);

	// Should be empty
	if (intStack.getNumElements() != 0)
		pass = false;

	intStack.Push(1);
	intStack.Push(1);
	intStack.Push(1);
	// Should be 3 elements
	if (intStack.getNumElements() != 3)
		pass = false;

	intStack.Pop();
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
	Stack<string> stringStack(3);

	// Should be empty
	if (stringStack.getNumElements() != 0)
		pass = false;

	stringStack.Push("Pizza");
	stringStack.Push("Pizza");
	stringStack.Push("Pizza");
	// Should be 3 elements
	if (stringStack.getNumElements() != 3)
		pass = false;

	stringStack.Pop();
	stringStack.Pop();
	stringStack.Pop();
	// Should be empty
	if (stringStack.getNumElements() != 0)
		pass = false;

	cout << "Test_GetNumElementsComplex ";

	return pass;
}

bool Test_GetSize()
{
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack1;
	Stack<int> intStack2;
	intStack2.setSize(2);
	Stack<int> intStack3(3);

	// intStack1 should be 0
	if (intStack1.getSize() != 0)
		pass = false;

	// intStack2 should be 2
	if (intStack2.getSize() != 2)
		pass = false;

	// intStack3 should be 3
	if (intStack3.getSize() != 3)
		pass = false;

	cout << "Test_GetSize ";

	return pass;
}

bool Test_GetSizeComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack1;
	Stack<string> stringStack2;
	stringStack2.setSize(2);
	Stack<string> stringStack3(3);

	// stringStack1 should be 0
	if (stringStack1.getSize() != 0)
		pass = false;

	// stringStack2 should be 2
	if (stringStack2.getSize() != 2)
		pass = false;

	// stringStack3 should be 3
	if (stringStack3.getSize() != 3)
		pass = false;

	cout << "Test_GetSizeComplex ";

	return pass;
}

bool Test_IsEmpty()
{
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack1(5);
	Stack<int> intStack2(5);
	intStack2.Push(1);
	intStack2.Push(1);

	// intStack1 = 0/5 elements
	if (!intStack1.isEmpty())
		pass = false;
	// intStack2 = 2/5 elements
	if (intStack2.isEmpty())
		pass = false;

	cout << "Test_IsEmpty ";

	return pass;
}

bool Test_IsEmptyComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack1(5);
	Stack<string> stringStack2(5);
	stringStack2.Push("Marc");

	// stringStack1 = 0/5 elements
	if (!stringStack1.isEmpty())
		pass = false;
	// stringStack2 = 1/5 elements
	if (stringStack2.isEmpty())
		pass = false;

	cout << "Test_IsEmptyComplex ";

	return pass;
}

bool Test_IsFull()
{
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack1(3);
	Stack<int> intStack2(3);
	intStack2.Push(1);
	intStack2.Push(1);
	Stack<int> intStack3(3);
	intStack3.Push(2);
	intStack3.Push(2);
	intStack3.Push(2);

	// intStack1 = 0/3 elements
	if (intStack1.isFull())
		pass = false;
	// intStack2 = 2/3 elements
	if (intStack2.isFull())
		pass = false;
	// intStack3 = 3/3 elements
	if (!intStack3.isFull())
		pass = false;

	cout << "Test_IsFull ";

	return pass;
}

bool Test_IsFullComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack1(2);
	Stack<string> stringStack2(2);
	stringStack2.Push("Marc");
	Stack<string> stringStack3(2);
	stringStack3.Push("Marc");
	stringStack3.Push("Barc");

	// stringStack1 = 0/2 elements
	if (stringStack1.isFull())
		pass = false;
	// stringStack2 = 1/2 elements
	if (stringStack2.isFull())
		pass = false;
	// stringStack3 = 2/2 elements
	if (!stringStack3.isFull())
		pass = false;

	cout << "Test_IsFullComplex ";

	return pass;
}

bool Test_PushOnZeroSize()
{
	bool pass = false;

	// INITIALIZE
	Stack<int> intStack;

	try
	{
		intStack.Push(1);
	}
	catch (Exception& exception)
	{
		pass = true;
	}
	
	cout << "Test_PushOnZeroSize ";

	return pass;
}

bool Test_PushOnZeroSizeComplex()
{
	bool pass = false;

	// INITIALIZE
	Stack<string> stringStack;

	try
	{
		stringStack.Push("Clark");
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_PushOnZeroSizeComplex ";

	return pass;
}

bool Test_PushOnFull()
{
	bool pass = false;

	// INITIALIZE
	Stack<int> intStack(1);

	try
	{
		intStack.Push(2);
		intStack.Push(2);
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_PushOnFull ";

	return pass;
}

bool Test_PushOnFullComplex()
{
	bool pass = false;

	// INITIALIZE
	Stack<string> stringStack(1);

	try
	{
		stringStack.Push("Solid");
		stringStack.Push("Snake");
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_PushOnFullComplex ";

	return pass;
}

bool Test_Pop()
{
	bool pass = true;
	int test_data[] = { 1, 2, 1, 0 };
	int num_elements = 4;

	// INITIALIZE
	Stack<int> intStack(4);
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
	Stack<string> stringStack(4);
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

bool Test_PopOnZeroSize()
{
	bool pass = false;

	// INITIALIZE
	Stack<int> intStack;

	try
	{
		intStack.Pop();
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_PopOnZeroSize ";

	return pass;
}

bool Test_PopOnZeroSizeComplex()
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

	cout << "Test_PopOnZeroSizeComplex ";

	return pass;
}

bool Test_PopOnEmpty()
{
	bool pass = false;

	// INITIALIZE
	Stack<int> intStack(5);

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
	Stack<string> stringStack(5);

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
	Stack<int> intStack(5);
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
	Stack<string> stringStack(5);
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

bool Test_SetSizeOnEmpty()
{
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack;

	intStack.setSize(2);

	// intStack = 0/2 elements
	if (intStack.getNumElements() != 0 || intStack.getSize() != 2)
		pass = false;

	cout << "Test_SetSizeOnEmpty ";

	return pass;
}

bool Test_SetSizeOnEmptyComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack;

	stringStack.setSize(2);

	// stringStack = 0/2 elements
	if (stringStack.getNumElements() != 0 || stringStack.getSize() != 2)
		pass = false;

	cout << "Test_SetSizeOnEmptyComplex ";

	return pass;
}

bool Test_SetSizeOnFullDecrease()
{
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack(3);
	intStack.Push(3);
	intStack.Push(2);
	intStack.Push(1);

	// intStack { 3, 2, 1 } -> { 3, 2 }
	intStack.setSize(2);
	
	if (intStack.getNumElements() != 2 || intStack.getSize() != 2)
		pass = false;
	if (intStack.Peek() != 2)
		pass = false;

	cout << "Test_SetSizeOnFullDecrease ";

	return pass;
}

bool Test_SetSizeOnFullDecreaseComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack(3);
	stringStack.Push("Monster");
	stringStack.Push("Hunter");
	stringStack.Push("Wilds");

	// stringStack { "Monster", "Hunter", "Wilds" } -> { "Monster", "Hunter" }
	stringStack.setSize(2);

	if (stringStack.getNumElements() != 2 || stringStack.getSize() != 2)
		pass = false;
	if (stringStack.Peek() != "Hunter")
		pass = false;

	cout << "Test_SetSizeOnFullDecreaseComplex ";

	return pass;
}

bool Test_SetSizeOnFullIncrease()
{
	bool pass = true;

	// INITIALIZE
	Stack<int> intStack(2);
	intStack.Push(1);
	intStack.Push(2);

	// intStack { 1, 2 } -> { 1, 2, T{} }
	intStack.setSize(3);

	// intStack = 2/3 elements
	if (intStack.getNumElements() != 2 || intStack.getSize() != 3)
		pass = false;
	if (intStack.Peek() != 2)
		pass = false;

	cout << "Test_SetSizeOnFullIncrease ";

	return pass;
}

bool Test_SetSizeOnFullIncreaseComplex()
{
	bool pass = true;

	// INITIALIZE
	Stack<string> stringStack(2);
	stringStack.Push("Solid");
	stringStack.Push("Snake");

	// intStack { "Solid", "Snake" } -> { "Solid", "Snake", T{} }
	stringStack.setSize(3);

	// intStack = 2/3 elements
	if (stringStack.getNumElements() != 2 || stringStack.getSize() != 3)
		pass = false;
	if (stringStack.Peek() != "Snake")
		pass = false;

	cout << "Test_SetSizeOnFullIncreaseComplex ";

	return pass;
}

bool Test_SetSizeNegativeLength()
{
	bool pass = false;

	// INITIALIZE
	Stack<int> intStack;

	try
	{
		intStack.setSize(-5);
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_SetSizeNegativeLength ";

	return pass;
}

bool Test_SetSizeNegativeLengthComplex()
{
	bool pass = false;

	// INITIALIZE
	Stack<string> stringStack;

	try
	{
		stringStack.setSize(-5);
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_SetSizeNegativeLengthComplex ";

	return pass;
}
