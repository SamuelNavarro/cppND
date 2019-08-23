#include<iostream>
#include<memory>


class MyClass
{
  public:
		void classMethod()
		{
			std::cout << "Message from MyClass::classMethod" << std::endl;
		}
};



int main(){

	std::unique_ptr<MyClass> ptr_1 (new MyClass);
	// What's the difference between these two 
	//std::unique_ptr<MyClass> ptr_1 = std::make_unique<MyClass>();
	ptr_1->classMethod();
	std::cout << ptr_1.get() << std::endl;

	// transfer ownership to ptr_2
	std::unique_ptr<MyClass> ptr_2 = std::move(ptr_1);
	ptr_2 -> classMethod();
	std::cout << "ptr_1.get() result: " << ptr_1.get() << std::endl;
	std::cout << "ptr_2.get() result: " << ptr_2.get() << std::endl;

	// transfer ownership to ptr_3
	std::unique_ptr<MyClass> ptr_3 = std::move(ptr_2);
	ptr_3->classMethod();
	std::cout << "ptr_1.get() result: " << ptr_1.get() << std::endl;
	std::cout << "ptr_2.get() result: " << ptr_2.get() << std::endl;
	std::cout << "ptr_3.get() result: " << ptr_3.get() << std::endl;

	return 0;


}
