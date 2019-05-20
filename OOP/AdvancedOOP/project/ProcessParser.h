#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <cstring>
#include <cerrno>
#include <algorithm>
#include <experimental/filesystem>


#include "constants.h"
#include "util.h"


using namespace std;


class ProcessParser{
	private:
		std::ifstream stream;
    public:
		static string getCmd(string pid); //Check
		static vector<string> getPidList();  //Check
		static string getVmSize(string pid);  // Check
		static string getCpuPercent(string pid);  //check
		static long int getSysUpTime();   //check
		static string getProcUpTime(string pid); //check
		static string getProcUser(string pid); //check
		static int getNumberCores(); //check
		static vector<string> getSysCpuPercent(string coreNumber=""); //Check
		static float getSysRamPercent(); //check
		static string getSysKernelVersion(); //check
		static int getTotalThreads(); //check
		static int getTotalNumberOfProcesses();
		static int getNumberOfRunningProcesses(); //check
		static string getOSName(); //check
		static string PrintCpuStats(vector<string> values1, vector<string>values2); //check
		static bool isPidExisting(string pid);
};



// TODO: Define all of the above functions below:
string ProcessParser::getVmSize(string pid){
	string line;
	string name = "VmData";
	vector<string> values;

	ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));

	values = Util::processFiles(line, stream, name);	
	return to_string(stof(values[1])/float(1024));
}



string ProcessParser::getCpuPercent(string pid){
	string line;
	float result;

	ifstream stream = Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
	getline(stream, line);
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> values(beg, end);

	float utime = stof(ProcessParser::getProcUpTime(pid));
	float stime = stof(values[14]);
	float cutime = stof(values[15]);
	float cstime = stof(values[16]);
	float starttime = stof(values[21]);

	float uptime = ProcessParser::getSysUpTime();
	float freq = sysconf(_SC_CLK_TCK);


	float total = stime + cutime + cstime + utime;
	float seconds = uptime - (starttime/freq);
	
	result = 100.0 * ((total/freq)/seconds);

	return to_string(result);
}


string ProcessParser::getProcUpTime(string pid){
	string line;
	ifstream stream = Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
	getline(stream, line);
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> values(beg, end);
	return to_string(float(stof(values[13])/sysconf(_SC_CLK_TCK)));
}



long int ProcessParser::getSysUpTime(){
	string line;
	long int result;

	ifstream stream = Util::getStream((Path::basePath() + Path::upTimePath()));
	getline(stream, line);
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> values(beg, end);
	result = stol(values[0]);
	return result;
}



string ProcessParser::getProcUser(string pid){
	string line;
	string name = "Uid:";
	string result = "";
	vector<string> values;

	ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));

	values = Util::processFiles(line, stream, name);


	stream = Util::getStream("/etc/passwd");

	// Differences when you don't use parenthesis:
	// name = "x:" + value;
	name = ("x:" + values[1]);
	
	while(getline(stream, line)){
		// string::find returns npos if no substring is found
		if(line.find(name) != string::npos){
			result = line.substr(0, line.find(":"));
			return result;
		}
	}
	return "";
}



vector<string> ProcessParser::getPidList(){
	DIR* dir;

	vector<string> container;
	if(!(dir = opendir("/proc")))
		throw std::runtime_error(std::strerror(errno));

	while(dirent* dirp = readdir(dir)){
		if(dirp->d_type != DT_DIR)
			continue;

		if (all_of(dirp->d_name, dirp->d_name + std::strlen(dirp->d_name), [](char c) { return std::isdigit(c); })){
			container.push_back(dirp->d_name);
		}
	}

	if(closedir(dir))
		throw std::runtime_error(std::strerror(errno));
	return container;

}


string ProcessParser::getCmd(string pid){
	string line;
	ifstream stream = Util::getStream((Path::basePath() + pid + Path::cmdPath()));
	getline(stream, line);
	return line;
}



int ProcessParser::getNumberCores(){
	string line;
	string name = "cpu cores";
	ifstream stream = Util::getStream(Path::basePath() + "cpuinfo"); 


	vector<string> values = Util::processFiles(line, stream, name);
	return stoi(values[3]);
}



