#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <time.h>
#include <sstream>
#include <iomanip>


#include "SysInfo.h"
#include "ProcessContainer.h"



void writeSysInfoToConsole(SysInfo sys, WINDOW* sys_win)
{
    sys.setAttributes();

    mvwprintw(sys_win,2,2,getCString(( "OS: " + sys.getOSName())));
    mvwprintw(sys_win,3,2,getCString(( "Kernel version: " + sys.get_kernel_version())));
    mvwprintw(sys_win,4,2,getCString( "CPU: "));
    wattron(sys_win,COLOR_PAIR(1));
    wprintw(sys_win,getCString(Util::getProgressBar(sys.get_cpu_percent())));
    wattroff(sys_win,COLOR_PAIR(1));
    mvwprintw(sys_win,5,2,getCString(( "Other cores:")));
    wattron(sys_win,COLOR_PAIR(1));
    std::vector<std::string> val = sys.get_cores_stats();
    for (int i = 0; i < val.size(); i++) {
        mvwprintw(sys_win,(6+i),2,getCString(val[i]));
    }
    wattroff(sys_win,COLOR_PAIR(1));
    mvwprintw(sys_win,10,2,getCString(( "Memory: ")));
    wattron(sys_win,COLOR_PAIR(1));
    wprintw(sys_win,getCString(Util::getProgressBar(sys.get_mem_percent())));
    wattroff(sys_win,COLOR_PAIR(1));
    mvwprintw(sys_win,11,2,getCString(( "Total Processes:" + sys.get_total_proc())));
    mvwprintw(sys_win,12,2,getCString(( "Running Processes:" + sys.get_running_proc())));
    mvwprintw(sys_win,13,2,getCString(( "Up Time: " + Util::convertToTime(sys.get_up_time()))));

}
