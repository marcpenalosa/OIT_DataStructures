/*********************************************
* Author:		Marc Penalosa
* Filename:		test.cpp
* Date Created:	2/17/26
*********************************************/
/**********************************************************************************
*
* Lab Assignment: Lab 12 - Hash Table
*
* Overview:
*		This program tests a Hash Table class's ctors and methods using a struct
*
* Input:
*		None
*
* Output:
*		Print strings on the console window that depends on whether or not
*		each tests passed
*		Displays contents of a Hash Table of Book
**********************************************************************************/

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <list>
using std::list;
using std::pair;
#include <queue>
using std::queue;
#include "hashTable.h"

struct Book
{
	string m_title;
	string m_author;
	int m_pages = 0;
};

Book book1 = { "C++: Learn by Doing", "Todd Breedlove, Troy Scevers, et. al", 635 };
Book book2 = { "How to Bark Like a Dog", "Marc Penalosa", 1 };
Book book3 = { "How to Tweet Like a Bird", "Marc Penalosa", 1 };
Book book4 = { "How to Glub Like a Fish", "Marc Penalosa", 3 };
Book book5 = { "How to Hiss Like a Snake", "Marc Penalosa", 1 };
Book book6 = { "Connor's Guide to Professional Clowning", "Connor Metalgear", 540 };
Book book7 = { "Scotts's Guide to Professional Clowning", "Scott Eldenring", 541 };
const Book BOOK_LIST[] = { book1, book2, book3, book4, book5, book6, book7 };
const string BOOK_ISBN[] = { "1234512345", "4140972546", "6274618939", "1588822345", "9320478174", "7738663634", "8373627813" };

// A HashTable with 5 elements using AsciiHash should Traverse like this
const string AsciiKeyOrder[] = { "1234512345", "6274618939", "9320478174", "1588822345", "4140972546", "7738663634", "8373627813" };
const Book AsciiBookOrder[] = { book1, book3, book5, book4, book2, book6, book7 };
// A HashTable with 5 elements using StoiLast3Hash should Traverse like this
const string StoiKeyOrder[] = { "1234512345", "1588822345", "4140972546", "8373627813", "6274618939", "9320478174", "7738663634" };
const Book StoiBookOrder[] = { book1, book4, book2, book7, book3, book5, book6 };

queue<string> stringQueue;
queue<Book> bookQueue;

int AsciiHash(string input);
int StoiLast3Hash(string input);
void Display(int value);
void Display(Book book);
void StoreString(string input);
void StoreBook(Book book);

typedef bool (*FunctionPointer)();
// Class Ctors
bool Test_DefaultCtor();
bool Test_ArgCtor();
bool Test_CopyCtor();
bool Test_MoveCtor();
bool Test_OpCopy();
bool Test_OpMove();

// Class Methods
bool Test_setHash();
bool Test_setHashRehash();
bool Test_Insert();
bool Test_InsertZeroSize();
bool Test_InsertNullHash();
bool Test_OpSubscript();
bool Test_OpSubscriptSizeZero();
bool Test_OpSubscriptInvalidKey();
bool Test_Delete();	// also try catches an exception trying to access the key again
bool Test_Traverse();

void TraverseDisplay();

FunctionPointer test_functions[] = { Test_DefaultCtor, Test_ArgCtor, Test_CopyCtor, Test_MoveCtor, Test_OpCopy,
Test_OpMove, Test_setHash, Test_setHashRehash, Test_Insert, Test_InsertZeroSize, Test_InsertNullHash, Test_OpSubscript,
Test_OpSubscriptSizeZero, Test_OpSubscriptInvalidKey, Test_Delete, Test_Traverse };

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

	TraverseDisplay();

	return 0;
}

int AsciiHash(string input)
{
	int result = 0;
	for (int i = 0; i < input.size(); i++)
		result += char(input[i]);
	return result;
}

int StoiLast3Hash(string input)
{
	// string substr (size_t pos = 0, size_t len = npos) const;
	// first parameter is the index, second parameter is how many characters including the index
	return std::stoi(input.substr(input.length() - 3, 3));
}

void Display(int value)
{
	cout << "Num Pages: " << value << endl;
}

