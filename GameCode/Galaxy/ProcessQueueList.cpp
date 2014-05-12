#include "ProcessQueue.h"
#include "Process.h"
#include "StatsTrackingProcess.h"

ProcessQueue::ProcessQueue()
{
	// This basically gives me an initial iterator to use
	mProcessPointers.push_back(StrongProcessPtr(GALAXY_NEW StatsTrackingProcess()));
	mNextProcess = mProcessPointers.begin();
}

void ProcessQueue::AddProcessToQueue(StrongProcessPtr& aProcess)
{
	mProcessPointers.push_back(aProcess);
}

ProcessPointerContainer::iterator ProcessQueue::GetNextProcess()
{
	ProcessPointerContainer::iterator currentProcess = mNextProcess;
	++mNextProcess;
	if (mNextProcess == mProcessPointers.end())
	{
		mNextProcess = mProcessPointers.begin();
	}
	return currentProcess;
}

void ProcessQueue::DoProcesses(unsigned long& aMaxMilliseconds)
{
	clock_t startTime = clock();
	clock_t currentTime = clock();
	long timeRemaining = GalaxyAlgorithms::TimeRemaining(aMaxMilliseconds, startTime, currentTime);
	while ((timeRemaining > 0) && (!mProcessPointers.empty()))
	{
		auto it = this->GetNextProcess();
		(*it)->LockProcess();
		enum Process::ProcessResult result = (*it)->ProcessUpdate(currentTime);
		(*it)->UnLockProcess();
		switch (result)
		{
		case Process::SUCCESS:
			mProcessPointers.erase(it);
			break;
		case Process::FAIL:
			mProcessPointers.erase(it);
			break;
		case Process::STALL:
			break;
		}
		currentTime = clock();
		timeRemaining = GalaxyAlgorithms::TimeRemaining(aMaxMilliseconds, startTime, currentTime);
	}

}

void ProcessQueue::RemoveProcessesIf(EventData* aEventData)
{
	mProcessPointers.remove_if(std::bind(&Process::ProcessRemoval, std::placeholders::_1, aEventData));

	// Because nextProcess may have been erased!
	mNextProcess = mProcessPointers.begin();
}

