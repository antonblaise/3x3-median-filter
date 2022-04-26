#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using std::ofstream;

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

#define N 2000
int img_array[N][N];

int main() {

  // Read image dat and store in vec
  ifstream dat_in("./data/input.dat");
  int num;
  vector<int> vec;

  while (dat_in >> num)
      vec.push_back(num);

  // Get image dimensions
  ifstream dim_in("./data/dimension.dat");
  int val;
  vector<int> dim;

  while (dim_in >> val)
      dim.push_back(val);

  int width = dim[0], height = dim[1], row, col, pixel_pointer=0;

  // set all elements = 0
  for (row = 0; row < N; row++){
    for (col = 0; col < N; col++){
      img_array[row][col] = 0;
    }
  }
  
  // store pixel data into img_array matrix
  // // // With zero padding
  // for (row = 1; row < height-1; row++){
  //   for (col = 1; col < width-1; col++){
  //     img_array[row][col] = vec[pixel_pointer];
  //     pixel_pointer++;
  //   }
  // }

  // // No padding
  for (row = 0; row < height; row++){
    for (col = 0; col < width; col++){
      img_array[row][col] = vec[pixel_pointer];
      pixel_pointer++;
    }
  }

  // save img_array matrix content in img_array.dat
  ofstream arrdata;
  arrdata.open("./data/img_array.dat"); // opens the file
  if( !arrdata ) { // file couldn't be opened
    cerr << ">> Error: file could not be opened" << endl;
    exit(1);
  }
  
  for (row = 0; row < height; row++){
    for (col = 0; col < width; col++){
      // cout << img_array[row][col] << "\t";
      arrdata << img_array[row][col] << "\t";
    }
    arrdata << endl;
  }
  arrdata.close();
  cout << ">> Saved input pixels matrix as img_array.dat" << endl;

  // 3x3 median filter main algorithm
  int window[9];
  cout << ">> Performing 3x3 median filter, please wait..." << endl;

  ofstream v_outdata, m_outdata;
  v_outdata.open("./data/v_outdata.dat"); // opens the file
  m_outdata.open("./data/m_outdata.dat");
  if( !v_outdata || !m_outdata ) { // file couldn't be opened
    cerr << ">> Error: file could not be opened" << endl;
    exit(1);
  }

  for(row = 1; row <= height; row++)
  {
    for(col = 1; col <= width; col++)
    {
      // Window = 3x3 matrix, centered at (row,col)
      window[0] = img_array[row-1][col-1];
      window[1] = img_array[row-1][col];
      window[2] = img_array[row-1][col+1];
      window[3] = img_array[row][col-1];
      window[4] = img_array[row][col];
      window[5] = img_array[row][col+1];
      window[6] = img_array[row+1][col-1];
      window[7] = img_array[row+1][col];
      window[8] = img_array[row+1][col+1];

      //sort window array (pick any sorting algorithm above)
      insertionSort(window, 9);
      v_outdata << window[4] << endl;
      m_outdata << window[4] << "\t";
    }
    m_outdata << endl;
  }
  v_outdata.close();
  m_outdata.close();  
  
  cout << ">> Saved processed output pixels matrix as m_output.dat, and flattened as v_output.dat." << endl;

  return 0;
}
