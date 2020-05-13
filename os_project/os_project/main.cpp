#include <string>
#include <deque>
#include <fstream>
#include <queue>


#include <Process.h>
#include <Shedule.h>
#include <stdio.h>


#include <FCFS.h>
#include <ProcessReader.h>


using namespace std;

int main () {

	Reader* reader = new Reader("test1.txt");

	int memorySize = reader -> getMemorySize();
	int pageSize = reader -> getPageSize();
	int roundRobinQ = reader -> getRoundRobinQ();
	int contextSwitch = reader -> getContextSwitch();
	deque < Process > processes = reader -> getAllProcesses();


	
	return 0;
}
