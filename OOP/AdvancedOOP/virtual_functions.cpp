#include <iostream>

const double PI = 3.14159;

class Shape{
	public:
		Shape() {}
		virtual double Area() const = 0;
		virtual double PerimeterLength() const = 0;
};


class Rectangle : public Shape {
	private:
		int width, height;
	public:
		Rectangle(int width, int height){
			Rectangle::width = width;
			Rectangle::height = height;
		}
		double Area() const override {
			std::cout << "Rectangle: "<<  std::endl;
			return width * height;
		};
		double PerimeterLength() const override {
			return 2*(width * height);	
		};
};


int main(){

}
