#include <iostream>
#include <thread>
#include <vector>

void printHello(){
	std::cout << "Hello from Worker thread # " << std::this_thread::get_id() << std::endl;
}


int main(){

	std::vector<std::thread> threads;

	for (size_t i = 0; i < 5; i++){

    // copying thread objects causes a compile error
    /*
    std::thread t(printHello);
    threads.push_back(t); In this line is where we are copying the thread object.
    */

    // moving thread objects will work

		threads.emplace_back(std::thread(printHello));
	}

	std::cout << "Hello from Main thread # " << std::this_thread::get_id() << std::endl;


	for (auto& t: threads)
		t.join();


	return 0;
}


