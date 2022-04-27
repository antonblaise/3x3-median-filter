//========================================================================
// Main 3x3 Median Filter program for High-Level Synthesis (Vivado HLS)
//========================================================================

#include <iostream>
#include <cstdlib>

using namespace std;

//void swap(int *xp, int *yp)
//{
//    int temp = *xp;
//    *xp = *yp;
//    *yp = temp;
//}

void selectionSort(int inputArray[], int arraySize)
{

#pragma HLS pipeline II=1 enable_flush rewind

    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < arraySize-1; i++)
    {
#pragma HLS unroll
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < arraySize; j++) {
#pragma HLS unroll
        	if (inputArray[j] < inputArray[min_idx]) {
        		min_idx = j;
        	}
        }

        // Swap the found minimum element with the first element
        swap(inputArray[min_idx], inputArray[i]);
    }
}

void bubbleSort (int inputArray[], int arraySize)
{

#pragma HLS pipeline II=1 enable_flush rewind

	int i, j;

	for (i = 0; i < arraySize - 1; i++ ){
#pragma HLS unroll
		for (j = 0; j < arraySize - i - 1; j++) {
#pragma HLS unroll
			if (inputArray[j] > inputArray[j + 1]) {
				swap(inputArray[j], inputArray[j + 1]);
			}
		}
	}
}

void insertionSort (int inputArray[], int arraySize)
{

#pragma HLS pipeline II=1 enable_flush rewind

	int i, j, key;

	for (i = 1; i < arraySize; i++) {

#pragma HLS unroll
		key = inputArray[i];
		j = i - 1;

		while (j >= 0 && inputArray[j] > key) {
#pragma HLS unroll
			inputArray[j + 1] = inputArray[j];
			j = j - 1;
		}

	inputArray[j + 1] = key;

	}
}

// Top function
void median_filter(int window[9], int &median){

#pragma HLS pipeline II=1 enable_flush rewind

	//sort window array (pick any sorting algorithm above)
//	insertionSort(window, 9);
	bubbleSort(window, 9);
//	selectionSort(window, 9);
	median = window[4];

}

