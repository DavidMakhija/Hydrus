#include "../Galaxy/ActorComponent.h"

class HydrusActorStats : public ActorComponent
{
public:
	static const std::string gName;

	virtual const std::string GetComponentString() { return gName;}

	void ModifyStats(int aModifier,
					 const std::string& aStatType,
					 const std::string& aSource,
					 const enum OutputStrings aMessage);

	HydrusActorStats(WeakActorPtr aActor) :
		ActorComponent(aActor),
		mHealth(100) {}

	~HydrusActorStats();

	void ChangeHealth(int aModifier);

private:
	int mHealth;
	static const int mMinHealth = 0;
	static const int mMaxHealth = 100;

	HydrusActorStats(const HydrusActorStats& aStats);
	HydrusActorStats& operator=(const HydrusActorStats& aStats);

	static int StringToInt(const std::string& aString);
};