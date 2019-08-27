#include <iostream>
#include <thread>
#include <future>

class Vehicle
{
	private:
		int _id;
		std::string *_name;
	public:
		// Default constructor
		Vehicle() : _id(0), _name(new std::string("Default Name"))
	{
		std::cout << "Vehicle # " << _id << " Default constructor called" << std::endl;
	}

		// Initializing constructor
		Vehicle(int id, std::string name) : _id(id), _name(new std::string(name))
	{
		std::cout << "Vehicle # " << _id << " Initializing constructor called" << std::endl;
	}
	
	// Copy Constructor
	Vehicle(Vehicle const &src)
	{
		_id = src._id;
		if (src._name != nullptr){
      _name = new std::string;
			*_name = *src._name;
		}
  std::cout << "Vehicle #" << _id << " copy constructor called" << std::endl;
	}


	// Move Constructor
	Vehicle(Vehicle && src)
	{
		_id = src.getID();
		_name = new std::string(src.getName());

		// reset previous one
		src.setID(0);
		src.setName("Default Name");

		std::cout << "Vehicle #" << _id << " move constructor called" << std::endl;
	}
  void setID(int id) { _id = id; }
	int getID() { return _id; }
	void setName(std::string name) { *_name = name; }
	std::string getName() { return *_name; }
};


int main()
{

	Vehicle v0;
	Vehicle v1(1, "Vehicle 1");

	std::future<void> ftr = std::async([](Vehicle v){
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			v.setName("Vehicle 2");
			}, v0);

	v0.setName("Vehicle 3");
	
	ftr.wait();

	std::cout << v0.getName() << std::endl;

	return 0;
}
