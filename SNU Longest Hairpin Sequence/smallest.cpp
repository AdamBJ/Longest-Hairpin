#include <algorithm>    // std::min
//returns the minium of three input values

int smallest(int x, int y, int z){
	return std::min(std::min(x, y), z);
}