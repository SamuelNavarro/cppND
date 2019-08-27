#include <iostream>
#include <thread>

class Vehicle{
	private:
		int id;
  public:
		Vehicle(int _id) : id(_id){}
		void operator()(){
      std::cout << "Vehicle #: " << id << " has been created" << std::endl;
		}
};


int main(){
	// Using copy initialization.
	std::thread t = std::thread(Vehicle(1)); 


	// Do something in main
	std::cout << "Finished work in main \n " << std::endl;

	// wait for thread to finish
	t.join();


	return 0;
}
