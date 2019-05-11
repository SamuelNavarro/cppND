#include <iostream>


class Rectangle;


class Square {
	friend class Rectangle;
	private:
		int slide;

	public:
		Square(int _slide) : slide(_slide){};
};


int main(){


	return 0;
}
