#include <iostream>
#include <string>
#include <cstring>

class Car{
	private:
		int horsepower;
		int weight;
		char* brand;
	public:
		int GetHorsePower() const {return horsepower;}
		int GetWeight() const {return weight;}
		void SetHorsePower(int horsepower );
		void SetWeight(int weight);
		void SetBrand(std::string brandName);
		std::string GetBrand();
};


void Car::SetBrand(std::string brandName){
	Car::brand = new char[brandName.length() + 1];

	// Copy each and every element of brandName into brand.
	// First we convert it into c style string.
	strcpy(Car::brand, brandName.c_str());
}

std::string Car::GetBrand(){
	std::string result = "Brand name: ";
	result += Car::brand;
	return result;
}


void Car::SetHorsePower(int newhorsepower){
	horsepower = newhorsepower;
}


int main(){
	Car car;
	char brand[] = "Peugeot";
	car.SetBrand(brand);
	std::cout << car.GetBrand() << "\n" << std::endl;
	car.SetHorsePower(33);
	std::cout << car.GetHorsePower() << std::endl;
}
