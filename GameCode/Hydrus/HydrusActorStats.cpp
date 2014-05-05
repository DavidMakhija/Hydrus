#include "HydrusActorStats.h"
#include "../Galaxy/StringHandler.h"
#include "../Galaxy/Actor.h"
#include "HydrusGame.h"

extern StringHandler* g_pStringHandler;
extern GalaxyGame* p_gGame;

const std::string HydrusActorStats::gName = "stats";

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
		p_gGame->ActorDeath(actor);
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