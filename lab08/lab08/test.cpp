/*******************************************
* Author:			Marc Penalosa
* Filename:			test.cpp
* Date Created:		1/27/26
*******************************************/
/*******************************************
*
* Lab Assignment: Lab 8 - Linked List Based Queue
*
* Overview:
*		This program tests a Queue class's ctors and methods
*
* Input:
*		None
*
* Output:
*		Print strings on the console window that depends on whether
*		or not the tests passed
*******************************************/

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "queue.h"

typedef bool(*FunctionPointer)();

// Class Ctors
bool Test_DefaultCtor();
bool Test_DefaultCtorComplex();
bool Test_CopyCtor();
bool Test_CopyCtorComplex();
bool Test_MoveCtor();
bool Test_MoveCtorComplex();
bool Test_OpEqual();
bool Test_OpEqualComplex();
bool Test_MoveEqual();
bool Test_MoveEqualComplex();

// Class Methods
bool Test_GetNumElements();
bool Test_GetNumElementsComplex();
bool Test_IsEmpty();
bool Test_IsEmptyComplex();
bool Test_EnqueueAndDequeue();
bool Test_EnqueueAndDequeueComplex();
bool Test_DequeueOnEmpty();
bool Test_DequeueOnEmptyComplex();
bool Test_Peek();
bool Test_PeekComplex();
bool Test_PeekOnEmpty();
bool Test_PeekOnEmptyComplex();

FunctionPointer test_functions[] = { Test_DefaultCtor, Test_DefaultCtorComplex, Test_CopyCtor,
Test_CopyCtorComplex, Test_MoveCtor, Test_MoveCtorComplex, Test_OpEqual, Test_OpEqualComplex, Test_MoveEqual, Test_MoveEqualComplex,
Test_GetNumElements, Test_GetNumElementsComplex, Test_IsEmpty, Test_IsEmptyComplex, Test_EnqueueAndDequeue, Test_EnqueueAndDequeueComplex, 
Test_DequeueOnEmpty, Test_DequeueOnEmptyComplex, Test_Peek, Test_PeekComplex, Test_PeekOnEmpty, Test_PeekOnEmptyComplex };

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	for (FunctionPointer func : test_functions)
	{
		if (func())
			cout << "passed" << endl;
		else
			cout << "***** FAILED *****" << endl;
	}

	return 0;
}

bool Test_DefaultCtor()
{
	cout << "***** CLASS CTORS *****" << endl;
	bool pass = true;

	Queue<int> intQueue;

	// intQueue should be empty
	if (intQueue.getNumElements() != 0)
		pass = false;

	cout << "Test_DefaultCtor ";

	return pass;
}

bool Test_DefaultCtorComplex()
{
	bool pass = true;

	Queue<string> stringQueue;

	// stringQueue should be empty
	if (stringQueue.getNumElements() != 0)
		pass = false;

	cout << "Test_DefaultCtorComplex ";

	return pass;
}

bool Test_CopyCtor()
{
	bool pass = true;

	Queue<int> intQueue1;
	intQueue1.Enqueue(2);
	Queue<int> intQueue2(intQueue1);

	// intQueue2 should have the value 2 and have 1 element
	if (intQueue2.Peek() != 2 || intQueue2.getNumElements() != 1)
		pass = false;

	cout << "Test_CopyCtor ";

	return pass;
}

bool Test_CopyCtorComplex()
{
	bool pass = true;

	Queue<string> stringQueue1;
	stringQueue1.Enqueue("Barc");
	Queue<string> stringQueue2(stringQueue1);

	// stringQueue2 should have "Barc" and have 1 element
	if (stringQueue2.Peek() != "Barc" || stringQueue2.getNumElements() != 1)
		pass = false;

	cout << "Test_CopyCtorComplex ";

	return pass;
}

