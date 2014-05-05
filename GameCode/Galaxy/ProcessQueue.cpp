#include "ProcessQueue.h"
#include "Process.h"

ProcessQueue::ProcessQueue()
{

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
