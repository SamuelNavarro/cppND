#include <iostream>
#include <thread>

void threadFunction(){
	// simulate work
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "Finished work in thread \n" << std::endl;
}


int main(){
	std::thread t(threadFunction);

	// simulate work
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::cout << "Finished work in main \n" << std::endl;


	// wait for thread to finish
	t.join();
	return 0;
}

