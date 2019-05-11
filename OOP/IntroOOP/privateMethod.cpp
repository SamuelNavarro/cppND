#include <iostream>

class Abstract{
	private:
		int number;
		char character;
		void ProcessAttributes();

	public:
		void SetMyValues(int newnumber, char newcharacter);
		void GetMyValues(void);

};


void Abstract::ProcessAttributes(){
	Abstract::number *= 6;
	Abstract::character++;
}

void Abstract::SetMyValues(int newnumber, char newcharacter){
	number = newnumber;
	character = newcharacter;
}


void Abstract::GetMyValues(void){
	Abstract::ProcessAttributes();
	std::cout << "Number is: " << Abstract::number << std::endl;
	std::cout << "Character is: " << Abstract::character << std::endl;
}



int main(){
	Abstract a;
    a.SetMyValues(100, 'X');
    a.GetMyValues();
    a.GetMyValues();
}
