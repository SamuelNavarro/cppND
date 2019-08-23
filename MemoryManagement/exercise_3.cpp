#include <iostream>

int* createArr(int size){
	int* ptr = new int[size];
	return ptr;
}


int* resizeArr(int* ptr, int expandPlaces, int _size){

  int* newArr = new int[_size + expandPlaces];

	for(int i=0; i<_size; i++){
	  newArr[i] = ptr[i];
	}

	delete [] ptr;
	return newArr;

}


int main(){
	int size;
	int newSize;
	std::cout << "Input size of new array: " << std::endl;
	std::cin >> size;

	int* ptr = createArr(size);
	for(int i=0; i<size; i++){
	  ptr[i] = i;
	}

	std::cout << "Created array: " << std::endl;
	for(int i = 0; i<size; i++){
		std::cout << ptr[i] << std::endl;
	}

  std::cout << "Number of expansions to our previous array: "  << std::endl;
	std::cin >> newSize;

  ptr = resizeArr(ptr, newSize, size);	

	std::cout << "New array: " << std::endl;
	for(int i=0; i<(size + newSize); i++){
	  std::cout << ptr[i] << std::endl;
	}

	delete [] ptr;
	return 0;

}
