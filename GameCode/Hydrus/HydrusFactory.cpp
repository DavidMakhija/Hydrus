#pragma once
#include "HydrusFactory.h"
#include "HydrusGame.h"
#include "BattleTimer.h"
#include "HydrusActorStats.h"
#include "ArtificialBrain.h"
#include "HumanBrain.h"


void HydrusFactory::Initialize()
{

}

ActorId HydrusFactory::CreateActor(HydrusGame* aGame,
								   const std::string& aName,
								   const enum ActorType aType)
{
	std::pair<ActorId,WeakActorPtr> newActor = GalaxyFactory::CreateActor(aGame,aName);
	StrongActorPtr actor = MakeStrongPointer(newActor.second);
	AttributeVec attVec = HydrusFactory::ActorAttributes(aType);
	for(std::string& i : attVec)
	{
		if (i == "battletimer")
		{
			actor->AddComponent("battletimer",new BattleTimer(newActor.second));
		}
		else if (i == "ai")
		{
			actor->AddComponent("brain",new ArtificialBrain(newActor.second));
		}
		else if (i == "humanbrain")
		{
			actor->AddComponent("brain", new HumanBrain(newActor.second));
		}
		else if (i == "encounter")
		{
			assert(0); // Not set up yet
		}
		else if (i == "stats")
		{
			actor->AddComponent("stats",new HydrusActorStats(newActor.second));
			break;
		}
	}

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