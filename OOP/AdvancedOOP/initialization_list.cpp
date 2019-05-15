#include <iostream>
#include <string>

class A {
	private:
		int attr1;
		double attr2;
		char attr3;
	public:
		A(int a, double b, char c) : attr1(a), attr2(b), attr3(c){
			std::cout << "A constructor" << std::endl;	
		}

		void print() const{
			std::cout << "attr1: " << attr1 << ", attr2: " << attr2 << ", attr3: " << attr3 << std::endl;
		}
};

class B {
	private:
		int number;
		A attr;

	public:
		B(int number, int a, double b, char c) : number(number), attr(a, b, c){
		std::cout << "B constructor" << std::endl;
		}
		
		void print(){
		std::cout << "number: " << number <<  std::endl;
		attr.print();
		}

};


int main()
{
	std::cout << "A Object: "  << std::endl;
	A obj(1, 1.3, 'A');
	obj.print();

	std::cout << "B Object: " << std::endl;
	B objb(1, 2, 3.13, 'X');
	objb.print();
}
