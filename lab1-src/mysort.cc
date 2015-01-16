#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static void insertionSort(int, int, void*, void*, int, CompareFunction);
static void swap(void*, void*, int);

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	insertionSort(n, elementSize, array, array + (n-1)* elementSize, ascending, compFunc);
}

void insertionSort(int n, int elementSize, void* start, void* end, int ascending, 
	CompareFunction comp) {
	for (void* i = end - elementSize; i >= start; i -= elementSize) {
		for (void* j = i; j < end; j += elementSize) {
			int comparison = comp(j, j + elementSize);
			comparison = ascending ? comparison : comparison * -1;

			if (comparison > 0)
				swap(j, j + elementSize, elementSize);
			else
				break;
		}
	}
}

void swap(void* first, void* second, int elementSize) {
	void* temp = malloc(elementSize);
	temp = memcpy(temp, first, elementSize);
	memcpy(first, second, elementSize);
	memcpy(second, temp, elementSize);
	free(temp);
}

