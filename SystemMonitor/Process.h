#include <string>
#include "ProcessParser.h"
using std::string;


class Process {
    private:
        string pid;
        string user;
        string cmd;
        string cpu;
        string mem;
        string up_time;

    public:
        Process(string pid)
        {
            this->pid = pid;
            this->user = ProcessParser::getProcUser(pid);
            this->mem = ProcessParser::getVmSize(pid);
            this->cmd = ProcessParser::getCmd(pid);
            this->up_time = ProcessParser::getProcUpTime(pid);
            this->cpu  = ProcessParser::getCpuPercent(pid);
        }
        void setPid(int pid);
        string getPid() const;
        string getProcess();
};


void Process::setPid(int pid)
{
    this->pid = pid;
}



string Process::getPid() const 
{
    return this->pid;
}



string Process::getProcess()
{
	if(!ProcessParser::isPidExisting(this->pid))
		return "";
    this->mem = ProcessParser::getVmSize(this->pid);
    this->up_time = ProcessParser::getProcUpTime(this->pid);
    this->cpu = ProcessParser::getCpuPercent(this->pid);

    return (this->pid + "   "
                    + this->user
                    + "   "
                    + this->mem.substr(0,5)
                    + "     "
                    + this->cpu.substr(0,5)
                    + "     "
                    + this->up_time.substr(0,5)
                    + "    "
                    + this->cmd.substr(0,30)
                    + "...");
}
