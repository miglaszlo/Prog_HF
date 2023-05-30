#include"MyException.h"
#include<exception>

const char* MyException::what() const noexcept {
	return "Invalid input";
}
