#pragma once
#include "GalaxyDefs.h"
#include <list>
class EventData;


typedef std::vector<StrongProcessPtr> ProcessPointerContainer;

class ProcessQueue
{
private:
	ProcessPointerContainer mProcessPointers;
	int mNextProcessIndex;

	bool empty() { return mProcessPointers.empty(); }

	StrongProcessPtr pop(int aIndex);
protected:

public:
	ProcessQueue();

	void AddProcessToQueue(StrongProcessPtr& aProcess);

	void DoProcesses(unsigned long& aMaxMilliseconds);

	void RemoveProcessesIf(EventData* aEventData);

	ProcessPointerContainer::iterator begin() { return mProcessPointers.begin(); }
	ProcessPointerContainer::iterator end() { return mProcessPointers.end(); }
};