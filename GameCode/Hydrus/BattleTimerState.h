#pragma once
#include "BattleTimer.h"
#include <bitset>

class BattleTimerState
{
public:
	enum ActorState
	{
		MINIMUM_HEALTH,
		ATTACKING,
		BEING_ATTACKED,
		MAX_ALREADY_PROCESSED,
		END_MARKER
	};


	void SetState(const enum ActorState aState, const bool aIsSet)
	{
		mState.set(aState, aIsSet);

	}

	bool AdvanceIsOk() { return mState.count() == 0; }

private:
	std::bitset<END_MARKER> mState;
};