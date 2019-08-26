#include <iostream>
#include <thread>

class Vehicle
{
	private:
		int _id;
	public:
		Vehicle() : _id(0) {}
		void addID(int id) { _id = id; }
		void printID(){
		  std::cout << "Vehicle ID = " << _id << std::endl;	
		}
};


int main(){
  Vehicle v1, v2;
	// pass by value. A copy is made. Doesn't affect
	// the orignal living in main thread.
	std::thread t1 = std::thread(&Vehicle::addID, v1, 1);
	// pas by reference
	std::thread t2 = std::thread(&Vehicle::addID, &v2, 2);

	std::cout << "Before t1.join() = " << std::endl;

	v1.printID();

	// wait for thread to finish
	t1.join();
	t2.join();


	v1.printID();
	v2.printID();



	return 0;
}
