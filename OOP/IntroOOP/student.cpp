#include <iostream>

class Student {
	private:
		std::string name;
		unsigned int grade;
		float gpa;
	public:
		Student(std::string name, unsigned int grade, float gpa) : 
			name(name), grade(grade), gpa(gpa){

				if(gpa < 0.0 || gpa > 4.0){
					throw "Invalid gpa";
				}

				if(grade < 1 || grade > 12){
					throw "Invalid grade";	
				}
			
			};
		
		std::string Name(){return name;}
		unsigned int Grade() const {return grade;}
		float GPA() const {return gpa;}

		void SetName(std::string newname){ name = newname; }

		void SetGrade(unsigned int newgrade){
			if(newgrade < 1 || newgrade > 12){
				throw "Invalid grade";	
			}
			grade = newgrade; 
		}

		void SetGPA(float newgpa){ 
			if(gpa < 0.0 || gpa > 4.0){
				throw "Invalid gpa";
			}
			gpa = newgpa; 
		}
};


int main(){
	Student samuel("samuel", 10, 4);
	std::cout << "Student: " << samuel.Name() << std::endl;
	std::cout << "Student: " << samuel.Grade() << std::endl;
	std::cout << "Student: " << samuel.GPA() << std::endl;
	samuel.SetGrade(1234);
}
