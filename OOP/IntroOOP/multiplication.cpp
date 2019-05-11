#include <iostream>
// Define class Multiply
class Multiply{
    // Define private attributes
    private:
        int a;
        int b;
    // Define public constructor, getters and setters
    // Define a function to multiply private attributes
    public:
        // class constructor
        Multiply(int a, int b){
            Multiply::a = a;
            Multiply::b = b;
        }
        // getters and setters
        int GetA() {
            return a;
        }

        void SetA(int a) {
            Multiply::a = a;
        }

        int GetB(){
            return b;
        }

        void SetB(int b) {
            Multiply::b = b;
        }

        // method for multiplying numbers
        int MultiplyNumbers(){
             return a*b;
        }
};

int main()
{
    Multiply m(5, 4);

    std::cout << "product = " << m.MultiplyNumbers() << "\n";
}
