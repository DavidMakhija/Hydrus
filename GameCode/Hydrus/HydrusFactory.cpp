#pragma once
#include "HydrusFactory.h"
#include "HydrusGame.h"
#include "BattleTimer.h"
#include "HydrusActorStats.h"
#include "ArtificialBrain.h"
#include "HumanBrain.h"
#include "HydrusEvents.h"
#include "EventData_Hydrus.h"

extern EventManager* p_gEventManager;

extern GalaxyGame* p_gGame;

void HydrusFactory::Initialize()
{

}

ActorId HydrusFactory::CreateActor(const std::string& aName,
								   const enum ActorType aType)
{
	IdWeakPtrPair newActor = GalaxyFactory::CreateActor(p_gGame, aName);
	StrongActorPtr actor = MakeStrongPointer(newActor.second);
	AttributeVec attVec = HydrusFactory::ActorAttributes(aType);
	for(std::string& i : attVec)
	{
		if (i == "battletimer")
		{
			actor->AddComponent("battletimer",GALAXY_NEW BattleTimer(newActor.second));
		}
		else if (i == "ai")
		{
			actor->AddComponent("brain", GALAXY_NEW ArtificialBrain(newActor.second));
		}
		else if (i == "humanbrain")
		{
			actor->AddComponent("brain", GALAXY_NEW HumanBrain(newActor.second));
		}
		else if (i == "encounter")
		{
			assert(0); // Not set up yet
		}
		else if (i == "stats")
		{
			actor->AddComponent("stats", GALAXY_NEW HydrusActorStats(newActor.second));
			break;
		}
	}

	StrongEventPtr actorCreatedEvent(GALAXY_NEW ActorCreatedEvent(GALAXY_NEW EventData_ActorCreated(newActor)));
	p_gEventManager->FireEvent(actorCreatedEvent);

	return newActor.first;
}

AttributeVec HydrusFactory::ActorAttributes(const enum ActorType aType)
{
	AttributeVec aiStrings;
	switch (aType)
	{
	case AI:
		aiStrings.push_back("ai");
		aiStrings.push_back("stats");
		break;
	case USER:
		aiStrings.push_back("humanbrain");
		aiStrings.push_back("stats");
		break;
	}

	return aiStrings;
}