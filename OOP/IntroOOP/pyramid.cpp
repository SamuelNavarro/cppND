#include <iostream>
#include <cmath>


class Pyramid{
	private:
		unsigned int base_length;
		unsigned int base_width;
		unsigned int height;
	public:
		Pyramid(int length, int width, int height);

		void SetLength(int length);
		void SetWidth(int width);
		void SetHeight(int height);

		unsigned int GetLength() const {return base_length;}
		unsigned int GetWidth() const {return base_width;}
		unsigned int GetHeight() const {return height;}

		float CalculateVolume();
		float CalculateArea();
		void CheckValues();

};

Pyramid::Pyramid(int length, int width, int height) : base_length(length), base_width(width), height(height){};


float Pyramid::CalculateVolume(){
	float volumen = base_length * base_width * height / 3;
	return volumen;
}

float Pyramid::CalculateArea(){
	return base_length*base_width + base_length*std::sqrt(std::pow(base_width/2, 2) + std::pow(height, 2)) + base_width*std::sqrt(std::pow(base_length/2, 2) + std::pow(height, 2));
}

void Pyramid::SetLength(int length){
	base_length = length;
}

void Pyramid::SetWidth(int width){
	base_width = width;
}



int main(){
	// width must be equal to length
	Pyramid pyramid(10, 10, 30);
	std::cout << pyramid.GetLength() << std::endl;

	std::cout << "New length: " << pyramid.GetLength() << std::endl;
	std::cout << "The volumen is: " << pyramid.CalculateVolume() << std::endl;
	std::cout << "The Area is: " << pyramid.CalculateArea() << std::endl;

}
