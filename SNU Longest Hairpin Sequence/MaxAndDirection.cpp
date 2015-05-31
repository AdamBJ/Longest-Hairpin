#include <algorithm>    // std::max

int* MaxAndDirection(int first, int second, int third){
	//first comes from left neighbour, second from top-left neighbour, and third from top neighbour.
	int *maxValue_direction = new int[2];//store maxVal in [0], direction in [1]. Use the heap, otherwise we'll lose the array when we return.
	int currMax = std::max(first, second);
	
	if ( currMax == first) {
		maxValue_direction[0] = first;
		maxValue_direction[1] = 1;
	}
	else {
		maxValue_direction[0] = second;
		maxValue_direction[1] = 2;
	}

	currMax = std::max(currMax, third);
	if (currMax == third) {
		maxValue_direction[0] = third;
		maxValue_direction[1] = 3;
	}
	
	return maxValue_direction;
}