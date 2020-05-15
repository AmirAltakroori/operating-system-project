using namespace std;

//! A MagicAlgorithm class.
/*!
CPU scheduler simulater.
This class simulate the CPU scheduler where it revices a list of processess,
then it can perform three different sheduling algorithm which are:
1- First Come First Serve
2- Round Ropin
3- Shortest Jop first

The implementation of the three algorithms is the same, but it different of the
behavior of the used STL data structure.
It provides a time sheduling after processesing tasks
*/
class MagicAlgorithm {

public:

	//! A constructor
	/*!
	a parametrized constructor 

	@param processes as a list of processe that need execution
	@param cs as a context switch value
	*/
	MagicAlgorithm (deque <Process> processes, int cs) {

		sort (processes.begin(), processes.end(), compInArrvial);

		this -> processes = processes;
		this -> cs = cs;
		this -> isTimeConsidered = true;
		this -> roundRobinQ = INT_MAX;

	}

	//! First Come First Serve Algorithm function
	/*!
	Public void function that perform the First Come First Serve Algorithm and fill
	the sheduler of the process history.
	This function use a priority queue that store data 
	based on arrival time in an increasing order.
	@param
	@return
	*/
	void runFCFS () {
		priority_queue<Process, vector<Process>, CompareProcess> temp(isTimeConsidered);
		watingQueue = temp;
		runAlgorithm();
	}

	//! Shortest Jop First Algorithm function
	/*!
	Public void function that perform the Shortest Jop First Algorithm and fill
	the sheduler of the process history.
	This function use a priority queue that store data 
	based on burset time in an increasing order.
	@param
	@return
	*/
	void runSJF () {
		priority_queue<Process, vector<Process>, CompareProcess> temp(!isTimeConsidered);
		watingQueue = temp;
		runAlgorithm();
	}

	//! Round Ropin Algorithm function
	/*!
	Public void function that perform the Round Ropin Algorithm and fill
	the sheduler of the process history.
	This function use a priority queue that store data and process it
	based on arrival time in an increasing order with a context switch.
	@param cs as a context switch
	@return
	*/
	void runRoundRobi (int roundRobinQ) {
		this -> roundRobinQ = roundRobinQ;
		priority_queue<Process, vector<Process>, CompareProcess> temp(isTimeConsidered);
		watingQueue = temp;
		runAlgorithm();
	}

	//! Getter function
	/*!
	public function that give the round sheduler table of the process for the caller
	@return deque < Shedule >: sheduler process table
	*/
	deque < Shedule > getSheduler () {
		return sheduler;
	}

private:

	/**
	A private vaiable.
	vairable has context switch value
	*/
	int cs;

	/**
	A private vaiable.
	vairable has list of processes that will processed
	*/
	deque < Process > processes;

	/**
	A private vaiable.
	vairable has list of shedule that store the history of exceuting processes
	*/
	deque < Shedule > sheduler;

	/**
	A private vaiable.
	vairable has round robin quantum value
	*/
	int roundRobinQ;

	/**
	A private vaiable.
	vairable to cheack that if the algorith give the arrival time hight priority
	*/
	bool isTimeConsidered;

	//! Function container
	/**
	A private vaiable contains function.
	vairable to carry the way of sorting data in priority queue
	*/
	struct CompareProcess { 

		//! Comparetor helper function
		/*!
		Private boolean function that used for define the priority_queue behavior 
		in storing and retreving data
		@param time as boolean cheacker flag.
		@return
		*/
		CompareProcess(): ordering(){}
		CompareProcess( bool time ) : ordering( time ) {}
		bool operator()(Process const& p1, Process const& p2) 
		{ 
			if(ordering)
				/** Order based on arrival time in increasing order */
				return p1.arrivalTime > p2.arrivalTime; 

			/** Order based on burst time in increasing order */
			return p1.cpuBurst > p2.cpuBurst; 
		} 
		bool ordering;
	};

	/**
	A private vaiable.
	vairable to store processes in sorted order based on condition
	*/
	priority_queue<Process, vector<Process>, CompareProcess> watingQueue;

	//! Main algorithm function
	/*!
	private boolean function that cheack if the executed process is
	a real process and needs processing
	@param inProcess as a current excuting process
	@return bool: true when eal process and needs processing
	*/
	void runAlgorithm () {

		/** initailze important variables */
		int time = 0;		
		Shedule shedule = {-3, -3, -3, -3};
		Process inProcess = getEmpetyProcess();
		int roundQ = roundRobinQ;

		/** Continue processesing until finshing processing  */
		while ( couldExecuting () || isInProcessing (inProcess) ) {

			updateWatingQueue(time);

			/** The processor is free from real process */
			if (inProcess.id == -2 ) {

				/** There is waiting processes */
				if ( !watingQueue.empty() ) {

					/** getting the top process on the waiting queue */
					inProcess = watingQueue.top();
					roundQ = roundRobinQ;
					watingQueue.pop();

					/** there was a real process needs switching */
					if ( !sheduler.empty() && sheduler.back().id >= 0 && inProcess.id != sheduler.back().id) {
						Shedule contextSwitch = performContextSwitchShedule (time);		//! time will be updated since it is called by reference
						sheduler.push_back(contextSwitch);
					}

				} else {
					//! The empty process still in the cpu
					inProcess.cpuBurst = 1; //! Give the empty process 1 unit time for excution
				}

				startProcessingSheduling (shedule, inProcess, time);

			}

			inProcess.cpuBurst--;
			time++;
			roundQ--;

			/** The process is finshed */
			if (inProcess.cpuBurst == 0 || roundQ == 0) {
				finishProcessingSheduling (shedule, inProcess, time, roundQ);
			}

		}

	}
	
