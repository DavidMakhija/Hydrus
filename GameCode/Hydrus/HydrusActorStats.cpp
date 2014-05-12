#include "HydrusActorStats.h"
#include "../Galaxy/StringHandler.h"
#include "../Galaxy/Actor.h"
#include "HydrusGame.h"
#include "HydrusEvents.h"
#include "BattleTimer.h"

extern StringHandler* g_pStringHandler;
extern GalaxyGame* p_gGame;
extern EventManager* p_gEventManager;

const std::string HydrusActorStats::sName = "stats";

void HydrusActorStats::ModifyStats(int aModifier,
					 const std::string& aStatType,
					 const std::string& aSource,
					 const enum OutputStrings aMessage)
{
	switch(this->StringToInt(aStatType))
	{
	case 1:
		this->ChangeHealth(aModifier);
		break;
	default:
		assert(0);
		break;
	}
	g_pStringHandler->PrintStringNoReturn(STAT_CHANGE);
	std::cout << MakeStrongPointer<Actor>(this->GetActor())->GetName() << std::endl;
	g_pStringHandler->PrintStringNoReturn(aMessage);
	std::cout << aSource;
	std::cout << " " << aModifier << std::endl;
}

void HydrusActorStats::ChangeHealth(int aModifier)
{
	mHealth += aModifier;
	mHealth = std::max(mMinHealth,mHealth);
	mHealth = std::min(mHealth,mMaxHealth);

	if (mHealth == mMinHealth)
	{
		StrongActorPtr actor = MakeStrongPointer(this->GetActor());
		actor->GET_COMPONENT(BattleTimer)->SetActorState(BattleTimerState::MINIMUM_HEALTH,true);
		p_gEventManager->FireEvent(StrongEventPtr(GALAXY_NEW ActorMinHealthEvent(GALAXY_NEW EventData_ActorMinHealth(actor->GetActorId()))));
	}
}

int HydrusActorStats::StringToInt(const std::string& aString)
{
	if (aString == "health")
	{
		return 1;
	}
	else
	{
		assert(0);
	}
	assert(0);
	return -1;
}