bool Test_MoveCtor()
{
	bool pass = true;

	Queue<int> intQueue1;
	intQueue1.Enqueue(2);
	Queue<int> intQueue2(std::move(intQueue1));

	// intQueue2 should have the value 2 and have 1 element
	if (intQueue2.Peek() != 2 || intQueue2.getNumElements() != 1)
		pass = false;

	cout << "Test_MoveCtor ";

	return pass;
}

bool Test_MoveCtorComplex()
{
	bool pass = true;

	Queue<string> stringQueue1;
	stringQueue1.Enqueue("Barc");
	Queue<string> stringQueue2(std::move(stringQueue1));

	// stringQueue2 should have "Barc" and have 1 element
	if (stringQueue2.Peek() != "Barc" || stringQueue2.getNumElements() != 1)
		pass = false;

	cout << "Test_MoveCtorComplex ";

	return pass;
}

bool Test_OpEqual()
{
	bool pass = true;

	Queue<int> intQueue1;
	intQueue1.Enqueue(2);
	Queue<int> intQueue2 = intQueue1;

	// intQueue1 should have the value 2 and have 1 element
	if (intQueue1.Peek() != 2 || intQueue1.getNumElements() != 1)
		pass = false;

	// intQueue2 should have the value 2 and have 1 element
	if (intQueue2.Peek() != 2 || intQueue2.getNumElements() != 1)
		pass = false;

	cout << "Test_OpEqual ";

	return pass;
}

bool Test_OpEqualComplex()
{
	bool pass = true;

	Queue<string> stringQueue1;
	stringQueue1.Enqueue("Barc");
	Queue<string> stringQueue2 = stringQueue1;

	// stringQueue1 should have "Barc" and have 1 element
	if (stringQueue1.Peek() != "Barc" || stringQueue2.getNumElements() != 1)
		pass = false;

	// stringQueue2 should have "Barc" and have 1 element
	if (stringQueue2.Peek() != "Barc" || stringQueue2.getNumElements() != 1)
		pass = false;

	cout << "Test_OpEqualComplex ";

	return pass;
}

bool Test_MoveEqual()
{
	bool pass = true;

	Queue<int> intQueue1;
	intQueue1.Enqueue(2);
	Queue<int> intQueue2 = std::move(intQueue1);

	// intQueue2 should have the value 2 and have 1 element
	if (intQueue2.Peek() != 2 || intQueue2.getNumElements() != 1)
		pass = false;

	cout << "Test_MoveEqual ";

	return pass;
}

bool Test_MoveEqualComplex()
{
	bool pass = true;

	Queue<string> stringQueue1;
	stringQueue1.Enqueue("Barc");
	Queue<string> stringQueue2 = std::move(stringQueue1);

	// stringQueue2 should have "Barc" and have 1 element
	if (stringQueue2.Peek() != "Barc" || stringQueue2.getNumElements() != 1)
		pass = false;

	cout << "Test_MoveEqualComplex ";

	return pass;
}

bool Test_GetNumElements()
{
	cout << endl << "***** CLASS METHODS *****" << endl;
	bool pass = true;

	Queue<int> intQueue1;
	Queue<int> intQueue2;
	intQueue2.Enqueue(1);
	intQueue2.Enqueue(1);

	// intQueue1 should have 0 elements
	if (intQueue1.getNumElements() != 0)
		pass = false;

	// intQueue2 should have 2 elements
	if (intQueue2.getNumElements() != 2)
		pass = false;

	cout << "Test_GetNumElements ";

	return pass;
}

bool Test_GetNumElementsComplex()
{
	bool pass = true;

	Queue<string> stringQueue1;
	Queue<string> stringQueue2;
	stringQueue2.Enqueue("Barc");
	stringQueue2.Enqueue("Barc");

	// stringQueue1 should have 0 elements
	if (stringQueue1.getNumElements() != 0)
		pass = false;

	// stringQueue2 should have 0 elements
	if (stringQueue2.getNumElements() != 2)
		pass = false;

	cout << "Test_GetNumElementsComplex ";

	return pass;
}

