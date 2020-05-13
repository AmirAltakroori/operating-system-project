using namespace std;

class FCFS {

private:
	int cs;
	deque < Process > processes;
	deque < Shedule > sheduler;
	queue < Process > watingQueue;

	void runAlgorithm() {

		int time = 0;
		Shedule shedule = {-1, -1, -1, -1};

		Process inProcess = getEmpetyProcess();

		while ( !processes.empty() || !watingQueue.empty() || inProcessing (inProcess) ) {

			updateWatingQueue(time);

			/** The processor is free */
			if (inProcess.id == -2 ) {

				/** There is whaing process */
				if ( !watingQueue.empty() ) {

					inProcess = watingQueue.front();
					watingQueue.pop();

					/** there was a real process needs switching */
					if ( !sheduler.empty()) {
						Shedule contextSwitch = performContextSwitchShedule (time);		//! time will be updated since it is called by reference
						sheduler.push_back(contextSwitch);

					}

				} else {
					inProcess.cpuBurst += inProcess.cpuBurst == 0;
				}

				startProcessingSheduling (shedule, inProcess, time);

			}


			inProcess.cpuBurst--;
			time++;

			/** The process is finshed */
			if (inProcess.cpuBurst == 0) {
				finishProcessingSheduling (shedule, inProcess, time);
			}

		}

	}

	bool inProcessing (Process inProcess) {
		return inProcess.id >= 0 && inProcess.cpuBurst > 0;
	}


	void startProcessingSheduling( Shedule& shedule, Process& inProcess, int time ) {
		shedule.arrivalTime = inProcess.arrivalTime;
		shedule.id = inProcess.id;
		shedule.startExc = time;
	}


	void finishProcessingSheduling ( Shedule& shedule, Process& inProcess, int time ) {
		shedule.endExc = time;
		if (!sheduler.empty() && shedule.id == sheduler.back().id)
			sheduler.back().endExc = shedule.endExc;
		else
			sheduler.push_back(shedule);
		restSehedule(shedule);			//! reset value of shedule
		inProcess = getEmpetyProcess();
	}


	void updateWatingQueue(int time) {
		while (!processes.empty() && processes[0].arrivalTime <= time) {
			watingQueue.push(processes[0]);
			processes.pop_front();
		}
	}


	Shedule performContextSwitchShedule(int& startTime) {

		Shedule shedule;
		shedule.startExc = startTime;
		startTime += cs;
		shedule.endExc = startTime;
		shedule.id = -1;
		shedule.arrivalTime = -1;

		return shedule;
	}

	Process getEmpetyProcess() {
		Process emptyProcess;
		emptyProcess.arrivalTime = -1;
		emptyProcess.id = -2;
		emptyProcess.cpuBurst = 1;
		emptyProcess.processSize = -1;
		return emptyProcess;
	}


	void restSehedule (Shedule& shedule) {
		shedule.id = -1;
		shedule.startExc = -1;
		shedule.endExc = -1;
		shedule.arrivalTime = -1;
	}

	bool comp (Process first, Process second) {
		return first.arrivalTime < second.arrivalTime;
	}


public:
	FCFS (deque <Process> processes, int cs) {

		//sort (processes.begin(), processes.end(), comp);

		this -> processes = processes;
		this -> cs = cs;

		runAlgorithm();
	}

	deque < Shedule > getSheduler() {
		return sheduler;
	}






};