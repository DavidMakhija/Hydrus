#include "../Galaxy/ActorComponent.h"

class HydrusActorStats : public ActorComponent
{
public:
	static const std::string sName;

	static const std::string GetComponentString() { return sName;}

	void ModifyStats(int aModifier,
					 const std::string& aStatType,
					 const std::string& aSource,
					 const enum OutputStrings aMessage);

	HydrusActorStats(WeakActorPtr aActor) :
		ActorComponent(aActor),
		mHealth(100),
		mVitality(10),
		mSpirit(10),
		mStrength(10),
		mMagic(10)	{}

	~HydrusActorStats();

	void ChangeHealth(int aModifier);

	int GetHealth() { return mHealth; }

	int GetVitality() const { return mVitality; }
	int GetSpirit() const   { return mSpirit; }
	int GetStrength() const { return mStrength; }
	int GetMagic() const    { return mMagic; }

	bool IsMinHealth() { return mHealth == mMinHealth; }

private:
	int mHealth;
	static const int mMinHealth = 0;
	static const int mMaxHealth = 100;

	int mVitality;
	int mSpirit;
	int mStrength;
	int mMagic;

	HydrusActorStats(const HydrusActorStats& aStats);
	HydrusActorStats& operator=(const HydrusActorStats& aStats);

	static int StringToInt(const std::string& aString);
};