void Display(Book book)
{
	cout << "Title: " << book.m_title << endl;
	cout << "Author: " << book.m_author << endl;
	cout << "Num Pages: " << book.m_pages << endl << endl;
}

void StoreString(string input)
{
	stringQueue.push(input);
}

void StoreBook(Book book)
{
	bookQueue.push(book);
}

bool Test_DefaultCtor()
{
	cout << "***** CLASS CTORS *****" << endl;
	bool pass = true;
	HashTable<string, Book> table;

	if (table.getSize() != 0)
		pass = false;

	cout << "Test_DefaultCtor ";

	return pass;
}

bool Test_ArgCtor()
{
	bool pass = true;
	HashTable<string, Book> table(10);

	if (table.getSize() != 10)
		pass = false;

	cout << "Test_ArgCtor ";

	return pass;
}

bool Test_CopyCtor()
{
	bool pass = true;
	HashTable<string, Book> table(10);
	HashTable<string, Book> tableCopy(table);

	if (tableCopy.getSize() != 10)
		pass = false;

	cout << "Test_CopyCtor ";

	return pass;
}

bool Test_MoveCtor()
{
	bool pass = true;
	HashTable<string, Book> table(10);
	HashTable<string, Book> tableCopy(std::move(table));

	if (tableCopy.getSize() != 10)
		pass = false;

	cout << "Test_MoveCtor ";

	return pass;
}

bool Test_OpCopy()
{
	bool pass = true;
	HashTable<string, Book> table(10);
	HashTable<string, Book> tableCopy = table;

	if (tableCopy.getSize() != 10)
		pass = false;

	cout << "Test_OpCopy ";

	return pass;
}

bool Test_OpMove()
{
	bool pass = true;
	HashTable<string, Book> table(10);
	HashTable<string, Book> tableCopy = std::move(table);

	if (tableCopy.getSize() != 10)
		pass = false;

	cout << "Test_OpMove ";

	return pass;
}

bool Test_setHash()
{
	cout << endl << "***** CLASS METHODS *****" << endl;
	bool pass = true;

	HashTable<string, Book> table(5);

	table.setHash(AsciiHash);
	table.Insert("1234512345", book1);

	Book bookResult = table["1234512345"];
	if (bookResult.m_author != book1.m_author)
		pass = false;
	if (bookResult.m_title != book1.m_title)
		pass = false;
	if (bookResult.m_pages != book1.m_pages)
		pass = false;

	cout << "Test_setHash ";

	return pass;
}

bool Test_setHashRehash()
{
	bool pass = true;

	HashTable<string, Book> table(5);
	Book temp;

	table.setHash(AsciiHash);
	for (int i = 0; i < 7; i++)
	{
		table.Insert(BOOK_ISBN[i], BOOK_LIST[i]);
	}
	table.setHash(StoiLast3Hash);
	table.Traverse(StoreBook);

	// the order should follow StoiBookOrder structure
	for (int i = 0; i < 7; i++)
	{
		temp = bookQueue.front();
		if (temp.m_title != StoiBookOrder[i].m_title)
			pass = false;
		if (temp.m_author != StoiBookOrder[i].m_author)
			pass = false;
		if (temp.m_pages != StoiBookOrder[i].m_pages)
			pass = false;
		bookQueue.pop();
	}

	cout << "Test_setHashRehash ";

	return pass;
}

bool Test_Insert()
{
	bool pass = true;

	HashTable<string, Book> table(5, AsciiHash);
	for (int i = 0; i < 7; i++)
		table.Insert(BOOK_ISBN[i], BOOK_LIST[i]);
	Book temp;
	table.Traverse(StoreBook);

	for (int i = 0; i < 7; i++)
	{
		temp = bookQueue.front();
		if (temp.m_title != AsciiBookOrder[i].m_title)
			pass = false;
		if (temp.m_author != AsciiBookOrder[i].m_author)
			pass = false;
		if (temp.m_pages != AsciiBookOrder[i].m_pages)
			pass = false;
		bookQueue.pop();
	}

	cout << "Test_Insert ";

	return pass;
}

bool Test_InsertZeroSize()
{
	bool pass = false;

	HashTable<string, Book> table;

	try
	{
		table.Insert("10", book1);
	}
	catch (Exception)
	{
		pass = true;
	}

	cout << "Test_InsertZeroSize ";

	return pass;
}

