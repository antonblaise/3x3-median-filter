*University of Technology Malaysia (UTM)</br>
SKEL 4673 - DSP Architectures</br>
Group 4</br>
Ha How Ung, Kenneth Lo, Yeap Eng Jau</br>
Assignment 1*</br>

# 3x3-median-filter
 Image processing - noise reduction with 3x3 median filter</br>
 Note that this tool is only useable on Windows, and it can only produce grayscale outputs.

# Requirements
[C++ compiler](https://sourceforge.net/projects/mingw/) (mingw32-gcc-g++)</br>
[Python 3](https://www.python.org/downloads/)</br>
[NumPy](https://numpy.org/install/)</br>
[Pillow](https://pypi.org/project/Pillow/)</br>

# Usage guide
- Run the following command in command prompt `cmd.exe` under your desired folder.</br>`git clone https://github.com/antonblaise/3x3-median-filter.git` 
- Double click on the new `3x3-median-filter` folder.
- For first time usage after fresh install, `python requirements.py` before using the program. 
- Place your input image inside the `data` folder, and rename it as `input.png`.
- Double click `launcher.bat` to run the program.
- The result is generated and saved in both the main directory and the `data` folder as `output.png`. 

# Example
![PhotoGrid_Plus_1650919314164](https://user-images.githubusercontent.com/68864109/165171614-822e5def-642c-40f2-881c-87bfa46b779a.jpg)
</br>Input, grayscaled, and output.

# Code explanation
- Each program file is run in the correct order, with the help of automation using the `launcher.bat` file. So we don't have to run the files one by one every time. The PDF below shows brief explanations of each of the scripts involved.</br>[3x3 Median Filter.pdf](https://github.com/antonblaise/3x3-median-filter/files/8692515/3x3.Median.Filter.pdf)

- The `clear_dat.py` is run at the very beginning to remove all the old `.dat` files to avoid erroneous overlapping.
- Running `requirements.py` helps to install the packages listed.

# Major amendments
### 27 April 2022
- Switched from static to dynamic memory allocation for the huge matrices and vectors to overcome segmentation fault besides improving processing speed.
- Eliminated the usage of `fstream` library, as it causes problems during integration with Vivado HLS.
