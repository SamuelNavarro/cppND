#include "gc_pointer.h"
#include "LeakTester.h"

int main()
{
    Pointer<int> p = new int(19);
    Pointer<int> t = new int(21);
    Pointer<int> s = new int(28);
		Pointer<int> x, y;
		x = p;
		y = x;
		y.showlist();
		std::cout << "p value: " <<*p << std::endl;
		std::cout << " p address: " << p << std::endl;

    


    return 0;
}
