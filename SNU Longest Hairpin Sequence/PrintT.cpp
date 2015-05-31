#include <iostream>
#include <fstream>

using namespace std;

void PrintT(int **m, int rows, int cols, std::string top, std::string btm, std::string title) {

	//Creates an instance of ofstream, and opens example.txt
	ofstream a_file2(title);
	// Outputs to example.txt through a_file

	a_file2 << "      ";
	for (int k = 0; k < cols; ++k)
		a_file2 << btm[k] << ". ";

	a_file2 << endl;
	
	for (int i = 0; i < rows; ++i) {
		if (i == 0)
			a_file2 << "   ";
		else
			a_file2 << top[i-1] << ". ";
	
		for (int j = 0; j < cols; ++j) 
				a_file2 << m[i][j] << "  ";	

		a_file2 << endl;
	}
}