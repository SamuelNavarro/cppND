#include <iostream>
#include <cmath>

const double PI = 3.14159;

class Shape{
	public:
		Shape() {}
		virtual double Area() const = 0;
		virtual double PerimeterLength() const = 0;
};


class Rectangle : public Shape {
	private:
		double width, height;
	public:
		Rectangle(double width, double height){
			Rectangle::width = width;
			Rectangle::height = height;
		}
		virtual double Area() const override {
			std::cout << "Rectangle: " << std::endl;
			return width*height;
		}
		virtual double PerimeterLength() const override {
			std::cout << "Rectangle: " << std::endl;
			return 2*(width * height);	
		}
};

class Circle : public Shape {
	private:
		double radius;
	public:
		Circle(double r){
			Circle::radius = r;	
		}
		virtual double Area() const override {
			std::cout << "Circle: " << std::endl;
			return PI * std::pow(radius, 2);
		}
		virtual double PerimeterLength() const override {
			std::cout << "Circle: " << std::endl;
			return 2*radius*PI;
		}

};



int main(){
	Shape* rp = new Rectangle(10, 10);
	Shape* cp = new Circle(1.3);
	//double area_rectangle = rp->Area();
	std::cout << "Area" << std::endl;
	std::cout <<  rp->Area() << std::endl;
	std::cout << cp->Area() << "\n" << std::endl;

	std::cout << "Perimeter" << std::endl;
	std::cout <<  rp->PerimeterLength()<< std::endl;
	std::cout << cp->PerimeterLength() << std::endl;

	//Shape* cp = new Circle(3.3);
	//double area_circle = cp->Area();
	/*std::cout << area << std::endl;*/
}
