#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>

#include "constants.h"
#include "util.h"


using namespace std;


class ProcessParser{
	private:
		std::ifstream stream;
    public:
		static string getCmd(string pid);
		static vector<string> getPidList();
		static std::string getVmSize(string pid);
		static std::string getCpuPercent(string pid);
		static long int getSysUpTime();
		static std::string getProcUpTime(string pid);
		static string getProcUser(string pid);
		static vector<string> getSysCpuPercent(string coreNumber = "");
		static float getSysRamPercent();
		static string getSysKernelVersion();
		static int getTotalThreads();
		static int getTotalNumberOfProcesses();
		static int getNumberOfRunningProcesses();
		static string getOSName();
		static std::string PrintCpuStats(std::vector<std::string> values1, std::vector<std::string>values2);
		static bool isPidExisting(string pid);
};



// TODO: Define all of the above functions below:
std::string getVmSize(std::string pid){
	std::string line;
	std::string name = "VmData";
	std::string value;
	float result;
	
	std::ifstream stream = Util::getStream(Path::basePath() + pid + Path::statPath());

	while(std::getline(stream, line)){
		if( line.compare(0, name.size(), name) == 0){
			std::istringstream buf(line);
			std::istream_iterator<std::string> beg(buf), end;
			std::vector<std::string> values(beg, end);	
		}
	}


}



long int ProcessParser::getSysUpTime(){
	std::ifstream uptime = Util::getStream(Path::upTimePath());
	 
}
