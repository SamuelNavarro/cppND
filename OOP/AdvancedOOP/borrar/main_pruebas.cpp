#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cerrno>
#include <dirent.h>


#include "../project/constants.h"
#include "../project/util.h"

using namespace std;



int getNumberOfRunningProcesses(){
	string line;
	string name = "procs_running";
	vector<string> values;
	ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));

	values = Util::processFiles(line, stream, name);
	return stoi(values[1]);
}


string getVmSize(string pid){
	string line;
	string name = "VmData";
	vector<string> values;

	ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));

	values = Util::processFiles(line, stream, name);	
	return to_string(stof(values[1])/float(1024));
}



vector<string> getSysCpuPercent(string coreNumber = ""){
	string line;
	string name = "cpu" + coreNumber;
	vector<string> values;
	ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));

	values = Util::processFiles(line, stream, name);
	return values;
}


float getSysRamPercent(){

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


string getSysKernelVersion(){
	string name = "Linux version ";
	ifstream stream = Util::getStream((Path::basePath() + Path::versionPath()));
	string line;
	vector<string> version = Util::processFiles(line, stream, name);
	return version[2];
}



// why using erase-remove idiom:
// https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
// https://en.wikipedia.org/wiki/Erase-remove_idiom
string getOSName(){
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


vector<string> getPidList(){
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


int getTotalThreads(){
	vector<string> pidlist = getPidList();
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


int getTotalNumberOfProcesses(){
	string line;
	string name = "processes";

	ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));

	vector<string> values = Util::processFiles(line, stream, name);
	return stoi(values[1]);

}

int main(){
	
	int threds = getTotalThreads();
	std::cout << threds << "\n" << std::endl;

	int procs = getTotalNumberOfProcesses();

	std::cout << "processes: " << procs << std::endl;

}
