#include <string>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

void PrintT(int **m, int rows, int cols, std::string top, std::string btm, std::string title);
bool basesMatch(char b1, char b2);
int* MaxAndDirection(int first, int second, int third);

//backtrack through s[i,j] according to the Smith-Waterman algorithm and print the result.
void BackTrack(std::string subSeq, int i, int j, int h) {
	int test = subSeq.length();
	int mid = ceil((subSeq.length()) / 2) -1;
	std::string top = subSeq.substr(0, mid + 1);
	std::string btm = subSeq.substr(mid + 1);
	std::reverse(btm.begin(), btm.end());

	//we now have two sequences (top and btm) that we can plug into SW alg to find optimal local alignment

	//create table T. top is vertical and btm is horizontal as in slide 8 of http://www.slideshare.net/avrilcoghlan/the-smith-waterman-algorithm
	const int numRows = top.length()+1;
	const int numCols = btm.length()+1;

	//initialize the table T and the direction table D. T holds the score, D tells us which of the three possible table entries a given table
	//entry was calculated from.
	int **T = new int*[numRows]; // pointer to a pointer. T holds pointers to each row.
	int **D = new int*[numRows]; //1 means taken from left neighboor, 2 from top left, 3 from top.
	for (int i = 0; i <= numRows; ++i) {
		T[i] = new int[numCols]; //each row is a pointer that points to an array of length numCols
		D[i] = new int[numCols]; //each row is a pointer that points to an array of length numCols
		for (int j = 0; j <= numCols; j++){
			T[i][j] = 9;
			D[i][j] = 0;
		}

	}

	T[0][0] = 0;
	D[0][0] = -1;
	int initVal = 0;
	for (int i = 1; i < numCols; i++) {
		T[0][i] = initVal;
		D[0][i] = 1;
		initVal = initVal - 2;
	}

	initVal = 0;
	for (int i = 1; i < numRows; i++){
		T[i][0] = initVal;
		D[i][0] = 3;
		initVal = initVal - 2;
	}
	


	
	
 //fill the table
	int S; //see Smith-Waterman rec relation for details. S = 2 if bases match, -1 if they don't.
	
	for (int i = 1; i <= numRows; i++){
		for (int j = 1; j <= numCols; j++){

			if (basesMatch(top[i-1], btm[j-1]))
				S = 1;
			else
				S = -1;

			int *max_and_direction = MaxAndDirection(T[i][j - 1] - 2, T[i - 1][j - 1] + S, T[i - 1][j] - 2);
			T[i][j] = max_and_direction[0];
			D[i][j] = max_and_direction[1];
			
		}
	}	

	PrintT(T, numRows, numCols, top, btm, "T.txt");
	PrintT(D, numRows, numCols, top, btm, "D.txt");

	//Find the optimal structure with backtracking

	//starting with bottom right entry..., backtrack.
	std::vector<char> topArm;
	std::vector<char> btmArm;

	//left arrow is miss on bottom arm, up arrow is miss on top arm, diag is match.
	int row = top.length();
	int col = btm.length();
	int direction = 0;
	//Top arm is 1st half of subseq, btm is reversed second half. btm is the columns in D,T.
	while (direction != -1) {//top left corner is only place in D with value -1
		direction = D[row][col];
		if (direction == 1){//left arrow, miss on bottom
			topArm.push_back('-');
			btmArm.push_back(btm[col - 1]);
			col--;
		}
		else if (direction == 2){//diag, match
			topArm.push_back(top[row-1]);
			btmArm.push_back(btm[col-1]);
			col--;
			row--;
		}
		else if (direction == 3) {//top arrow, miss on top
			topArm.push_back(top[row - 1]);
			btmArm.push_back('-');
			row--;
		}
	}
	//pushing each character results in backwards final arrays, reverse them to fix. 
	std::reverse(topArm.begin(), topArm.end());
	std::reverse(btmArm.begin(), btmArm.end());


	//suck as many chars into the loop as possible, we can get rid of some misses that way if we're lucky.
	if (h % 2 != 0) h--;	

	//i=11, j=26, length=26, loop_length=4, miss=2
	int noMisses = 0;
	for (int i = 0; i < topArm.size() - h / 2; i++) {
		if (!basesMatch(topArm[i], btmArm[i]))
			noMisses++;
	}
	int loop_length = 0;
	for (int j = topArm.size() - (h / 2); j < topArm.size(); j++){
		if (topArm[j] != '-') loop_length++;
		if (btmArm[j] != '-') loop_length++;
	}

	std::cout << "i=" << i << ", j=" << j << ", length=" << j - i + 1 << ", loop_length=" << loop_length << ", miss=" << noMisses << std::endl;

	

	//print the top arm up to the loop
	for (int i = 0; i < topArm.size() - (h / 2); i++) {
		std::cout << topArm[i];
	}

	//print the loop
	
	std::cout << " ";
	//if (!armLengthsMatch) std::cout << btmArm[btm.length()-1]; //print the odd man out, now we can treat arms as equal lengths
	for (int j = topArm.size() - (h / 2); j < topArm.size(); j++){
		if (topArm[j] != '-') std::cout << topArm[j];
	    if (btmArm[j] != '-') std::cout << btmArm[j];	
	}
	
	std::cout << std::endl;

	//print the "|"s
	for (int i = 0; i < topArm.size() - h / 2; i++) {
		if (basesMatch(topArm[i], btmArm[i]))
			std::cout << "|";
		else 
			std::cout << " ";
	}
	
	std::cout << std::endl;
	//print the bottom arm
	for (int j = 0; j < topArm.size() - (h / 2); j++){
		std::cout << btmArm[j];
	}
	std::cout << std::endl <<std::endl;
}
