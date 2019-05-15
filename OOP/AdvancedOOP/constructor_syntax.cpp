#include <iostream>
#include <string>

class InitList {
	private:
		int &ref;
		const char c;
	public:
		InitList(int &_ref, char _c) : ref(_ref), c(_c) {}
		void print(){
			std::cout << ref << " " << c << std::endl;
		}
};

int main(){
	int var = 10;
	InitList obj(var, 'A');
	obj.print();
	// Referenced variable:
	var += 10;
	obj.print();
}
