#include <iostream>

class Point {
	private:
		double x;
		double y;
	public:
		Point(double xc, double yc) : x(xc), y(yc) {}
		Point operator+(const Point &p){
			Point res(x, y);
			res.x = this->x + p.x;
			res.y = this->y + p.y;
			return res;
		}
		void Print(){
		std::cout << "x: " << this->x << "\n" << "y: " << this->y << std::endl;	
		}
};


int main(){
	Point pa(3, 4);
	Point pb(1, 1);
	pa.Print();
	std::cout << "\n New point" << std::endl;
	Point newpoint = pa + pb;
	newpoint.Print();
}
