#include <iostream>

class Point{
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
			std::cout << "Point: (" << Point::x << ", " << Point::y << ")" << std::endl;
		}
		void Print(double x){ 
			std::cout << "Point: (" << x << ", " << Point::y << ")" << std::endl;
		}
		void Print(const double &x, const double &y){
			std::cout << "Point: (" << x << ", " << y << ")" << std::endl;
		}
};



int main(){
	Point p1(10, 20);
	Point p2(5, 10);
	Point p3 = p1 + p2;
	p3.Print();
	p3.Print(3);
	p3.Print(8, 10);	

}