vector<string> ProcessParser::getSysCpuPercent(string coreNumber){
	string line;
	string name = "cpu" + coreNumber;
	vector<string> values;
	ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));

	values = Util::processFiles(line, stream, name);
	return values;
}



float getSysActiveCpuTime(vector<string> values)
{
    return (stof(values[S_USER]) +
            stof(values[S_NICE]) +
            stof(values[S_SYSTEM]) +
            stof(values[S_IRQ]) +
            stof(values[S_SOFTIRQ]) +
            stof(values[S_STEAL]) +
            stof(values[S_GUEST]) +
            stof(values[S_GUEST_NICE]));
}

float getSysIdleCpuTime(vector<string>values)
{
    return (stof(values[S_IDLE]) + stof(values[S_IOWAIT]));
}



string ProcessParser::PrintCpuStats(vector<string> values1, vector<string>values2){

	float activeTime = getSysActiveCpuTime(values2) - getSysActiveCpuTime(values1);
	float idleTime = getSysIdleCpuTime(values2) - getSysIdleCpuTime(values1);
	float totalTime = activeTime + idleTime;
	float result = 100.0*(activeTime / totalTime);
	return to_string(result);

}



float ProcessParser::getSysRamPercent(){

	ifstream stream1 = Util::getStream((Path::basePath() + Path::memInfoPath()));
	ifstream stream2 = Util::getStream((Path::basePath() + Path::memInfoPath()));
	ifstream stream3 = Util::getStream((Path::basePath() + Path::memInfoPath()));

	string line;
	string name1 = "MemAvailable:";
	string name2 = "MemFree:";
	string name3 = "Buffers:";

	float totalMem = 0;
	float freeMem = 0;
	float buffers = 0;

	vector<string> values1 = Util::processFiles(line, stream1, name1);
	totalMem = stof(values1[1]);

    vector<string> values2 = Util::processFiles(line, stream2, name2);
	freeMem = stof(values2[1]);

	vector<string> values3 = Util::processFiles(line, stream3, name3);
	buffers = stof(values3[1]);

	return float(100.0*(1 - (freeMem/(totalMem-buffers))));

}


string ProcessParser::getSysKernelVersion(){
	string name = "Linux version ";
	ifstream stream = Util::getStream((Path::basePath() + Path::versionPath()));
	string line;
	vector<string> version = Util::processFiles(line, stream, name);
	return version[2];
}


// why using erase-remove idiom:
// https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
// https://en.wikipedia.org/wiki/Erase-remove_idiom
string ProcessParser::getOSName(){
	string line;
	string name = "PRETTY_NAME="; 

	ifstream stream = Util::getStream(("/etc/os-release"));

	while(getline(stream, line)){
		if(line.compare(0, name.size(), name) == 0){
			// https://en.cppreference.com/w/cpp/string/basic_string/find
			// size_type can represent any posible string size.
			string::size_type res = line.find("=");
			res++; // Interesante este truco
			// ya que res es un número que representa la posición,
			// al aumentarlo eliminamos el =
			if(res == string::npos) {
				std::cout << "OS Name not found" << std::endl;
			} else {
				string output = line.substr(res);	
			    output.erase(remove(output.begin(), output.end(), '"'), output.end());
				return output;
			}
		} // end of if
	} // End of while
	return "";
}


int ProcessParser::getTotalThreads(){
	vector<string> pidlist = ProcessParser::getPidList();
	int total = 0;

	for(string& pid : pidlist){
		ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));
		string name = "Threads:"; 
		string line;
		vector<string> values = Util::processFiles(line, stream, name);	
		int value = stoi(values[1]);
		total += value;
	}
	return total;
}



int ProcessParser::getNumberOfRunningProcesses(){
	string line;
	string name = "procs_running";
	ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));

	vector<string> values = Util::processFiles(line, stream, name);
	return stoi(values[1]);
}


int ProcessParser::getTotalNumberOfProcesses(){
	string line;
	string name = "processes";

	ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));

	vector<string> values = Util::processFiles(line, stream, name);
	return stoi(values[1]);

}
