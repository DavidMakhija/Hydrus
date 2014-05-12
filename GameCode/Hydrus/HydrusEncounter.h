#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/Process.h"
#include "BattleTimer.h"
#include <vector>
#include <map>

class EventData;

class HydrusEncounter : public Process
{
public:
	HydrusEncounter(const std::vector<ActorId>& aActorIdsSide1, const std::vector<ActorId>& aActorIdsSide2);

	void CreateTargetedProc(ActorId attackerId, ActorId targetId, enum ActionType aAction);

	void PrintTargets(ActorId aCurrentActor);

	ActorId GetActorIdFromIndex(ActorId aCurrentActor, int actorIndex);

	~HydrusEncounter();

	std::pair<int, int> GetAllyEnemyPair(ActorId aCurrentActor);

	std::vector<ActorId> GetOppenentIdVec(ActorId aActorId);

	std::vector<ActorId> GetAllyIdVec(ActorId aActorId);

	int GetNumAllies(ActorId aActorId) { return GetAllyIdVec(aActorId).size(); }

	int GetNumOpponents(ActorId aActorId) { return GetOppenentIdVec(aActorId).size(); }

	virtual bool OnActorDeath(ActorId aActorId);

protected:
	virtual enum ProcessResult Update(unsigned long aElapsedTime);

	virtual void UpdateBattleTimers(unsigned long aElapsedTime);

private:
	std::map<int, std::vector<ActorId>> mActorIdSeqs;
};