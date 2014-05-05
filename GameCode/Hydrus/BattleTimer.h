#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/ActorComponent.h"

class HydrusEncounter;

class BattleTimer : public ActorComponent
{
public:
	static const std::string gName;
	
	virtual const std::string GetComponentString() {return gName;}

	BattleTimer(WeakActorPtr aActor) : 
		ActorComponent(aActor),
		mProgress(rand() % 100), 
		mTimeScale(6000) {}

	void Update(unsigned long aElapsedTime);

	int GetProgress() {return mProgress;}

	void ResetBattleTimer() {mProgress = 0;}

	void SetEncounter(HydrusEncounter* aEncounter)
	{
		mEncounter = aEncounter;
	}

protected:

private:
	int mProgress;
	unsigned long mTimeScale;
	HydrusEncounter* mEncounter;
};