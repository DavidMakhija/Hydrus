#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/Process.h"
#include "BattleTimer.h"
#include <vector>

class HydrusEncounter : public Process
{
public:
	HydrusEncounter(const std::vector<ActorId>& aActorIds);

	void CreateAttackProc(ActorId attackerId, ActorId targetId);

	void PrintTargets();

	ActorId GetActorId(int actorIndex);

	~HydrusEncounter();

protected:
	virtual enum ProcessResult Update(unsigned long aElapsedTime);

	virtual void UpdateBattleTimers(unsigned long aElapsedTime);

private:
	std::vector<ActorId> mActorIdSeq;
};