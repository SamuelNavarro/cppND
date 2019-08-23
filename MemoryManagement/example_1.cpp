#include <iostream>

int main(){

	int val = 20;
	// declare pointer variable
	int* ptr = nullptr;
	// note that data type
	// of ptr and variable must be the same
	ptr = &val;
	// assign the address of a variable to a pointer
	std::cout << "Value at ptr (address): "<< ptr << std::endl;
	std::cout << "Value at &var:          "<< &val << std::endl;
	std::cout << "Value at var (variable data): "<< val << std::endl;
	std::cout << "Value at *ptr (dereferencing pointer): "<< *ptr << std::endl;

	return 0;



}
