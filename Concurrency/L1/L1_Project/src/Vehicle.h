#ifndef VEHICLE_H
#define VEHICLE_H

#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Street;
class Intersection;

class Vehicle : public TrafficObject, public std::enable_shared_from_this<Vehicle>
{
public:
    // constructor / desctructor
    Vehicle();

    // getters / setters
    void setCurrentStreet(std::shared_ptr<Street> street) { _currStreet = street; };
    void setCurrentDestination(std::shared_ptr<Intersection> destination);

    // typical behaviour methods
		// We overwritte simulate
    void simulate();

    // miscellaneous
		// With shared pointers, if you want to pass pointer to an object
		// of a class itself, you would use the this keyword, but
		// you cannot to it with shared_ptr. This is why we add 
		// std::enable_shared_from_this. This enable us to pass
		// "this" as a pointer. 
    std::shared_ptr<Vehicle> get_shared_this() { return shared_from_this(); }

private:
    // typical behaviour methods
    void drive();

    std::shared_ptr<Street> _currStreet;            // street on which the vehicle is currently on
    std::shared_ptr<Intersection> _currDestination; // destination to which the vehicle is currently driving
    double _posStreet;                              // position on current street
    double _speed;                                  // ego speed in m/s
};

#endif
