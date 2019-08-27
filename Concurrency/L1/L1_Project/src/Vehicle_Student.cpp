#include <iostream>
#include <thread>
#include <random>
#include "Street.h"
#include "Intersection.h"
#include "Vehicle.h"

Vehicle::Vehicle()
{
    _currStreet = nullptr;
    _posStreet = 0.0;
    _type = ObjectType::objectVehicle;
    _speed = 400; // m/s
}


void Vehicle::setCurrentDestination(std::shared_ptr<Intersection> destination)
{
    // update destination
    _currDestination = destination;

    // reset simulation parameters
    _posStreet = 0.0;
}

void Vehicle::simulate()
{
    // Task L1.2 : Start a thread with the member function „drive“ and the object „this“ as the launch parameters. 
    // Also, add the created thread into the _thread vector of the parent class. 
	threads.emplace_back(std::thread(&Vehicle::drive, this));

	// Ninguna de las de abajo funciona no sé pq.
	//
	  //Vehicle v;
	// pass by value. A copy is made. Doesn't affect
	// the orignal living in main thread.
	//std::thread t1 = std::thread(&Vehicle::addID, v1, 1);
	// pas by reference
	//std::thread t = std::thread(&Vehicle::drive, this);

	//threads.emplace_back(t); // esta es la línea que me da el error. No puedo hacer move semantics de lo de arriba. 


	//std::shared_ptr<Vehicle> v(new Vehicle);
	//call member function on object v. 
	//std::thread t = std::thread(&Vehicle::drive, v, this);
	
	//threads.emplace_back(t);


/*
 *
 *  std::thread t = std::thread(&Vehicle::drive, this);
 *  threads.emplace_back(t);
 *
 */
	
}

// virtual function which is executed in a thread
void Vehicle::drive()
{
    // print id of the current thread
    std::cout << "Vehicle #" << _id << "::drive: thread id = " << std::this_thread::get_id() << std::endl;

    // initalize variables
    bool hasEnteredIntersection = false;
    double cycleDuration = 1; // duration of a single simulation cycle in ms
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    // init stop watch
    lastUpdate = std::chrono::system_clock::now();
    while (true)
    {
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeSinceLastUpdate >= cycleDuration)
        {
            // update position with a constant velocity motion model
            _posStreet += _speed * timeSinceLastUpdate / 1000;

            // compute completion rate of current street
            double completion = _posStreet / _currStreet->getLength();

            // compute current pixel position on street based on driving direction
            std::shared_ptr<Intersection> i1, i2;
            i2 = _currDestination;
            i1 = i2->getID() == _currStreet->getInIntersection()->getID() ? _currStreet->getOutIntersection() : _currStreet->getInIntersection();

            double x1, y1, x2, y2, xv, yv, dx, dy, l;
            i1->getPosition(x1, y1);
            i2->getPosition(x2, y2);
            dx = x2 - x1;
            dy = y2 - y1;
            l = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (x1 - x2));
            xv = x1 + completion * dx; // new position based on line equation in parameter form
            yv = y1 + completion * dy;
            this->setPosition(xv, yv);

            // check wether halting position in front of destination has been reached
            if (completion >= 0.9 && !hasEnteredIntersection)
            {
                // slow down and set intersection flag
                _speed /= 10.0;
                hasEnteredIntersection = true;
            }

            // check wether intersection has been crossed
            if (completion >= 1.0 && hasEnteredIntersection)
            {
                // choose next street and destination
                std::vector<std::shared_ptr<Street>> streetOptions = _currDestination->queryStreets(_currStreet);
                std::shared_ptr<Street> nextStreet;
                if (streetOptions.size() > 0)
                {
                    // pick one street at random and query intersection to enter this street
                    std::random_device rd;
                    std::mt19937 eng(rd());
                    std::uniform_int_distribution<> distr(0, streetOptions.size() - 1);
                    nextStreet = streetOptions.at(distr(eng));
                }
                else
                {
                    // this street is a dead-end, so drive back the same way
                    nextStreet = _currStreet;
                }
                
                // pick the one intersection at which the vehicle is currently not
                std::shared_ptr<Intersection> nextIntersection = nextStreet->getInIntersection()->getID() == _currDestination->getID() ? nextStreet->getOutIntersection() : nextStreet->getInIntersection(); 

                // assign new street and destination
                this->setCurrentDestination(nextIntersection);
                this->setCurrentStreet(nextStreet);

                // reset speed and intersection flag
                _speed *= 10.0;
                hasEnteredIntersection = false;
            }

            // reset stop watch for next cycle
            lastUpdate = std::chrono::system_clock::now();
        }
    } // eof simulation loop
}
