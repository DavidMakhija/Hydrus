#pragma once
#include "GalaxyDefs.h"
#include <list>
class EventData;


typedef std::list<StrongProcessPtr> ProcessPointerContainer;

class ProcessQueue
{
private:
	ProcessPointerContainer mProcessPointers;
	ProcessPointerContainer::iterator mNextProcess;

	ProcessPointerContainer::iterator GetNextProcess();

	bool empty() { return mProcessPointers.empty(); }


protected:

public:
	ProcessQueue();

	void AddProcessToQueue(StrongProcessPtr& aProcess);

	void DoProcesses(unsigned long& aMaxMilliseconds);

	void RemoveProcessesIf(EventData* aEventData);

	ProcessPointerContainer::iterator begin() { return mProcessPointers.begin(); }
	ProcessPointerContainer::iterator end() { return mProcessPointers.end(); }
};