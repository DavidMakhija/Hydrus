#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/ActorComponent.h"
#include "BattleTimerState.h"

class HydrusEncounter;


class BattleTimer : public ActorComponent
{
public:
	static const std::string sName;
	
	static const std::string GetComponentString() {return sName;}

	BattleTimer(WeakActorPtr aActor) :
		ActorComponent(aActor),
		mProgress(rand() % 100),
		mTimeScale(6000) {}

	void Update(unsigned long aElapsedTime);

	int GetProgress() {return mProgress;}

	void ResetBattleTimer() { mProgress = 0; }

	void SetEncounter(HydrusEncounter* aEncounter)
	{
		mEncounter = aEncounter;
	}

	void SetActorState(const enum BattleTimerState::ActorState aState, const bool aIsSet)
	{
		mStateSet.SetState(aState, aIsSet);
	}

protected:

private:

	int mProgress;
	unsigned long mTimeScale;
	HydrusEncounter* mEncounter;

	BattleTimerState mStateSet;
};