#include <string>
#include <deque>
#include <fstream>
#include <queue>

#include <iostream>

#include <Process.h>
#include <Shedule.h>
#include <stdio.h>
#include <algorithm>

#include <MagicAlgorithm.h>
#include <ProcessReader.h>


using namespace std;

string printFormat (deque <Shedule> sheduler) {
	string output = "";
	for (auto shedule: sheduler) { // same as for (int i = 0; i < sheduler.size(); i++)
		if (shedule.id >= 0) {
			output += "Process id:\t" + to_string(shedule.id);
			output += "\t\t\tarival time: " +  to_string(shedule.arrivalTime);
			output += "\t\t\tstart time: " +  to_string(shedule.startExc);
			output += "\t\tend time: " +  to_string(shedule.endExc);
			output += '\n';
		}
		else if (shedule.id == -1)
			output += "context switch:\n";
		else 
			output += "empty\n";


	}

	return output + "\n\n";
}


int main () {

	Reader* reader = new Reader("test1.txt");

	int memorySize = reader -> getMemorySize();
	int pageSize = reader -> getPageSize();
	int roundRobinQ = reader -> getRoundRobinQ();
	int contextSwitch = reader -> getContextSwitch();
	deque < Process > processes = reader -> getAllProcesses();

	deque <Shedule> sheduler;

	MagicAlgorithm* magic2 = new MagicAlgorithm (processes, contextSwitch);

	cout << "RR" << endl;
	magic2 -> runRoundRobi(roundRobinQ);
	sheduler = magic2 -> getSheduler();
	cout << printFormat (sheduler);


	MagicAlgorithm* magic1 = new MagicAlgorithm (processes, contextSwitch);
	magic1 -> runSJF();
	sheduler = magic1 -> getSheduler();
	cout << "SJF" << endl;
	cout << printFormat (sheduler);




	MagicAlgorithm* magic = new MagicAlgorithm (processes, contextSwitch);

	cout << " FCFS " << endl;
	magic -> runFCFS();
	sheduler = magic -> getSheduler();
	cout << printFormat (sheduler);







	return 0;
}
