//! A Process struct.
/*!
	It stores the arrival time of the process,
	cpu burst time, process size and the process id
*/
struct Process
{
	int id;					//! process id
	int arrivalTime;		//! arrival time of the process
	int cpuBurst;			//! Burst time of the proccess
	int processSize;		//! Process size
};