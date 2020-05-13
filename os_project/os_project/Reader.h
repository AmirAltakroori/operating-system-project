#include <string>
#include <Process.h>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Reader {

private :
	char const * filePath;
	int memorySize;
	int pageSize;
	int roundRobinQ;
	int contextSwitch;
	deque < Process > processes;

public :
	Reader (string path) {
		filePath = path.c_str() ;
		readData();
	}

	void readData() {

		freopen	(filePath, "r", stdin);

		cin >> memorySize >> pageSize >> roundRobinQ >> contextSwitch;
		Process processIn;
		while (cin >> processIn.id >> processIn.arrivalTime >> processIn.cpuBurst >> processIn.processSize)
		{
			processes.push_back(processIn);
		}

	}

	int getMemorySize () {
		return memorySize;
	}

	int getPageSize () {
		return pageSize;
	}

	int getRoundRobinQ () {
		return roundRobinQ;
	}

	int getContextSwitch () {
		return contextSwitch;
	}

	deque < Process > getAllProcesses ()  {
		return processes;
	}

};
