#include <iostream>
#include <thread>
#include <string>


class Vehicle
{
	private:
		int _id;
		std::string _name;

	public:
		Vehicle() : _id(0), _name("Hola ") {}
		void addID(int id) { _id = id;}
		void printID()
		{
			std::cout << "Vehicle ID = " << _id << std::endl;
		}
		void setName(std::string name)
		{
		  _name+=name;	
		}
		void printName()
		{
			std::cout << "New Name = " << _name << std::endl;
		}
};


int main(){

	std::string samuel = "Samuel";

	std::shared_ptr<Vehicle> v(new Vehicle);
	//call member function on object v. 
	std::thread t = std::thread(&Vehicle::addID, v, 1);
	
	// Cualquiera de las dos sirve
	//std::thread t2 = std::thread(&Vehicle::setName, v, samuel);
	std::thread t2 = std::thread(&Vehicle::setName, v, "samuel");

	// wait for thread to finish
	t.join();
	t2.join();

	v->printID();
	v->printName();

	return 0;

}
