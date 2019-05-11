#include <iostream>

class A{
	private:
		int a_attr;
	public:
		void SetA(int val_a){ a_attr = val_a; }
		int GetA(){return a_attr;}
};


class B : public A{
	private:
		int b_attr;
	public:
		void SetB(int val_b){  b_attr = val_b;}
		int GetB(){ return b_attr;}
		void SetAB(int val_a, int val_b);
		void PrintAB();
};

void B::SetAB(int val_a, int val_b){
	B::SetA(val_a);
	B::b_attr = val_b;
}

void B::PrintAB(){
	std::cout << B::GetA() << ", " << B::GetB() << std::endl;

}


class C : public B {
	private:
		int c_attr;
	public:
		void SetC(int val_c){ c_attr = val_c ; }
		int GetC(){ return c_attr; }
		void SetABC(int val_a, int val_b, int val_c);
		void PrintABC();
};


void C::SetABC(int val_a, int val_b, int val_c){
	C::SetAB(val_a, val_b);
	C::SetC(val_c);
}

void C::PrintABC(){
	std::cout << C::GetA() << ", " << C::GetB() << ", " << C::GetC() << std::endl;
}


int main(){

	B b;
	b.SetAB(3, 3);
	b.PrintAB();
	
	C c;
	c.SetABC(1, 2, 3);
	c.PrintABC();

}
