#pragma once
#include "Brain.h"
#include "HydrusEncounter.h"

class ArtificialBrain : public Brain
{
public:
	ArtificialBrain(WeakActorPtr aActor) : Brain(aActor) {}

	virtual void AttackAction(HydrusEncounter* aEncounter)
	{
		StrongActorPtr actor = MakeStrongPointer(this->GetActor());
		aEncounter->CreateAttackProc(actor->GetActorId(), aEncounter->GetActorId(0));
	}

	virtual enum ActionType DetermineAction(HydrusEncounter* aEncounter) { return ATTACK; }

};