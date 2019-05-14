#include <iostream>

class Base{
	public:
		Base(){}
		virtual void print() const = 0;
		void calc(){
			std::cout << "Base class" << std::endl;
		}
};


class Derived : public Base {
	public:
		Derived(){}
		virtual void print() const override {
			std::cout << "Derived class" << std::endl;	
		};
		void calc(){
			std::cout << "Derived class" << std::endl;
		}


};

int main(){
	Base* bp = new Derived();
	std::cout << "Msg from Derived class: (virtual) " << std::endl;
	bp->print();

	std::cout << "Msg from Base class: " << std::endl;
	bp->calc();



	// Another form
   /* Base *base_ptr;*/
	//Derived derived;
	//base_ptr = &derived;
	//base_ptr->print();
	/*base_ptr->calc();*/
}
