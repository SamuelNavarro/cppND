#include <iostream>


int main(){

  int* arr_ptr = new(std::nothrow) int[5];
  for(int i=0; i<5; i++){
    std::cout << "Input value: "  << std::endl;
		std::cin >> arr_ptr[i];
	}

	for(int i=0; i<5; i++){
    std::cout << "Arr address of "<< i << " is: " << &arr_ptr[i] << std::endl;
    std::cout << "Value in "<< i << " is: " << arr_ptr[i] << std::endl;
	}

	delete[] arr_ptr;


}
