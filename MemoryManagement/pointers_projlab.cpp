#include <iostream>


template <class T, int size>
bool Pointer<T, size>::collect(){

  bool memfreed = false;
	typename std::list<PtrDetails<T>>::iterator p;
	do {
		// Scan refContainer looking for unreferenced pointers.
		for (p = refContainer.begin(); p != refContainer.end(); p++){

		// TODO: Implement collect()
		// If in-use, skip.
		if (p->refcount > 0)
			continue;
	  memfreed = true;
		
		// Remove unused entry from refContainer.
		refContainer.remove(*p);

		// Free memory unless the Pointer is null.
	  if (p->memPtr){

			if(p->isArray){
				delete[] p->memPtr;
			}else{
				delete p->memPtr;
			}

		}
		// Restart the search.
			break;
		}
	} while ( p != refContainer.end());
	return memfreed;
}





//Destructor of Pointer
template <class T, int size>
Pointer<T, size>::~Pointer(){
  typename std::list<PtrDetails<T>>::iterator p;
	p = findPtrInfo(addr);
	if(p->refcount)
		p->refcount--;
	collect();
  // TODO: Finalize Pointer destructor
  // decrement ref count
  
  // Collect garbage when a pointer goes out of scope.

  // For real use, you might want to collect unused memory less frequently,
  // such as after refContainer has reached a certain size, after a certain number of Pointers have gone out of scope,
  // or when memory is low.


}


template <class T>
class PtrDetails {
  //all attributes and methods are going to be public
	//because they are going to be used by other classes
  public:
		int refcount;
		T* memPtr;
		bool isArray;
		int arraySize;
		PtrDetails(T* ptr, int size_=0){ 
	    if(size_>0){ isArray = true; }
		}
};


template <class T>
bool operator==(const PtrDetails<T> &obj_1,
		            const PtrDetails<T> &obj_2)
{
  return obj_1.memPtr == obj_2.memPtr;
}
