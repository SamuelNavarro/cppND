#include <string>
#include <vector>
#include <fstream>

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
