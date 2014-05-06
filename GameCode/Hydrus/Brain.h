#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/ActorComponent.h"

class HydrusEncounter;

class Brain : public ActorComponent
{
public:
	Brain(WeakActorPtr aActor) : ActorComponent(aActor) {}

	static const std::string gName;

	static const std::string GetComponentString() { return gName; }

	virtual void AttackAction(HydrusEncounter* aEncounter) = 0;

	virtual enum ActionType DetermineAction(HydrusEncounter* aEncounter) = 0;
private:

};