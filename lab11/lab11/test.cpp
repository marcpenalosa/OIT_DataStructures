/**********************************************************************************
* Author:			Marc Penalosa
* Filename:			test.cpp
* Date Created:		2/02/26
* Date Modified:	2/10/26
*						- Added tests to delete single node trees
*					2/16/26
*						- Modified to be used for AVL Trees
**********************************************************************************/
/**********************************************************************************
*
* Lab Assignment: Lab 11 - AVL Tree
*
* Overview:
*		This program tests an AVL Tree class's ctors and methods
*
* Input:
*		None
*
* Output:
*		Print strings on the console window that depends on whether or not
*		each tests passed
**********************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "bsTree.h"
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
bool Test_OpEqualMove();
bool Test_OpEqualMoveComplex();

// Class Methods
bool Test_Insert();
bool Test_InsertComplex();
bool Test_Delete();
bool Test_DeleteComplex();
bool Test_DeleteSingle();
bool Test_DeleteSingleComplex();
bool Test_DeleteOnEmpty();
bool Test_DeleteOnEmptyComplex();
bool Test_DeleteOnTargetNotFound();
bool Test_DeleteOnTargetNotFoundComplex();
bool Test_Purge();
bool Test_PurgeComplex();
bool Test_Height();
bool Test_HeightComplex();
bool Test_InOrder();
bool Test_InOrderComplex();
bool Test_PreOrder();
bool Test_PreOrderComplex();
bool Test_PostOrder();
bool Test_PostOrderComplex();
bool Test_BreadthFirst();
bool Test_BreadthFirstComplex();

// AVL Balancing Tests
bool Test_LLRotation();
bool Test_LLRotationComplex();
bool Test_RRRotation();
bool Test_RRRotationComplex();
bool Test_LRRotation();
bool Test_LRRotationComplex();
bool Test_RLRotation();
bool Test_RLRotationComplex();
bool Test_DeleteSingleRotation();
bool Test_DeleteSingleRotationComplex();
bool Test_DeleteDoubleRotation();
bool Test_DeleteDoubleRotationComplex();

FunctionPointer test_functions[] = { Test_DefaultCtor, Test_DefaultCtorComplex, Test_CopyCtor, Test_CopyCtorComplex, Test_MoveCtor, Test_MoveCtorComplex,
Test_OpEqual, Test_OpEqualComplex, Test_OpEqualMove, Test_OpEqualMoveComplex, Test_Insert, Test_InsertComplex, Test_Delete, Test_DeleteComplex, Test_DeleteSingle,
Test_DeleteSingleComplex, Test_DeleteOnEmpty, Test_DeleteOnEmptyComplex, Test_DeleteOnTargetNotFound, Test_DeleteOnTargetNotFoundComplex, Test_Purge, Test_PurgeComplex,
Test_Height, Test_HeightComplex, Test_InOrder, Test_InOrderComplex, Test_PreOrder, Test_PreOrderComplex, Test_PostOrder, Test_PostOrderComplex,
Test_BreadthFirst, Test_BreadthFirstComplex, Test_LLRotation, Test_LLRotationComplex, Test_RRRotation, Test_RRRotationComplex, Test_LRRotation, Test_LRRotationComplex,
Test_RLRotation, Test_RLRotationComplex, Test_DeleteSingleRotation, Test_DeleteSingleRotationComplex, Test_DeleteDoubleRotation, Test_DeleteDoubleRotationComplex };

// visit functions and variables for testing integrity
void StoreInt(int data);
void StoreString(string data);
Queue<int> globalIntQueue;
Queue<string> globalStringQueue;

const int INT_DATA[] = { 50, 30, 70, 20, 40, 60, 80, 65, 75 };
const char* STRING_DATA[] = { "ea", "ca", "ga", "ba", "da", "fa", "ha", "fb", "gb" };
const int NUM_DATA = 9;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << "********************************************************************************" << endl;
	cout << "THIS IS MY BINARY SEARCH TREE'S TEST BUT ADDED THE BALANCING TESTS AT THE BOTTOM" << endl;
	cout << "********************************************************************************" << endl;

	for (FunctionPointer func : test_functions)
	{
		if (func())
			cout << "passed" << endl;
		else
			cout << "***** FAILED *****" << endl;
	}

	return 0;
}

void StoreInt(int data)
{
	globalIntQueue.Enqueue(data);
}

void StoreString(string data)
{
	globalStringQueue.Enqueue(data);
}

bool Test_DefaultCtor()
{
	cout << "***** CLASS CTORS *****" << endl;
	bool pass = true;

	BSTree<int> intTree;

	if (intTree.Height() != -1)
		pass = false;

	cout << "Test_DefaultCtor ";

	return pass;
}

bool Test_DefaultCtorComplex()
{
	bool pass = true;

	BSTree<string> stringTree;

	if (stringTree.Height() != -1)
		pass = false;

	cout << "Test_DefaultCtorComplex ";

	return pass;
}

bool Test_CopyCtor()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}
	intTree.BreadthFirst(StoreInt);
	// Transfer the global data stored in a queue into a local queue for comparison. Then reset global queue
	Queue<int> originalData = globalIntQueue;
	globalIntQueue = Queue<int>();

	// Copy tree
	BSTree<int> intTreeCopy(intTree);

	// Check integrity
	intTreeCopy.BreadthFirst(StoreInt);
	while (!globalIntQueue.isEmpty())
	{
		if (originalData.Dequeue() != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_CopyCtor ";

	return pass;
}

bool Test_CopyCtorComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}
	stringTree.BreadthFirst(StoreString);
	// Transfer the global data stored in a queue into a local queue for comparison. Then reset global queue
	Queue<string> originalData = globalStringQueue;
	globalIntQueue = Queue<int>();

	// Copy tree
	BSTree<string> stringTreeCopy(stringTree);

	// Check integrity
	stringTreeCopy.BreadthFirst(StoreString);
	while (!globalIntQueue.isEmpty())
	{
		if (originalData.Dequeue() != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_CopyCtorComplex ";

	return pass;
}

bool Test_MoveCtor()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	// Move tree
	BSTree<int> intTreeCopy(std::move(intTree));

	// Check integrity
	intTreeCopy.BreadthFirst(StoreInt);
	for (int i = 0; i < NUM_DATA; i++)
	{
		if (INT_DATA[i] != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_MoveCtor ";

	return pass;
}

bool Test_MoveCtorComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	// Move tree
	BSTree<string> stringTreeCopy(std::move(stringTree));

	// Check integrity
	stringTreeCopy.BreadthFirst(StoreString);
	for (int i = 0; i < NUM_DATA; i++)
	{
		if (STRING_DATA[i] != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_MoveCtorComplex ";

	return pass;
}

bool Test_OpEqual()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}
	intTree.BreadthFirst(StoreInt);
	// Transfer the global data stored in a queue into a local queue for comparison. Then reset global queue
	Queue<int> originalData = globalIntQueue;
	globalIntQueue = Queue<int>();

	// Copy assign tree
	BSTree<int> intTreeCopy = intTree;

	// Check integrity
	intTreeCopy.BreadthFirst(StoreInt);
	while (!globalIntQueue.isEmpty())
	{
		if (originalData.Dequeue() != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_OpEqual ";

	return pass;
}

bool Test_OpEqualComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}
	stringTree.BreadthFirst(StoreString);
	// Transfer the global data stored in a queue into a local queue for comparison. Then reset global queue
	Queue<string> originalData = globalStringQueue;
	globalStringQueue = Queue<string>();

	// Copy assign sstree
	BSTree<string> stringTreeCopy(stringTree);

	// Check integrity
	stringTreeCopy.BreadthFirst(StoreString);
	while (!globalStringQueue.isEmpty())
	{
		if (originalData.Dequeue() != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_OpEqualComplex ";

	return pass;
}

bool Test_OpEqualMove()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	// Move assign tree
	BSTree<int> intTreeCopy = std::move(intTree);

	// Check integrity
	intTreeCopy.BreadthFirst(StoreInt);
	for (int i = 0; i < NUM_DATA; i++)
	{
		if (INT_DATA[i] != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_OpEqualMove ";

	return pass;
}

bool Test_OpEqualMoveComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	// Move assign tree
	BSTree<string> stringTreeCopy = std::move(stringTree);

	// Check integrity
	stringTreeCopy.BreadthFirst(StoreString);
	for (int i = 0; i < NUM_DATA; i++)
	{
		if (STRING_DATA[i] != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_MoveCtorComplex ";

	return pass;
}

bool Test_Insert()
{
	cout << endl << "***** CLASS METHODS *****" << endl;
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}
	intTree.BreadthFirst(StoreInt);

	// Check integrity
	for (int i = 0; i < NUM_DATA; i++)
	{
		if (INT_DATA[i] != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_Insert ";

	return pass;
}

bool Test_InsertComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}
	stringTree.BreadthFirst(StoreString);

	// Check integrity
	for (int i = 0; i < NUM_DATA; i++)
	{
		if (STRING_DATA[i] != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_InsertComplex ";

	return pass;
}

bool Test_Delete()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	// Delete leaf
	intTree.Delete(20);
	// Delete node with left empty | right data
	intTree.Delete(60);
	// Delete node with left data | right empty
	intTree.Delete(80);
	// Delete node with left and right data
	intTree.Delete(70);

	intTree.BreadthFirst(StoreInt);
	// Tree BreadthFirst structure should be like this
	int test_data[] = { 50, 30, 65, 40, 75 };
	int num_data = 5;

	// Check integrity
	for (int i = 0; i < 5; i++)
	{
		if (test_data[i] != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_Delete ";

	return pass;
}

bool Test_DeleteComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	// Delete leaf
	stringTree.Delete("ba");
	// Delete node with left empty | right data
	stringTree.Delete("fa");
	// Delete node with left data | right empty
	stringTree.Delete("ha");
	// Delete node with left and right data
	stringTree.Delete("ga");

	stringTree.BreadthFirst(StoreString);
	// Tree BreadthFirst structure should be like this
	const char* test_data[] = { "ea", "ca", "fb", "da", "gb" };
	int num_data = 5;

	// Check integrity
	for (int i = 0; i < 5; i++)
	{
		if (test_data[i] != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_DeleteComplex ";

	return pass;
}

bool Test_DeleteSingle()
{
	bool pass = false;

	BSTree<int> intTree;
	intTree.Insert(50);
	intTree.Delete(50);

	try
	{
		intTree.BreadthFirst(StoreInt);
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_DeleteSingle ";

	return pass;
}

bool Test_DeleteSingleComplex()
{
	bool pass = false;

	BSTree<string> stringTree;
	stringTree.Insert("a");
	stringTree.Delete("a");

	try
	{
		stringTree.BreadthFirst(StoreString);
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_DeleteSingleComplex ";

	return pass;
}

bool Test_DeleteOnEmpty()
{
	bool pass = false;

	BSTree<int> intTree;

	try
	{
		intTree.Delete(5);
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_DeleteOnEmpty ";

	return pass;
}

bool Test_DeleteOnEmptyComplex()
{
	bool pass = false;

	BSTree<string> stringTree;

	try
	{
		stringTree.Delete("a");
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_DeleteOnEmptyComplex ";

	return pass;
}

bool Test_DeleteOnTargetNotFound()
{
	bool pass = false;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	try
	{
		intTree.Delete(1000);
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_DeleteOnTargetNotFound ";

	return pass;
}

bool Test_DeleteOnTargetNotFoundComplex()
{
	bool pass = false;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	try
	{
		stringTree.Delete("a");
	}
	catch (Exception& exception)
	{
		pass = true;
	}

	cout << "Test_DeleteOnTargetNotFoundComplex ";

	return pass;
}

bool Test_Purge()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	intTree.Purge();

	// Tree should be empty
	if (intTree.Height() != -1)
		pass = false;

	cout << "Test_Purge ";

	return pass;
}

bool Test_PurgeComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	stringTree.Purge();

	// Tree should be empty
	if (stringTree.Height() != -1)
		pass = false;

	cout << "Test_PurgeComplex ";

	return pass;
}

bool Test_Height()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	// Populate height of 0
	BSTree<int> intTree2;
	intTree2.Insert(1);

	// Height of -1 (empty)
	BSTree<int> intTree3;

	if (intTree.Height() != 3)
		pass = false;
	if (intTree2.Height() != 0)
		pass = false;
	if (intTree3.Height() != -1)
		pass = false;

	cout << "Test_Height ";

	return pass;
}

bool Test_HeightComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	// Populate height of 0
	BSTree<string> stringTree2;
	stringTree2.Insert("a");

	// Height of -1 (empty)
	BSTree<string> stringTree3;

	if (stringTree.Height() != 3)
		pass = false;
	if (stringTree2.Height() != 0)
		pass = false;
	if (stringTree3.Height() != -1)
		pass = false;

	cout << "Test_HeightComplex ";

	return pass;
}

bool Test_InOrder()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	// Store data to a queue InOrder
	intTree.InOrder(StoreInt);

	// InOrder should give the queue this pattern
	int test_data[] = { 20, 30, 40, 50, 60, 65, 70, 75, 80 };

	for (int i = 0; i < NUM_DATA; i++)
	{
		if (test_data[i] != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_InOrder ";

	return pass;
}

bool Test_InOrderComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	// Store data to a queue InOrder
	stringTree.InOrder(StoreString);

	// InOrder should give the queue this pattern
	string test_data[] = { "ba", "ca", "da", "ea", "fa", "fb", "ga", "gb", "ha" };

	for (int i = 0; i < NUM_DATA; i++)
	{
		if (test_data[i] != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_InOrderComplex ";

	return pass;
}

bool Test_PreOrder()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	// Store data to a queue PreOrder
	intTree.PreOrder(StoreInt);

	// PreOrder should give the queue this pattern
	int test_data[] = { 50, 30, 20, 40, 70, 60, 65, 80, 75 };

	for (int i = 0; i < NUM_DATA; i++)
	{
		if (test_data[i] != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_PreOrder ";

	return pass;
}

bool Test_PreOrderComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	// Store data to a queue PreOrder
	stringTree.PreOrder(StoreString);

	// PreOrder should give the queue this pattern
	string test_data[] = { "ea", "ca", "ba", "da", "ga", "fa", "fb", "ha", "gb" };

	for (int i = 0; i < NUM_DATA; i++)
	{
		if (test_data[i] != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_PreOrderComplex ";

	return pass;
}

bool Test_PostOrder()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	// Store data to a queue PostOrder
	intTree.PostOrder(StoreInt);

	// PostOrder should give the queue this pattern
	int test_data[] = { 20, 40, 30, 65, 60, 75, 80, 70, 50 };

	for (int i = 0; i < NUM_DATA; i++)
	{
		if (test_data[i] != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_PostOrder ";

	return pass;
}

bool Test_PostOrderComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	// Store data to a queue PostOrder
	stringTree.PostOrder(StoreString);

	// PostOrder should give the queue this pattern
	string test_data[] = { "ba", "da", "ca", "fb", "fa", "gb", "ha", "ga", "ea" };

	for (int i = 0; i < NUM_DATA; i++)
	{
		if (test_data[i] != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_PostOrderComplex ";

	return pass;
}

bool Test_BreadthFirst()
{
	bool pass = true;

	// Populate tree
	BSTree<int> intTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		intTree.Insert(INT_DATA[i]);
	}

	// Store data to a queue BreadthFirst
	intTree.BreadthFirst(StoreInt);

	// BreadthFirst should give the queue this pattern
	int test_data[] = { 50, 30, 70, 20, 40, 60, 80, 65, 75 };

	for (int i = 0; i < NUM_DATA; i++)
	{
		if (test_data[i] != globalIntQueue.Dequeue())
			pass = false;
	}

	cout << "Test_BreadthFirst ";

	return pass;
}

bool Test_BreadthFirstComplex()
{
	bool pass = true;

	// Populate tree
	BSTree<string> stringTree;
	for (int i = 0; i < NUM_DATA; i++)
	{
		stringTree.Insert(STRING_DATA[i]);
	}

	// Store data to a queue BreadthFirst
	stringTree.BreadthFirst(StoreString);

	// BreadthFirst should give the queue this pattern
	string test_data[] = { "ea", "ca", "ga", "ba", "da", "fa", "ha", "fb", "gb" };

	for (int i = 0; i < NUM_DATA; i++)
	{
		if (test_data[i] != globalStringQueue.Dequeue())
			pass = false;
	}

	cout << "Test_BreadthFirstComplex ";

	return pass;
}

bool Test_LLRotation()
{
	cout << endl << "***** AVL BALANCING TESTS *****" << endl;
	bool pass = true;

	BSTree<int> intTree;
	intTree.Insert(30);
	intTree.Insert(20);
	intTree.Insert(10);	// Left child's left subtree

	intTree.BreadthFirst(StoreInt);

	int expected_data[] = { 20, 10, 30 };

	for (int i = 0; i < 3; i++)
	{
		if (globalIntQueue.Dequeue() != expected_data[i])
			pass = false;
	}

	cout << "Test_LLRotation ";

	return pass;
}

bool Test_LLRotationComplex()
{
	bool pass = true;

	BSTree<string> stringTree;
	stringTree.Insert("c");
	stringTree.Insert("b");
	stringTree.Insert("a");	// Left child's left subtree

	stringTree.BreadthFirst(StoreString);

	string expected_data[] = { "b", "a", "c" };

	for (int i = 0; i < 3; i++)
	{
		if (globalStringQueue.Dequeue() != expected_data[i])
			pass = false;
	}

	cout << "Test_LLRotationComplex ";

	return pass;
}

bool Test_RRRotation()
{
	bool pass = true;

	BSTree<int> intTree;
	intTree.Insert(10);
	intTree.Insert(20);
	intTree.Insert(30);	// Right child's right subtree

	intTree.BreadthFirst(StoreInt);

	int expected_data[] = { 20, 10, 30 };

	for (int i = 0; i < 3; i++)
	{
		if (globalIntQueue.Dequeue() != expected_data[i])
			pass = false;
	}

	cout << "Test_RRRotation ";

	return pass;
}

bool Test_RRRotationComplex()
{
	bool pass = true;

	BSTree<string> stringTree;
	stringTree.Insert("a");
	stringTree.Insert("b");
	stringTree.Insert("c");	// Right child's right subtree

	stringTree.BreadthFirst(StoreString);

	string expected_data[] = { "b", "a", "c" };

	for (int i = 0; i < 3; i++)
	{
		if (globalStringQueue.Dequeue() != expected_data[i])
			pass = false;
	}

	cout << "Test_RRRotationComplex ";

	return pass;
}

bool Test_LRRotation()
{
	bool pass = true;

	BSTree<int> intTree;
	intTree.Insert(30);
	intTree.Insert(10);
	intTree.Insert(20);

	intTree.BreadthFirst(StoreInt);

	int expected_data[] = { 20, 10, 30 };

	for (int i = 0; i < 3; i++)
	{
		if (globalIntQueue.Dequeue() != expected_data[i])
			pass = false;
	}

	cout << "Test_LRRotation ";

	return pass;
}

bool Test_LRRotationComplex()
{
	bool pass = true;

	BSTree<string> stringTree;
	stringTree.Insert("c");
	stringTree.Insert("a");
	stringTree.Insert("b");

	stringTree.BreadthFirst(StoreString);

	string expected_data[] = { "b", "a", "c" };

	for (int i = 0; i < 3; i++)
	{
		if (globalStringQueue.Dequeue() != expected_data[i])
			pass = false;
	}

	cout << "Test_LRRotationComplex ";

	return pass;
}

bool Test_RLRotation()
{
	bool pass = true;

	BSTree<int> intTree;
	intTree.Insert(10);
	intTree.Insert(30);
	intTree.Insert(20);

	intTree.BreadthFirst(StoreInt);

	int expected_data[] = { 20, 10, 30 };

	for (int i = 0; i < 3; i++)
	{
		if (globalIntQueue.Dequeue() != expected_data[i])
			pass = false;
	}

	cout << "Test_RLRotation ";

	return pass;
}

bool Test_RLRotationComplex()
{
	bool pass = true;

	BSTree<string> stringTree;
	stringTree.Insert("a");
	stringTree.Insert("c");
	stringTree.Insert("b");

	stringTree.BreadthFirst(StoreString);

	string expected_data[] = { "b", "a", "c" };

	for (int i = 0; i < 3; i++)
	{
		if (globalStringQueue.Dequeue() != expected_data[i])
			pass = false;
	}

	cout << "Test_LRRotationComplex ";

	return pass;
}

bool Test_DeleteSingleRotation()
{
	bool pass = true;

	// Left side balance
	BSTree<int> intTree1;

	intTree1.Insert(30);
	intTree1.Insert(20);
	intTree1.Insert(40);
	intTree1.Insert(10);
	intTree1.Delete(40);
	intTree1.BreadthFirst(StoreInt);

	int expected_data1[] = { 20, 10, 30 };

	for (int i = 0; i < 3; i++)
	{
		if (globalIntQueue.Dequeue() != expected_data1[i])
			pass = false;
	}

	// Right side balance
	BSTree<int> intTree2;

	intTree2.Insert(20);
	intTree2.Insert(10);
	intTree2.Insert(30);
	intTree2.Insert(40);
	intTree2.Delete(10);
	intTree2.BreadthFirst(StoreInt);

	int expected_data2[] = { 30, 20, 40 };

	for (int i = 0; i < 3; i++)
	{
		if (globalIntQueue.Dequeue() != expected_data2[i])
			pass = false;
	}

	cout << "Test_DeleteSingleRotation ";

	return pass;
}

bool Test_DeleteSingleRotationComplex()
{
	bool pass = true;

	// Left side balance
	BSTree<string> stringTree1;

	stringTree1.Insert("c");
	stringTree1.Insert("b");
	stringTree1.Insert("d");
	stringTree1.Insert("a");
	stringTree1.Delete("d");
	stringTree1.BreadthFirst(StoreString);

	string expected_data1[] = { "b", "a", "c" };

	for (int i = 0; i < 3; i++)
	{
		if (globalStringQueue.Dequeue() != expected_data1[i])
			pass = false;
	}

	// Right side balance
	BSTree<string> stringTree2;

	stringTree2.Insert("b");
	stringTree2.Insert("a");
	stringTree2.Insert("c");
	stringTree2.Insert("d");
	stringTree2.Delete("a");
	stringTree2.BreadthFirst(StoreString);

	string expected_data2[] = { "c", "b", "d" };

	for (int i = 0; i < 3; i++)
	{
		if (globalStringQueue.Dequeue() != expected_data2[i])
			pass = false;
	}

	cout << "Test_DeleteSingleRotationComplex ";

	return pass;
}

bool Test_DeleteDoubleRotation()
{
	bool pass = true;

	// Left side balance
	BSTree<int> intTree1;

	intTree1.Insert(50);
	intTree1.Insert(30);
	intTree1.Insert(70);
	intTree1.Insert(20);
	intTree1.Insert(40);
	intTree1.Insert(35);
	intTree1.Delete(70);
	intTree1.BreadthFirst(StoreInt);

	int expected_data1[] = { 40, 30, 50, 20, 35 };

	for (int i = 0; i < 5; i++)
	{
		if (globalIntQueue.Dequeue() != expected_data1[i])
			pass = false;
	}

	// Right side balance
	BSTree<int> intTree2;

	intTree2.Insert(30);
	intTree2.Insert(10);
	intTree2.Insert(50);
	intTree2.Insert(40);
	intTree2.Insert(60);
	intTree2.Insert(45);
	intTree2.Delete(10);
	intTree2.BreadthFirst(StoreInt);

	int expected_data2[] = { 40, 30, 50, 45, 60 };

	for (int i = 0; i < 5; i++)
	{
		if (globalIntQueue.Dequeue() != expected_data2[i])
			pass = false;
	}

	// Added this just to make sure about something :)
	BSTree<int> intTree3;

	intTree3.Insert(2);
	intTree3.Insert(5);
	intTree3.Insert(8);
	intTree3.Insert(9);
	intTree3.Insert(10);
	intTree3.Insert(15);
	intTree3.Insert(11);
	intTree3.Insert(20);
	intTree3.Delete(5);
	intTree3.Delete(2);
	intTree3.BreadthFirst(StoreInt);

	int expected_data3[] = { 11, 9, 15, 8, 10, 20 };

	for (int i = 0; i < 6; i++)
	{
		if (globalIntQueue.Dequeue() != expected_data3[i])
			pass = false;
	}

	cout << "Test_DeleteDoubleRotation ";

	return pass;
}

bool Test_DeleteDoubleRotationComplex()
{
	bool pass = true;

	// Left side balance
	BSTree<string> stringTree1;

	stringTree1.Insert("e");
	stringTree1.Insert("c");
	stringTree1.Insert("g");
	stringTree1.Insert("b");
	stringTree1.Insert("d");
	stringTree1.Insert("ca");
	stringTree1.Delete("g");
	stringTree1.BreadthFirst(StoreString);

	string expected_data1[] = { "d", "c", "e", "b", "ca" };

	for (int i = 0; i < 5; i++)
	{
		if (globalStringQueue.Dequeue() != expected_data1[i])
			pass = false;
	}

	// Right side balance
	BSTree<string> stringTree2;

	stringTree2.Insert("c");
	stringTree2.Insert("a");
	stringTree2.Insert("e");
	stringTree2.Insert("d");
	stringTree2.Insert("f");
	stringTree2.Insert("da");
	stringTree2.Delete("a");
	stringTree2.BreadthFirst(StoreString);

	string expected_data2[] = { "d", "c", "e", "da", "f" };

	for (int i = 0; i < 5; i++)
	{
		if (globalStringQueue.Dequeue() != expected_data2[i])
			pass = false;
	}

	cout << "Test_DeleteDoubleRotationComplex ";

	return pass;
}
