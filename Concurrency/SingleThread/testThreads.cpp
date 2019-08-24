#include <thread>
#include <vector>
#include <algorithm>

int main(){
	std::vector<std::thread> threads;

	int nThreads = 4;

	for(int i = 0; i < nThreads; i++){
		// lambda function: is what's been sent through the
		// thread to be executed in parallel. 
		threads.emplace_back(std::thread([](){
					while (true);
					}));
	}


	// wait for threads to finish before leaving main
	std::for_each(threads.begin(), threads.end(), [](std::thread &t){
			t.join();
			});

	return 0;

}

