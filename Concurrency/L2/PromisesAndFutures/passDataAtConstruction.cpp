#include <iostream>
#include <thread>

void printMessage(std::string msg){
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::cout << "Thread 1: " << msg << std::endl;
}

int main(){
  std::string msg = "My Msg";

	// Thread using variadic templates
	std::thread t1(printMessage, msg);

	// Thread using Lambdas
  std::thread t2([msg](){
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			std::cout << "Thread 2: " << msg << std::endl;
	});

	// Thread Lambda parameter list
	// ESTA NOS SACA UN ERROR. 
	/*std::thread t3([](std::string msg){*/
			//std::this_thread::sleep_for(std::chrono::milliseconds(10));
			//std::cout << "Thread 2: " << msg << std::endl;
	/*});*/




	t1.join();
	t2.join();

	return 0;

}
