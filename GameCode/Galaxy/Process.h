#pragma once
#include "GalaxyDefs.h"
#include "GalaxyGame.h"

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
		unsigned long elapsedTime = unsigned long(double(aCurrentTime - mClockStart) / CLOCKS_PER_SEC *1000);
		return this->Update(elapsedTime);
	}

	void AddChildProcess(StrongProcessPtr aProcess)
	{
		mChildProcesses.push_back(aProcess);
	}

protected:
	Process();

private:
	typedef std::vector<StrongProcessPtr> ChildProcessVec;

	ChildProcessVec mChildProcesses;

	clock_t mClockStart;

};