	//! Flag helper function
	/*!
	private boolean function that cheack if the cpu 
	will not have more processes in the future
	@param
	@return bool: true when the waiting queue and processes are empty
	*/
	bool couldExecuting ()  {
		return !processes.empty() || !watingQueue.empty();
	}

	//! Flag helper function
	/*!
	private boolean function that cheack if the executed process is
	a real process and needs processing
	@param inProcess as a current excuting process
	@return bool: true when eal process and needs processing
	*/
	bool isInProcessing (Process inProcess) {
		return inProcess.id >= 0 && inProcess.cpuBurst > 0;
	}

	//! Helper function
	/*!
	private void function that makes the statring information demand
	by taking the process information
	and store it in the shedule
	@param shedule as a information container
	@param inProcess as a current excuting process
	@param time as a current excuting time
	@return
	*/
	void startProcessingSheduling ( Shedule& shedule, Process& inProcess, int time ) {
		shedule.arrivalTime = inProcess.arrivalTime;
		shedule.id = inProcess.id;
		shedule.startExc = time;
	}

	//! Helper function
	/*!
	private void function that makes the fishing information demand
	by storing the shedule in the sheduler,
	cheack if the process needs more execution and it reinitalize the process
	when it done
	@param shedule as a information container
	@param inProcess as a current excuting process
	@param time as a current excuting time
	@param roundQ as a round quantum time
	@return
	*/
	void finishProcessingSheduling ( Shedule& shedule, Process& inProcess, int time, int& roundQ) {

		shedule.endExc = time;		

		/** cheack if the last shedule in sheduler is the same of current process */
		if (!sheduler.empty() && shedule.id == sheduler.back().id && shedule.startExc == sheduler.back().endExc && shedule.id < 0)
			/** modify fishing time */
			sheduler.back().endExc = shedule.endExc;
		else
			/** add to sheduler */
			sheduler.push_back(shedule);

		/** cheack if the current process needs more processing */
		if (inProcess.cpuBurst > 0 && inProcess.id >= 0) {
			inProcess.arrivalTime = time;
			watingQueue.push(inProcess);
		} else {
			inProcess = getEmpetyProcess();
		}

		restSehedule(shedule);		//! reset value of shedule to prepare it for new process
		inProcess = getEmpetyProcess();
		roundQ = roundRobinQ;		//! restart the round of processing
	}
	
	//! Helper function
	/*!
	private void function that store all arrived process 
	on the wating queue
	@param time as a current excuting time
	@return
	*/
	void updateWatingQueue (int time) {
		while (!processes.empty() && processes[0].arrivalTime <= time) {
			watingQueue.push(processes[0]);
			processes.pop_front();
		}
	}

	//! Helper function
	/*!
	private returned function that perform the context switch
	process with chaing time of excution 
	and it returned valued shedule with id = -1
	@param time as a current excuting time
	@return Shedule: context switch shedule with id = -1
	*/
	Shedule performContextSwitchShedule (int& time) {

		Shedule shedule;
		shedule.arrivalTime = time;
		shedule.startExc = time;
		time += cs;
		shedule.endExc = time;
		shedule.id = -1;

		return shedule;
	}

	//! Helper function
	/*!
	private returned function that creat an empty process
	with unreal intial values
	@param 
	@return Shedule: empty process with id = -2
	*/
	Process getEmpetyProcess () {
		Process emptyProcess;
		emptyProcess.arrivalTime = -1;
		emptyProcess.id = -2;
		emptyProcess.cpuBurst = 1;
		emptyProcess.processSize = -1;
		return emptyProcess;
	}

	//! Helper function
	/*!
	private returned function that reset the shedule value
	with unreal intial values
	@param 
	@return Shedule: empty shedule with id = -1
	*/
	void restSehedule (Shedule& shedule) {
		shedule.id = -3;
		shedule.startExc = -3;
		shedule.endExc = -3;
		shedule.arrivalTime = -3;
	}

	//! Helper function
	/*!
	private returned function that helps sort functions
	to store data in increasing order based on arrival time
	@param a as an first process
	@param b as an second process
	@return bool: it returns true when the data saty correctly
	*/
	static bool compInArrvial (Process a, Process b) {
		return a.arrivalTime < b.arrivalTime;
	}

};