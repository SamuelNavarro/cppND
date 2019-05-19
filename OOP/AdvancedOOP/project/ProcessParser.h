#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <unistd.h>


#include "constants.h"
#include "util.h"

using namespace std;

class ProcessParser{
	private:
		std::ifstream stream;
    public:
		static string getCmd(string pid);
		static vector<string> getPidList();
		static string getVmSize(string pid);  // Check
		static string getCpuPercent(string pid);
		static long int getSysUpTime();
		static string getProcUpTime(string pid);
		static string getProcUser(string pid);
		static vector<string> getSysCpuPercent(string coreNumber = "");
		static float getSysRamPercent();
		static string getSysKernelVersion();
		static int getTotalThreads();
		static int getTotalNumberOfProcesses();
		static int getNumberOfRunningProcesses();
		static string getOSName();
		static string PrintCpuStats(vector<string> values1, vector<string>values2);
		static bool isPidExisting(string pid);
};



// TODO: Define all of the above functions below:
string ProcessParser::getVmSize(string pid){
	string line, value;
	string name = "VmData";
	float result;

	ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));

	value = Util::processFiles(line, stream, name);	
	result = (stof(value)/float(1024));
	return to_string(result);
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



int ProcessParser::getNumberOfRunningProcesses(){
	string line, value;
	int result;
	string name = "procs_running";
	ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));

	value = Util::processFiles(line, stream, name);
	result = stoi(value);
	return result;
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
	string line, value;
	string name = "Uid:";
	string result = "";

	ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));

	value = Util::processFiles(line, stream, name); 

	stream = Util::getStream("/etc/passwd");

	// Differences when you don't use parenthesis:
	// name = "x:" + value;
	name = ("x:" + value);
	
	while(getline(stream, line)){
		// string::find returns npos if no substring is found
		if(line.find(name) != string::npos){
			result = line.substr(0, line.find(":"));
			return result;
		}
	}
	return "";
}





