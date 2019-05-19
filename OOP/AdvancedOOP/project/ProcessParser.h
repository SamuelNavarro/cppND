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
		static string PrintCpuStats(vector<std::string> values1, vector<std::string>values2);
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



//string ProcessParser::getCpuPercent(string pid){
/*}*/


string ProcessParser::getProcUpTime(string pid){
	string line, result;
	ifstream stream = Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
	getline(stream, line);


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
	std::string line;
	long int result;

	ifstream stream = Util::getStream((Path::basePath() + Path::upTimePath()));
	getline(stream, line);
	istringstream buf(line);
	istream_iterator<string> beg(buf), end;
	vector<string> values(beg, end);
	result = stol(values[0]);
	return result;
}









