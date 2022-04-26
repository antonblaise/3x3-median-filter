//========================================================================
// Main 3x3 Median Filter program for High-Level Synthesis (Vivado HLS)
//========================================================================

#include <iostream>
#include <cstdlib>

using namespace std;

void bubbleSort (int inputArray[], int arraySize)
{

	int i, j;

	for (i = 0; i < arraySize - 1; i++ ){
#pragma HLS unroll factor 9
		for (j = 0; j < arraySize - i - 1; j++) {
#pragma HLS unroll factor 4
			if (inputArray[j] > inputArray[j + 1]) {
				swap(inputArray[j], inputArray[j + 1]);
			}
		}
	}
}

void insertionSort (int inputArray[], int arraySize)
{
	int i, j, key;

	for (i = 1; i < arraySize; i++) {
#pragma HLS unroll factor 9
	key = inputArray[i];
	j = i - 1;

	while (j >= 0 && inputArray[j] > key) {
#pragma HLS unroll factor 4
		inputArray[j + 1] = inputArray[j];
		j = j - 1;
	}

	inputArray[j + 1] = key;

	}
}

// Top function
void median_filter(int window[9], int &median){

	//sort window array (pick any sorting algorithm above)
	insertionSort(window, 9);
	median = window[4];

}