bool Test_IsEmpty()
{
	bool pass = true;

	Queue<int> intQueue1;
	Queue<int> intQueue2;
	intQueue2.Enqueue(1);
	intQueue2.Enqueue(1);

	// intQueue1 should have 0 elements
	if (!intQueue1.isEmpty())
		pass = false;

	// intQueue2 should have 2 elements
	if (intQueue2.isEmpty())
		pass = false;

	cout << "Test_IsEmpty ";

	return pass;
}

bool Test_IsEmptyComplex()
{
	bool pass = true;

	Queue<string> stringQueue1;
	Queue<string> stringQueue2;
	stringQueue2.Enqueue("Barc");
	stringQueue2.Enqueue("Barc");

	// stringQueue1 should have 0 elements
	if (!stringQueue1.isEmpty())
		pass = false;

	// stringQueue2 should have 0 elements
	if (stringQueue2.isEmpty())
		pass = false;

	cout << "Test_IsEmptyComplex ";

	return pass;
}

bool Test_EnqueueAndDequeue()
{
	bool pass = true;
	int test_data[] = { 5, 2, 1, 2 };

	Queue<int> intQueue;
	intQueue.Enqueue(5);
	intQueue.Enqueue(2);
	intQueue.Enqueue(1);
	intQueue.Enqueue(2);

	// intQueue should have { 5, 2, 1, 2 }
	if (intQueue.getNumElements() != 4)
		pass = false;

	for (int i = 0; i < 4; i++)
	{
		if (intQueue.Dequeue() != test_data[i])
			pass = false;
	}
	
	cout << "Test_EnqueueAndDequeue ";

	return pass;
}

bool Test_EnqueueAndDequeueComplex()
{
	bool pass = true;
	const char* test_data[] = { "Marc", "Barc", "Shark", "Barc" };

	Queue<string> stringQueue;
	stringQueue.Enqueue("Marc");
	stringQueue.Enqueue("Barc");
	stringQueue.Enqueue("Shark");
	stringQueue.Enqueue("Barc");

	// stringQueue should have { "Marc", "Barc", "Shark", "Barc" }
	if (stringQueue.getNumElements() != 4)
		pass = false;

	for (int i = 0; i < 4; i++)
	{
		if (stringQueue.Dequeue() != test_data[i])
			pass = false;
	}

	cout << "Test_EnqueueAndDequeueComplex ";

	return pass;
}

bool Test_DequeueOnEmpty()
{
	bool pass = false;

	Queue<int> intQueue;

	try
	{
		intQueue.Dequeue();
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_DequeueOnEmpty ";

	return pass;
}

bool Test_DequeueOnEmptyComplex()
{
	bool pass = false;

	Queue<string> stringQueue;

	try
	{
		stringQueue.Dequeue();
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_DequeueOnEmptyComplex ";

	return pass;
}

bool Test_Peek()
{
	bool pass = true;

	Queue<int> intQueue;
	intQueue.Enqueue(0);
	intQueue.Enqueue(1);

	// intQueue Peek should look at the first element
	if (intQueue.Peek() != 0)
		pass = false;

	// and should not have dequeued it
	if (intQueue.getNumElements() != 2)
		pass = false;

	cout << "Test_Peek ";

	return pass;
}

bool Test_PeekComplex()
{
	bool pass = true;

	Queue<string> stringQueue;
	stringQueue.Enqueue("Shark");
	stringQueue.Enqueue("Snake");

	// stringQueue Peek should look at the first element
	if (stringQueue.Peek() != "Shark")
		pass = false;

	// and should not have dequeued it
	if (stringQueue.getNumElements() != 2)
		pass = false;

	cout << "Test_PeekComplex ";

	return pass;
}

bool Test_PeekOnEmpty()
{
	bool pass = false;

	Queue<int> intQueue;

	try
	{
		intQueue.Peek();
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

	Queue<int> stringQueue;

	try
	{
		stringQueue.Peek();
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_PeekOnEmptyComplex ";

	return pass;
}
