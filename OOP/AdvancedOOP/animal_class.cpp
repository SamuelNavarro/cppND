#include <iostream>

class Animal{
	protected:
		std::string color, name;
		int age;
	public:
		void SetColor(std::string c){ color = c; }
		void SetName(std::string n){ name = n; }
		void SetAge(int _age){ age = _age; } // I don't know if I like this convention better.
		std::string GetColor(){ return color; }
		std::string GetName(){ return name; }
		int GetAge(){ return age; }
};


class Snake : public Animal{
	private: 
		int length;
	public:
		void SetLength(int _length){ length = _length; }
		int GetLength(){ return length; }
};


class Cat : public Animal{
	private:
		int height;
	public:
		void SetHeight(int _height){ height = _height; }
		int GetHeight(){ return height; }
};



int main(){
	Snake s;
	s.SetAge(3);
	s.SetName("Python");
	s.SetColor("Green");

	Cat c;
	c.SetAge(3);
	c.SetName("catty");
	c.SetColor("Brown");
	c.SetHeight(15);

	std::cout << "Cat attrs: " << std::endl;
	std::cout << "Edad: " << c.GetAge() << std::endl;
	std::cout << "Nombre: " << c.GetName() << std::endl;
	std::cout << "Color: " << c.GetColor() << std::endl;
	std::cout << "Height: " << c.GetHeight() << std::endl;


}
