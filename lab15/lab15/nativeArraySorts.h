/******************************************************
* Author:		Marc Penalosa
* Filename:		nativeArraySorts.h
* Date Created:	3/10/26
******************************************************/
#ifndef NATIVE_ARRAY_SORTS_H
#define NATIVE_ARRAY_SORTS_H

namespace NativeSort
{
	void BruteForceBubble(int* array, int size);
	void FlaggedBubble(int* array, int size);
	void Selection(int* array, int size);
	void Insertion(int* array, int size);
	void Shell(int* array, int size);
	void Heap(int* array, int size);
	void MoveDown(int* array, int first, int last);
	void Merge(int* array, int size);
	void Merge(int* array, int* temp, int left, int right);
	void Merge(int* array, int* temp, int left, int right, int rightEnd);
	void QuickSort(int* array, int size);
	void QuickSort(int* array, int first, int last);
}

#endif // !NATIVE_ARRAY_SORTS_H