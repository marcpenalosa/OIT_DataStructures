/******************************************************
* Author:		Marc Penalosa
* Filename:		myArraySorts.h
* Date Created:	3/10/26
******************************************************/
#ifndef MY_ARRAY_SORTS_H
#define MY_ARRAY_SORTS_H

#include "array.h"

namespace MyArray
{
	void BruteForceBubble(Array<int>& array);
	void FlaggedBubble(Array<int>& array);
	void Selection(Array<int>& array);
	void Insertion(Array<int>& array);
	void Shell(Array<int>& array);
	void Heap(Array<int>& array);
	void MoveDown(Array<int>& array, int first, int last);
	void Merge(Array<int>& array);
	void Merge(Array<int>& array, Array<int>& temp, int left, int right);
	void Merge(Array<int>& array, Array<int>& temp, int left, int right, int rightEnd);
	void QuickSort(Array<int>& array);
	void QuickSort(Array<int>& array, int first, int last);
}

#endif // !MY_ARRAY_SORTS_H
