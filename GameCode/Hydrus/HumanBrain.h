#pragma once
#include "Brain.h"

class HumanBrain : public Brain
{
public:
	HumanBrain(WeakActorPtr aActor) : Brain(aActor) {}

	virtual void AttackAction(HydrusEncounter* aEncounter);

	virtual enum ActionType DetermineAction(HydrusEncounter* aEncounter);

private:

};