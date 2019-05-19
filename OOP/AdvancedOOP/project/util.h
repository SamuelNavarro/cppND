#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

class Util{
	public:
		static std::string convertToTime( long int input_seconds );
		static std::string getProgressBar(std::string percent);
		static std::ifstream getStream(std::string path);
		static std::string processFiles(std::string line, std::ifstream& stream, std::string name);
};


std::string Util::processFiles(std::string line, std::ifstream& stream, std::string name){
	std::string result;
	while(getline(stream, line)){
		if(line.compare(0, name.size(), name) == 0){
			std::istringstream buf(line);
			std::istream_iterator<std::string> beg(buf), end;
			std::vector<std::string> values(beg, end);
			result = values[1];
			break;
		}
	};
	return result;
}


std::string Util::convertToTime(long int input_seconds){
	long minutes = input_seconds / 60;
	long hours = minutes / 60;
	long seconds = int(input_seconds%60);
	minutes = int(minutes%60);
	std::string result = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
	return result;
}



// Constructing string for given percentage
// 50 bars uniformly streched 0 - 100 %
// meaning: every 2% is one bar (|)
std::string Util::getProgressBar(std::string percent){
	std::string result = "0%";
	int _size = 50;
	int boundaries = (stof(percent)/100)*_size;

	for(int i=0; i<_size; i++){
		if(i<=boundaries){
			result += "|";
		}
		else {
			result += " ";
		}
	}
	
	result += " " + percent.substr(0, 5) + " /100%";
	return result;
}


std::ifstream Util::getStream(std::string path){
	std::ifstream stream(path);
	if (!stream){
		throw std::runtime_error("Non - existing PID");
	}
	return stream;
}




