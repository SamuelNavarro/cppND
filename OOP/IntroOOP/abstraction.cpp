#include <iostream>
// Define Abstraction class
class Abstraction {
    // Define private attributes
    private:
        double a, b;
    // Define public setter and printing functions
    public:

        // This method allows us to set the values of  
        // private class members

        void SetValues(double first, double second){
            a = first;
            b = second;
        }

        // This method displays to the screen private
        // class members

        void DisplayValues(){
            std::cout << "Value of a: " << a << "\n";
            std::cout << "Value of b: " << b << "\n";
        }

};
// Test in main()
int main() {
    Abstraction a;
    a.SetValues(3.14, 42);
    a.DisplayValues();
    
}
