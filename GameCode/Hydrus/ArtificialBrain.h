#pragma once
#include "Brain.h"
#include "HydrusEncounter.h"

class ArtificialBrain : public Brain
{
public:
	ArtificialBrain(WeakActorPtr aActor) : Brain(aActor) {}

	virtual void DetermineAction(HydrusEncounter* aEncounter)
	{
		StrongActorPtr actor = MakeStrongPointer(this->GetActor());
		ActorId targetId = this->SelectTarget(actor->GetActorId(), aEncounter, ATTACK);
		aEncounter->CreateTargetedProc(actor->GetActorId(), targetId, ATTACK);
	}

	virtual int SelectTarget(ActorId aActorId, HydrusEncounter* aEncounter, enum ActionType aAction)
	{
		std::vector<ActorId> enemyActors = aEncounter->GetOppenentIdVec(aActorId);
		return enemyActors[0];
	}

};