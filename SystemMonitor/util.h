#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;
// Classic helper function
class Util {

public:

static string convertToTime ( long int input_seconds );
static string getProgressBar(std::string percent);
static ifstream getStream(string path);
static vector<string> processFiles(string line, ifstream& stream, string name);
};


vector<string> Util::processFiles(string line, ifstream& stream, string name){
    while(getline(stream, line)){
        if(line.compare(0, name.size(), name) == 0){
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            return values;
			break;
        }
    };
    return (vector<string>());
}


string Util::convertToTime (long int input_seconds){
long minutes = input_seconds / 60;
long hours = minutes / 60;
long seconds = int(input_seconds%60);
minutes = int(minutes%60);
std::string result = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
return result;
}
// constructing string for given percentage
// 50 bars is uniformly streched 0 - 100 %
// meaning: every 2% is one bar(|)
string Util::getProgressBar(std::string percent){

    std::string result = "0%% ";
    int _size= 50;
    int  boundaries;
    try {
        boundaries = (stof(percent)/100)*_size;
    } catch (...){
    boundaries = 0;
    }

    for(int i=0;i<_size;i++){
        if(i<=boundaries){
        result +="|";
        }
        else{
        result +=" ";
        }
    }

    result +=" " + percent.substr(0,5) + " /100%%";
    return result;
}

// wrapper for creating streams

ifstream Util::getStream(string path){
    ifstream stream(path);
    if (!stream){
        throw runtime_error("Non - existing PID");
    }
    return stream;
}

