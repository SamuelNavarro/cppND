#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <future>
#include <mutex>

class Vehicle
{
	private:
		int _id;
	public:
		Vehicle(int id) : _id(id) {}
		int getID() { return _id; } 
};



class WaitingVehicles
{
	private:
		std::vector<Vehicle> _vehicles;
		std::timed_mutex _tmutex;
	public:
		WaitingVehicles() {}

		void printSize()
		{
			_tmutex.lock();
      std::cout << "# Vehicles = " << _vehicles.size() << std::endl;
			_tmutex.unlock();
		}

		void pushBack(Vehicle &&v){
			// if i < 3 we kind of ensure that we pass 1000 vehicles.
			// but if i < i (just one try), we will get less vehicles.
			for(int i = 0; i < 1; i++){
				if(_tmutex.try_lock_for(std::chrono::milliseconds(1))){
			    _vehicles.emplace_back(std::move(v));
			    _tmutex.unlock();
					// Why this break????
					break;
					}else{
						std::cout << "Attemp failed. Vehicle # " << v.getID() << std::endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(5000));
					}
			} // end of for
		} // end of pushback
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
