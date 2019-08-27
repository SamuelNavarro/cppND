#include <iostream>
#include <thread>


void threadFunctionEven(){
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	std::cout << "Even thread \n" << std::endl;
}


void threadFunctionOdd(){
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	std::cout << "Odd thread \n" << std::endl;
}

int main(){


	int nThreads = 6;

	for(int i = 0; i < nThreads; i++){

		if(i % 2 == 0){
	    std::thread t(threadFunctionEven);
	    t.detach();
		}else{
			std::thread t(threadFunctionOdd);
			t.detach();
		}
	}


	// Some threads are executed after the main function reaches its end. 
	// That's why the outputs sometimes has the 7 threds and sometimes less
	// threds. Moreover, if we comment out the sleep_for in the main
	// thread, this threads will not finish before the program terminates.
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	std::cout << "Main thread \n" << std::endl;

	return 0;
}
