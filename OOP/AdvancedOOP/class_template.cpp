#include <iostream>
#include <vector>

template <typename T>
class Container {
	std::vector<T> arr;
	int s;
	public:
		Container() : s(0){ arr.clear();}
		int size(void) const {
			return Container::s;
		}
		void add(T el)
		{
			Container::s++;
			arr.push_back(el);
		}
		void print(void)
		{
			for (T i : arr){
				std::cout << i << std::endl;
			}
			std::cout << "Container::size: " << Container::s << std::endl;
		}
};


int main(){
	Container<double> obj;
	obj.add(2.00329132);
	obj.print();
	obj.add(8.83);
	obj.print();
	std::cout << "size" << std::endl;
	int tam = obj.size();
	std::cout << tam << std::endl;
	std::cout << "Probando con otro tipo" << std::endl;

	Container<std::string> obj_char;
	obj_char.add("A");
	obj_char.print();	
	obj_char.add("Samuel");
	obj_char.print();
	return 0;
}

