#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/Process.h"
class GalaxyGame;

class AttackProc : public Process
{
public:
	AttackProc(ActorId aAttacker, ActorId aTarget);
	~AttackProc();

protected:
	virtual enum ProcessResult Update(unsigned long aElapsedTime);

private:
	ActorId mAttacker;
	ActorId mTarget;

	int mProgress;
	int mTimeScale;

	void Attack(StrongActorPtr aAttacker, StrongActorPtr aTarget);

	bool ProcessRemovalTest(EventData* aEventData) const;

	virtual bool OnActorDeath(ActorId aActorId) { return ((aActorId == mAttacker) || (aActorId == mTarget)); }
};