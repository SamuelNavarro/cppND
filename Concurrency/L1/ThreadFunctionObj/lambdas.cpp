#include <iostream>

int main(){

	int id = 0;

  // Error: id cannot be accessed. 
	//auto f0 = []{ std::cout << "ID: " << id << std::endl;};
	id++;
	// Ok, id is captured by value.
	auto f1 = [id]{ std::cout << "ID: " << id << std::endl;};

	id++;

	// Ok. Id is captured by reference.
	auto f2 = [&id]{ std::cout << "ID: " << id << std::endl;};


	// Error, 'id' may not be modified
	// auto f3 = [id]() mutable { std::cout << "ID++ : " << id++ << std::endl;};
	
	// Ok, 'id' may be modified
	auto f4 = [id]() mutable { std::cout << "++ID : " << ++id << std::endl;};


	//executes lambdas:
	f1();
	f2();
	f4();

	





	return 0;
}
