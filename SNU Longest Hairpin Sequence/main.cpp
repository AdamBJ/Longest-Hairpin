#include <string>
#include <iostream>
#include <fstream>


int smallest(int x, int y, int z);
bool basesMatch(char b1, char b2);
void PrintM(int **m, int rows, int cols, std::string title);
void BackTrack(std::string subSeq, int i, int j, int h);

int main() {
	const int N = 29;
	std::string seq = "GAATCATCGAGTCGAGACTCGCATGCTAC";
	std::string test = "cat";
	//std::reverse(test.begin(), test.end());
	char t = seq[0];
	std::string subSeq = seq.substr(1, 3);
	int h, l, mm;
	int i, j;
	l = 10;
	mm = 2;
	h = 5;
	/*
	//preallocate m
	int m[N][N]; //causes stack overflow for N=5000, too big for stack. put it on the heap.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) 
			m[i][j] = 9;		
	}
	*/
	int **m= new int*[N];
	for (int i = 0; i < N; ++i) {
		m[i] = new int[N];
		for (int j = 0; j < N; ++j){
			m[i][j] = 9;
		}
	}
		
	//initialize m[i, j] = 0 for 1≤ i ≤N-h+1, j=i+h-1
	for (int i = 0; i < N; i++){
		for (int j = i; j < N; j++) {
			if (j - i + 1 <= h) 
				m[i][j] = 0;			
		}
	}

	std::ofstream a_file("2d_array.txt");

	for (int i = 0; i<N; ++i) {
		for (int j = 0; j < N; ++j) 
			a_file << m[i][j] << ' ';
		a_file << std::endl;
	}

	//fill m[i, j] for 1≤i≤N-h+1, i+h≤j≤N using dynamic programming.
	//We can only fill in an entry when it is the top right corner of a square where the other corners are all filled in.
	//0 OK             0 X
	//0 0			   ? 0
	//Looking at 2d_array.txt, we need to fill the matrix diagonally from left to right, top to bottom.
	// Fill m(x+1,y+1), then m(x+2,y+2)...


	//	string seq = "GAATCATCGAGTCGAGACTCGCATGCTAC";
	//num_slices_processed represents the number of diagonal slices of m that we've calculated up to this point.
	for (int num_slices_processed = h; num_slices_processed < N; num_slices_processed++){
		//while j is in bounds, ie j < N. This fills in one diagonal slice of m from L->R top -> bottom.
		int i = 0;
		j = num_slices_processed;
		while (j < N) {
			if (basesMatch(seq[i], seq[j])) {
				t = m[i + 1][j - 1];
				m[i][j] = m[i + 1][j - 1];
			}
			else  {//bases don't match
				m[i][j] = smallest(m[i + 1][j] + 1, m[i][j - 1] + 1, m[i + 1][j - 1] + 1);
			}
			i++;
			j++;
		}
	}
	
	//PrintM(m, N, N, "mfin.txt");
	//i = 2 j = 26
	//BackTrack(seq.substr(2, 26-2+1), h);
	//BackTrack(seq.substr(8, 19-8+1), h);
	//BackTrack(seq, h);

	//using back tracking, print out the longest hairpin structure of each candidate subseqeuence s[i, j] that we identify with m.
	
	int maxCol = -1;//to start we need to search all the columns

	//deal with i = 0 first , a special case because we can't check m[i - 1][j + 1]
	if (m[0][N - 1] == mm){
		if (j + 1 >= l)
			BackTrack(seq.substr(0, N), 0 ,N-1, h);
		return 0; //every other hairpin could be extended to this one. Return.
	}
	for (int j = N - 2; j >= 0; j--){
		if (m[0][j] == mm && m[0][j + 1] == mm + 1) {
			if (j + 1 >= l) {
				BackTrack(seq.substr(0, j + 1), 0, j, h);
				maxCol = j;
				break;
			}
		}
	}

	for (int i = 1; i < N; i++){
		if (m[i][N - 1] == mm){
			if (j - N >= l)
				BackTrack(seq.substr(i, N), i, N-1, h);
			return 0; //every other remaining hairpin could be extended to this one. Return.
		}
		for (int j = N - 2; j > maxCol; j--){
			if (!(j - i + 1 >= l))
				break;
			if (m[i][j] == mm && m[i - 1][j + 1] == mm + 1){				
				BackTrack(seq.substr(i, j - i + 1), i , j, h);
				maxCol = j;
				break;				
			}
		}
	}
	return 0;
}