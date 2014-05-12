#include "ProcessQueue.h"
#include "Process.h"
#include "StatsTrackingProcess.h"

ProcessQueue::ProcessQueue() : mNextProcessIndex(0)
{
}

void ProcessQueue::AddProcessToQueue(StrongProcessPtr& aProcess)
{
	mProcessPointers.push_back(aProcess);
}

void ProcessQueue::DoProcesses(unsigned long& aMaxMilliseconds)
{
	clock_t startTime = clock();
	clock_t currentTime = clock();
	long timeRemaining = GalaxyAlgorithms::TimeRemaining(aMaxMilliseconds, startTime, currentTime);

	while ((timeRemaining > 0) && (!mProcessPointers.empty()))
	{
		StrongProcessPtr proc = this->pop(mNextProcessIndex);
		enum Process::ProcessResult result = proc->ProcessUpdate(currentTime);

		switch (result)
		{
		case Process::SUCCESS:
			break;
		case Process::FAIL:
			break;
		case Process::STALL:
			this->AddProcessToQueue(proc);
			break;
		}

		++mNextProcessIndex;
		if (mNextProcessIndex >= mProcessPointers.size())
		{
			mNextProcessIndex = 0;
		}

		currentTime = clock();
		timeRemaining = GalaxyAlgorithms::TimeRemaining(aMaxMilliseconds, startTime, currentTime);


	}

}

void ProcessQueue::RemoveProcessesIf(EventData* aEventData)
{
	auto removedStart = std::remove_if(mProcessPointers.begin(), mProcessPointers.end(), std::bind(&Process::ProcessRemoval, std::placeholders::_1, aEventData));
	mProcessPointers.erase(removedStart, mProcessPointers.end());

}

StrongProcessPtr ProcessQueue::pop(int aIndex)
{
	if (aIndex >= mProcessPointers.size())
	{
		assert(0); // Something has gone wrong
	}
	StrongProcessPtr proc = mProcessPointers[aIndex];
	if (mProcessPointers.size() == 1)
	{
		// No need to swap
	}
	else
	{
		ProcessPointerContainer::iterator it = mProcessPointers.begin();
		std::advance(it, aIndex);
		std::iter_swap(it, mProcessPointers.end() - 1);
	}

	mProcessPointers.erase(mProcessPointers.end() - 1);
	return proc;

}