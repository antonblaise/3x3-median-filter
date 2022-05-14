#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>

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

int main(){
    
	cout << ">> Reading data..." << endl;
	FILE *fin, *fdim, *fout, *fout_m, *ftime, *fspeed;
    
	// store image dimensions as dim
	int dim[2];
	fdim=fopen("./data/dimension.dat","r");
	fscanf(fdim, "%d", &dim[0]);
	fscanf(fdim, "%d", &dim[1]);
	fclose(fdim);

	// declare width and height
	int width = dim[0], height = dim[1], row, col, pixel_pointer=0;

	cout << ">> Allocating memory..." << endl;
	// store input.dat as vec
    int *vec = (int*) malloc(width*height * sizeof(int)); // Dynamically allocated (width x height) empty matrix space
    
	fin=fopen("./data/input.dat","r");
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
	double t, speed, sum_t=0, sum_speed=0;

	cout << ">> Performing 3x3 median filter, please wait..." << endl;

	fout=fopen("./data/out.gold.dat","w");
    fout_m=fopen("./data/out.m.dat","w");
	ftime=fopen("./data/time_ns.dat","w");
	fspeed=fopen("./data/speed_ns.dat","w");

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
			auto start = chrono::steady_clock::now(); // Start timer
			insertionSort(window, 9);
			auto end = chrono::steady_clock::now(); // Stop timer
			t = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); // get nanoseconds taken
			sum_t += t; // add to total time taken (still in nanoseconds)
			speed = std::isfinite(9.0/t) ? 9.0/t : speed; // Speed = (number of pixels in the window / time taken) = pixels per nanosecond
			sum_speed += speed;
			fprintf(ftime,"%.0f\n",t); // Write nanoseconds (per window) to time.dat
			fprintf(fspeed,"%.8f\n",speed); // write speed (pixels per nanosecond) to speed.dat
			fprintf(fout,"%d\n",window[4]); // Write median into out.gold.dat
            fprintf(fout_m,"%d\t",window[4]); // Write median into out.m.dat
		}
        fprintf(fout_m,"\n");
	}

	double pps = sum_speed*1e9/(width*height); // total speed / total pixels = average pixels per second

	fclose(fout);
    fclose(fout_m);

    free(img_array);
    free(vec);
    free(window);

	cout << ">> Time taken per pixel (nanoseconds) written as /data/time_ns.dat." << endl;
	cout << ">> Speed per pixel (pixels per nanoseconds) written as /data/speed_ns.dat." << endl;
	cout << ">> Saved processed output pixels matrix as /data/out.m.dat and flattened as /data/out.gold.dat." << endl;
	cout << endl << "- - - Time profiling - - -" << endl << ">> Total time taken = " << sum_t*1e-9 << " seconds." << endl;
	cout << ">> Processing speed = " << pps << " pixels per second." << endl;
    
    return 0;
}
