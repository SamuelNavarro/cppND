#include <iostream>


namespace test{
	int val = 5;
}

int val = 10;

void func(){
	int val = 15;
	std::cout << "Function val: " << val << std::endl;
}



int main(){

	int val = 20;
	std::cout << " Global val: " << ::val << std::endl;
	std::cout << " Namespace val: " << test::val << std::endl;
	func();
	std::cout << " Local val: " << val << std::endl;


}
