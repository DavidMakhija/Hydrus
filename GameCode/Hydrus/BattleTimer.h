#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/ActorComponent.h"

class HydrusEncounter;

class BattleTimer : public ActorComponent
{
public:
	static const std::string gName;
	
	static const std::string GetComponentString() {return gName;}

	BattleTimer(WeakActorPtr aActor) : 
		ActorComponent(aActor),
		mProgress(rand() % 100), 
		mTimeScale(6000),
		mBusy(false) {}

	void Update(unsigned long aElapsedTime);

	int GetProgress() {return mProgress;}

	void ResetBattleTimer() { mBusy = false; mProgress = 0; }

	void SetEncounter(HydrusEncounter* aEncounter)
	{
		mEncounter = aEncounter;
	}

	void SetBusyFlag(bool aBusy) { mBusy = aBusy; }

protected:

private:
	int mProgress;
	unsigned long mTimeScale;
	HydrusEncounter* mEncounter;

	// I feel like this should not be necessary.
	// Needed to prevent multiple "ready" states before attacking
	bool mBusy;
};