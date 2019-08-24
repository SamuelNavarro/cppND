#include <iostream>
#include <thread>


class Vehicle{
  public:
		void operator()(){
			std::cout << "Vehicle object has been created \n" << std::endl;
		}
};


int main(){
	std::thread t(Vehicle());
	std::cout << "Finished work in main\n" << std::endl;
	t.join();

  return 0;

}
