#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/ActorComponent.h"

class HydrusEncounter;

class Brain : public ActorComponent
{
public:
	Brain(WeakActorPtr aActor) : ActorComponent(aActor) {}

	static const std::string sName;

	static const std::string GetComponentString() { return sName; }

	virtual void DetermineAction(HydrusEncounter* aEncounter) = 0;

	virtual int SelectTarget(ActorId aActorId, HydrusEncounter* aEncounter, enum ActionType aAction) = 0;

private:

};