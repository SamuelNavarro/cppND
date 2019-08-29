#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <future>
#include <mutex>

class Vehicle
{
	public:
		Vehicle(int id) : _id(id) {}
	private:
		int _id;
};



class WaitingVehicles
{
	private:
		std::vector<Vehicle> _vehicles;
		std::mutex _mutex;
	public:
		WaitingVehicles() {}

		void printSize()
		{
			_mutex.lock();
      std::cout << "# Vehicles = " << _vehicles.size() << std::endl;
			_mutex.unlock();
		}

		void pushBack(Vehicle &&v){
			_mutex.lock();
			_vehicles.emplace_back(std::move(v));
			_mutex.unlock();
		}
};

int main(){


	std::shared_ptr<WaitingVehicles> queue(new WaitingVehicles);
	std::vector<std::future<void>> futures;
	for(int i=0; i<1000; i++){
		Vehicle v(i);
		// cuando es referencia a una función y se da un puntero, también se tiene que dar el valor?
		futures.emplace_back(std::async(std::launch::async, &WaitingVehicles::pushBack, queue, std::move(v)));
	}


	std::for_each(futures.begin(), futures.end(), [](std::future<void> &ftr){
			ftr.wait();
			});


	queue->printSize();


	return 0;
}
