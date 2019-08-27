#include <iostream>
#include <thread>
#include <future>


void modifyMsg(std::promise<std::string> && prms, std::string msg)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	std::string modifiedMsg = msg + " has been modified";
	prms.set_value(modifiedMsg);
}


int main(){

	std::string msgToThread = "My Msg";

	// create promise and future
	std::promise<std::string> prms;
	std::future<std::string> ftr = prms.get_future();

	//start thread and pass promise as argument.
	std::thread t(modifyMsg, std::move(prms), msgToThread);

	std::cout << "Original msg from main(): " << msgToThread << std::endl;


	// retrieve modified msg via future and print to console
	std::string msgFromThread = ftr.get();
	std::cout << "Modified msg from thread(): " << msgFromThread << std::endl;



	// SI no hago el get() se corre todo pero no obtengo el mensaje.
	// Sólo imprime: modified msg from thread():
	//std::cout << "Modified msg from thread(): " <<  std::endl;


	t.join();


	return 0;
}
