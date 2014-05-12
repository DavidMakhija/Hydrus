#pragma once
#include "GalaxyDefs.h"
#include "GalaxyGame.h"
#include "GalaxyAlgorithms.h"

class Process
{
	friend class ProcessQueue;

public:
	enum ProcessResult
	{
		STALL,
		SUCCESS,
		FAIL
	};

	virtual enum ProcessResult Update(unsigned long aElapsedTime) = 0;

	enum ProcessResult ProcessUpdate(clock_t aCurrentTime)
	{
		unsigned long elapsedTime = GalaxyAlgorithms::ToMilliseconds(mClockStart, aCurrentTime);
		return this->Update(elapsedTime);
	}

	void AddChildProcess(StrongProcessPtr aProcess)
	{
		mChildProcesses.push_back(aProcess);
	}

	virtual bool OnActorDeath(ActorId aActorId) { return false; }

	bool ProcessRemoval(EventData* aEventData) const
	{
		if (mIsLocked)
		{
			return false;
		}
		return this->ProcessRemovalTest(aEventData);
	}

	virtual bool ProcessRemovalTest(EventData* aEventData) const { return false; }

	void LockProcess() { mIsLocked = true; }

	void UnLockProcess() { mIsLocked = false; }

protected:
	Process();

private:
	typedef std::vector<StrongProcessPtr> ChildProcessVec;

	ChildProcessVec mChildProcesses;

	clock_t mClockStart;

	bool mIsLocked;

};