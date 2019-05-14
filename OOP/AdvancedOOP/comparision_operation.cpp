#include <iostream>

template <typename T>
T ReturnMax(T a, T b)
{
	if(a>b)
		return a;
	else
		return b;
}

int main(){
	int num1 = 50;
	int num2 = 10;
	
	int res = ReturnMax(num1, num2);
	std::cout << res << std::endl;


	double num3 = 13.3;
	double num4 = 34.1;

	double res1 = ReturnMax(num3, num4);
	std::cout << res1 << std::endl;



}
