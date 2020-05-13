//! A Shedule struct.
/*!
	It stores the time of process starting execution,
	time of process ending execution and the process id
*/
struct Shedule
{
	int startExc;			//! Time of starting process execution
	int endExc;				//! Time of ending process execution
	int arrivalTime;		//! Time where the process entered the system
	int id;					//! Process id		
};