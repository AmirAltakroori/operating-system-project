using namespace std;

class FCFS {

private:
	int cs;
	deque < Process > processes;
	deque < Shedule > sheduler;

	void runAlgorithm() {

		int time = 0;
	//	Shedule shedule = {0, 0, 0};

		while ( !processes.empty() ) {

			if (processes[0].cpuBurst <= 0) {

			}


			time++;
		}
		
	}


public:
	FCFS (int cs, deque <Process> processes) {
		this -> processes = processes;
		this -> cs = cs;

		runAlgorithm();
	}





};