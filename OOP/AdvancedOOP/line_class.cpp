#include <iostream>
#include <cmath>


class Line{
	protected:
		int length;
};


class Circle : Line{
	private:
		int radius;
	public:
		void SetRadius(int _radius){ radius = _radius; }
		int GetArea(const double pi){ return pi * std::pow(radius, 2);}
};


const double PI = 3.14159;

int main(){

	Circle c;
	c.SetRadius(10);
	std::cout << c.GetArea(PI) << std::endl;

}
