#include <stdio.h>
#include <ctype.h>
//accept b1, b2. Return true if b1 b2 match in terms of base pairing and false otherwise.

bool basesMatch(char b1, char b2) {
	//A-T G-C
	b1 = tolower(b1);
	b2 = tolower(b2);

	if (b1 == 'a'){
		if (b2 == 't')
			return true;
	}
	else if (b1 == 't') {
		if (b2 == 'a')
			return true;
	}
	else if (b1 == 'g'){
		if (b2 == 'c')
			return true;
	}
	else if (b1 == 'c'){
		if (b2 == 'g')
			return true;
	}

	return false; //not a match	
}