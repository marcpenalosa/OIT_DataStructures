/******************************************************
* Author:		Marc Penalosa
* Filename:		vectorSorts.h
* Date Created:	3/10/26
******************************************************/
#ifndef VECTOR_SORTS_H
#define VECTOR_SORTS_H

#include <vector>
using std::vector;

namespace VectorSort
{
	void BruteForceBubble(vector<int>& array);
	void FlaggedBubble(vector<int>& array);
	void Selection(vector<int>& array);
	void Insertion(vector<int>& array);
	void Shell(vector<int>& array);
	void Heap(vector<int>& array);
	void MoveDown(vector<int>& array, int first, int last);
	void Merge(vector<int>& array);
	void Merge(vector<int>& array, vector<int>& temp, int left, int right);
	void Merge(vector<int>& array, vector<int>& temp, int left, int right, int rightEnd);
	void QuickSort(vector<int>& array);
	void QuickSort(vector<int>& array, int first, int last);
}

#endif // !VECTOR_SORTS_H
