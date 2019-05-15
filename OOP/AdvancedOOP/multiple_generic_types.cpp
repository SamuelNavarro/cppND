#include <iostream>
#include <vector>

template <typename T>
void print(const std::vector<T> &a){
	for(T element : a){
		std::cout << element << std::endl;
	}
}


template <typename T1, typename T2>
void multiply(T1 num1, T2 &container){
	for( auto& element : container){
		element *= num1;	
	}
}


int main(){
	std::vector<int> foo = {1, 2, 3, 4, 5};
	int boo = 13;
	multiply(boo, foo);
	print(foo);
}
