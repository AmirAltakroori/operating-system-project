using namespace std;

//! A Reader class.
/*!
Read process data from a given file and retreve:
memory size, page size, round robin quantum,
context switch time and list of all processes
*/
class Reader {

private :

	/**
	A private vaiable.
	vairable has file path that data will be retreced from
	*/
	string filePath;				

	/**
	A private vaiable.
	vairable has the physical memory size
	*/
	int memorySize;					

	/**
	A private vaiable.
	vairable has the physical page size
	*/
	int pageSize;	

	/**
	A private vaiable.
	vairable has the round robin quantum time
	*/
	int roundRobinQ;				

	/**
	A private vaiable.
	vairable has the context switch time
	*/
	int contextSwitch;				

	/**
	A private vaiable.
	vairable has all process information 
	*/
	deque < Process > processes;	

	//! A read data function
	/*!
	private void function that reads data from the filePath private class member and
	set the value of memory size, page size, round robin quantum,
	context switch time and all processes
	*/
	void readData() {

		ifstream inFile;
		inFile.open(filePath);		//! open data file		

		inFile >> memorySize >> pageSize >> roundRobinQ >> contextSwitch;			//! read general data

		Process processIn;
		while (inFile >> processIn.id >> processIn.arrivalTime >> processIn.cpuBurst >> processIn.processSize) { //! read process data
			processes.push_back(processIn);			//! store process data
		}

		inFile.close();		//! close file

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

public :

	//! A constructor
	/*!
	a parametrized constructor 
	@param path (string) as a file path to retreve the data
	*/
	Reader (string path) {
		filePath = "input_test/" + path;
		readData();
	}

	//! Getter function
	/*!
	public function that give the memory size data member for the caller
	@return int: memory size
	*/
	int getMemorySize () {
		return memorySize;
	}

	//! Getter function
	/*!
	public function that give the page size data member for the caller
	@return int: page size
	*/
	int getPageSize () {
		return pageSize;
	}

	//! Getter function
	/*!
	public function that give the round robin quantum data member for the caller
	@return int: round robin quantum
	*/
	int getRoundRobinQ () {
		return roundRobinQ;
	}

	//! Getter function
	/*!
	public function that give the context switch data member for the caller
	@return int: context switch
	*/
	int getContextSwitch () {
		return contextSwitch;
	}

	//! Getter function
	/*!
	public function that give the all processes data member for the caller
	@return deque < Process >: all processes
	*/
	deque < Process > getAllProcesses ()  {
		return processes;
	}

	//! Getter function
	/*!
	public function that give the all processes data member for the caller
	sorted based on arrival time
	@return deque < Process >: all processes
	*/
	deque < Process > getAllProcessesSorted ()  {
		deque < Process > sortedProcesses = processes;
		sort (sortedProcesses.begin(), sortedProcesses.end(), compInArrvial);
		return sortedProcesses;
	}
};
