#include <iostream>
#include <string>

class BankAccount{
	public:
		int id;
		std::string name;
		double funds;
};



int main(){

	BankAccount account;
	account.id = 1234;
	account.name = "Samuel Navarro";
	account.funds = 123413243;
	std::cout << "Account information: \n";
	std::cout << "---------------------\n";
	std::cout << "The name is: "<< account.name << "\n" << std::endl;
	std::cout << "ID: " << account.id << "\n" << std::endl;
	std::cout << "Current funds: " << account.funds << "\n"  << std::endl;

}
