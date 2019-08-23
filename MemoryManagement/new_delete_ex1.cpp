#include <iostream>

int main(){

  int* ptr = nullptr;
	ptr = new(std::nothrow) int(10);
  
	std::cout << "Address of ptr: " << ptr << std::endl;
	std::cout << "Value of ptr: " << *ptr << std::endl;

	delete ptr;
	return 0;


}
