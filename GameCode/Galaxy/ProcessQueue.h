#pragma once
#include "GalaxyDefs.h"
#include <list>



typedef std::list<StrongProcessPtr> ProcessPointerContainer;

class ProcessQueue
{
private:
	ProcessPointerContainer mProcessPointers;
	ProcessPointerContainer::iterator mNextProcess;
	
protected:

public:
	ProcessQueue();

	void AddProcessToQueue(StrongProcessPtr& aProcess);

	bool empty() {return mProcessPointers.empty();}

	void PrepareProcessing() {mNextProcess = mProcessPointers.begin();}

	ProcessPointerContainer::iterator GetNextProcess();

	void erase(ProcessPointerContainer::iterator aLoc)
	{
		mProcessPointers.erase(aLoc);
	}

};