#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>


double divideByNumber(double num, double denom)
{

	std::cout << "Worker thread is = " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	if(denom==0)
		throw std::runtime_error("Exception from thread: Division by zero!");
	return num / denom;
}


int main(){


	std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;

	// use async to start a task
  double num = 42.0, denom = 2.0;

  std::future<double> ftr = std::async(std::launch::deferred, divideByNumber, num, denom);


	try
	{
		double result = ftr.get();
		std::cout << "Result = " << result << std::endl;
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
	}



	
	return 0;
}
