#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void PrintM(int **m, int rows, int cols, std::string title) {

	//Creates an instance of ofstream, and opens example.txt
	ofstream a_file2(title);
	// Outputs to example.txt through a_file

	a_file2 << "    ";
	for (int k = 0; k < cols; ++k) 
		a_file2 << k << ". ";
	
	a_file2 << endl;

	for (int i = 0; i < rows; ++i) {
		a_file2 << i << ". ";
		if (i < 10) 
			a_file2 << " ";
		for (int j = 0; j < cols; ++j) {
			if (j < 9)
				a_file2 << m[i][j] << "  ";
			else
				a_file2 << m[i][j] << "   ";
		}
		a_file2 << endl;
	}
}