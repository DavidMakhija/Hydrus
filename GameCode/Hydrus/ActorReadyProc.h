#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/Process.h"

class HydrusEncounter;

class ActorReadyProc : public Process
{
public:
	ActorReadyProc(ActorId aActorId, HydrusEncounter* aEncounter);
	virtual enum ProcessResult Update(unsigned long aElapsedTime);

private:
	ActorId mActorId;

	HydrusEncounter* mEncounter;

};