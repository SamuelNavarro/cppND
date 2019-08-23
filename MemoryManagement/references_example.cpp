#include <iostream>
#include <string>


void addSpaces(const char * &str1) { 
    // we are declaring new pointer for storage of new spaces (characters)
    char *temp = new char(sizeof(str1)*2);
    // Because we are going to move our input pointer
    // during our modification we need to remember our start address
		
    char *start = temp;

    // moving our pointer to the end of array of character
		
    while(*str1 != '\0'){
        // using pointer arithmetics
        // copying value of str1 to memory location where temp is pointing
        // after that we are moving through array with these two pointers
        *temp++ = *str1++;
        // after saving the string value to new allocated space 
        // we are adding space character and moving 
        // one more place to prepare our pointer to new string value
        *temp++ = ' ';
    }
    // resetting our original pointer to start address
    str1 = start;
}



int main(){

  std::string str = "Hello world";

	const char* ptr = str.c_str();

  std::cout << "string is: " << ptr << std::endl;
	std::cout << "string adress: " << &ptr << std::endl;

	// addSpaces is just going to perform operations on the
	// address on the string. 
  addSpaces(ptr);	

	std::cout << "string is: " << ptr << std::endl;
	std::cout << "string adress: " << &ptr << std::endl;


}
