#include "myArraySorts.h"

void MyArray::BruteForceBubble(Array<int>& array)
{
	// the amount of passes we need
	for (int i = array.getLength(); i > 0; i--)
	{
		// loop through all the index, one less for every pass
		for (int j = 0; j < i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

void MyArray::FlaggedBubble(Array<int>& array)
{
	bool sorted = false;
	// the amount of passes we need
	for (int i = array.getLength(); i > 0 && !sorted; i--)
	{
		sorted = true;
		// loop through all the index, one less for every pass
		for (int j = 0; j < i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				sorted = false;
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

void MyArray::Selection(Array<int>& array)
{
	int n = array.getLength();
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		// iterate through everything to find the minimum
		// increase left-most index to the right by one every pass
		for (int j = i + 1; j < n; j++)
		{
			if (array[j] < array[min])
				min = j;
		}
		// then place it at the front
		int temp = array[i];
		array[i] = array[min];
		array[min] = temp;
	}
}

void MyArray::Insertion(Array<int>& array)
{
	int j = 0;
	int temp = 0;

	for (int i = 1; i < array.getLength(); i++)
	{
		temp = array[i];
		for (j = i; j > 0 && temp < array[j - 1]; j--)
		{
			array[j] = array[j - 1];
		}
		array[j] = temp;
	}
}

void MyArray::Shell(Array<int>& array)
{
	for (int gap = array.getLength() / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < array.getLength(); i++)
		{
			// current element to compare and place correctly
			int temp = array[i];
			int j = 0;

			// stores the left element to the right element if it's bigger
			// skips if left element is smaller than the stored temp (right element)
			for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
				array[j] = array[j - gap];

			// stores the bigger element to the right, does nothing if it already is
			array[j] = temp;
		}
	}
}

void MyArray::Heap(Array<int>& array)
{
	// build heap
	// start from the midpoint
	for (int i = array.getLength() / 2 - 1; i >= 0; i--)
	{
		MoveDown(array, i, array.getLength() - 1);
	}

	// sort heap
	for (int i = array.getLength() - 1; i > 0; i--)
	{
		// swap root that has the largest element, with the last element
		int temp = array[0];
		array[0] = array[i];
		array[i] = temp;

		// restore heap
		MoveDown(array, 0, i - 1);
	}
}

void MyArray::MoveDown(Array<int>& array, int first, int last)
{
	int largest = first * 2 + 1; // starts as the left child of the parent

	while (largest <= last)
	{
		// if largest is less than last
		// AND if the left child is less than the right child
		// then go to the right child because it's the bigger element so manipulate
		if (largest < last && array[largest] < array[largest + 1])
			largest++;

		// if parent is smaller than the largest child
		if (array[first] < array[largest])
		{
			// swap parent and child
			int temp = array[first];
			array[first] = array[largest];
			array[largest] = temp;

			// move the first pointer to largest child
			// then recalculate largest to point to the new left child
			first = largest;
			largest = first * 2 + 1;
		}
		else
			largest = last + 1;	// forces the loop to end
	}
}

void MyArray::Merge(Array<int>& array)
{
	Array<int> temp(array.getLength());
	Merge(array, temp, 0, array.getLength() - 1);
}

void MyArray::Merge(Array<int>& array, Array<int>& temp, int left, int right)
{
	// check to see if there is one lement in subarray
	if (left < right)
	{
		int mid = (left + right) / 2;
		Merge(array, temp, left, mid); // left half
		Merge(array, temp, mid + 1, right); // right half
		Merge(array, temp, left, mid + 1, right);	// Merge 2 halves
	}
}

void MyArray::Merge(Array<int>& array, Array<int>& temp, int left, int right, int rightEnd)
{
	int start = left;
	int leftEnd = right - 1;
	int tempPos = left;
	int numElements = rightEnd - left + 1;

	// until we reach the end of one of the arrays
	while (left <= leftEnd && right <= rightEnd)
	{
		if (array[left] <= array[right])
		{
			temp[tempPos] = array[left];
			tempPos++;
			left++;
		}
		else
		{
			temp[tempPos] = array[right];
			tempPos++;
			right++;
		}
	}

	// copy the rest of the left array into the temp array
	while (left <= leftEnd)
	{
		temp[tempPos] = array[left];
		tempPos++;
		left++;
	}

	// copy the rest of the right array into the temp array
	while (right <= rightEnd)
	{
		temp[tempPos] = array[right];
		tempPos++;
		right++;
	}

	// copy the temp array over the top of the original array
	for (int i = start; i <= rightEnd; i++)
	{
		array[i] = temp[i];
	}
}

void MyArray::QuickSort(Array<int>& array)
{
	// finds the largest element of the array and places it at the end of the array
	int max = 0;

	if (array.getLength() >= 2)
	{
		for (int i = 1; i < array.getLength(); i++)
		{
			if (array[max] < array[i])
				max = i;
		}
		// swap
		int temp = array[array.getLength() - 1];
		array[array.getLength() - 1] = array[max];
		array[max] = temp;

		QuickSort(array, 0, array.getLength() - 2);
	}
}

void MyArray::QuickSort(Array<int>& array, int first, int last)
{
	// initialize index
	int small = first + 1;
	int large = last;
	int pivot = array[first];

	while (small <= large)
	{
		while (array[small] < pivot)
			small++;
		while (array[large] > pivot)
			large--;

		if (small < large)
		{
			// swap (array[small++], array(large--)
			int temp = array[small];
			array[small] = array[large];
			array[large] = temp;
			small++;
			large--;
		}
		else
			small++;
	}

	//swap (array[large], array[first])
	int temp = array[large];
	array[large] = array[first];
	array[first] = temp;

	if (first < large - 1)
		QuickSort(array, first, large - 1); // sort left
	if (last > large + 1)
		QuickSort(array, large + 1, last); // sort right
}
