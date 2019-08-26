#include <iostream>
#include <thread>
#include <string>


void printName(std::string name, int waitTime)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
	std::cout << "Name (from Thread) = " << name << std::endl;
}


int main(){
	std::string name1 = "MyThread1";
	std::string name2 = "MyThread2";

	// starting threads using value-copy and move semantics
	std::thread t1(printName, name1, 50);
	std::thread t2(printName, std::move(name2), 100);

  // wait for threads before returning
	t1.join();
	t2.join();

	std::cout << "Name 1 (from Main) = " << name1 << std::endl;
	std::cout << "Name 2 (from Main) = " << name2 << std::endl;



	return 0;
}
