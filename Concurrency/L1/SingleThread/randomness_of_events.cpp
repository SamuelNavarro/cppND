#include <iostream>
#include <thread>


void threadFunction(){
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "Finished work 1 in thread \n" << std::endl;


	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "Finished work 2 in thread \n" << std::endl;


}


int main(){
  std::thread t(threadFunction);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "Finished work 1 in main \n" << std::endl;



	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "Finished work 2 in main \n" << std::endl;


	t.join();


	return 0;
}


