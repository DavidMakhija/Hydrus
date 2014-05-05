#pragma once
#include "../Galaxy/GalaxyDefs.h"
#include "../Galaxy/Process.h"
class GalaxyGame;

class AttackProc : public Process
{
public:
	AttackProc(ActorId aAttacker, ActorId aTarget);

protected:
	virtual enum ProcessResult Update(unsigned long aElapsedTime);

private:
	ActorId mAttacker;
	ActorId mTarget;

	int mProgress;
	int mTimeScale;

	void Attack(StrongActorPtr aAttacker, StrongActorPtr aTarget);

};