#include <iostream>




class Square {
	friend class Rectangle;
	private:
		int side;

	public:
		Square(int _side) : side(_side){};
};


class Rectangle {
	friend class Square;
	private:
		int width, height;
	public:
		int area(){ return width * height; }
		void convert(Square a);
};


void Rectangle::convert(Square a){
	Rectangle::height = a.side;	
	Rectangle::width = a.side;
}


int main(){

	Square square(10);
	Rectangle rec;
	rec.convert(square);
	std::cout << rec.area() << std::endl;

}
