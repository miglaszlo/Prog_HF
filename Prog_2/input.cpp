#include "input.h"
#include <iostream>
#include <string>
#include <sstream>


bool my_input(unsigned& menuselect) {
	std::string input;
	std::istringstream iss;
	std::cout << "Enter your choice: ";

	std::getline(std::cin, input);
	iss.str(input);
	if (iss >> menuselect) {
		return true;
	}
	else {
		return false;
	}

}