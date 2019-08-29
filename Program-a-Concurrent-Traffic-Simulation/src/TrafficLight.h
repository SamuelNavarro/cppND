#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <algorithm>
#include <condition_variable>
#include "TrafficObject.h"




enum TrafficLightPhase {
    red,
		green,
};


// forward declarations to avoid include cycle
class Vehicle;


template <class T>
class MessageQueue
{
public:
	void send(T && msg);
	T receive();
private:
  std::deque<TrafficLightPhase> _queue;
	std::condition_variable _cond;
	std::mutex _mtx;
};


class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight() {
			_currentPhase = red;
      msgs = std::make_shared<MessageQueue<TrafficLightPhase>>();      
		};
    ~TrafficLight(){
			std::for_each(threads.begin(), threads.end(), [](std::thread &t){
					t.join();
					});
		};
    // getters / setters
    // typical behaviour methods
		void waitForGreen();
		void simulate();
		TrafficLightPhase getCurrentPhase() { return _currentPhase;}

private:
    // typical behaviour methods
		void cycleThroughPhases();
	  TrafficLightPhase _currentPhase;
    std::mutex _mutex;
		std::shared_ptr<MessageQueue<TrafficLightPhase>> msgs;
};

#endif
