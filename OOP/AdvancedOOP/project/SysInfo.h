#include <vector>
#include <string>



#include "ProcessParser.h"

using namespace std;

class SysInfo {
	private:
		vector<string> lastCpuStats;
		vector<string> currentCpuStats;
		vector<string> coresStats;
		vector<vector<string>> lastCpuCoresStats;
		vector<vector<string>> currentCpuCoresStats;
		string cpuPercent;
		float memPercent;
		string OSname;
		string kernelVer;
		long upTime;
		int totalProc;
		int runningProc;
		int threads;

	public:
		SysInfo(){
			this->getOtherCores(getNumberOfCores());
			this->setLastCpuMeasures();
			this->setAttributes();
			this-> OSname = ProcessParser::getOSName();
			this-> kernelVer = ProcessParser::getSysKernelVersion();
		}
		void setAttributes();
		void setLastCpuMeasures();
		string getMemPercent() const;
		long getUpTime() const;
		string getThreads() const;
		string getTotalProc() const;
		string getRunningProc() const;
		string getKernelVersion() const;
		string getOSName() const;
		string getCpuPercent() const;
		void getOtherCores(int _size);
		void setCpuCoresStats();
		vector<string> getCoresStats() const;
};


void SysInfo::getOtherCores(int _size){
	this->coresStats = vector<string>();
	this->coresStats.resize(_size);
	this->lastCpuCoresStats = vector<vector<string>>();
	this->lastCpuCoresStats.resize(_size);
	this->currentCpuCoresStats = vector<vector<string>>();
	this->currentCpuCoresStats.resize(_size);

	for(int i=0; i<_size; i++){
		this->lastCpuCoresStats[i] = ProcessParser::getSysCpuPercent(to_string(i));
	}
}


void SysInfo::setCpuCoresStats(){
	for(int i=0; i<this->currentCpuCoresStats.size(); i++){
		this->currentCpuCoresStats[i] = ProcessParser::getSysCpuPercent(to_string(i));	
	}
	for(int i=0; i<this->currentCpuCoresStats.size(); i++){
		this->coresStats[i] = ProcessParser::PrintCpuStats(this->lastCpuCoresStats[i], this->currentCpuCoresStats[i]);
	}
	this->lastCpuCoresStats = this->currentCpuCoresStats;
}


void SysInfo::setAttributes(){
	this-> memPercent = ProcessParser::getSysRamPercent();
	this-> upTime = ProcessParser::getSysUpTime();
	this-> totalProc = ProcessParser::getTotalNumberOfProcesses();
	this-> runningProc = ProcessParser::getNumberOfRunningProcesses();
	this-> threads = ProcessParser::getTotalThreads();
	this-> currentCpuStats = ProcessParser::getSysCpuPercent();
	this-> cpuPercent = ProcessParser::PrintCpuStats(this->lastCpuStats, this->currentCpuStats);
	this-> lastCpuStats = this->currentCpuStats;
	this-> setCpuCoresStats();
}


vector<string> SysInfo::getCoresStats() const {
	vector<string> result = vector<string>();
	for(int i=0; i<this->coresStats.size(); i++){
		string temp = ("cpu" + to_string(i) + ": ");
		float check = stof(this->coresStats[i]);
		if(!check || this->coresStats[i] == "nan"){
			return vector<string>();	
		}
		temp += Util::getProgressBar(this->coresStats[i]);
		result.push_back(temp);
	}
	return result;
}


string SysInfo::getCpuPercent() const
{
	return this->cpuPercent;
}


string SysInfo::getMemPercent() const
{
	return to_string(this->memPercent);
}


long SysInfo::getUpTime() const
{
	return this->upTime;
}


string SysInfo::getKernelVersion() const
{
	return this->kernelVer;
}


string SysInfo::getTotalProc() const
{
	return to_string(this->totalProc);
}


string SysInfo::getRunningProc() const
{
	return to_string(this->runningProc);
}


string SysInfo::getThreads() const
{
	return to_string(this->threads);
}


string SysInfo::getOSName() const
{
	return this->OSname;
}


void SysInfo::setLastCpuMeasures()
{
	this->lastCpuStats = ProcessParser::getSysCpuPercent();
}