bool Test_InsertNullHash()
{
	bool pass = false;

	HashTable<string, Book> table(5);

	try
	{
		table.Insert("10", book1);
	}
	catch (Exception)
	{
		pass = true;
	}

	cout << "Test_InsertNullHash ";

	return pass;
}

bool Test_OpSubscript()
{
	bool pass = true;
	
	HashTable<string, Book> table(5, AsciiHash);
	for (int i = 0; i < 7; i++)
		table.Insert(BOOK_ISBN[i], BOOK_LIST[i]);
	Book temp;
	string isbn;

	for (int i = 0; i < 7; i++)
	{
		isbn = BOOK_ISBN[i];
		temp = table[isbn];
		if (temp.m_title != BOOK_LIST[i].m_title)
			pass = false;
		if (temp.m_author != BOOK_LIST[i].m_author)
			pass = false;
		if (temp.m_pages != BOOK_LIST[i].m_pages)
			pass = false;
	}

	cout << "Test_OpSubscript ";

	return pass;
}

bool Test_OpSubscriptSizeZero()
{
	bool pass = false;

	HashTable<string, Book> table;

	try
	{
		table["10"];
	}
	catch (Exception)
	{
		pass = true;
	}

	cout << "Test_OpSubscriptSizeZero ";

	return pass;
}

bool Test_OpSubscriptInvalidKey()
{
	bool pass = false;

	HashTable<string, Book> table(5, AsciiHash);
	table.Insert("1234512345", book1);

	try
	{
		table["10"];
	}
	catch (Exception)
	{
		pass = true;
	}

	cout << "Test_OpSubscriptInvalidKey ";

	return pass;
}

bool Test_Delete()
{
	bool pass = true;
	bool exceptionPass = false;

	HashTable<string, Book> table(5, AsciiHash);
	for (int i = 0; i < 7; i++)
		table.Insert(BOOK_ISBN[i], BOOK_LIST[i]);
	Book temp;
	string isbn;

	table.Delete("9320478174");

	// Delete book5 isbn
	// Traverse should now look like this
	string NewAsciiKeyOrder[] = { "1234512345", "6274618939", "1588822345", "4140972546", "7738663634", "8373627813" };
	Book NewAsciiBookOrder[] = { book1, book3, book4, book2, book6, book7 };

	// check that data is kept
	for (int i = 0; i < 6; i++)
	{
		isbn = NewAsciiKeyOrder[i];
		temp = table[isbn];
		if (temp.m_title != NewAsciiBookOrder[i].m_title)
			pass = false;
		if (temp.m_author != NewAsciiBookOrder[i].m_author)
			pass = false;
		if (temp.m_pages != NewAsciiBookOrder[i].m_pages)
			pass = false;
	}

	// check that this key is removed
	try
	{
		table["9320478174"];
	}
	catch (Exception)
	{
		exceptionPass = true;
	}

	cout << "Test_Delete ";

	return pass && exceptionPass;
}

bool Test_Traverse()
{
	bool pass = true;

	HashTable<string, Book> table(5, AsciiHash);
	for (int i = 0; i < 7; i++)
	{
		table.Insert(BOOK_ISBN[i], BOOK_LIST[i]);
	}

	table.Traverse(StoreBook);

	// table should follow AsciiBookOrder structure
	for (int i = 0; i < 7; i++)
	{
		if (bookQueue.front().m_title != AsciiBookOrder[i].m_title)
			pass = false;
		if (bookQueue.front().m_author != AsciiBookOrder[i].m_author)
			pass = false;
		if (bookQueue.front().m_pages != AsciiBookOrder[i].m_pages)
			pass = false;
		bookQueue.pop();
	}

	cout << "Test_Traverse ";

	return pass;
}

void TraverseDisplay()
{
	cout << endl;
	cout << "*********************************************" << endl;
	cout << "**************DISPLAY OF BOOKS***************" << endl;
	cout << "*********************************************" << endl;

	HashTable<string, Book> table(5, StoiLast3Hash);
	for (int i = 0; i < 7; i++)
	{
		table.Insert(BOOK_ISBN[i], BOOK_LIST[i]);
	}

	table.Traverse(Display);
}
