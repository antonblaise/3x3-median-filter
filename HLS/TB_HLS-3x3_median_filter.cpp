//========================================================================
// Testbench for the 3x3 Median Filter program
//========================================================================

#include <iostream>
#include <stdlib.h>
using namespace std;

void median_filter();

int main(){

	median_filter(); // DUT, produces the out.dat for verification

	//Comparing results with the golden output.
	printf ("Comparing against out.gold.dat \n");

	if (system("diff -w out.dat out.gold.dat")) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	} else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "PASS: The output matches the golden output!\n");
		fprintf(stdout, "*******************************************\n");
		return 0;
	}
}
