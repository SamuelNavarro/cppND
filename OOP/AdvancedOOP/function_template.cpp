#include <iostream>

template <typename Type>
	Type average(Type a, Type b)
	{
		return (a + b) / 2;
	}

int main(){
	std::cout << average(1, 2) << std::endl;
	std::cout << average<double>(13.31, 13.34) << std::endl;
	std::cout << average('a', 'c') << std::endl;
}

