#include "Actor.h"
#include "GalaxyAlgorithms.h"
#include "StringHandler.h"
#include "../Hydrus/HydrusEncounter.h"

extern StringHandler* g_pStringHandler;

Actor::Actor(const std::string& aName, const ActorId aActorId) :
	mName(aName),
	mActorId(aActorId)
{

}

enum ActionType Actor::DetermineAction()
{
	if (!this->GetComponent<BattleTimer>("ai"))
	{
		return this->HumanInputAction();
	}
	return PASS;
}

enum ActionType Actor::HumanInputAction()
{
	// Get the action
	std::string actionType;
	system("cls");
	std::cout << mName << std::endl;
	g_pStringHandler->PrintString(READY_OPTIONS);
	GalaxyAlgorithms::StringInput(actionType, "a");
	
	return GalaxyAlgorithms::ConvertStringToAction(actionType);
}

void Actor::AttackAction(HydrusEncounter* aEncounter)
{
	if (!this->GetComponent<BattleTimer>("ai"))
	{
		this->HumanAttackAction(aEncounter);
	}
}


void Actor::HumanAttackAction(HydrusEncounter* aEncounter)
{
	std::cout << "Select Target to attack\n";
	aEncounter->PrintTargets();
	int targetId = GalaxyAlgorithms::AskForTargetId(std::string("2"));
	ActorId attackTargetId = aEncounter->GetActorId(targetId);
	aEncounter->CreateAttackProc(mActorId,attackTargetId);

}
/*
void Actor::ModifyStats(int aModifier,
					 const std::string& aStatType,
					 const std::string& aSource,
					 const enum OutputStrings aMessage)
{
	if (mStats)
	{
		mStats->ModifyStats(aModifier,aStatType,aSource,aMessage);
	}
	else
	{
		assert(0);
	}
}

void Actor::SetStats(ActorStats* aStats)
{
	assert(mStats == nullptr);
	mStats = aStats; 
	mStats->SetActor(this);
}
*/