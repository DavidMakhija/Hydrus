#include "GalaxyDefs.h"
#include "Process.h"

class StatsTrackingProcess : public Process
{
public:
	virtual enum ProcessResult Update(unsigned long aElapsedTime) { return STALL; }
//	~StatsTrackingProcess() { assert(0); } // Right now I don't want to delete this process
};