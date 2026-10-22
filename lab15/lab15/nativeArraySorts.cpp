#include "nativeArraySorts.h"

void NativeSort::BruteForceBubble(int* array, int size)
{
	for (int i = size; i > 0; i--)
	{
		for (int j = 0; j < i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				// swap
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

void NativeSort::FlaggedBubble(int* array, int size)
{
	bool sorted = false;
	for (int i = size; i > 0 && !sorted; i--)
	{
		sorted = true;
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

void NativeSort::Selection(int* array, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		// iterate through everything to find the minimum
		// increase left-most index to the right by one every pass
		for (int j = i + 1; j < size; j++)
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

void NativeSort::Insertion(int* array, int size)
{
	int j = 0;
	int temp = 0;

	for (int i = 1; i < size; i++)
	{
		temp = array[i];
		for (j = i; j > 0 && temp < array[j - 1]; j--)
		{
			array[j] = array[j - 1];
		}
		array[j] = temp;
	}
}

void NativeSort::Shell(int* array, int size)
{
	for (int gap = size/2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < size; i++)
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

void NativeSort::Heap(int* array, int size)
{
	// build heap
	// start from the midpoint
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		MoveDown(array, i, size - 1);
	}

	// sort heap
	for (int i = size - 1; i > 0; i--)
	{
		// swap root that has the largest element, with the last element
		int temp = array[0];
		array[0] = array[i];
		array[i] = temp;

		// restore heap
		MoveDown(array, 0, i - 1);
	}
}

void NativeSort::MoveDown(int* array, int first, int last)
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

void NativeSort::Merge(int* array, int size)
{
	int* temp = new int[size];
	Merge(array, temp, 0, size - 1);
	delete[] temp;
}

void NativeSort::Merge(int* array, int* temp, int left, int right)
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

void NativeSort::Merge(int* array, int* temp, int left, int right, int rightEnd)
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

void NativeSort::QuickSort(int* array, int size)
{
	// finds the largest element of the array and places it at the end of the array
	int max = 0;

	if (size >= 2)
	{
		for (int i = 1; i < size; i++)
		{
			if (array[max] < array[i])
				max = i;
		}
		// swap
		int temp = array[size - 1];
		array[size - 1] = array[max];
		array[max] = temp;

		QuickSort(array, 0, size - 2);
	}
}

void NativeSort::QuickSort(int* array, int first, int last)
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
		QuickSort(array, large +1, last); // sort right
}
