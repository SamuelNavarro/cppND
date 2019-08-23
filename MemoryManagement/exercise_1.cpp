#include <iostream>


int main(){

	int* ptr;
	ptr = new int;
	*ptr = 25;
	std::cout << "Address of pointer: " << ptr << std::endl;
	std::cout << "Value of pointer: " << *ptr << std::endl;

	delete ptr;

	return 0;

}

