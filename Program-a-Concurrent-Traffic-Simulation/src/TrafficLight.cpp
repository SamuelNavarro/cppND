#include <iostream>
#include <algorithm>
#include <random>
#include <future>
#include <mutex>
#include <thread>
#include "TrafficLight.h"


template <typename T>
T MessageQueue<T>::receive()
{
	std::unique_lock<std::mutex> lck(_mtx);
  _cond.wait(lck, [this] { return !_queue.empty(); });
	T msg = std::move(_queue.back());
	_queue.pop_back();

	return msg;
}

template <typename T>
void MessageQueue<T>::send(T&& msg)
{
	std::unique_lock<std::mutex> lck(_mtx);
	lck.unlock();
	std::cout << " Message " << msg << " has been sent to the queue" << std::endl;
	lck.lock();
  _queue.push_back(std::move(msg));
	_cond.notify_one();
}


void TrafficLight::waitForGreen()
{
		while(true){
		  auto light = msgs->receive();	
			if(light == TrafficLightPhase::green){
				return;
			}
		}
}


void TrafficLight::simulate()
{
	threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
  std::unique_lock<std::mutex> lck(_mutex);	
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<std::mt19937::result_type> dist3(4,6);
	int cycle_duration = dist3(rng);

  std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();

  while(true){
			auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>( std::chrono::high_resolution_clock::now() - t0).count();

			if(elapsedTime >= cycle_duration){


        // switch the light
				if(_currentPhase == TrafficLightPhase::red){
					_currentPhase = TrafficLightPhase::green;
				}else{
					_currentPhase = TrafficLightPhase::red;
				}

			  //std::shared_ptr<MessageQueue<TrafficLightPhase>> msgs(new MessageQueue<TrafficLightPhase>);
			  auto ftr = std::async(std::launch::async, &MessageQueue<TrafficLightPhase>::send, msgs, std::move(_currentPhase));
			  ftr.wait();
			  std::this_thread::sleep_for(std::chrono::milliseconds(1));
	      t0 = std::chrono::high_resolution_clock::now();

				cycle_duration = dist3(rng);
			}
	}
}

