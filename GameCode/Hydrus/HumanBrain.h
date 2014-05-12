#pragma once
#include "Brain.h"

class HumanBrain : public Brain
{
public:
	HumanBrain(WeakActorPtr aActor) : Brain(aActor) {}

	virtual void DetermineAction(HydrusEncounter* aEncounter);

	virtual int SelectTarget(ActorId aActorId, HydrusEncounter* aEncounter, enum ActionType aAction);

private:

};