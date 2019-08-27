#ifndef TRAFFICOBJECT_H
#define TRAFFICOBJECT_H

#include <vector>
#include <thread>

enum ObjectType
{
    noObject,
    objectVehicle,
    objectIntersection,
    objectStreet,
};

class TrafficObject
{
public:
    // constructor / desctructor
    TrafficObject();
    ~TrafficObject();

    // getter and setter
    int getID() { return _id; }
    void setPosition(double x, double y);
    void getPosition(double &x, double &y);
    ObjectType getType() { return _type; }

    // typical behaviour methods
		// virtual can be overwritten by classes which 
		// are derived from traffic object and thus
		// they can implemente their own flavor of this
		// simulation. 
    virtual void simulate(){};



protected:
    ObjectType _type;                 // identifies the class type
    int _id;                          // every traffic object has its own unique id
    double _posX, _posY;              // vehicle position in pixels
    std::vector<std::thread> threads; // holds all threads that have been launched within this object

private:
		// by making static this variable we make sure that
		// this variable is independent of instances of
		// traffic object.  
    static int _idCnt; // global variable for counting object ids
};

#endif
