#include <iostream>
#include <math.h>

void trigonometry(double* _sin, double* _cos, double angle){
	*_sin = std::sin(angle);
	*_cos = std::cos(angle);
}


int main(){

	double angle, _sin, _cos;
	std::cout << "Declare angle: " << std::endl;
	std::cin  >> angle;

	trigonometry(&_sin, &_cos, angle);
	
	std::cout << "Sine is: "<< _sin << std::endl;
	std::cout << "Cosine is: "<< _cos << std::endl;

	std::cout << "Sine address is: " << &_sin << std::endl;
	std::cout << "Cosine address is: " << &_cos << std::endl;



	return 0;

}
