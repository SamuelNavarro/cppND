#include <iostream>


int main(){

  int x;
	double y;
	int& ref_x = x;
	double& ref_y = y;


	std::cout << "Value of ref_x: " << ref_x << std::endl;
	std::cout << "Value of ref_y: " << ref_y << std::endl;

  x = 5;
	y = 11.7;

	std::cout << "Value of ref_x: " << ref_x << std::endl;
	std::cout << "Value of ref_y: " << ref_y << std::endl;
}
