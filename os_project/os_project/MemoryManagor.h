using namespace std;

class MemoryManeger {
private: 
	vector < vector < int > > processesPages;
	vector < int > freeFrames;
	int memorySize;
	int pageSize;
	int framesInMemory;
	int numberOfProcesses;
	deque < Process > processes;
	vector < Page > pageTable;

	vector < int > generateFreeFrames (int framesInMemory) {
		vector < int > freeFrames (framesInMemory);
		for (int i = 0; i < freeFrames.size(); i++)
		{
			freeFrames [i] = i;
		}
		random_shuffle (freeFrames.begin(), freeFrames.end());

		return freeFrames;
	}

	int getFreeMemorySize () {
		return freeFrames.size() * pageSize;
	}

	vector < int > getRandomPages(int numberOfPages) {

		vector < int > randomPages;
		
		if (numberOfPages <= freeFrames.size()) {

			for (int i = 0; i < numberOfPages; i++)
			{
				randomPages.push_back(freeFrames.back());
				freeFrames.pop_back();
			}

		}

		return randomPages;
	}





public:
	MemoryManeger( deque < Process > processes, int memorySize, int pageSize ) {
		
		this -> memorySize = memorySize;
		this -> pageSize = pageSize;
		this -> processes = processes;
		this -> numberOfProcesses = processes.size();

		framesInMemory = memorySize / pageSize;

		freeFrames = generateFreeFrames (framesInMemory);

		processesPages.resize(numberOfProcesses);

		pageTable.resize(framesInMemory);

	}

	void runPaging () {

		for (int p = 0; p < processes.size(); p++) { 

			Process process = processes[p];

			if (process.processSize > getFreeMemorySize() ) {

				if (process.processSize > memorySize)
					processesPages[p].push_back(-1);	

				continue;

			}

			int numberOfPages = ceil((process.processSize * 1.0) / pageSize);

			processesPages[p] = getRandomPages(numberOfPages);

			// error
			for (int r = 0; r < processesPages.size(); r++)	{
				int frame = processesPages[p][r];
				pageTable[frame].pageId = r;
				pageTable[frame].processId = processes[p].id;
			}
		}

	}

	int getPhysicalAddress (int processId, int logicalAddress) {

		int displacment = logicalAddress;
		int pageNumber = (logicalAddress / pageSize) - 1;
		int frameNumber = - 1;

		//if (
	}

};
