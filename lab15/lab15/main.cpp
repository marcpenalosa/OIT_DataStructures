/******************************************************
* Author:		Marc Penalosa
* Filename:		main.cpp
* Date Created:	3/10/26
******************************************************/
/**********************************************************************************
*
* Lab Assignment: Lab 15 - Sorts
*
* Overview:
*		This program performs a series of sorting algorithms on the same randomized data.
*		It records their sort duration and outputs it into a file.
*
* Input:
*		none
*
* Output:
*		Prints the sorts and their sort duration on the console.
*		Outputs the same information into a file ("results.txt")
**********************************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::stoi;
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
#include <fstream>
using std::ofstream;

#include "nativeArraySorts.h"
#include "vectorSorts.h"
#include "myArraySorts.h"

typedef void(*NativeSorts)(int* array, int size);
typedef void(*VectorSorts)(vector<int>& array);
typedef void(*MyArraySorts)(Array<int>& array);

NativeSorts nativeSorts[] = { NativeSort::BruteForceBubble, NativeSort::FlaggedBubble, NativeSort::Selection,
NativeSort::Insertion, NativeSort::Shell, NativeSort::Heap, NativeSort::Merge, NativeSort::QuickSort };

VectorSorts vectorSorts[] = { VectorSort::BruteForceBubble, VectorSort::FlaggedBubble, VectorSort::Selection,
VectorSort::Insertion, VectorSort::Shell, VectorSort::Heap, VectorSort::Merge, VectorSort::QuickSort };

MyArraySorts myArraySorts[] = { MyArray::BruteForceBubble, MyArray::FlaggedBubble, MyArray::Selection,
MyArray::Insertion, MyArray::Shell, MyArray::Heap, MyArray::Merge, MyArray::QuickSort };

void ResetData(int* data, vector<int>& vData, Array<int>& mData, int* originalData, int size);
void timer(int* array, int size, vector<int>& vArray, Array<int>& mArray, ofstream& fout, string sort,
	NativeSorts nativeSort, VectorSorts vectorSort, MyArraySorts myArray);

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (argc < 2)
	{
		cout << "Missing command line arg" << endl;
	}

	int n = stoi(argv[1]);
	string sorts[] = {"Brute Force Bubble", "Flagged Bubble", "Selection", "Insertion", "Shell", "Heap",
	"Merge", "Quick Sort" };

	// randomize original data array
	srand(time(0));
	int* originalData = new int[n];
	for (int i = 0; i < n; i++)
	{
		originalData[i] = rand() % 1000;
	}

	// open output file
	ofstream file("results.txt");

	// initialize arrays
	int* data = new int[n];
	vector<int> vData;
	Array<int> mData(n);
	ResetData(data, vData, mData, originalData, n);

	for (int i = 0; i < 8; i++)
	{
		timer(data, n, vData, mData, file, sorts[i], nativeSorts[i], vectorSorts[i], myArraySorts[i]);
		ResetData(data, vData, mData, originalData, n);
	}

	// randomize original efficient data array
	int efficientN = 80000;
	int* originalEfficientData = new int[efficientN];
	for (int i = 0; i < efficientN; i++)
	{
		originalEfficientData[i] = rand() % 1000;
	}

	int* efficientData = new int[efficientN];
	vector<int> vEfficientData;
	Array<int> mEfficientData(efficientN);
	ResetData(efficientData, vEfficientData, mEfficientData, originalEfficientData, efficientN);

	cout << "***************************************************" << endl;
	cout << "EFFICIENT SORTS" << endl;
	cout << "***************************************************" << endl;
	file << "***************************************************" << endl;
	file << "EFFICIENT SORTS" << endl;
	file << "***************************************************" << endl;
	for (int i = 4; i < 8; i++)
	{
		timer(efficientData, efficientN, vEfficientData, mEfficientData, file, sorts[i], nativeSorts[i], vectorSorts[i], myArraySorts[i]);
		ResetData(efficientData, vEfficientData, mEfficientData, originalEfficientData, efficientN);
	}

	delete[] originalData;
	delete[] data;
	delete[] originalEfficientData;
	delete[] efficientData;
	return 0;
}

void ResetData(int* data, vector<int>& vData, Array<int>& mData, int* originalData, int size)
{
	for (int i = 0; i < size; i++)
	{
		data[i] = originalData[i];
	}

	vData.clear();
	for (int i = 0; i < size; i++)
	{
		vData.push_back(originalData[i]);
	}

	for (int i = 0; i < size; i++)
	{
		mData[i] = originalData[i];
	}
}

void timer(int* array, int size, vector<int>& vArray, Array<int>& mArray, ofstream& fout, string sort, NativeSorts nativeSort, VectorSorts vectorSort, MyArraySorts myArray)
{
	auto start = high_resolution_clock::now();
	nativeSort(array, size);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<std::chrono::milliseconds>(end - start);
	cout << "**********" << endl;
	fout << "**********" << endl;
	cout << "Native Array " << sort << endl;
	fout << "Native Array " << sort << endl;
	cout << "Sort Duration: " << duration.count() << " ms" << endl;
	fout << "Sort Duration: " << duration.count() << " ms" << endl;
	for (int i = 0; i < size; i += 1000)
	{
		fout << array[i] << " ";
	}
	cout << endl << endl;
	fout << endl << endl;

	start = high_resolution_clock::now();
	vectorSort(vArray);
	end = high_resolution_clock::now();
	duration = duration_cast<std::chrono::milliseconds>(end - start);
	cout << "**********" << endl;
	fout << "**********" << endl;
	cout << "Vector " << sort << endl;
	fout << "Vector " << sort << endl;
	cout << "Sort Duration: " << duration.count() << " ms" << endl;
	fout << "Sort Duration: " << duration.count() << " ms" << endl;
	for (int i = 0; i < size; i += 1000)
	{
		fout << vArray[i] << " ";
	}
	cout << endl << endl;
	fout << endl << endl;

	start = high_resolution_clock::now();
	myArray(mArray);
	end = high_resolution_clock::now();
	duration = duration_cast<std::chrono::milliseconds>(end - start);
	cout << "**********" << endl;
	fout << "**********" << endl;
	cout << "My Array " << sort << endl;
	fout << "My Array " << sort << endl;
	cout << "Sort Duration: " << duration.count() << " ms" << endl;
	fout << "Sort Duration: " << duration.count() << " ms" << endl;
	for (int i = 0; i < size; i += 1000)
	{
		fout << mArray[i] << " ";
	}
	cout << endl << endl;
	fout << endl << endl;
}
