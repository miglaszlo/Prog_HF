#include "isPart.h"


bool isPart(unsigned& menuselect) {
	unsigned array[] = { 1,2,3,4,5,6,7,8,9,10 };
	for (unsigned j = 0; j <= 10; j++) {
		if (array[j] == menuselect) {
			return true;
		}

	}
	return false;
}