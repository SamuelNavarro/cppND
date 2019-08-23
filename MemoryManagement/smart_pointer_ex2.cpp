#include <iostream>
#include <memory>


class A{
  public:
		void classMethod(){
     std::cout << "Msg from A::classMethod()" << std::endl;
		}
};


int main()
{
	//std::shared_ptr<A> p1 = std::make_shared<A>();
	std::shared_ptr<A> p1 (new A);
	std::cout << "Msg from first p1.get(): " << p1.get() << std::endl;
	std::shared_ptr<A> p2 (p1);
	std::cout << "Msg from 2nd p1.get(): " << p1.get() << std::endl;
	std::cout << "Msg from 1st p2.get(): "<< p2.get() << std::endl;
	

	// Return the number of shared_ptr objects
	// referring to the same managed object.
	std::cout << "p1.use_count(): " << p1.use_count() << std::endl;
	std::cout << "p2.use_count(): " << p2.use_count() << std::endl;


	// Relinquishes ownership of p1 on the object
	// and pointer becomes NULL
	p1.reset();
	std::cout << p1.get() << std::endl;
	std::cout << p2.use_count() << std::endl;
	std::cout << p2.get() << std::endl;
	return 0;


}
