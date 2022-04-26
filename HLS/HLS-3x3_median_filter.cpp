//========================================================================
// Main 3x3 Median Filter program for High-Level Synthesis (Vivado HLS)
//========================================================================

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

void bubbleSort (int inputArray[], int arraySize)
{
	int i, j;

	for (i = 0; i < arraySize - 1; i++ ){
		for (j = 0; j < arraySize - i - 1; j++) {
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

	key = inputArray[i];
	j = i - 1;

	while (j >= 0 && inputArray[j] > key) {
		inputArray[j + 1] = inputArray[j];
		j = j - 1;
	}

	inputArray[j + 1] = key;

	}
}

void median_filter(){
    
	cout << ">> Reading data..." << endl;
	FILE *fin, *fdim, *fout;
    
	// store image dimensions as dim
	int dim[2];
	fdim=fopen("dimension.dat","r");
	fscanf(fdim, "%d", &dim[0]);
	fscanf(fdim, "%d", &dim[1]);
	fclose(fdim);

	// declare width and height
	int width = dim[0], height = dim[1], row, col, pixel_pointer=0;

	cout << ">> Allocating memory..." << endl;
	// store input.dat as vec
    int *vec = (int*) malloc(width*height * sizeof(int)); // Dynamically allocated (width x height) empty matrix space
    
	fin=fopen("input.dat","r");
	for (int i = 0; i < width*height; i++) {
		fscanf(fin, "%d", &vec[i]);
	}
	fclose(fin);

	// declare storage to store image data (not working directly on image data in vec, 
	// allowing the choise of whether to use preprocessing such as padding)
	int N = 2000;
    int *img_array = (int *)malloc(N * N * sizeof(int)); // Dynamically allocated (2000x2000) empty matrix space

	cout << ">> Preprocessing data..." << endl;

	// set all elements = 0
	for (row = 0; row < N; row++){
		for (col = 0; col < N; col++){
			img_array[row*N + col] = 0; // equivalent to img_array[row, col]
		}
	}

	// store pixel data into img_array matrix
	// // // With zero padding
	// for (row = 1; row < height-1; row++){
	//   for (col = 1; col < width-1; col++){
	//     img_array[row*N + col] = vec[pixel_pointer];
	//     pixel_pointer++;
	//   }
	// }

	// // No padding
	for (row = 0; row < height; row++){
		for (col = 0; col < width; col++){
			img_array[row*N + col] = vec[pixel_pointer];
			pixel_pointer++;
		}
	}

	// 3x3 median filter main algorithm

	// int window[9];
    int *window = (int*)malloc(9 * sizeof(int));
	cout << ">> Performing 3x3 median filter, please wait..." << endl;

	fout=fopen("out.dat","w");

	for(row = 1; row <= height; row++)
	{
		for(col = 1; col <= width; col++)
		{
			// Window = 3x3 matrix, centered at (row,col)
			window[0] = img_array[(row-1)*N + (col-1)];
			window[1] = img_array[(row-1)*N + (col)];
			window[2] = img_array[(row-1)*N + (col+1)];
			window[3] = img_array[(row*N) + (col-1)];
			window[4] = img_array[(row*N) + (col)];
			window[5] = img_array[(row*N) + (col+1)];
			window[6] = img_array[(row+1)*N + (col-1)];
			window[7] = img_array[(row+1)*N + (col)];
			window[8] = img_array[(row+1)*N + (col+1)];

			//sort window array (pick any sorting algorithm above)
			insertionSort(window, 9);
			fprintf(fout,"%d\n",window[4]);
		}
	}
	fclose(fout);

    free(img_array);
    free(vec);
    free(window);

	cout << ">> Saved processed output pixels as out.dat." << endl;
    
}

