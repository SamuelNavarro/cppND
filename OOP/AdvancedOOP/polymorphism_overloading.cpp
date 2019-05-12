#include <iostream>

class Date{
	private:
		int day, month, year;
		std::string month_name;
	public:
		void SetDate(int day, int month, int year);
		int GetDay(){ return day;}
		int GetMonth(){ return month;}
		std::string GetMonthName(){return month_name;}
		int GetYear(){ return year;}
		std::string PrintDate(int day, std::string month_name, int year);
		std::string PrintDate(int day, int month, int year);
};

void Date::SetDate(int day, int month, int year){

	int day_numbers[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string month_names[]{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	if(year % 4 == 0 || year % 100 != 0 || year % 400 == 0){
		day_numbers[1]++;	
	}

	if(year < 1 || day < 1 || month < 1 || month > 12 || day > day_numbers[month - 1]){
		throw std::domain_error("Invalid date!");
	}

	Date::day = day;
	Date::month = month;
	Date::month_name = month_names[month - 1];
	Date::year = year;

}

std::string Date::PrintDate(int day, std::string month_name, int year){
	std::string result = month_name + " " + std::to_string(day) + ", " + std::to_string(year);
	std::cout << "Using string notation" << std::endl;
	return result;

}

std::string Date::PrintDate(int day, int month, int year){
	std::string result = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
	std::cout << "Using number notation"  << std::endl;
	return result;
}

int main(){
	Date date;
	date.SetDate(1, 10, 2019);
	std::cout << date.PrintDate(1, "Feb", 2003) << "\n";
	std::cout << date.PrintDate(1, 2, 2003) << "\n";
}
